#include <omp.h>
#include <stdio.h>

int main() {
    int i,x,N=5;
    int b[]={1,2,3,4,5};
    int a2[]={1,2,3,4,5};
    int c[]={1,2,3,4,5};;
    int a[]={1,2,3,4,5};
   #pragma omp parallel for shared (a, a2)
    for(i=0; i < N-1; i++){
        printf("hilo %d, a2[%d]: %d, a[%d]: %d ,a[%d +1]:%d\n", omp_get_thread_num(), i, a2[i],i, a[i],i,a[i+1]);
        a2[i] = a[i+1];
        printf("hilo %d, a2[%d]: %d, a[%d]: %d ,a[%d +1]:%d\n", omp_get_thread_num(), i, a2[i],i, a[i],i,a[i+1]);
            printf("------------------\n");
    }
    
    #pragma omp parallel for shared (a, a2) lastprivate(x)
    for(i=0;i< N-1; i++)
    {
     printf("hilo %d a2[%d]: %d\n", omp_get_thread_num(), i, a2[i]);
    x = b[i] + c[i];
    a[i] = a2[i] + x;
    }

    return 0;
}
