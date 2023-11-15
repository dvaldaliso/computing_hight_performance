# Cloud_computing

## CMCP -- programcion parallea
### Compilacion openMP
### gcc-4.2 >gcc -fopenmp prg-omp.c -o prg-omp
### sun > cc -xopenmp -x03 prg-omp.c
### intel > icc -openmp prg-omp.c
#### Ejecucion
### ./fileprograma

## MPI
## Compilacion
## mpicc -Wall -o hellow hellow.c
### mpicc -show
## Ejecucion
### mpiexec -n p programa [argumentos]
#### mpiexec -n 2 ./hellow
