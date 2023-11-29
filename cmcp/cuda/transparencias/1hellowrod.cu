// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda_runtime.h>
#define N 8
/*
En el siguiente ejemplo se muestran las diferencias y las similitudes que existen a la hora
de reservar memoria tanto en el host como en el device. En este ejemplo se reserva espacio
para una matriz cuadrada de NN elementos, se inicializa en el host con valores aleatorios2
(entre 0 y 9) de tipo float y después se transfieren los datos desde el host hasta el device:
*/
// MAIN: rutina principal ejecutada en el host
int main(int argc, char** argv)
{
// declaracion
 float *hst_matriz;
 float *dev_matriz;
// reserva en el host
 hst_matriz = (float*)malloc( N*N*sizeof(float) );
// reserva en el device
 cudaMalloc( (void**)&dev_matriz, N*N*sizeof(float) );
// inicializacion de datos
 srand ( (int)time(NULL) );
 for (int i=0; i<N*N; i++)
 {
 hst_matriz[i] = (float)( rand() % 10 );
 }
// copia de datos
 cudaMemcpy(dev_matriz, hst_matriz, N*N*sizeof(float), cudaMemcpyHostToDevice);
// salida
 cudaFree( dev_matriz );
 printf("\npulsa INTRO para finalizar...");
 fflush(stdin);
 char tecla = getchar();
 return 0;
}