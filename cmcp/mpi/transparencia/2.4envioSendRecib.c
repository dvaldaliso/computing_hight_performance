#include <stdio.h>
#include <mpi.h>
#include <string.h>

void process(double* a,int cnt){
    int i = 0;
   for (i = 0; i < cnt-1; i++) {
    printf("valor recibidos:%lf \n",*(a+i));
    }
}

void compute(double* a,int b){
    int i = 0;
    for (i = 0; i < b-1; i++) {
    printf("valor enviados:%lf \n",*(a+i));
    }
    
}
int main(int argc, char* argv[]) 
{
    int N=5;
    
     int rank, numProcesos, next, prev;
    double a[N];
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);
    
  
   if (rank == 0) prev = MPI_PROC_NULL;
   else prev = rank-1;
   if (rank == numProcesos-1) next = MPI_PROC_NULL;
   else next = rank+1;
   MPI_Sendrecv_replace(a, N, MPI_DOUBLE, next, 0, prev, 0,
   comm, &status);

    MPI_Finalize();
    return 0;
}