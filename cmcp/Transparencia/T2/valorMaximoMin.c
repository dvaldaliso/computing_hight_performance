#include <omp.h>
#include <stdio.h>

int main()
{
  int n=4;
  int a[n]; 
  int i, cur_max = -100000;
  int cur_min = 100000;
  for (i = 0; i< n; i++)
    a[i] = i; 
  
  #pragma omp parallel for
  for (i=0; i<n; i++) {
    if (a[i] > cur_max) {
        #pragma omp critical
        if (a[i] > cur_max) {// El segundo if es necesario porque se ha leído cur_max fuera de la sección crítica Esta solución entra en la sección crítica con menor frecuencia
            cur_max = a[i];
        }
    }
    if (a[i] < cur_min) {
      #pragma omp critical (minimo)
      if (a[i] < cur_min)
      cur_min = a[i];
    }
  }

  printf("Valor minimo: %d Valor maximo : %d\n", cur_min, cur_max);
return 0;
}