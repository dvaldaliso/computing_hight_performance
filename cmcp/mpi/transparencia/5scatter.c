#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
//este ejemplo envia los datos de un proceso al vecino derecho
int main(int argc, char* argv[]) 
{

   int i, size, rank, n=10, nloc;
   double *a, *aloc;
   /* Extracción de argumentos */
  if (argc > 1) { /* El usuario ha indicado el valor de N */
     if ((n = atoi(argv[1])) < 0) n = 10;
  }
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   if (rank==0) {
    a = malloc(n*sizeof(double));
    for (i=0;i<n;i++) a[i] = 1; /* rellena array */
   }
   nloc = n/size;
   /* asumimos division exacta */
   aloc = (double*) malloc(nloc*sizeof(double));

   MPI_Scatter(
    a, //datos que se van a distribuir
    nloc, // El size que ira a cada proceso
    MPI_DOUBLE, //tipo
    aloc, //lugar donde cada proceso almacena la parte local 
    nloc, // el size que se recibira
    MPI_DOUBLE,
    0, // el proceso que va ha realizar el proceso
    MPI_COMM_WORLD);

   printf("rank %d valor de nlocal:%lf\n",rank, *(aloc + 1));

   
   MPI_Finalize();
   free(a);
  free(aloc);
    return 0;
}

