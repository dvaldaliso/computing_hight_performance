#include "omp.h"
#include <stdio.h>

#define MAXV 100000

int main( int argc, char *argv[] )
{
  double empieza, termina;

    int idproc, numprocs;
    double a[MAXV], b[MAXV], /* vectores operando */
           vsum[MAXV],
           vprod[MAXV],
           vdiv[MAXV], /* vector resultado */
           prod; /* producto escalar */ 
    int vsize, /* tam vectores */
	i;
    
  if (argc != 2) {
    scanf("%d",&vsize);
  }else{
   
    vsize=atoi(argv[1]);
  }

    printf("Tam. vectores (menor que %d): %d",MAXV,vsize);
//   scanf("%d", &vsize);

    numprocs = omp_get_num_procs();

   
    printf("\nGenerando datos...\n");
    for (i=0; i<vsize; i++) {
       a[i]=(double) i+1;
       b[i]=(double) i+1;
    }

    empieza = omp_get_wtime();

     
    {
// Producto escalar
     prod = 0;
    
     for (i=0; i<vsize; i++) {
//         idproc = omp_get_thread_num() ;
//         printf("Soy %d, ejecuto %d\n",idproc,i);
         prod = prod+(a[i]*b[i]);
     }	

// Suma
     for (i=0; i<vsize; i++) {
//         idproc = omp_get_thread_num() ;
//         printf("Soy %d, ejecuto %d\n",idproc,i);
         vsum[i]= a[i]+b[i];
     }	

// Mult
     for (i=0; i<vsize; i++) {
//         idproc = omp_get_thread_num() ;
//         printf("Soy %d, ejecuto %d\n",idproc,i);
         vprod[i]= a[i]*b[i];
     }	

// Div
     for (i=0; i<vsize; i++) {
//         idproc = omp_get_thread_num() ;
//         printf("Soy %d, ejecuto %d\n",idproc,i);
         vdiv [i]= a[i]/b[i];
     }	
    }
     printf("El producto escalar es %f\n", prod );
     for (i=0; i<vsize; i++) {
        printf("Suma= %lf; Prod= %lf; Div= %lf\n", vsum[i],vprod[i],vdiv[i]);
     }	

    termina = omp_get_wtime();
    printf("\nTiempo=%lf\n", termina-empieza);

    return 0;
}
