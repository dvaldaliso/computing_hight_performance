#include <stdio.h>
#include <mpi.h>
#define TAG 111
void read_value(double* val,int rank){
    printf("valor recibido %lf from process %d\n", *val, rank);
}
void send_value(double* val,int rank){
    printf("valor enviado %lf from process %d\n", *val, rank);
}
int main(int argc, char* argv[]) 
{
    
    double val;
    int p, rank, i;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
    val=2.35;
    send_value(&val,rank);
    /* valor a difundir */
    printf("valor de P:%d",p);
   for (i=1; i<p; i++)
    MPI_Send(&val,1,MPI_DOUBLE,i,TAG,MPI_COMM_WORLD);
    } else {
    MPI_Recv(&val,1,MPI_DOUBLE,0,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    read_value(&val,rank);
    }
    MPI_Finalize();
    return 0;
}

