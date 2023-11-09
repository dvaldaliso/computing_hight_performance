#include <omp.h>
#include <stdio.h>
int big(int i){
  printf("%d\n",i*i);
  return i*i;
}
int main()
{
  int n=5;
  double x[n];
  int i, sumPrivate = 0;
  double t1, t2;
  t1 = omp_get_wtime();
  //Acumulador privado
  #pragma omp parallel for private(sumPrivate)
  for (i=0; i<n; i++) {
    sumPrivate = sumPrivate + i;
  }  
  printf("valor de la suma total privada: %d\n", sumPrivate);

  //Acumulador compartido
  int sumCompartida = 0;
  #pragma omp parallel for shared(sumCompartida)
  for (i=0; i<n; i++) {
    printf("Avalor de x+i:%d valor de la suma privada: %d\n",i, sumCompartida);

    sumCompartida = sumCompartida + i;
    printf("Dvalor de x+i:%d valor de la suma privada: %d\n",i, sumCompartida);

  }
  printf("valor de la suma total compartida: %d\n", sumCompartida);

  //reduccion este es el correcto
  int sumaRed = 0;
  #pragma omp parallel for reduction(+:sumaRed)
  for (i=0; i<n; i++) {
  sumaRed = sumaRed + i;
  }
  printf("valor de la suma total reducida: %d\n", sumaRed);
  
  t2 = omp_get_wtime();
  printf("Tiempo transcurrido: %f s.\n", t2-t1);
return 0;
}