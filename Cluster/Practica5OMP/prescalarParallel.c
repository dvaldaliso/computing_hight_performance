#include "omp.h"
#include <stdio.h>

#define MAXV 100000

int main( int argc, char *argv[] )
{
  double empieza, termina;

    int idproc, numprocs;
    double a[MAXV], b[MAXV], /* vectores operando */
           prod; /* producto escalar */ 
    int vsize, /* tamao vectores */
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
         a[i]=(double) i;
	 b[i]=(double) i;
       }
     
     empieza = omp_get_wtime();

     prod = 0;
    #pragma omp parallel for private(i)	
     for (i=0; i<vsize; i++) {

         idproc = omp_get_thread_num() ;
//       printf("Soy %d, ejecuto %d\n",idproc,i);
         prod = prod+(a[i]*b[i]);
     }	
     printf("El producto escalar es %f\n", prod );

    termina = omp_get_wtime();
    printf("\nTiempo=%lf\n", termina-empieza);

    return 0;
}
