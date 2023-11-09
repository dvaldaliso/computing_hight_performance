#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int main(){
int a, j;
#pragma omp parallel for private(j) lastprivate(a) 
for (j=0; j<5;j++)
{
    a = j + 2;
    printf("Thread %d has a value of a = %d for j = %d\n",
    omp_get_thread_num(), a, j);
  }
  printf("%d\n", a);//El valor de "a" es 6 porque lastprivate toma el valor que tiene inicializado fuera del parallel y toma el ultimo privado de la iteracion que seria (j+2)=4+2
}