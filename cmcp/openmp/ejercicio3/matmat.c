#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#include <time.h> 
/*
Imprimir resultado
*/
void imprimirMatriz(double *M, int n){
  int i,j;
  for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%f ", M[i*n+j]);
		}
		printf("\n");
	}
}

/*
 * Multiplicación de matrices
 *  C = A*B, con A, B, C matrices cuadradas de dimensión n
 */
void matmat(int n,double *A, double *B, double *C)
{
  int i, j, k;
  
  //#pragma omp parallel for private(i,j,k)
  for (i=0; i<n; i++) {
    #pragma omp parallel for private(j,k)
    for (j=0; j<n; j++) {
      C[i*n+j] = 0.0;
      //#pragma omp parallel for reduction(+:C[i*n+j])
      for (k=0; k<n; k++) {
        C[i*n+j] += A[i*n+k]*B[k*n+j];
      }
    }
  }
  
}

/*
 * Comprueba que el resultado de matmat es correcto (no paralelizar esta función)
 */
void verify(int n,double *A, double *B, double *C)
{
  int i, j, k;
  double *Z,err=0.0;

  Z = (double*)malloc(n*n*sizeof(double));
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      Z[i*n+j] = 0.0;
      for (k=0; k<n; k++) {
        Z[i*n+j] += A[i*n+k]*B[k*n+j];
      }
      err += fabs(Z[i*n+j]-C[i*n+j]);
    }
  }
  if (err>3e-16) printf("error = %g\n",err);
  free(Z);
}

int main(int argc, char **argv)
{
  int i, j, n=50;
  double *A, *B, *C;
  

  /* Extracción de argumentos */
  if (argc == 2) { /* El usuario ha indicado el valor de n */
     if ((n = atoi(argv[1])) < 0) n = 50;
  }

  /* Creación de las matrices */
  A = (double*)malloc(n*n*sizeof(double));
  B = (double*)malloc(n*n*sizeof(double));
  C = (double*)malloc(n*n*sizeof(double));

  /* Inicializar matrices */
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      A[i+n*j] = drand48();
      B[i+n*j] = drand48();
    }
  }
printf("matriz A \n"); 
 imprimirMatriz(A,n); 
 printf("matriz B \n"); 
 imprimirMatriz(B,n); 

 double start = omp_get_wtime( );
  /* Multiplicación de matrices */
  matmat(n,A,B,C);
 double end = omp_get_wtime( );  
 printf("multiplicacion tomo %f segundos en ejecutarse \n", end-start); 
 imprimirMatriz(C,n); 
  /* Comprobación de resultado */
  if (n<1000) verify(n,A,B,C);

  free(A);
  free(B);
  free(C);

  return 0;
}

