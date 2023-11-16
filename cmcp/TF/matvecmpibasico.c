#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define NREPS 2

/* 
 * Multiplicación de una matriz banda por un vector
 *  w = A*v, con A matriz cuadrada de dimensión N y ancho de banda b
 *  Algoritmo orientado a filas
 */
void matvec(int nlocal,int N,int b,double *A, double *vlocal, double *wlocal, int rank, int size)
{
  int ilocal, jglobal, li, ls;
  int next, prev;
  if (rank == 0) prev = MPI_PROC_NULL;
  else prev = rank-1;
  if (rank == size-1) next = MPI_PROC_NULL;
  else next = rank+1;
  //Prueba del send y recib
  /*for (int i = 0; i < nlocal+2*b; i++)
  {
   printf(" v[%d]:%lf rank:%d ",i,vlocal[i],rank);
  }
  printf("\n");
  MPI_Sendrecv( &vlocal[0],2, MPI_DOUBLE, next, 0, &vlocal[3], 2, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 */
  
// Envía al siguiente y recibe del anterior(abajo)  
  MPI_Sendrecv( &vlocal[nlocal+b-1],b, MPI_DOUBLE, next, 0, &vlocal[0], b, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  //Envia al anterior y recibe del siguiente
  MPI_Sendrecv( &vlocal[0],b, MPI_DOUBLE, prev, 0, &vlocal[nlocal+b-1], b, MPI_DOUBLE, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  /*for (int i = 0; i < nlocal+2*b; i++)
  {
   printf(" v[%d]:%lf rank:%d ",i,vlocal[i],rank);
  }*/
  //printf(" rank:%d ",rank);
  
  for (ilocal=0; ilocal<nlocal; ilocal++) {
    int iglobal = ilocal +(nlocal*rank);
    wlocal[ilocal] = 0.0;
    li = iglobal-b<0? 0: iglobal-b;  //limite inferior 
    ls = iglobal+b>N-1? N-1: iglobal+b;  // limite superior 
    for (jglobal=li; jglobal<=ls; jglobal++) {
      int jlocal = jglobal - (nlocal*rank);
      wlocal[ilocal] += A[ilocal*N+jglobal]* vlocal[jlocal];
      printf("V[%d]:%lf",jlocal, vlocal[jlocal]);
    }
  }
  
  printf("\n");
}

int main(int argc, char **argv) 
{
  int i, j, k, N=50, b=4, nlocal;
  double *A, *vlocal, *wlocal, *local_A;
  MPI_Comm comm ;


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
  comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  nlocal= N / size;
  /* Reserva de memoria */
  local_A = (double*)calloc(nlocal*N,sizeof(double));
  wlocal = (double*)calloc((nlocal + 2*b),sizeof(double));
  vlocal = (double*)calloc((nlocal + 2*b),sizeof(double));

  /* Inicializar datos */
  if (rank == 0) {
      A = (double*)calloc(N * N , sizeof(double));
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

  for (i=0; i<nlocal+2*b; i++) vlocal[i] = 1.0;


  /* Multiplicación de matrices */
  for (k=0; k<NREPS; k++) matvec(nlocal, N, b, local_A, vlocal, wlocal, rank, size);
  double *W = NULL;

  if (rank == 0) {
      W = (double *)calloc((N), sizeof(double));
  }

  //MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm)
  MPI_Gather( wlocal, nlocal, MPI_DOUBLE, W, nlocal, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Imprimir solución */
  printf("Matriz resultante W\n");
   if (rank == 0) {
   if (N<100) for (i=0; i<N; i++) printf("w[%d] = %g\n", i, W[i]);
      free(W);
  }

  free(A);
  free(vlocal);
  free(wlocal);

  return 0;
}

