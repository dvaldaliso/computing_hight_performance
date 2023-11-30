/******************************************************************************
 *cr
 *cr            (C) Copyright 2010 The Board of Trustees of the
 *cr                        University of Illinois
 *cr                         All Rights Reserved
 *cr
 ******************************************************************************/

#include <stdio.h>
#include "support.h"
#include "kernel.cu"

// tamano de los vectores
#define BLOCK 5 // tamano del bloque

int main(int argc, char**argv) {

    Timer timer;
    cudaError_t cuda_ret;

    // Initialize host variables ----------------------------------------------

    float *d_A, *d_B, *d_C;

    printf("\nSetting up the problem..."); fflush(stdout);
    startTime(&timer);

    unsigned int n;
    if(argc == 1) {
        n = 10000;
    } else if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("\n    Invalid input parameters!"
           "\n    Usage: ./vecadd               # Vector of size 10,000 is used"
           "\n    Usage: ./vecadd <m>           # Vector of size m is used"
           "\n");
        exit(0);
    }

    float* h_A = (float*) malloc( sizeof(float)*n );
    for (unsigned int i=0; i < n; i++) { h_A[i] = (rand()%100)/100.00; }

    float* h_B = (float*) malloc( sizeof(float)*n );
    for (unsigned int i=0; i < n; i++) { h_B[i] = (rand()%100)/100.00; }

    float* h_C = (float*) malloc( sizeof(float)*n );

    stopTime(&timer); printf("%f s\n", elapsedTime(timer));
    printf("    Vector size = %u\n", n);

    // Allocate device variables ----------------------------------------------
    printf("Allocating device variables..."); fflush(stdout);
    startTime(&timer);

    //INSERT CODE HERE
    cudaMalloc( (void**)&d_A, n*sizeof(float));
    cudaMalloc( (void**)&d_B, n*sizeof(float));
    cudaMalloc( (void**)&d_C, n*sizeof(float));


    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Copy host variables to device ------------------------------------------

    printf("Copying data from host to device..."); fflush(stdout);
    startTime(&timer);

    //INSERT CODE HERE
    cudaMemcpy(d_A, h_A, n*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, n*sizeof(float), cudaMemcpyHostToDevice);


    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Launch kernel ----------------------------------------------------------
    printf("Launching kernel..."); fflush(stdout);
    startTime(&timer);

    //INSERT CODE HERE
     int nBloques = n/BLOCK;
    if (n%BLOCK != 0)
    {
        nBloques = nBloques + 1;
    }
    int hilosB = BLOCK;
    printf("Vector de %d elementos\n", n);
    printf("Lanzamiento con %d bloques (%d hilos)\n", nBloques, nBloques*hilosB);

    vecAddKernel<<< nBloques, hilosB >>>( d_A, d_B, d_C, n);

    cuda_ret = cudaGetLastError();
    if(cuda_ret != cudaSuccess) FATAL("Unable to launch kernel");
    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Copy device variables from host ----------------------------------------

    printf("Copying data from device to host..."); fflush(stdout);
    startTime(&timer);

    //INSERT CODE HERE
    cudaMemcpy(h_C, d_C, n*sizeof(float), cudaMemcpyDeviceToHost);


    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Verify correctness -----------------------------------------------------

    printf("Verifying results..."); fflush(stdout);

    verify(h_A, h_B, h_C, n);

    // Free memory ------------------------------------------------------------

    free(h_A);
    free(h_B);
    free(h_C);

    //INSERT CODE HERE
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);



    return 0;

}

