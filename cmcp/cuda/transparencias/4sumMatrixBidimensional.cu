// includes
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
// defines
#define N 20
// declaracion de funciones
// GLOBAL: funcion llamada desde el host y ejecutada en el device (kernel)
__global__ void suma_gpu( float *A, float *B, float *C )
{
    // indice de columna
    int columna = threadIdx.x;
    // indice de fila
    int fila = threadIdx.y;
    // indice lineal
    int myID = columna + fila * blockDim.x;
    // sumamos cada elemento
    C[myID] = A[myID] + B[myID];
}
// MAIN: rutina principal ejecutada en el host
int main(int argc, char** argv)
{
    // declaraciones
    float *hst_A, *hst_B, *hst_C;
    float *dev_A, *dev_B, *dev_C;
    // reserva en el host
    hst_A = (float*)malloc(N*N*sizeof(float));
    hst_B = (float*)malloc(N*N*sizeof(float));
    hst_C = (float*)malloc(N*N*sizeof(float));
    
    // reserva en el device
    cudaMalloc( (void**)&dev_A, N*N*sizeof(float));
    cudaMalloc( (void**)&dev_B, N*N*sizeof(float));
    cudaMalloc( (void**)&dev_C, N*N*sizeof(float));
    
    // incializacion
    
    for(int i=0;i<N*N;i++)
    {
        hst_A[i] = (float)( rand() % 10 );
        hst_B[i] = (float)( rand() % 10 );
    }
    // copia de datos
    cudaMemcpy( dev_A, hst_A, N*N*sizeof(float), cudaMemcpyHostToDevice );
    cudaMemcpy( dev_B, hst_B, N*N*sizeof(float), cudaMemcpyHostToDevice );
    cudaMemcpy( dev_C, hst_C, N*N*sizeof(float), cudaMemcpyHostToDevice );
    
    // dimensiones del kernel
    dim3 Nbloques(1);
    dim3 hilosB(N,N);
    // llamada al kernel bidimensional de NxN hilos
    suma_gpu<<<Nbloques,hilosB>>>(dev_A, dev_B, dev_C);
    // recogida de datos
    cudaMemcpy( hst_C, dev_C, N*N*sizeof(float), cudaMemcpyDeviceToHost );

    // impresion de resultados
    printf("A:\n");
     for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%2.0f ",hst_A[j+i*N]);
        }
        printf("\n");
    }
    printf("B:\n");
     for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%2.0f ",hst_B[j+i*N]);
        }
        printf("\n");
    }
    printf("C:\n");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%2.0f ",hst_C[j+i*N]);
        }
        printf("\n");
    }
    // salida
    printf("\npulsa INTRO para finalizar...");
    fflush(stdin);
    char tecla = getchar();
    return 0;
}