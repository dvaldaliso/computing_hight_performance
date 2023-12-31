/******************************************************************************
 *cr
 *cr            (C) Copyright 2010 The Board of Trustees of the
 *cr                        University of Illinois
 *cr                         All Rights Reserved
 *cr
 ******************************************************************************/

__global__ void vecAddKernel(float* A, float* B, float* C, int n) {

    // Calculate global thread index based on the block and thread indices ----

    //INSERT KERNEL CODE HERE

    int myID = threadIdx.x + blockDim.x * blockIdx.x;

    // Use global index to determine which elements to read, add, and write ---

    //INSERT KERNEL CODE HERE
    if (myID < n)
    {
        C[myID] = A[myID] + B[myID];
    }

}

