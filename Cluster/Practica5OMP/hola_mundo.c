#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

int nthreads, tid, ncpus;

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();
  printf("Hello World from thread = %d\n", tid);

  /* Only master thread does this */
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
	ncpus = omp_get_num_procs();
    printf("Number of threads = %d\n", nthreads);
	printf("Number of cpus = %d\n", ncpus);
    }

  }  /* All threads join master thread and disband */

}

