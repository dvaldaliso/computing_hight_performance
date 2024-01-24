# Cloud_computing
## Makefile (Es usado para agrupar ciertas reglas para la compilacion)
## Todos los ejercicios que tengan este archivo -> make 

# CMCP -- programacion paralela
##    openMP
###     Compilacion -> gcc -fopenmp file.c -o fileprograma
###     Ejecucion shedule -> OMP_NUM_THREADS=4 OMP_SCHEDULE=guided ./fileprograma
###     Ejecucion -> ./fileprograma

##     MPI
###      Compilacion -> mpicc -Wall -o hellow hellow.c
###     mpicc -show
###     Ejecucion -> mpiexec -n p programa [argumentos]
###    mpiexec -n 2 ./hellow

##     Cuda
###       Compilacion -> nvcc -o dquery dquery.cu
###       Ejecucion   -> ./dquery

# HCAP Herramientas de computación de altas prestaciones (HCAP)
## algorimo de matrices  bloquesm descomposicion de matrices LU

# interesante 

# TPP Tecnologia de la programacion paralela
## sino se pone -fopenmp no se ejecuta en paralela
## gcc -fopenmp -o actividad1 actividad1.c ctimer.c -lm -DCHECK
## ssh -Y -l dvallop@alumno.upv.es knights.dsic.upv.es
### Para correr con tareas OMP_NUM_THREADS=4 OMP_SCHEDULE=guided ./prog
### gcc -fopenmp -o knapsackBF knapsackBF.c -lm -DCHECK (se pone el -DCHECK PARA QUE EJECUTE UNA PARTE ESPECIFICA DEL CODIGO)
## Compilacion c++ -> g++ -o file file.cpp
## Google Colab
## OPencl -> permite programar en cpu y gpu(programacion heterogenea)

# MPICAP -> Modelado y resolución de problemas en ingeniería mediante computación de altas prestaciones
## Esta asignatura es en Matlab

# PSC -> Programacion Sistemas cloud
### Chat, microservicios, queue, Faas
### golang -> dependencias -> go get    