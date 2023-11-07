#include <omp.h>
#include <stdio.h>

int main()
{
 int i, j;
 int n=5;
 int m=5;
  #pragma omp parallel for private(j)
  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      printf("valor i: %d, valor de j:%d\n",i,j);
    }
}
return 0;
}