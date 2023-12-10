/*
 * What is written in the standard output?
 */
#include <omp.h>
#include <stdio.h>

int main()
{
  int i,n=4;
  omp_set_num_threads(3);
  printf("Threads before = %d\n",omp_get_num_threads());
  #pragma omp parallel for
  for (i=0;i<n;i++) {
    printf("Threads = %d\n",omp_get_num_threads());
    printf("I am %d, execute iteration %d\n",omp_get_thread_num(),i);
  }
  return 0;
}

