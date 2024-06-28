#include "mex.h"
#include <math.h>
#include <string.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    double *A, *x0, *lambda0, *x, *lambda;
    double tol = 1e-5;
    int n, i, j;
    double *I, *F, *Jx, *Jlambda, *J, *delta, normF;

    if (nrhs != 3) {
        mexErrMsgIdAndTxt("MATLAB:newton_rp:nrhs", "Three inputs required.");
    }
    if (nlhs != 2) {
        mexErrMsgIdAndTxt("MATLAB:newton_rp:nlhs", "Two outputs required.");
    }

    A = mxGetPr(prhs[0]);
    x0 = mxGetPr(prhs[1]);
    lambda0 = mxGetPr(prhs[2]);

    n = mxGetM(prhs[1]);

    plhs[0] = mxCreateDoubleMatrix(n, 1, mxREAL);
    plhs[1] = mxCreateDoubleScalar(0);

    x = mxGetPr(plhs[0]);
    lambda = mxGetPr(plhs[1]);

    memcpy(x, x0, n * sizeof(double));
    *lambda = *lambda0;

    I = mxMalloc(n * n * sizeof(double));
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            I[i + j * n] = (i == j) ? 1.0 : 0.0;
        }
    }

    F = mxMalloc(n * sizeof(double));
    Jx = mxMalloc(n * n * sizeof(double));
    Jlambda = mxMalloc(n * sizeof(double));
    J = mxMalloc(n * (n + 1) * sizeof(double));
    delta = mxMalloc((n + 1) * sizeof(double));

    while (1) {
        for (i = 0; i < n; i++) {
            F[i] = 0;
            for (j = 0; j < n; j++) {
                F[i] += A[i + j * n] * x[j];
            }
            F[i] -= (*lambda) * x[i];
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                Jx[i + j * n] = A[i + j * n];
            }
            Jx[i + i * n] -= *lambda;
            Jlambda[i] = -x[i];
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                J[i + j * n] = Jx[i + j * n];
            }
            J[i + n * n] = Jlambda[i];
        }

        /* Solve J * delta = -F using Gaussian elimination */
        for (i = 0; i < n; i++) {
            J[i + n * (n + 1)] = -F[i];
        }

        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                double factor = J[j + i * n] / J[i + i * n];
                for (int k = 0; k <= n; k++) {
                    J[j + k * n] -= factor * J[i + k * n];
                }
            }
        }

        for (i = n - 1; i >= 0; i--) {
            delta[i] = J[i + n * (n + 1)];
            for (j = i + 1; j < n; j++) {
                delta[i] -= J[i + j * n] * delta[j];
            }
            delta[i] /= J[i + i * n];
        }

        for (i = 0; i < n; i++) {
            x[i] += delta[i];
        }
        *lambda += delta[n];

        normF = 0;
        for (i = 0; i < n; i++) {
            normF += F[i] * F[i];
        }
        normF = sqrt(normF);

        if (normF <= tol) {
            break;
        }
    }

    mxFree(I);
    mxFree(F);
    mxFree(Jx);
    mxFree(Jlambda);
    mxFree(J);
    mxFree(delta);
}