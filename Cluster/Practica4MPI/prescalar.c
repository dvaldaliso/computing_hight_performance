#include "mpi.h"
#include <stdio.h>

#define MAXV 10000

int main( int argc, char *argv[] )
{

    int idproc, numprocs;
    double a[MAXV], b[MAXV], /* vectores operando */
           prod, /* producto escalar */ 
	   datoa, datob, /* datos recibidos en cada proc */
	   dato; /* producto enviado al 0 */
    int vsize, /* tam vectores */
        cadaproc, /* lo que le toca a cada proc */
	resto, /* el resto lo har�el cero */
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
          /*  Send dato: ptr  --tamaño-- dst tag communicator  */
          MPI_Send(&cadaproc, 1, MPI_INT, i,  0, MPI_COMM_WORLD);
          printf("Send: src %d dst %d dato %d\n", idproc, i, cadaproc); 
          for (j=0; j<cadaproc; j++) {
            /* Enviamos a cada procesador los datos que le tocan */
            /*
              MPI_Send(&a[k]...
              MPI_Send(&b[k]...
            */
            printf("Send: src %d dst %d dato %d\n", idproc, i, a[k]); 
            printf("Send: src %d dst %d dato %d\n", idproc, i, b[k]); 
            k++;
	  }
       }
       /* el resto lo hace el cero */       
       prod =0;
       for (j=0; j<resto; j++) {
         prod = prod+(a[k]*b[k]);
	 k++;
       }
     
       for (i=1; i<numprocs; i++) {
         /* Recibimos de cada procesador su resultado */
         /*
          MPI_Recv(&dato,...
         */
		 printf("Recv: dst %d src %d numfila %d\n", idproc, status.MPI_SOURCE, dato); 
         prod = prod+dato;
       }
       printf("El producto escalar es %f\n", prod );
    } 
    else {
       /* Recibimos cuantos datos nos tocan                           */
       /*  Recv dato: ptr  --tamaño-- dst tag communicator    status  */
       MPI_Recv(&cadaproc, 1, MPI_INT, 0,  0, MPI_COMM_WORLD, 
&status );
	   printf("Recv: dst %d src %d numfila %d\n", idproc, status.MPI_SOURCE, cadaproc); 
       prod = 0;
       for (j=0; j<cadaproc; j++) {
         /* Recibimos cada elemento del vector que nos toca, multiplicamos y acumulamos */
         /*
          MPI_Recv(&datoa...
          MPI_Recv(&datob... 
         */
		 printf("Recv: dst %d src %d numfila %d\n", idproc, status.MPI_SOURCE, datoa); 
		 printf("Recv: dst %d src %d numfila %d\n", idproc, status.MPI_SOURCE, datob); 
         prod = prod + datoa*datob;
       }
       /*
        MPI_Send...  
       */
       printf("Send: src %d dst %d dato %d\n", idproc, 0, prod); 
    }
           
    MPI_Finalize();
    return 0;
}
