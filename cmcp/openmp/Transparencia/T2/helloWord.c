#include <stdio.h>
#include <omp.h>
int main() {
    omp_set_num_threads(5);
    printf("total threads out from parallel before that = %d\n",omp_get_num_threads());
    #pragma omp parallel
        {
             printf("total threads = %d\n",omp_get_num_threads());
              printf("I am %d\n",omp_get_thread_num());
        }
    printf("total threads out from parallel after that = %d\n",omp_get_num_threads());    
return 0;
}