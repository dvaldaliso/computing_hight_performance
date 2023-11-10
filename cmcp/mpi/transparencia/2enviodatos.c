#include <stdio.h>
#include <mpi.h>
// Enviar datos de P0 a P1
void compute(int rank, double a[], int N){
    int i;
    for ( i = 0; i < N; i++)
    {
        printf("dato enviado  %lf del proceso P%d\n",a[i], rank);
    }
    
}
void process(int rank, double a[],int N){
    int i;
    for ( i = 0; i < N; i++)
    {
        printf("datos recibidos %lf del proceso P%d\n",a[i],rank);
    }
    
}
int main(int argc, char* argv[]) 
{
    int N=5;
    int M=5;
    int rank, cnt;
    double a[N], b[M];
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    MPI_Status stat;
    a[0]=5.5;
    a[1]=3.8;
    a[2]=4.6;
    a[3]=9.7;
    a[4]=10.7;
   
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
    if (rank == 0) {
        compute(rank, a, N);
        /* rellenar el array */
        MPI_Send(a, N, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(b, M, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &stat);
        MPI_Get_count(&stat, MPI_DOUBLE, &cnt);
        process(rank, b, cnt);
        /* usar los datos recibidos */
    }
    MPI_Finalize();
    return 0;
}