#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, char **argv)
{
  
  int i;
  int n=8;
  int a[n];
  int tid ;
  #pragma omp parallel for private(tid) schedule(static,1) num_threads(4)
  for (i = 0; i < n; i ++) {
   tid = omp_get_thread_num();
   a[tid] += i;
   printf("El hilo %d realiza la iteración %d.\n",tid,i);
};

  
  return 0;
  return 0;
}

