#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NREPS 1

/*
 * Multiplicación de una matriz banda por un vector
 *  w = A*v, con A matriz cuadrada de dimensión N y ancho de banda b
 *  Algoritmo orientado a filas
 */
void imprimirVector(int rank, int size, double* v, int b, int nlocal){
   for (int i = 0; i < size; i++)
    {
        if (rank == i)
        {
            printf("rank %d: \n", rank);
              for (int j = 0; j < nlocal + b; j++)
            {
               
                    printf("%3.0f ", v[j]);
               
            }
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
void matvec(int nlocal, int N,int b,double *A, double *v, double *w, double *auxw, int rank, int size)
{
  int li, ls;
  int next, prev;

  if (rank == 0) prev = MPI_PROC_NULL;
  else prev = rank-1;
  if (rank == size-1) next = MPI_PROC_NULL;
  else next = rank+1;
 // Envía al anterior y recibe el siguiente(ir hacia arriba)  
  MPI_Sendrecv( &v[0],b, MPI_DOUBLE, prev, 0, &v[nlocal], b, MPI_DOUBLE, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  for (int ilocal=0; ilocal<nlocal+b; ilocal++) {
    w[ilocal] = 0.0;
  }
  for (int ilocal=0; ilocal<nlocal; ilocal++) {
    int iglobal = ilocal + (nlocal * rank);
    
    li = iglobal;  /* limite inferior */
    ls = iglobal+b > N-1 ? N-1: iglobal+b;  /* limite superior */
    
    for (int jglobal=li; jglobal<=ls; jglobal++) {
      int jlocal = jglobal - (nlocal*rank );
     
      w[ilocal] += A[ilocal*N+jglobal] * v[jlocal];
      
      if(iglobal!=jglobal){
        w[jlocal] += A[ilocal*N+jglobal] * v[ilocal];
        //printf("distintos i != j: \n");
      }
      //printf("wi[%d]:%lf = %lf * v[%d]:%lf-- \n",ilocal, w[ilocal] , A[ilocal*N+jglobal] , jlocal, v[jlocal] );
      //printf("wj[%d]:%lf = %lf * v[%d]:%lf --\n",jlocal, w[jlocal] , A[ilocal*N+jglobal] , ilocal, v[ilocal] );
    }
     //printf("rank %d\n", rank );
  }
   // Envía al siguiente y recibe el siguiente(ir hacia abajo)
  MPI_Sendrecv( &w[nlocal],b,MPI_DOUBLE, next,0,&auxw[0],b, MPI_DOUBLE, prev, 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

 for (int i=0; i<b; i++) {
    w[i] += auxw[i];
  }
}

int main(int argc, char **argv)
{
  int i, j, k, N=50, b=4, nlocal;
  double *A, *vlocal, *wlocal, *wauxlocal, *local_A;
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

//En este ejercicio tener en cuenta que funciona para divisiones con resto 0
  nlocal= N / size;
  //printf("%d %d %d\n",nlocal,rank,size);
  /* Reserva de memoria */
  /*Se puede usar calloc que inicializa los valores en 0 a diferencia de malloc*/
  local_A = (double*)calloc(nlocal*N,sizeof(double));
  wlocal = (double*)calloc((nlocal+ b),sizeof(double));
  wauxlocal = (double*)calloc(b,sizeof(double));
  vlocal = (double*)calloc((nlocal + b),sizeof(double));

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
  //repartimos los valores de v a vlocales de cada procesos( Esto se puede hacer con scatter mirar el basic)
  for (i=0; i<nlocal; i++) vlocal[i] = 1.0;
  //imprimirVector(rank, size, vlocal, b, nlocal);


  /* Multiplicación de matrices */
  for (k=0; k<NREPS; k++) matvec(nlocal,N,b,local_A,vlocal,wlocal,wauxlocal,rank,size);
  double *W = NULL;

  if (rank == 0) {
      W = (double *)calloc((N), sizeof(double));
  }
  //MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm)
  MPI_Gather( wlocal, nlocal, MPI_DOUBLE, W, nlocal, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Imprimir solución */

  if (rank == 0) {
   if (N<100) for (i=0; i<N; i++) printf("w[%d] = %g\n", i, W[i]);
      free(W);
  }

  free(A);
  free(vlocal);
  free(wlocal);
  free(wauxlocal);
  MPI_Finalize();
  return 0;
}