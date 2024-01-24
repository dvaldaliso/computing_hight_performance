
/************************************************
 * Simple CUDA example to transfer data CPU-GPU *
 ************************************************/

#include <stdio.h>
#include <stdlib.h>

#define CUDA_SAFE_CALL( call ) {                                         \
 cudaError_t err = call;                                                 \
 if( cudaSuccess != err ) {                                              \
   fprintf(stderr,"CUDA: error occurred in cuda routine. Exiting...\n"); \
   exit(err);                                                            \
 } }

#define	A(i,j)		A[ (j) + ((i)*(n)) ]
#define	B(i,j) 		B[ (j) + ((i)*(n)) ]

int main( int argc, char *argv[] ) {
  unsigned int m, n;
  unsigned int i, j;

  /* Generating input data */
  if( argc<3 ) {
    printf("Usage: %s rows cols \n",argv[0]);
    exit(-1);
  }
  sscanf(argv[1],"%d",&m);
  sscanf(argv[2],"%d",&n);

  /* STEP 1: Allocate memory for two m-by-n matrices called A and B in the host */
  float *A, *B;
  A = (float*) malloc(m*n*sizeof(float));
  B = (float*) malloc(m*n*sizeof(float));

  /* STEP 2: Fill matrix A with real random values between -1.0 and 1.0 */
  for (i=0; i < m; i++) { 
      for (j=0; j < n; j++) { 
          A(i,j) = (2.0f * (float) rand() / RAND_MAX ) - 1.0f; 
      }
   }
  /* STEP 3: Allocate memory for three m-by-n matrices into the device memory */
  float *d_A, *d_B;
  CUDA_SAFE_CALL( cudaMalloc( (void **) &d_A, m*n*sizeof(float) ) );/* Allocate memory for d_A */
  CUDA_SAFE_CALL( cudaMalloc( (void **) &d_B, m*n*sizeof(float) ) );/* Allocate memory for d_B */ 

  /* STEP 4: Copy host matrix A to the device matrix d_A */
  CUDA_SAFE_CALL( cudaMemcpy( d_A, A, m*n*sizeof(float), cudaMemcpyHostToDevice )  ); /* Copy Host matrix A into matrix d_A on Device */

  /* STEP 5: Copy device matrix d_A into device memory d_B */
  CUDA_SAFE_CALL( cudaMemcpy( d_B, d_A, m*n*sizeof(float), cudaMemcpyDeviceToDevice ) ); /* Copy device matrix d_A into matrix d_B on Device */

  /* STEP 6: Copy back from device memory into the host memory only data corresponding to matrix B (d_B) */
  CUDA_SAFE_CALL( cudaMemcpy( B, d_B, m*n*sizeof(float), cudaMemcpyDeviceToHost ) ); /* Copy device matrix d_B into host matrix B */

  /* STEP 7: Deallocate device memory */
  CUDA_SAFE_CALL( cudaFree(d_A) );/* Deallocate d_A */
  CUDA_SAFE_CALL( cudaFree(d_B) ); /* Deallocate d_B */ 

  double error = 0.0;
  for( i=0; i<m; i++ ) {
    for( j=0; j<n; j++ ) {
      error += A(i,j) - B(i,j);
    }
  }
  printf("Error = %f\n",error);

  /* STEP 8: Deallocate host memory */
  free(A);
  free(B);
}

