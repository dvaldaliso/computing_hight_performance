#include <stdio.h>
#include <omp.h>
int main() {
    omp_set_num_threads(5);
    #pragma omp parallel
        {
             printf("total threads = %d\n",omp_get_num_threads());
              printf("I am %d\n",omp_get_thread_num());
        }
return 0;
}