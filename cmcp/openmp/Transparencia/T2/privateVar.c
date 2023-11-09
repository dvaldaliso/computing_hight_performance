#include <omp.h>
#include <stdio.h>
int main()
{
    int nthr;
    #pragma omp parallel
    {
        int myid; // Variables creadas dentro de la region son privadas en cada hilo
        nthr = omp_get_num_threads();
        myid = omp_get_thread_num();
        if (myid==0)
        printf("threads = %d\n",nthr);
    #pragma omp barrier
        printf("I am %d\n",myid);
    }
return 0;
}