#include <omp.h>
#include <stdio.h>
int big(int i){
  printf("%d\n",i*i);
  return i*i;
}
int main()
{
 int i;
 int N=6;
 int a[N];
 
 //Secuencial
 int j = 6;
  for (i=0; i<N; i++) {
    j += 2;
    a[i] = big(j);
  }
//Shedule Parallel
  #pragma omp parallel for schedule(dynamic,2)
  for (i=0; i<N; i++) {
    int j = 5 + 2*(i+1);//Aqui independizamos el valor de j en el ciclo
    printf("numero de hilo: %d\n", omp_get_thread_num());
    a[i] = big(j);
  }
  printf("valor de la 1ra posicion de a: %d",a[0]);
return 0;
}