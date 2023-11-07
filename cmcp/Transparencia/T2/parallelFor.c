#include <omp.h>
#include <stdio.h>
int calc(int i){
  printf("%d\n",i*i);
  return i*i;
}
int main()
{
  int i;
  int value=5;
  int *a=&value;
  omp_set_num_threads(5);
  #pragma omp parallel for
  for (i=0; i<5; i++) {
    a[i] = calc(i);
  }
return 0;
}