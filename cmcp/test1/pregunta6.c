#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, char **argv)
{
  #pragma omp parallel
{
printf("Y hilo:%d ->",omp_get_thread_num());
int i;
#pragma omp for
for (i=0; i<2; i++)
printf("i: %d ", i);

#pragma omp single //se ejecuta en el orden que lo pongas
printf("Z ");
}
 return 0;
}

