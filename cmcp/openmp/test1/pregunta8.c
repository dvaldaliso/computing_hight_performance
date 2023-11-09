#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv)
{
int n = 0;
#pragma omp parallel num_threads(4)
#pragma omp atomic
++n;
printf("Hello World from thread %d\n",omp_get_thread_num());
printf("valor n: %d",n);
  return 0;
}

