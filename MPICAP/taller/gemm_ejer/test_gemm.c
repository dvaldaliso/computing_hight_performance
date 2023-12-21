#include <math.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"
#include "utils.h"



// ============================================================================
// Declaration of local prototypes.

int test_read_info( 
    int * ndim, int ** mvalues, int ** nvalues, int ** kvalues,
    //// int * nnb, int ** mbvalues, int ** nbvalues,
    int * nexecs, int * print_data, int * check_result, 
    int * seed );

void print_result_no_residual( char * name, int itest, int m, int n, int k, 
    double texec );

void print_result( char * name, int itest, int m, int n, int k, 
    double texec, double resid );

void my_dgemm( int m, int n, int k,
    double * a, int ldim_a,
    double * b, int ldim_b,
    double * c, int ldim_c );



// ============================================================================
int main( int argc, char *argv[] ) {
  int    ndim, idim, * mvalues, * nvalues, * kvalues, m, n, k,
         //// nnb, inb, * mbvalues, * nbvalues, mb, nb,
         nexecs, ne, info, print_data, check_result, seed[ 4 ],
         ldim_a, ldim_b, ldim_c1, ldim_c2, itest;
  double t1, t2, ttotal, texec, resid, d_zero = 0.0, d_one = 1.0,
         * a, * b, * c1, * c2;

  // Check the number of arguments.
  if ( argc != 1 ) {
    printf( "Usage:  %s\n\n", argv[0] );
    exit( -1 );
  }

  // Read the input arguments.
  info = test_read_info( & ndim, & mvalues, & nvalues, & kvalues,
             //// & nnb, & mbvalues, & nbvalues, 
             & nexecs, & print_data, & check_result, 
             seed );
  if( info != 0 ) {
    printf( "ERROR: a problem in test_read_info.\n" );
    exit( -1 );
  }

  printf( "%%\n" );
  printf( "%% Method                   m     n     " );
  printf( "k       time       gflops   residual\n" );
  printf( "%% -------------------------------------" );
  printf( "----------------------------------------\n" );
 
  itest = 1; 
  for ( idim = 0; idim < ndim; idim++ ) {
    m = mvalues[ idim ];
    n = nvalues[ idim ];
    k = kvalues[ idim ];

    // ========================================================================
    // Create and generate data: matrices a, b, and c.
    // ========================================================================

    a  = ( double * ) malloc( m * k * sizeof( double ) ); 
    b  = ( double * ) malloc( k * n * sizeof( double ) ); 
    c1 = ( double * ) malloc( m * n * sizeof( double ) ); 
    c2 = ( double * ) malloc( m * n * sizeof( double ) ); 
    ldim_a  = m;
    ldim_b  = k;
    ldim_c1 = m;
    ldim_c2 = m;
    if( ( a == NULL )||( b == NULL )||( c1 == NULL )||( c2 == NULL ) ) {
      printf( "ERROR: Not enough memory\n" );
      exit( -1 );
    }

    matrix_generate( m, k, a,  ldim_a,  seed[ 0 ] );
    matrix_generate( k, n, b,  ldim_b,  seed[ 1 ] );
    matrix_generate( m, n, c1, ldim_c1, seed[ 2 ] );
    matrix_generate( m, n, c2, ldim_c2, seed[ 2 ] );

 
    // ========================================================================
    // Timing C code.
    // ========================================================================

    // Print initial data.
    if( print_data == 1 ) {
      printf( "\n" );
      print_formatted_matrix( "aini_ccode", m, k, a, ldim_a );
      print_formatted_matrix( "bini_ccode", k, n, b, ldim_b );
      //// print_formatted_matrix( "cini_ccode", m, n, c1, ldim_c1 );
      printf( "\n" );
    }
 
    // Time method.
    t1 = omp_get_wtime();
    for ( ne = 0; ne < nexecs; ne++ ) {
      my_dgemm( m, n, k, a, ldim_a, b, ldim_b, c1, ldim_c1 );
    }
    t2 = omp_get_wtime();
    ttotal = t2 - t1;
    texec = ttotal / ( ( double ) nexecs );

    // Print final data.
    if( print_data == 1 ) {
      //// print_formatted_matrix( "afin_ccode", m, k, a, ldim_a );
      //// print_formatted_matrix( "bfin_ccode", k, n, b, ldim_b );
      print_formatted_matrix( "cfin_ccode", m, n, c1, ldim_c1 );
      printf( "\n" );
    }

    // Print results.
    print_result_no_residual( "dgemm_ccode", itest, m, n, k, texec );

    // ========================================================================
    // Timing method from the BLAS library.
    // ========================================================================

    // Print initial data.
    if( print_data == 1 ) {
      printf( "\n" );
      print_formatted_matrix( "aini_blas", m, k, a, ldim_a );
      print_formatted_matrix( "bini_blas", k, n, b, ldim_b );
      //// print_formatted_matrix( "cini_blas", m, n, c2, ldim_c2 );
      printf( "\n" );
    }
    double alpha=1.0;
    double beta=0.0;
    // Time method.
    t1 = omp_get_wtime();
    for ( ne = 0; ne < nexecs; ne++ ) {
      // Insert here the BLAS call to compute:  c2 = a * b.
      // ...
      // https://www.smcm.iqfr.csic.es/docs/intel/mkl/mkl_manual/bla/functn_gemm.htm#functn_gemm
      dgemm_("N","N",&m, &n,&k,&alpha,a,&ldim_a,b,&ldim_b,&beta,c2,&ldim_c2);
      //dgemm(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc)
    }
    t2 = omp_get_wtime();
    ttotal = t2 - t1;
    texec = ttotal / ( ( double ) nexecs );

    // Print final data.
    if( print_data == 1 ) {
      //// print_formatted_matrix( "afin_blas", m, k, a, ldim_a );
      //// print_formatted_matrix( "bfin_blas", k, n, b, ldim_b );
      print_formatted_matrix( "cfin_blas", m, n, c2, ldim_c2 );
      printf( "\n" );
    }

    // Compute norm of the difference of c1 and c2.
    if( check_result == 1 ) {
      resid = matrix_diff( m, n, c1, ldim_c1, c2, ldim_c2 );
    } else {
      resid = -1.0;
    }

    // Print results.
    //itest = numero test
    print_result( "dgemm_blas", itest, m, n, k, texec, resid );
    printf( "\n" );


 
    // Remove dynamic data vectors.
    free( a );
    free( b );
    free( c1 );
    free( c2 );

    itest++;
  }

  // Remove dynamic vectors.
  free( mvalues );
  free( nvalues );
  free( kvalues );
  //// free( mbvalues );
  //// free( nbvalues );

  printf( "%% End of Program\n" );
  return 0;
}

// ============================================================================
int test_read_info( int * ndim, int ** mvalues, int ** nvalues, int ** kvalues,
    //// int * nnb, int ** mbvalues, int ** nbvalues,
    int * nexecs, int * print_data, int * check_result, 
    int * seed ) {
//
  const int MAX_LINE_LENGTH = 1024;
  FILE      * fp;
  char      myLine[ MAX_LINE_LENGTH ];
  int       i, rv;
  char      * rv_pc;

  // Open the file.
  if ( ( fp = fopen( "test.in", "r" ) ) == NULL )
    return -1;

  printf( "%%\n" );

  // Reading number of dimensions to test.
  rv = fscanf( fp, "%d", ndim );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  if( * ndim == 0 ) {
    printf( "ERROR: Number of dimensions is zero.\n" ); 
    return (-1);
  }

  // Creating the vectors to hold the dimensions.
  *mvalues = (int *) malloc( *ndim * sizeof( int ) );
  *nvalues = (int *) malloc( *ndim * sizeof( int ) );
  *kvalues = (int *) malloc( *ndim * sizeof( int ) );

  // Reading the dimensions "m".
  for( i = 0; i < * ndim; i++ ) {
    rv = fscanf( fp, "%d", (*mvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Reading the dimensions "n".
  for( i = 0; i < * ndim; i++ ) {
    rv = fscanf( fp, "%d", (*nvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Reading the dimensions "k".
  for( i = 0; i < * ndim; i++ ) {
    rv = fscanf( fp, "%d", (*kvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Write the dimensions.
  printf( "%% Test %d dimensions:\n", * ndim );
  printf( "%%   m: " );
  for( i = 0; i < * ndim; i++ ) {
    printf( "%4d ", *(*mvalues+i) );
  }
  printf( "\n" );

  printf( "%%   n: " );
  for( i = 0; i < * ndim; i++ ) {
    printf( "%4d ", *(*nvalues+i) );
  }
  printf( "\n" );

  printf( "%%   k: " );
  for( i = 0; i < * ndim; i++ ) {
    printf( "%4d ", *(*kvalues+i) );
  }
  printf( "\n" );

#if 0
  // Reading number of block sizes to test.
  rv = fscanf( fp, "%d", nnb );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  if( * nnb == 0 ) {
    printf( "ERROR: Number of block sizes is zero.\n" ); 
    return (-1);
  }

  // Creating the vectors to hold the dimensions.
  *mbvalues = (int *) malloc( *nnb * sizeof( int ) );
  *nbvalues = (int *) malloc( *nnb * sizeof( int ) );

  // Reading the block sizes "mb".
  for( i = 0; i < * nnb; i++ ) {
    rv = fscanf( fp, "%d", (*mbvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Reading the block sizes "nb".
  for( i = 0; i < * nnb; i++ ) {
    rv = fscanf( fp, "%d", (*nbvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
#endif


  // Reading the number of executions.
  rv = fscanf (fp, "%d", nexecs );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  printf( "%% nexecs:          %d\n", * nexecs );

  // Reading whether print data.
  rv = fscanf( fp, "%d", print_data );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  printf( "%% print_data:      %d\n", * print_data );

  // Reading whether check result.
  rv = fscanf( fp, "%d", check_result );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  printf( "%% check_result:    %d\n", * check_result );

  // Reading seeds. Last value must be odd.
  rv = fscanf( fp, "%d", seed );
  rv = fscanf( fp, "%d", seed+1 );
  rv = fscanf( fp, "%d", seed+2 );
  rv = fscanf( fp, "%d", seed+3 );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  if( *( seed+3 ) % 2 == 0 ) {
    printf( "ERROR: Last value of seeds must be odd.\n" ); 
    return (-1);
  }
  printf( "%% Seeds:           %d %d %d %d\n",
          *seed, *(seed+1), *(seed+2), *(seed+3) );

  // Close the file.
  fclose( fp );

  return 0;
}

// ============================================================================
void print_result_no_residual( char * name, int itest, int m, int n, int k, 
    double texec ) {
//
  double gflops;

  if( texec != 0.0 ) {
    gflops = 2.0 * ( ( (double) m ) * ( (double) n ) * ( (double) k ) ) / 
             ( texec * 1.0e9 );
  } else {
    gflops = -1.0;
  }
  printf( "%-10s ( %2d, 1:5 )=[ %5d %5d %5d %11.4e %9.2lf ];\n", 
          name, itest, m, n, k, texec, gflops );
  fflush( stdout );
}

// ============================================================================
void print_result( char * name, int itest, int m, int n, int k, 
    double texec, double resid ) {
//
  double gflops;

  if( texec != 0.0 ) {
    gflops = 2.0 * ( ( (double) m ) * ( (double) n ) * ( (double) k ) ) / 
             ( texec * 1.0e9 );
  } else {
    gflops = -1.0;
  }
  printf( "%-10s ( %2d, 1:6 )=[ %5d %5d %5d %11.4e %9.2lf %8.1le ];\n", 
          name, itest, m, n, k, texec, gflops, resid );
  fflush( stdout );
}

// ============================================================================
void my_dgemm( int m, int n, int k,
    double * a, int ldim_a,
    double * b, int ldim_b,
    double * c, int ldim_c ) {
//
  int     i, j, kk;
  double  dotp;

  for( i = 0; i < m; i++ ) {
    for( j = 0; j < n; j++ ) {
      dotp = 0.0;
      for( kk = 0; kk < k; kk++ ) {
        dotp += a[ i + kk * ldim_a ] * b[ kk + j * ldim_b ];
      }
      c[ i + j * ldim_c ] = dotp;
    }
  }
}


