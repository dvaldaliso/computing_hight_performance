

/*==========================================================
 * arrayProduct.c - example in MATLAB External Interfaces
 *
 * Multiplies an input scalar (multiplier) 
 * times a 1xN matrix (inMatrix)
 * and outputs a 1xN matrix (outMatrix)
 *
 * The calling syntax is:
 *
 *      outMatrix = arrayProduct(multiplier, inMatrix)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2007-2010 The MathWorks, Inc.
 *
 *========================================================*/
/* $Revision: 1.1.10.3 $ */

#include "mex.h"

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


/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{

    double *A,*B, *C;               /* 1xN input matrix */
    size_t arows,acols,bcols;                   /* size of matrix */
    double *outMatrix;              /* output matrix */

    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }
    /* make sure the first input argument is scalar */
 
    
    
    /* check that number of rows in second input argument is 1 */
  
    
  

    /* create a pointer to the real data in the input matrix  */
    A = mxGetPr(prhs[0]);    
    B = mxGetPr(prhs[1]);

    /* get dimensions of the input matrix */
    arows = mxGetM(prhs[0]);
    acols = mxGetN(prhs[0]);
    bcols = mxGetN(prhs[1]);

    if (acols != mxGetM(prhs[1])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:invalidDimensions", "Las dimensiones de la matriz no son compatibles para la multiplicacion..");
    }

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix((mwSize)arows,(mwSize)bcols,mxREAL);

    /* get a pointer to the real data in the output matrix */
    C = mxGetPr(plhs[0]);

    /* call the computational routine */
    matprod(A,B,C,(mwSize)bcols,(mwSize)acols,(mwSize)arows);
}

