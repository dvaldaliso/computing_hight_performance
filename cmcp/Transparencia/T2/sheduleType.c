#include <omp.h>
#include <stdio.h>
int main()
{
 int d, s, g;
 omp_set_num_threads(4);
//Shedule Parallel
#pragma omp parallel for schedule(dynamic)
for (d=0; d<12; d++) {
  printf("Dinamyc %d hilo : %d\n", d, omp_get_thread_num());
}

#pragma omp parallel for schedule(static)
for (s=0; s<12; s++) {
  printf("Static %d hilo: %d\n", s, omp_get_thread_num());
} 

#pragma omp parallel for schedule(guided)
for (g=0; g<12; g++) {
  printf("Guided %d hilo: %d\n", g, omp_get_thread_num());
}
return 0;
}