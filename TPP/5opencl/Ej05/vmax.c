//------------------------------------------------------------------------------
//
// Name:       vadd.c
//
// Purpose:    Elementwise addition of two vectors (c = a + b)
//
// HISTORY:    Written by Tim Mattson, December 2009
//             Updated by Tom Deakin and Simon McIntosh-Smith, October 2012
//             Updated by Tom Deakin, July 2013
//             Updated by Tom Deakin, October 2014
//
//------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h> //Para tipos de datos de opencl que se utilizan
#include <unistd.h>
#else
#include <CL/cl.h>
#include <CL/cl_ext.h>
#endif

#include "cl_utils.h"

#define LENGTH 1024*1024 // length of vectors v

#define DEVICE_TYPE CL_DEVICE_TYPE_ALL

int main(int argc, char** argv)
{
    cl_int           err;           // error code returned from OpenCL calls
    cl_platform_id   platform;      // compute platform id
    cl_uint          numPlatforms;  // number of available platforms
    cl_device_id     devices[MAX_DEVICES];     // list of available devices
    cl_device_id     device;        // compute device id
    cl_context       context;       // compute context
    cl_command_queue commands;      // compute command queue
    cl_program       program;       // compute program
    cl_kernel        kernel;        // compute kernel

    cl_mem d_v;                     // device memory used for the input  a vector
    cl_mem d_vmax;                  // device memory used for the output  a vector with max values

    char * filename="vmax.cl";      // name of the file containing the kernel

    float*       h_v = (float*) calloc(LENGTH, sizeof(float));       // a vector
    float*       h_vmax = (float*) calloc(LENGTH, sizeof(float));       // a vector de maximos

    if (argc != 3) {
        printf("Uso: %s  <local_item_size>\n", argv[0]);
        return -1;
    }

    // Obtener los parámetros de la línea de comandos
    size_t local_item_size = atoi(argv[2]);
    // Fill vectors a and b with random float values
    size_t count = LENGTH;
    int i = 0;
    for(i = 0; i < LENGTH; i++){
        h_v[i] = rand() / (float)RAND_MAX;
    }

    // Obten la primera plataforma disponible
    err = clGetPlatformIDs(1, &platform, &numPlatforms);
    checkError(err, "Getting platforms");// funcion que esta en ccommun, chequea si hay error

    // Usa el primer dispositivo de tipo DEVICE_TYPE de la plataforma
    err = clGetDeviceIDs(platform, DEVICE_TYPE, 1, &device, NULL);
    checkError(err, "Finding a device");

    // Crea un contexto simple con un solo dispositivo
    // el dispositivo creado en la instruccion anterior
    context = clCreateContext(0, 1, &device, NULL, NULL, &err);// si quiseramos trabajar con mas dispositvo, donde esta 1 seria 2, device seria un vector.
    checkError(err, "Creating context");

    // Crea una cola de ordenes para alimentar el dispositivo:
    commands = clCreateCommandQueueWithProperties(context, device, 0, &err);
    checkError(err, "Creating command queue");

    // Construye el objeto programa
    char *kernelSource = getKernelSource(filename);
    program = clCreateProgramWithSource(context, 1, (const char **) &kernelSource, NULL, &err);

    // Compila el programa y construye la biblioteca dinamica de kernels
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        size_t len;
        char buffer[2048];
    
        printf("Error: Failed to build program executable!\n%s\n", err_code(err));
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);     
        return EXIT_FAILURE;
    }


    // Crea los objetos de memoria
    d_v  = clCreateBuffer(context,  CL_MEM_READ_ONLY,  LENGTH * sizeof(float), NULL, &err);//Reserva memoria en el dispositivo
    checkError(err, "Creating buffer d_v");
    d_vmax  = clCreateBuffer(context,  CL_MEM_WRITE_ONLY,  LENGTH * sizeof(float), NULL, &err);//Reserva memoria en el dispositivo
    checkError(err, "Creating buffer d_vmax");
    
    

    // Crea el kernel a partir del programa
    kernel = clCreateKernel(program, "vmax", &err);// coje un kernel vmax -> es el nombre del fichero vadd.cl
    checkError(err, "Creating kernel with vadd.cl");

    // Asocia objetos de memoria con los argumentos de la funcion kernel
    err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_v);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_vmax);
    err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
    checkError(err, "Setting kernel arguments");

    // Escribe los datos de entrada del host al dispositivo
    err = clEnqueueWriteBuffer(commands, d_v, CL_FALSE, 0, LENGTH * sizeof(float), h_v, 0, NULL, NULL);
    checkError(err, "Copying h_v to device at d_v");

    double rtime = wtime();

    // Ejecuta el kernel
    // count -> longitud del vector
    // 6to parametros-> numero de work-group
    err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &count, &local_item_size, 0, NULL, NULL);//comands ->cola que se quiere ejecutar, 1-> una dimension
    checkError(err, "Enqueueing kernel");

    // Lee los resultados del dispositivo al host
    err = clEnqueueReadBuffer( commands, d_vmax, CL_TRUE, 0, LENGTH * sizeof(float), h_vmax, 0, NULL, NULL );// d_vmax->h_vmax  
    checkError(err, "Error: Failed to read output array");

    // Espera a que finalicen todas las tareas antes de parar el temporizador
    err = clFinish(commands);
    checkError(err, "Waiting for kernel to finish");
   
    rtime = wtime() - rtime;
    printf("\nThe kernel ran in %lf seconds\n",rtime);


   // Buscar el maximo en el resultado
    float max = h_vmax[0];
    for (int i = 1; i < VECTOR_SIZE / GROUP_SIZE; i++) {
        if (h_vmax[i] > max) {
            max = h_vmax[i];
        }
    }


    // Libera los recursos y finaliza
    clReleaseMemObject(d_v);
    clReleaseMemObject(d_vmax);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);

    free(h_v);
    free(h_vmax);

    return 0;
}

