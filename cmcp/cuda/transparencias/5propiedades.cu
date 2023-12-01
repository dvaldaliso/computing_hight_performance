// includes
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
// MAIN: rutina principal ejecutada en el host
int main(int argc, char** argv)
{
cudaDeviceProp deviceProp;
int deviceID;
cudaGetDevice( &deviceID );
cudaGetDeviceProperties( &deviceProp,deviceID );
printf("MAX Threads per block: %d\n",deviceProp.maxThreadsPerBlock);
printf("MAX BLOCK SIZE\n");
printf(" [x -> %d]\n [y -> %d]\n [z -> %d]\n",deviceProp.maxThreadsDim[0],
deviceProp.maxThreadsDim[1], deviceProp.maxThreadsDim[2]);
printf("MAX GRID SIZE\n");
printf(" [x -> %d]\n [y -> %d]\n [z -> %d]\n",deviceProp.maxGridSize[0],
deviceProp.maxGridSize[1], deviceProp.maxGridSize[2]);
// salida
printf("\npulsa INTRO para finalizar...");
fflush(stdin);
char tecla = getchar();
return 0;
}