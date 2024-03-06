#include "mpi.h"
#include <stdio.h>

#define MAXV 10000

int main( int argc, char *argv[] )
{

    int idproc, numprocs;
    double a[MAXV], b[MAXV], /* vectores operando */
           prod, /* producto escalar */ 
           datoa[MAXV], datob[MAXV] /* datos recibidos en cada proc */
           dato; /* producto enviado al 0 */
    int vsize, /* tam vectores */
        cadaproc, /* lo que le toca a cada proc */
        resto, /* el resto lo hará el cero */
        i, j, k;
    MPI_Status status;
    
    MPI_Init (&argc, &argv );
    MPI_Comm_rank ( MPI_COMM_WORLD, &idproc );
    MPI_Comm_size ( MPI_COMM_WORLD, &numprocs );
    
    if (idproc == 0) {
       printf("Tam. vectores (menor que %d):",MAXV);
       scanf("%d", &vsize);
       printf("\nGenerando datos...\n");
       for (i=0; i<vsize; i++) {
         a[i]=(double) i;
         b[i]=(double) i;
       }
       cadaproc = vsize / (numprocs-1);
       resto = vsize % (numprocs-1);  

       k=0;
       for (i=1; i<numprocs; i++) {
          /* Enviamos a cada procesador cuantos datos le tocan */
          MPI_Send(&cadaproc, 1, MPI_INT, i,  0, MPI_COMM_WORLD);
          printf("Send: src %d dst %d dato %d\n", idproc, i, cadaproc); 
          /* Enviamos a cada procesador los datos que le tocan */
          MPI_Send(&a[k], cadaproc, MPI_DOUBLE, i,  0, MPI_COMM_WORLD);
          MPI_Send(&b[k], cadaproc, MPI_DOUBLE, i,  0, MPI_COMM_WORLD);
          printf("Send: src %d dst %d dato %f hasta %f\n", idproc, i, a[k], a[k + cadaproc - 1]); 
          printf("Send: src %d dst %d dato %f hasta %f\n", idproc, i, b[k], b[k + cadaproc - 1]); 
          k += cadaproc;
       }
       /* el resto lo hace el cero */       
       prod =0;
       for (j=0; j<resto; j++) {
         prod = prod+(a[k]*b[k]);
         k++;
       }
     
       for (i=1; i<numprocs; i++) {
         /* Recibimos de cada procesador su resultado */
         MPI_Recv(&dato, 1, MPI_DOUBLE, i,  0, MPI_COMM_WORLD, &status);
         printf("Recv: dst %d src %d dato %f\n", idproc, status.MPI_SOURCE, dato); 
         prod = prod+dato;
       }
       printf("El producto escalar es %f\n", prod );
    } 
    else {
       /* Recibimos cuantos datos nos tocan */
       MPI_Recv(&cadaproc, 1, MPI_INT, 0,  0, MPI_COMM_WORLD, &status);
       printf("Recv: dst %d src %d dato %d\n", idproc, status.MPI_SOURCE, cadaproc); 
       /* Recibimos cada elemento del vector que nos toca, multiplicamos y acumulamos */
       MPI_Recv(&datoa, cadaproc, MPI_DOUBLE, 0,  0, MPI_COMM_WORLD, &status);
       MPI_Recv(&datob, cadaproc, MPI_DOUBLE, 0,  0, MPI_COMM_WORLD, &status); 
       printf("Recv: dst %d src %d dato %f hasta %f\n", idproc, status.MPI_SOURCE, datoa[0], datoa[cadaproc - 1]); 
       printf("Recv: dst %d src %d dato %f hasta %f\n", idproc, status.MPI_SOURCE, datob[0], datob[cadaproc - 1]); 
       prod = 0;
       for (j=0; j<cadaproc; j++) {
         prod = prod + datoa[j] * datob[j];
       }
       /* Enviamos nuestro resultado al proceso 0 */
       MPI_Send(&prod, 1, MPI_DOUBLE, 0,  0, MPI_COMM_WORLD);
       printf("Send: src %d dst %d dato %f\n", idproc, 0, prod); 
    }
           
    MPI_Finalize();
    return 0;
}
