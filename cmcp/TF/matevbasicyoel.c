#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NREPS 1000

/*
 * Multiplicación de una matriz banda por un vector
 *  w = A*v, con A matriz cuadrada de dimensión N y ancho de banda b
 *  Algoritmo orientado a filas
 */
void matvec(int nlocal, int N,int b,double *A, double *v, double *w, int rank, int size)
{
  int i, j,  li, ls, iglobal;
    // Envía al siguiente y recibe del siguiente
    if (rank != size -1) MPI_Sendrecv(&v[nlocal], b, MPI_DOUBLE, rank + 1, 0, &v[nlocal+b], b, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Envía al anterior y recibe del anterior
    if (rank != 0) MPI_Sendrecv(&v[b], b, MPI_DOUBLE, rank - 1, 0, &v[0], b, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  for (i=0; i<nlocal; i++) {
    iglobal = i + nlocal * rank;
    w[i] = 0.0;
    li = iglobal-b<0? 0: iglobal-b;  /* limite inferior */
    ls = iglobal+b>N-1? N-1: iglobal+b;  /* limite superior */
    for (j=li; j<=ls; j++) {
      w[i] += A[i*N+j]* v[j-(rank*nlocal -b)]; //
    }
  }
  // for (i=0; i<nlocal; i++) printf("PROCESO %d --- w[%d] = %g\n", rank, i, w[i]);
}

int main(int argc, char **argv)
{
  int i, j, k, N=50, b=4, nlocal;
  double *A, *v, *w, *local_A;

  /* Extracción de argumentos */
  if (argc > 1) { /* El usuario ha indicado el valor de N */
     if ((N = atoi(argv[1])) < 0) N = 50;
  }
  if (argc > 2) { /* El usuario ha indicado el valor de b */
     if ((b = atoi(argv[2])) < 0) b = 1;
  }
  if (b>=N) { /* Valor de b incorrecto */
    printf("Error: ancho de banda excesivo, N=%d, b=%d\n", N, b);
    exit(1);
  }

  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  nlocal= N / size;

  /* Reserva de memoria */
  local_A = (double*)malloc(nlocal*N*sizeof(double));
  w = (double*)malloc(nlocal*sizeof(double));
  v = (double*)malloc((nlocal + (2*b))*sizeof(double));

  /* Inicializar datos */
if (rank == 0) {
        A = (double*)malloc(N * N * sizeof(double));
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (i == j) {
                    A[i * N + j] = 2 * b;
                } else if (abs(i - j) <= b) {
                    A[i * N + j] = -1.0;
                } else {
                    A[i * N + j] = 0.0;
                }
            }
        }
    }
    // Scatter A and v
    MPI_Scatter(A, nlocal * N, MPI_DOUBLE, local_A, nlocal * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0 ) free(A);

  for (i=b; i<nlocal+b; i++) v[i] = 1.0; // inicia solo la parte local del vector

  double tInicio, tFinal;

  // Hacemos una barrera para asegurar que todas los procesos comiencen la ejecucion
  // a la vez, para tener mejor control del tiempo empleado
  MPI_Barrier(MPI_COMM_WORLD);
  // Inicio de medicion de tiempo
  tInicio = MPI_Wtime();

  /* Multiplicación de matrices */
  for (k=0; k<NREPS; k++) matvec(nlocal,N,b,local_A,v,w,rank,size);

  double *full_w = NULL;

  MPI_Barrier(MPI_COMM_WORLD);
  // fin de medicion de tiempo
  tFinal = MPI_Wtime();

  if (rank == 0) {
      full_w = (double *)calloc((N), sizeof(double));
  }

  MPI_Gather(&w[0], nlocal, MPI_DOUBLE, full_w, nlocal, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Finalize(); //solo permanecerá el proceso 0


  /* Imprimir solución */
  if (rank == 0) {
   printf("Tiempo empleado en el cálculo: %g segundos", tFinal-tInicio);
   if (N<100) for (i=0; i<N; i++) printf("w[%d] = %g\n", i, full_w[i]);
      free(full_w);
  }

  free(local_A);
  free(v);
  free(w);

  return 0;
}