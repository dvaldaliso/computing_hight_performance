#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, char **argv)
{
 #pragma omp parallel num_threads(2)
{
  printf("Y ");
  int i;
  #pragma omp for
  for (i=0; i<2; i++)
    printf("%d ", i);

  #pragma omp single
  printf("Z ");
} 
 return 0;
}

