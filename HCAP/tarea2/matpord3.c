/*==========================================================
 * arrayProduct.c - example in MATLAB External Interfaces
 *
 * Multiplies an input scalar (multiplier) 
 * times a 1xN matrix (inMatrix)
 * and outputs a 1xN matrix (outMatrix)
 *
 * The calling syntax is:
 *
 *		outMatrix = arrayProduct(multiplier, inMatrix)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2007-2010 The MathWorks, Inc.
 *
 *========================================================*/
/* $Revision: 1.1.10.3 $ */

#include "mex.h"
/* The computational routine */
void milu(double *A,double *B, double *C, mwSize n, mwSize m, mwSize p)
{
    mwSize i,j,k;
    /* multiply each element y by x */
    for (j=0; j<p; j++) 
         for(k=0;k<m; k++)
             for(i=0;i<n; i++)
       {
        C[i+j*n]= C[i+n*j] + A[i*m+k]* B[k*p+j];
    }
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{

    double *A,*B,*C;
    size_t m, n, p;
    double *outMatrix;              /* output matrix */
    /* create a pointer to the real data in the input matrix  */
    A = mxGetPr(prhs[0]);
    B = mxGetPr(prhs[1]);
    /* get dimensions of the input matrix */
    n = mxGetM(prhs[0]);
    m = mxGetN(prhs[0]);
    p = mxGetN(prhs[1]);
    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix((mwSize)n,(mwSize)p,mxREAL);

    /* get a pointer to the real data in the output matrix */
    C = mxGetPr(plhs[0]);
    /* call the computational routine */
    milu(A,B,C,(mwSize)n, (mwSize)m, (mwSize)p);
}