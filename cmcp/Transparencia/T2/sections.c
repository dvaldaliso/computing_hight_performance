#include <omp.h>
#include <stdio.h>
void Xaxis()
{
    printf("Xaxis\n");
}
void Yaxis()
{
    printf("Yaxis\n");
}
void Zaxis()
{
    printf("Zaxis\n");
}
int main()
{
   #pragma omp parallel sections
    {
        #pragma omp section
            Xaxis();
        #pragma omp section
            Yaxis();
        #pragma omp section
            Zaxis();
    }

 
return 0;
}