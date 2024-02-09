%%writefile mini-nbody-sequential.cu
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BLOCK_SIZE 256
#define SOFTENING 1e-9f

typedef struct { float x, y, z, vx, vy, vz; } Body;

void randomizeBodies(float *data, int n)
{
  for (int i = 0; i < n; i++)
    data[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

}

__global__ void bodyForce(Body *p, float dt, int n)
{
  int x = threadIdx.x //index of thread in x dimension

  int i = blockDim.x * blockIdx.x + x;//Global index to a matrix row
  float Fx;
  __shared__ float Fx;
  if(i < n){
    // fx put in shared, Allow that all threads in the same block can access
    Fx = 0.0f; float Fy = 0.0f; float Fz = 0.0f;
    int j;
    for ( j = 0; j < n; j++) {
      float dx = p[j].x - p[i].x;
      float dy = p[j].y - p[i].y;
      float dz = p[j].z - p[i].z;
      float distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
      float invDist = rsqrtf(distSqr);
      float invDist3 = invDist * invDist * invDist;
      
      //syncthreds
      __syncthreads();
      Fx += dx * invDist3; Fy += dy * invDist3; Fz += dz * invDist3;
    }
    p[i].vx += dt*Fx; p[i].vy += dt*Fy; p[i].vz += dt*Fz;
  }
}

int main(const int argc, const char** argv)
{
  int nBodies = 30000; //size of the problem (bodies)

  if (argc > 1)
    nBodies = atoi(argv[1]);

  const float dt   = 0.01f; // time step
  const int nIters = 10;    // simulation iterations
  int bytes  = nBodies * sizeof(Body);
  float *buf = (float*) malloc (bytes);
  Body *p    = (Body*) buf;

  randomizeBodies(buf, 6*nBodies); // Init pos/vel data

  const double t1 = omp_get_wtime();
  Body *d_p;
  /* Allocate memory for d_p */
  CUDA_SAFE_CALL( cudaMalloc( (void **) &d_p, 6*nBodies*sizeof(Body) ) );
 
 /* STEP 4: Copy host p to the device d_p */
  CUDA_SAFE_CALL( cudaMemcpy( d_p, p, 6*nBodies*sizeof(Body), cudaMemcpyHostToDevice )  ); /* p->d_p */


  for (int iter = 1; iter <= nIters; iter++)
  {
  dim dimGrid( row_blocks, col_blocks );
  dim dimBlock( block_rows, block_cols );
  compute_kernel<<< dimGrid, dimBlock >>>( p, dt, nBodies );

    bodyForce(p, dt, nBodies); // compute interbody forces

    for (int i = 0 ; i < nBodies; i++) { // integrate position
      p[i].x += p[i].vx*dt;
      p[i].y += p[i].vy*dt;
      p[i].z += p[i].vz*dt;
    }

  }

  const double t2 = omp_get_wtime();

  double avgTime = (t2-t1) / (double)(nIters-1);

  float billionsOfOpsPerSecond = 1e-9 * nBodies * nBodies / avgTime;
  printf("\nSize (Bodies) = %d\n", nBodies);
  printf("%0.3f Billion Interactions/second\n", billionsOfOpsPerSecond);
  printf("%0.3f second\n", avgTime);

  free(buf);

  return 0;
}