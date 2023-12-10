/*
 * What is written in the standard output?
 */
#include <omp.h>
#include <stdio.h>

int main()
{
  int i,n=32;
  #pragma omp parallel for num_threads(4)
  for (i=0;i<n;i++) {
    if (!i) printf("threads = %d\n",omp_get_num_threads());
    printf("[thread %d] first loop, it=%d\n",omp_get_thread_num(),i);
  }
  printf("-------------\n");
  #pragma omp parallel for
  for (i=0;i<n;i++) {
    if (!i) printf("threads = %d\n",omp_get_num_threads());
    printf("[thread %d] second loop, it=%d\n",omp_get_thread_num(),i);
  }
  return 0;
}

