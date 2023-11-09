#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int main()
{

   int d = 10;

    #pragma omp parallel firstprivate(d)
    {
        // Cada hilo tiene su propia copia de 'x' inicializada a 10.
        d += omp_get_thread_num();
        printf("Hilo %d: x = %d\n", omp_get_thread_num(), d);
    }

    // Fuera de la región paralela, 'x' mantiene su valor original.
    printf("Valor original de x: %d\n", d);

  return 0;  
}