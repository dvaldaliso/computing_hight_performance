#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, char **argv)
{
  
  int i, nh = omp_get_num_threads();
  printf("Numero de hilos: %d\n", omp_get_num_threads());
  #pragma omp parallel for
  for (i=0; i<5; i++){
    printf("Soy el hilo: %d\n", omp_get_thread_num());
  }
  printf("Numero de hilos: %d\n", omp_get_num_threads());

  
  return 0;
  return 0;
}

