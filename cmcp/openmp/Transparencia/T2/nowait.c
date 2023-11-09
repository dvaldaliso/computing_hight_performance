#include <omp.h>
#include <stdio.h>
void work1()
{
    printf("Work1\n");
}
void work2()
{
    printf("Work2\n");
}
int main()
{
   #pragma omp parallel
    {
    #pragma omp single nowait
        printf("Empieza work1\n");
    work1();
    #pragma omp single
        printf("Finalizando work1\n");
    #pragma omp single nowait
        printf("Terminado work1, empieza work2\n");
    work2();
    }
return 0;
}