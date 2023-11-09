#include <omp.h>
#include <stdio.h>
int main()
{
    int nthr, myid;
    #pragma omp parallel
    {
        nthr = omp_get_num_threads();
        myid = omp_get_thread_num();
        if (myid==0)
        printf("threads = %d\n",nthr);
    #pragma omp barrier
        printf("I am %d\n",myid);
    }
return 0;
}