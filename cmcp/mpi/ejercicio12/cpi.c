#include <stdio.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char *argv[])
{
  int n, myid, numprocs, i, p;
  double PI25DT = 3.141592653589793238462643;
  double mypi, pi, h, sum, x, aux;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Status status;
  while (1) {
     if (myid == 0) {
         printf("Enter the number of intervals: (0 quits)\n");
         scanf("%d",&n);
     }
     /* Communication: value of n from process 0 to all other processes */
     if (myid == 0) {
         for (p=1; p<numprocs; p++) MPI_Send(&n, 1, MPI_INT, p, 11, MPI_COMM_WORLD);
     } else {
         MPI_Recv(&n, 1, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     }
     /* End communication */
     if (n == 0)
         break;
     else {
         h   = 1.0 / (double) n;
         sum = 0.0;
         for (i = myid + 1; i <= n; i += numprocs) {
             x = h * ((double)i - 0.5);
             sum += (4.0 / (1.0 + x*x));
         }
         mypi = h * sum;
         /* Communication: receive in process 0 the value of mypi from the rest of processes
            and accumulate it on pi in process 0 */
         if (myid == 0) {
             pi = mypi;
             for (p=1; p<numprocs; p++) {
                 MPI_Recv(&aux, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status);
                 printf("[MPI process %d] I received value %lf, from rank %d.\n", myid, aux, status.MPI_SOURCE);
                 pi += aux;
             }
         } else {
             MPI_Send(&mypi, 1, MPI_DOUBLE, 0, 22, MPI_COMM_WORLD);
         }
         /* End communication */
         if (myid == 0)
             printf("pi is approximately %.16f, Error is %.16f\n",
                    pi, fabs(pi - PI25DT));
     }
  }
  MPI_Finalize();
  return 0;
}
