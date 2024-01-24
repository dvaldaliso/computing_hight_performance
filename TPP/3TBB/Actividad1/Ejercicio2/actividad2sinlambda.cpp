#include <stdio.h>
#include <stdlib.h>
#include "ctimer.h"
#include <cmath>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
using namespace tbb;
using namespace std;

class Actividad2 {
  double **const M;
  double *const media;
  double *const desvt;
  int *const tam;
  int n_vectores;
  public:
    Actividad2(double* M[], double media[], double desvt[], int tam[], int n_vectores):
       M(M),  media(media), desvt(desvt), tam(tam), n_vectores(n_vectores){}
    
    void operator()( const blocked_range<size_t>& r ) const {
      for( size_t i=r.begin(); i!=r.end(); ++i )
        for( size_t v = 0; v<n_vectores; v++ ) {
          double suma;
          suma = 0.0;
          for( size_t i = 0; i<tam[v]; i++ ) {
            suma += M[v][i];
          }
          media[v] = suma / tam[v];
          suma = 0.0;
          for( size_t i = 0; i<tam[v]; i++ ) {
            suma += ((M[v][i]-media[v])*(M[v][i]-media[v]));
          }
          desvt[v] = sqrt( suma / tam[v] );
        }
  }  
};

void Parallel( double* M[], double media[], double desvt[], int tam[], int n_vectores, size_t n ) {
      parallel_for( blocked_range<size_t>( 0,n,1000), Actividad2(M, media, desvt, tam, n_vectores) );
}

int main( int argc, char *argv[] ) {

  double suma;

  if( argc<2 ) {
    printf("Usage: %s n_vectores [tam_max] \n",argv[0]);
    return 1;
  }
  int n_vectores;
  sscanf(argv[1],"%d",&n_vectores);
  int tam_max = 10000;
  if( argc>2 ) {
    sscanf(argv[2],"%d",&tam_max);
  }

  double **M = (double **) malloc (n_vectores*sizeof(double*));
  int *tam = (int *) malloc (n_vectores*sizeof(int));
  for( size_t v=0; v<n_vectores; v++ ) {
    int t = rand()%tam_max;
    tam[v] = t>0 ? t : 1;
    M[v] = (double *) malloc (tam[v]*sizeof(double));
    for( size_t i = 0; i<tam[v]; i++ ) {
      M[v][i] = (double) rand()/RAND_MAX * 2.0*tam[v] - 1.0*tam[v];
    }
  }

  double *media_seq = (double *) malloc (n_vectores*sizeof(double));
  double *desvt_seq = (double *) malloc (n_vectores*sizeof(double));
  for( size_t v = 0; v<n_vectores; v++ ) {
    suma = 0.0;
    for( size_t i = 0; i<tam[v]; i++ ) {
      suma += M[v][i];
    }
    media_seq[v] = suma / tam[v];
    suma = 0.0;
    for( size_t i = 0; i<tam[v]; i++ ) {
      suma += ((M[v][i]-media_seq[v])*(M[v][i]-media_seq[v]));
    }
    desvt_seq[v] = sqrt( suma / tam[v] );
  }
  double elapsed, ucpu, scpu;
  double *media = (double *) malloc (n_vectores*sizeof(double));
  double *desvt = (double *) malloc (n_vectores*sizeof(double));
  ctimer(&elapsed,&ucpu,&scpu);
//Este bucle es el que hay que tocar
  for( size_t v = 0; v<n_vectores; v++ ) {
    suma = 0.0;
    for( size_t i = 0; i<tam[v]; i++ ) {
      suma += M[v][i];
    }
    media[v] = suma / tam[v];
    suma = 0.0;
    for( size_t i = 0; i<tam[v]; i++ ) {
      suma += ((M[v][i]-media[v])*(M[v][i]-media[v]));
    }
    desvt[v] = sqrt( suma / tam[v] );
  }
//
  ctimer(&elapsed,&ucpu,&scpu);
  printf("Tiempo = %f segundos\n",elapsed);
  long int n=10000;
  Parallel(M, media, desvt, tam, n_vectores, n );
  double error = 0;
  for( size_t i=0; i<n_vectores; i++ ) {
    error += fabs(media_seq[i]-media[i]);
    error += fabs(desvt_seq[i]-desvt[i]);
  }
  printf("Error = %f \n",error);

  free(desvt);
  free(media);
  free(desvt_seq);
  free(media_seq);
  free(tam);
  for( size_t i = 0; i<n_vectores; i++ ) {
    free(M[i]);
  }
  free(M);

  return 0;
}
