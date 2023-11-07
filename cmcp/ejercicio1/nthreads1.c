/*
 * What is written in the standard output?
 */
#include <omp.h>
#include <stdio.h>

int main()
{
  //omp_set_num_threads(3);
  #pragma omp parallel
  {
    printf("threads = %d\n",omp_get_num_threads());
    printf("I am %d\n",omp_get_thread_num());
  }
  return 0;
}

