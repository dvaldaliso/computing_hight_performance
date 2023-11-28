#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char* argv[]) 
{
    char msg[] = "Hola, mundo!";
    int rank, count;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
  
    if (rank == 0) {
        printf ( "I am master. Sending Sending the message message.\n\n" );
        strcpy(msg, "Hello World!");
        
        MPI_Send(msg, 13, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        printf ("I am the slave %d. Receiving the message.\n", rank);
        MPI_Recv(msg, 13, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        
        printf ("The message  is: %s\n", msg);
        //El siguiente condifo guada en la direccion de count el status y se ve la cantidad exacta que trae.
        MPI_Get_count(&status, MPI_CHAR, &count);
        printf("Recibidos %d caracteres de %d con tag= %d\n", count, status.MPI_SOURCE, status.MPI_TAG);
    }
    MPI_Finalize();
    return 0;
}