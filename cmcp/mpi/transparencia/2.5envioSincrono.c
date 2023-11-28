#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char* argv[]) 
{
    
    int rank, numProcesos,x;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);
    MPI_Request request;
    if (rank==0) {
    x=100;
    MPI_Isend(&x, 1, MPI_INT, 1, 999, MPI_COMM_WORLD, &request);
    x=200;
    MPI_Wait(&request, &status);
    } else if (rank==1) {
    MPI_Recv(&x, 1, MPI_INT, 0, 999, MPI_COMM_WORLD, &status);
    printf("valor de x %d\n",x);
    }

    MPI_Finalize();
    return 0;
}