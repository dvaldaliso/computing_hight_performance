
#include <stdio.h>
#include <sys/time.h>

typedef struct {
    struct timeval startTime;
    struct timeval endTime;
} Timer;

#define FATAL(msg) \
    do {\
        fprintf(stderr, "[%s:%d] %s\n", __FILE__, __LINE__,(msg));\
        exit(-1);\
    } while(0)

#define min(a,b) ((a)<(b)?(a):(b))
#define BS 256

__global__ void matvec_kernel(int n,double *A,double *x,double *y)
{
  int i,j;
  double res = 0.0;

  // calculate global thread index based on the block and thread indices
  i = blockDim.x*blockIdx.x+threadIdx.x;
  if (i<n) {
    for (j=0; j<n; j++) {
      res += A[i+j*n]*x[j];
    }
    y[i] = res;
  }
}

// Check the result of matvec (in CPU)
void verify(int n,double *A, double *x, double *y)
{
  int i, j;
  double *z,err=0.0,nrm=0.0;

  z = (double*)malloc(n*sizeof(double));
  for (i=0; i<n; i++) {
    z[i] = 0.0;
    for (j=0; j<n; j++) {
      z[i] += A[i+j*n]*x[j];
    }
    err += fabs(z[i]-y[i]);
    nrm += fabs(z[i]);
  }
  if (err/nrm>1e-13) printf(" relative error = %g\n",err/nrm);
  else printf(" PASS\n");
  free(z);
}

void startTime(Timer* timer) {
    gettimeofday(&(timer->startTime), NULL);
}

void stopTime(Timer* timer) {
    gettimeofday(&(timer->endTime), NULL);
}

float elapsedTime(Timer timer) {
    return ((float) ((timer.endTime.tv_sec - timer.startTime.tv_sec) \
                + (timer.endTime.tv_usec - timer.startTime.tv_usec)/1.0e6));
}

double randvalue()
{
  return (double)((rand()/(double)((unsigned int)RAND_MAX+1)))-0.5;
}

int main(int argc, char**argv) {

    Timer timer;
    cudaError_t cuda_ret;

    // Initialize host variables ----------------------------------------------

    printf("\nSetting up the problem..."); fflush(stdout);
    startTime(&timer);

    unsigned int n;
    if(argc == 1) {
        n = 1000;
    } else if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("\n    Invalid input parameters!"
           "\n    Usage: ./matvec               # Matrix of size 1,000 is used"
           "\n    Usage: ./matvec <m>           # Matrix of size m is used"
           "\n");
        exit(0);
    }

    double* h_A = (double*) malloc( sizeof(double)*n*n );
    for (unsigned int i=0; i < n*n; i++) { h_A[i] = randvalue(); }

    double* h_x = (double*) malloc( sizeof(double)*n );
    for (unsigned int i=0; i < n; i++) { h_x[i] = randvalue(); }

    double* h_y = (double*) malloc( sizeof(double)*n );

    stopTime(&timer); printf("%f s\n", elapsedTime(timer));
    printf("    Matrix size = %u\n", n);

    // Allocate device variables ----------------------------------------------

    printf("Allocating device variables..."); fflush(stdout);
    startTime(&timer);

    double *d_A = NULL, *d_x = NULL, *d_y = NULL;
    cudaMalloc((void**)&d_A, sizeof(double)*n*n);
    cudaMalloc((void**)&d_x, sizeof(double)*n);
    cudaMalloc((void**)&d_y, sizeof(double)*n);

    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Copy host variables to device ------------------------------------------

    printf("Copying data from host to device..."); fflush(stdout);
    startTime(&timer);

    cudaMemcpy(d_A,h_A,sizeof(double)*n*n,cudaMemcpyHostToDevice);
    cudaMemcpy(d_x,h_x,sizeof(double)*n,cudaMemcpyHostToDevice);

    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Launch kernel ----------------------------------------------------------

    printf("Launching kernel..."); fflush(stdout);
    startTime(&timer);

    dim3 nthreads(BS);
    //dim3 nblocks((n+nthreads.x-1)/nthreads.x);
    dim3 nblocks(ceil(float(n)/BS));
    matvec_kernel<<<nblocks,nthreads>>>(n,d_A,d_x,d_y);

    cuda_ret = cudaGetLastError();
    if(cuda_ret != cudaSuccess) FATAL("Unable to launch kernel");
    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Copy device variables from host ----------------------------------------

    printf("Copying data from device to host..."); fflush(stdout);
    startTime(&timer);

    cudaMemcpy(h_y,d_y,sizeof(double)*n,cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();
    stopTime(&timer); printf("%f s\n", elapsedTime(timer));

    // Verify correctness -----------------------------------------------------

    printf("Verifying results..."); fflush(stdout);

    verify(n, h_A, h_x, h_y);

    // Free memory ------------------------------------------------------------

    free(h_A);
    free(h_x);
    free(h_y);
    cudaFree(d_A);
    cudaFree(d_x);
    cudaFree(d_y);

    return 0;

}

