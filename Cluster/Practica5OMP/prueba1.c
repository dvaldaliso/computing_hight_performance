#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

int i,nthreads, tid;
int a[100];

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
    printf("Number of threads = %d\n", nthreads);
    }
  #pragma omp for 
  for (i=1; i<100; i++){
    a[i]=i;
    tid = omp_get_thread_num();
     printf("Thread = %d It = %d\n", tid, i);

  }
  tid = omp_get_thread_num();
  printf("Bye bye World from thread = %d\n", tid);

  }  /* All threads join master thread and disband */

}

