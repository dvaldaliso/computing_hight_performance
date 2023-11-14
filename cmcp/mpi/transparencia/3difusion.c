#include <stdio.h>
#include <mpi.h>
#define TAG 111
void read_value(double* val){
    printf("%lf\n", *val);
}
int main(int argc, char* argv[]) 
{
    
    double val;
    int p, rank, i;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
    read_value(&val);
    /* valor a difundir */
   for (i=1; i<p; i++)
    MPI_Send(&val,1,MPI_DOUBLE,i,TAG,MPI_COMM_WORLD);
    } else {
    MPI_Recv(&val,1,MPI_DOUBLE,0,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    read_value(&val);
    }
    MPI_Finalize();
    return 0;
}

