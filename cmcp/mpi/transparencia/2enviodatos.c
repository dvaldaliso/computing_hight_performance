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
    int M=5;
     int rank, cnt;
    double a[N], b[M];
    MPI_Init(&argc, &argv);
    MPI_Status stat;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    a[0]=45.5;
  
    if (rank == 0) {
    compute(a, N);
    /* rellenar el array */
    MPI_Send(a, N, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
    MPI_Recv(b, M, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &stat);
    MPI_Get_count(&stat, MPI_DOUBLE, &cnt);
    process(b, cnt);
    /* usar los datos recibidos */
    }
    MPI_Finalize();
    return 0;
}