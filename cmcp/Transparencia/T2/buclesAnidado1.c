#include <omp.h>
#include <stdio.h>
#include <time.h>

int main()
{
 int i, j;
 int n=5;
 int m=5;
 double start = omp_get_wtime( );
 //Estadisitica mente probado con media ponderada en el ciclo de afuera es mas rapido( es decir como esta)
 #pragma omp parallel for private(j)
  for (i=0; i<n; i++) {
      for (j=0; j<m; j++) {
        printf("valor i: %d, valor de j:%d\n",i,j);
      }
    }
double end = omp_get_wtime( );  
 printf("tiempo = %g\n",end-start); 
return 0;
}