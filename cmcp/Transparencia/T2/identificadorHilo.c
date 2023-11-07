#include <omp.h>
#include <stdio.h>
int main()
{
#pragma omp parallel
{
    if (omp_get_thread_num()==0 || omp_get_thread_num()==1){
        printf("threads = %d\n",omp_get_num_threads());
    }
    #pragma omp barrier // Esto es como una barrera, lo anterior se ejecuta 1ro siempre
    printf("I am %d\n",omp_get_thread_num());
}
return 0;
}