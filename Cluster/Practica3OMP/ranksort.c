#include "omp.h"
#include <stdio.h>

#define MAXV 100000

    double values[MAXV], final[MAXV]; /* vectores operando */
    int vsize, /* tamao vectores */
	i;


void PutInPlace (int src)
{
	double testval;
	int j, rank;

	testval = values[src];
	j = src;
	rank = 0;
	do {
 		j = (j+1) % vsize;
		if (testval >= values[j]) 
			rank = rank+1;
   	} while (j!=src);
	final[rank-1] = testval;
       printf("finalrank Final[%d]=%lf\n",rank-1,final[rank-1]);

}


int main( int argc, char *argv[] )
{

    int idproc, numprocs;
    double empieza, termina;

	if (argc != 2) {
		printf("Tamaño del vector: ");
		scanf("%d",&vsize);
	}else{
		vsize=atoi(argv[1]);
	}
    
    numprocs = omp_get_num_procs();
	printf("Tam. vectores (menor que %d): %d",MAXV,vsize);
//       scanf("%d", &vsize);
//vsize=40000;
       printf("\nGenerando datos...\n");
       for (i=0; i<vsize; i++) {
		   values[i]= (double) random();
	printf("valuel[%d]=%lf\n",i,values[i]);      
}
       printf("\nOrdenando datos...\n");
       empieza = omp_get_wtime();
   
       for (i=0; i<vsize; i++) {
          idproc = omp_get_thread_num() ;
//          printf("Soy %d, ejecuto %d\n",idproc,i);
		   PutInPlace (i);
       }	
	
       termina = omp_get_wtime();
       printf("\nTiempo=%lf\n", termina-empieza);

       printf("\nResultado...\n");
      for (i=0; i<vsize; i++) {
         printf("Final[%d]=%lf\n",i,final[i]);
	}
    return 0;
}
