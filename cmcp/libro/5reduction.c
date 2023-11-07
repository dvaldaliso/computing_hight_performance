#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int main()
{
  int MAX=5;
 double avg = 0.0;
 int i;
 double a[] = {1.0, 2.0, 3.0, 4.0, 5.0};
 #pragma omp parallel for reduction (+:avg)
 for(i =0; i<MAX; i++) {avg += a[i];}
 avg /= MAX;
 printf("average: %lf", avg) ;
  return 0;  
}