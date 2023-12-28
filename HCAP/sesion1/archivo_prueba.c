#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//gcc –o prueba archivo_prueba.c ctimer.c

/* The computational routine */
void matprod(double *A, double *B, double *C, mwSize p,mwSize n,mwSize m)
{
    mwSize i,j,k;
    /* multiply each element y by x */
    for (j=0; j<p; j++) 
         for(k=0;k<n; k++){ 
             for(i=0;i<m; i++)
        {
         C[i + j * m] += A[i + k * m] * B[k + j * n];
        }
}}
int main( int argc, char *argv[] ) {

  int m=1000, n=1000,i;
  clock_t tic,toc;
  
  
  double *A = (double *) malloc( m*n*sizeof(double) );
  double *B = (double *) malloc( m*n*sizeof(double) );
  double *C = (double *) malloc( m*n*sizeof(double) ); 
  /* Reservamos memoria para los datos */



  /* Lo probamos */
  /*
  Si la matriz está almacenada por filas: A[i*Ncolumnas+j]
  Si la matriz está almacenada por columnas: A[i+j*Nfilas]
  */
  int j;
  for( j=0; j<m; j++ ) {
    for( i=0; i<n; i++ ) {
      A[i+j*n] = ((double) rand()/ RAND_MAX);
    }
  }
   for( j=0; j<m; j++ ) {
    for( i=0; i<n; i++ ) {
      B[i+j*n] = ((double) rand()/ RAND_MAX);
    }
  } 
  tic = clock();
  matprod(A, B, C,n);
  toc = clock();
  printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
  /* Liberamos memoria */
  free(A);
  free(B);
    free(C);
      return 0;
}



