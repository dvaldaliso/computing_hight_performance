#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int main()
{

  int i, j;
  
  int n=3;
  double x[n];
  x[0]=1.0;
  #pragma omp parallel for private (j) firstprivate (x)
  for(i=0; i < n; i++){
  for(j=1; j<4; j++){
    x[j]= x[j-1]*(i+1);
    printf("numero hilo: %d, valro i:%d   valor x[j: %d ] :%lf\n",omp_get_thread_num(), i, j, x[j]);
  }
  
  }
  return 0;  
}