# Cloud_computing

## CMCP -- programacion paralela
### openMP
### Compilacion -> gcc -fopenmp file.c -o fileprograma
#### 
### Ejecucion -> ./fileprograma

## MPI
## Compilacion -> mpicc -Wall -o hellow hellow.c
### mpicc -show
### Ejecucion -> mpiexec -n p programa [argumentos]
#### mpiexec -n 2 ./hellow

## Cuda
# Compilacion -> nvcc -o dquery dquery.cu
# Ejecucion   -> ./dquery


# interesante 

# TPP Tecnologia de la programacion paralela
## sino se pone -fopenmp no se ejecuta en paralela
## gcc -fopenmp -o actividad1 actividad1.c ctimer.c -lm -DCHECK
## ssh -Y -l dvallop@alumno.upv.es knights.dsic.upv.es
### Para correr con tareas OMP_NUM_THREADS=4 OMP_SCHEDULE=guided ./prog
### gcc -fopenmp -o knapsackBF knapsackBF.c -lm -DCHECK (se pone el -DCHECK PARA QUE EJECUTE UNA PARTE ESPECIFICA DEL CODIGO)

