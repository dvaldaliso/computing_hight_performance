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
  int i, j, li, ls, iglobal;

  if (rank < size - 1) {
   //MPI_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag,recvbuf, recvcount, recvtype, source, recvtag, comm,status)
   MPI_Sendrecv( &v[nlocal+b-1],b,MPI_DOUBLE,rank + 1,0,&v[nlocal+b-1],b,MPI_DOUBLE,rank + 1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   //MPI_Send(&v[nlocal+b-1], b, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
   //MPI_Recv(&v[nlocal+b-1], b, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  if (rank > 0) {
    MPI_Sendrecv(&v[0], b, MPI_DOUBLE, rank - 1, 1, &v[0], b, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //MPI_Send(&v[0], b, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);
    //MPI_Recv(&v[0], b, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  for (i=0; i<nlocal; i++) {
    iglobal = i + nlocal * rank;
    w[i] = 0.0;
    li = iglobal-b<0? 0: iglobal-b;  /* limite inferior */
    ls = iglobal+b>N-1? N-1: iglobal+b;  /* limite superior */
    for (j=li; j<=ls; j++) {
      w[i] += A[i*N+j] * 1//v[j-nlocal*rank+b]; // i es local pero la j es calculada respecto al iglobal
      //if (rank == 1) printf("Proceso : %g\n", v[j]);
    }
  }
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

//En este ejercicio tener en cuenta que funciona para divisiones con resto 0
  nlocal= N / size;

  /* Reserva de memoria */
  local_A = (double*)malloc(nlocal*N*sizeof(double));
  w = (double*)malloc((nlocal)*sizeof(double));// tener en en cuenta 2*b (w y v deben ser iguales)
  v = (double*)malloc((nlocal + (2*b))*sizeof(double));

  /* Inicializar datos */
  if (rank == 0) {
      A = (double*)malloc(N * N * sizeof(double));
      for (i=0; i<N; i++) A[i*N+i] = 2*b;
      for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
          if (i!=j && abs(i - j) <= b) {
            A[i * N + j] = -1.0;
          } 
        }
      }
  }
  // Scatter A and v
  //MPI_Scatter(sendbuf, sendcount, sendtype, recvbuf,recvcount, recvtype, root, comm)  
  MPI_Scatter( A, nlocal * N, MPI_DOUBLE, local_A, nlocal * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  for (i=0; i<nlocal+2*b; i++) v[i] = 1.0;


  /* Multiplicación de matrices */
  for (k=0; k<NREPS; k++) matvec(nlocal,N,b,local_A,v,w,rank,size);
  double *W = NULL;

  if (rank == 0) {
      W = (double *)calloc((N), sizeof(double));
  }
  //MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm)
  MPI_Gather( w, nlocal, MPI_DOUBLE, W, nlocal, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Imprimir solución */

  if (rank == 0) {
   if (N<100) for (i=0; i<N; i++) printf("w[%d] = %g\n", i, W[i]);
      free(W);
  }

  free(A);
  free(v);
  free(w);

  return 0;
}