

#include "mex.h"

/* The computational routine */
void matprod(double *A, double *B, double *C, mwSize n)
{
    mwSize i,j,k;
    /* multiply each element y by x */
    for (j=0; j<n; j++) 
         for(k=0;k<n; k++)
             for(i=0;i<n; i++)
       {
        C[i+n*j]= C[i+n*j]+ A[i+n*k]* B[k+n*j];
    }
}

