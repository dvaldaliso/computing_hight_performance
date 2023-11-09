#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char **argv)
{
 int h, s = 0;

#pragma omp parallel private(h) num_threads(4)
{
  h = omp_get_thread_num();
  printf("h %d\n",h);
  #pragma omp atomic
  s += h;
  
  #pragma omp barrier
  printf("valor h: %d valor de s:%d\n", h, s);
}
  return 0;
}

