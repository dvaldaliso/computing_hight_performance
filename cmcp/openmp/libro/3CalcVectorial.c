#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int main()
{
  int b[3];
  char *cptr;
  int i;
  cptr = malloc(1);
  #pragma omp parallel for
  for(i=0; i<3; i++)
    b[i]=i;
  #pragma omp parallel for
  for (int j=0; j<3; j++){
    printf("%d\n",b[j]);
  }
  return 0;  
}