#include <stdio.h>
#include "support.h"

__global__ void matAddKernel(float* A, float* B, float* C, int n) {

    // Calculate global thread indices based on the block and thread indices ----
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    

    // Use global indices to determine which elements to read, add, and write ---
    if (i<n && j<n) C[i*n+j] = A[i*n+j] + B[i*n+j];

}

int main(int argc, char**argv) {

    Timer timer;
    cudaError_t cuda_ret;

    // Initialize host variables ----------------------------------------------

    printf("\nSetting up the problem..."); fflush(stdout);
    startTime(&timer);

    unsigned int n;
    if(argc == 1) {
        n = 10000;
    } else if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("\n    Invalid input parameters!"
           "\n    Usage: ./matadd               # Matrix of size 10,000x10,000 is used"
           "\n    Usage: ./matadd <n>           # Matrix of size n is used"
           "\n");
        exit(0);
    }

    float* h_A = (float*) malloc( sizeof(float)*n*n );
    for (unsigned int i=0; i < n*n; i++) { h_A[i] = (rand()%100)/100.00; }

    float* h_B = (float*) malloc( sizeof(float)*n*n );
    for (unsigned int i=0; i < n*n; i++) { h_B[i] = (rand()%100)/100.00; }

    float* h_C = (float*) malloc( sizeof(float)*n*n );

    stopTime(&timer); printf("%f s\n", elapsedTime(timer));
    printf("    Matrix size = %u\n", n);

    // Allocate device variables ----------------------------------------------

    printf("Allocating device variables..."); fflush(stdout);
    startTime(&timer);

    float *d_A = NULL, *d_B = NULL, *d_C = NULL;
    cudaMalloc((void**)&d_A, sizeof(float)*n*n);
    cudaMalloc((void**)&d_B, sizeof(float)*n*n);
    cudaMalloc((void**)&d_C, sizeof(float)*n*n);

    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Copy host variables to device ------------------------------------------

    printf("Copying data from host to device..."); fflush(stdout);
    startTime(&timer);

    cudaMemcpy(d_A, h_A, sizeof(float)*n*n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, sizeof(float)*n*n, cudaMemcpyHostToDevice);

    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Launch kernel ----------------------------------------------------------

    printf("Launching kernel..."); fflush(stdout);
    startTime(&timer);

    dim3 nhilos(32,32);
    dim3 nbloques(ceil(float(n)/nhilos.x),ceil(float(n)/nhilos.y));
    matAddKernel<<<nbloques,nhilos>>>(d_A, d_B, d_C, n);

    cuda_ret = cudaGetLastError();
    if(cuda_ret != cudaSuccess) FATAL("Unable to launch kernel");
    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Copy device variables from host ----------------------------------------

    printf("Copying data from device to host..."); fflush(stdout);
    startTime(&timer);

    cudaMemcpy(h_C, d_C, sizeof(float)*n*n, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Verify correctness -----------------------------------------------------

    printf("Verifying results..."); fflush(stdout);

    verify(h_A, h_B, h_C, n);

    // Free memory ------------------------------------------------------------

    free(h_A);
    free(h_B);
    free(h_C);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;

}

