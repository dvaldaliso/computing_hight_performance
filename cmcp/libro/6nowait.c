#include <omp.h>
#include <stdio.h>

int main() {
    int i;
    int n = 4;
    int result = 0;

    #pragma omp parallel
    {
        #pragma omp for nowait 
        for (i = 0; i < n; i++) {
          
            #pragma omp critical
            {
                // Realizar trabajo en el bucle
                result += i;
                printf("result %d \n", result);
            }
        }

        // Otro trabajo que no necesita esperar
        // a que todos los hilos finalicen el bucle.
        #pragma omp barrier
        printf("Thread %d ha terminado el bucle\n", omp_get_thread_num());
    }

    printf("Resultado final: %d\n", result);

    return 0;
}
