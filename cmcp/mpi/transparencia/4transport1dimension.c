#include <stdio.h>
#include <mpi.h>
#define TAG 111
//este ejemplo envia los datos de un proceso al vecino derecho
int main(int argc, char* argv[]) 
{
    int p, rank;
    double a=3.014;
    int N=1;
    MPI_Comm comm;  // Va

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    comm = MPI_COMM_WORLD;


    MPI_Status status;
    if (rank == 0) {
        MPI_Send(&a, N, MPI_DOUBLE, rank+1, 0, comm);
    } else if (rank == p-1) {
        MPI_Recv(&a, N, MPI_DOUBLE, rank-1, 0, comm, &status);
    } else {
        MPI_Send(&a, N, MPI_DOUBLE, rank+1, 0, comm);
        MPI_Recv(&a, N, MPI_DOUBLE, rank-1, 0, comm, &status);
    }
   
    MPI_Finalize();
    return 0;
}

