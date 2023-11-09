#include <omp.h>
#include <stdio.h>

int main() {
    int i;
    int n = 4;
    int result = 0;

    #pragma omp parallel
    {
        #pragma omp single
        {

            printf("result %d, hilo:%d \n", result, omp_get_thread_num());
        }

        // Otro trabajo que no necesita esperar
        // a que todos los hilos finalicen el bucle.
        #pragma omp barrier
        printf("Thread %d ha terminado \n", omp_get_thread_num());

        #pragma omp for
        for(i=0; i<4; i++){
            printf("Thread %d iteracion %d \n", omp_get_thread_num(),i);
        }
    }

    printf("Resultado final: %d\n", result);

    return 0;
}
