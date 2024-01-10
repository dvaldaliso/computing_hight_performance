
/* 
 * Cholesky por bloques secuencial 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ctimer.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
using namespace tbb;

#define L(i,j)  L[j*n+i]
#define A(i,j)  A[j*n+i]
#define C(i,j)  C[j*n+i]
#define H(i,j)  H[j*my_n+i]

//inline int min(int a, int b) { return (a < b) ? a : b; }
#define min(a,b) ((a<b)?(a):(b))

#ifdef __cplusplus
extern "C" {
#endif
void dpotrf_( const char* uplo, const int* n, double* a, const int* lda, int* info );
void dgemm_(const char *transa, const char *transb, const int *m, const int *n, const int *k,
            const double *alpha, const double *a, const int *lda, const double *b, const int *ldb,
            const double *beta, double *c, const int *ldc);
void dsyrk_(const char *uplo, const char *trans, const int *n, const int *k,
            const double *alpha, const double *a, const int *lda, const double *beta,
            double *c, const int *ldc);
void dtrsm_(const char *side, const char *uplo, const char *transa, const char *diag,
            const int *m, const int *n, const double *alpha, const double *a, const int *lda,
            double *b, const int *ldb);
#ifdef __cplusplus
}
#endif

int cholesky( int n, int b, double *C );

int main( int argc, char *argv[] ) {
  int n, b, i, j, info;
  double *L, *A;

  if( argc<3 ) {
    fprintf(stderr,"usage: %s n block_size\n",argv[0]);
    exit(-1);
  }
  sscanf(argv[1],"%d",&n);
  if( ( L = (double*) malloc(n*n*sizeof(double)) ) == NULL ) {
    fprintf(stderr,"Error en la reserva de memoria para la matriz L\n");
    exit(-1);
  }
  for( j=0; j<n; j++ ) {
    for( i=0; i<j; i++ ) {
      L(i,j) = 0.0;
    }
    for( i=j; i<n; i++ ) {
      L(i,j) = ((double) rand()) / RAND_MAX;
    }
    L(j,j) += n;
  }
  /* Imprimir matriz */
  /*
  for( i=0; i<n; i++ ) {
    for( j=0; j<n; j++ ) {
      printf("%10.3lf",L(i,j));
    }
    printf("\n");
  }
  */
  if( ( A = (double*) malloc(n*n*sizeof(double)) ) == NULL ) {
    fprintf(stderr,"Error en la reserva de memoria para la matriz A\n");
    exit(-1);
  }

  /*********************************************************/
  /* Multiplicación A=L*L', donde L es triangular inferior */
  /* Devuelve la parte triangular inferior en A */
  double zero = 0.0;
  double one = 1.0;
  dsyrk_( "L", "N", &n, &n, &one, &L(0,0), &n, &zero, &A(0,0), &n );
  /*********************************************************/

  sscanf(argv[2],"%d",&b);

  /* Imprimir matriz */
  /*
  for( i=0; i<n; i++ ) {
    for( j=0; j<n; j++ ) {
      printf("%10.3lf",A(i,j));
    }
    printf("\n");
  }
  */

  double t1, t2, ucpu, scpu;
  ctimer( &t1, &ucpu, &scpu );
  info = cholesky( n, b, A );
  //dpotrf_( "L", &n, A, &n, &info ); 
  ctimer( &t2, &ucpu, &scpu );
  if( info != 0 ) {
    fprintf(stderr,"Error = %d en la descomposición de Cholesky de la matriz A\n",info);
    exit(-1);
  }

  /* Imprimir matriz */
  /*
  for( i=0; i<n; i++ ) {
    for( j=0; j<n; j++ ) {
      printf("%10.3lf",A(i,j));
    }
    printf("\n");
  }
  */

  /* ¿ A = L ? */
  double error = 0.0;
  for( j=0; j<n; j++ ) {
    for( i=j; i<n; i++ ) {
      double b = (A(i,j)-L(i,j));
      error += b*b;
    }
  }
  error = sqrt(error);
  //printf("Error = %10.4e\n",error);
  printf("%10d %10d %20.2f sec. %15.4e\n",n,b,t2-t1,error);

  free(A);
  free(L);
}



class MyDTRSM {
  int const my_k;
  int const my_b;
  int const my_n;
  double const my_one;
  double *const Cp;

  public:
    void operator()( const blocked_range<size_t>& r ) const {
      int m;
      int ii;
      for( size_t i=r.begin(); i!=r.end(); i+=1 ){
        ii = my_k+my_b+i*my_b;
        m = min( my_n-i, my_b );
        dtrsm_( "R", "L", "T", "N", &m, &my_b, &my_one, &Cp[my_k*my_n+my_k], &my_n, &Cp[my_k*my_n+ii], &my_n );
      }
        
  }
  
    MyDTRSM( int k, int b, int n, double one, double C[] ) : 
      my_k(k),
      my_b(b), 
      my_n(n), 
      my_one(one),
      Cp(C) {}
};



void ParallelDTRSM( int k, int b, int n, double one, double C[] ) {
      parallel_for( blocked_range<size_t>( 0, (n-k-1)/b), MyDTRSM(k, b, n, one, C) );
}



class MyDGEMM {
  int const k;
  int const b;
  int const my_n;
  int const m;
  int const ii;
  double const minusone;
  double const one;
  double *const Cp;

  public:
    MyDGEMM( int k, int b, int ii, int m, int n, double minusone, double one, double C[] ) : 
    k(k), 
    b(b), 
    m(m), 
    minusone(minusone), 
    my_n(n), 
    one(one), 
    ii(ii), 
    Cp(C) {}

    void operator()( const blocked_range<size_t>& r ) const {
      int j;
      double* H = Cp;
      for( size_t i=r.begin(); i!=r.end(); i+=1 ){
          j = k+b+i*b;
      //  dgemm_( "N", "T", &m, &my_b, &my_b, &my_minusone, &H(ii,my_k), &my_n, &H(j,my_k), &my_n, &my_one, &H(ii,j), &my_n );
          dgemm_( "N", "T", &m, &b, &b, &minusone, &H(ii,k), &my_n, &H(j,k), &my_n, &one, &H(ii,j), &my_n );
      }
        
    }

      
};

void ParallelDGEMM( int k, int b, int ii, int m, int n, double minusone, double one, double C[] ) {
      parallel_for( blocked_range<size_t>( 0, (ii-k-1)/b), MyDGEMM(k, b, ii, m, n, minusone, one, C) );
}

class MyDSYRK {
  int const my_k;
  int const my_b;
  int const my_n;
  double const my_minusone;
  double const my_one;
  double *const Cp;

  public:
    void operator()( const blocked_range<size_t>& r ) const {
      int m;
      int ii;
      int j;
      int jj;
      double* H = Cp;
      for( size_t i=r.begin(); i!=r.end(); i+=1 ){

        ii = my_k+my_b+i*my_b;
        m = min( my_n-ii, my_b );
        
        ParallelDGEMM(my_k, my_b, ii, m, my_n, my_minusone, my_one, H );
        //for ( jj = 0; jj < (ii-my_k-1)/my_b; jj++ ) {
        //  j = my_k+my_b+jj*my_b;
        //  dgemm_( "N", "T", &m, &my_b, &my_b, &my_minusone, &H(ii,my_k), &my_n, &H(j,my_k), &my_n, &my_one, &H(ii,j), &my_n );
        //}
        dsyrk_( "L", "N", &m, &my_b, &my_minusone, &H(ii,my_k), &my_n, &my_one, &H(ii,ii), &my_n );
      }
        
  }
  
    MyDSYRK( int k, int b, int n, double minusone, double one, double C[] ) : 
      my_k(k),
      my_b(b), 
      my_n(n), 
      my_minusone(minusone),
      my_one(one),
      Cp(C) {}
};


void ParallelDSYRK( int k, int b, int n, double minusone, double one, double C[] ) {
      parallel_for( blocked_range<size_t>( 0, (n-k-1)/b), MyDSYRK(k, b, n, minusone, one, C) );
}



int cholesky( int n, int b, double *C ) {
  int i, ii, j, jj, k, m;
  int info;
  const double one = 1.0;
  const double minusone = -1.0;
  for ( k = 0; k < n ; k+=b ) {
    m = min( n-k, b );
    dpotrf_( "L", &m, &C(k,k), &n, &info );
    if( info != 0 ) {
      fprintf(stderr,"Error = %d en la descomposición de Cholesky de la matriz C\n",info);
      return info;
    }

    ParallelDTRSM(k, b, n, one, C);
    //parallel_for( blocked_range<size_t>(ini_intervalo, fin_intervalo (no incluye el ultimo), GrainSize), Clase (sobreescribe operator())
    //parallel_for( blocked_range<size_t>( 0, (n-k-1)/b, 10), Body(k, b, n, one, C) );
    //for ( ii = 0; ii < (n-k-1)/b; ii++ ) {
    //  i = k+b+ii*b;
    //  m = min( n-i, b );
    //  dtrsm_( "R", "L", "T", "N", &m, &b, &one, &C(k,k), &n, &C(i,k), &n );
    //}

    ParallelDSYRK( k, b, n, minusone, one, C ); 
    //for ( ii = 0; ii < (n-k-1)/b; ii++ ) {
    //  i = k+b+ii*b;
    //  m = min( n-i, b );
    //
    //  for ( jj = 0; jj < (i-k-1)/b; jj++ ) {
    //    j = k+b+jj*b;
    //    dgemm_( "N", "T", &m, &b, &b, &minusone, &C(i,k), &n, &C(j,k), &n, &one, &C(i,j), &n );
    //  }
    //  dsyrk_( "L", "N", &m, &b, &minusone, &C(i,k), &n, &one, &C(i,i), &n );
    //}
  }
  return 0;
}

