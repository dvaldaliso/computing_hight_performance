
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"


int main(int argc, char *argv[]){

  double area, pi, x, valor;
  int i,n,tid,num_threads;
  double empieza, termina;

  
    if (argc != 3) {
//    scanf("%d",&n);
      printf ("Uso: pi n_iteraciones n_hilos\n");
      exit(1);
    } else {
      n=atoi(argv[1]);
      num_threads=atoi(argv[2]);
    }
  
    omp_set_num_threads(num_threads);

    empieza = omp_get_wtime();

    area = 0.0;
  
  #pragma omp parallel for private(x,valor,i)
    for(i=0; i<n; i++) {
	  x = (i+0.5)/n;
	  valor= 4.0/(1.0+x*x);	
	  #pragma omp atomic
	  area += valor;	
      }
    pi = area/n; 
    printf ("PI=%f\n", pi);

    termina = omp_get_wtime();
    printf("Hilos %d. Tiempo=%lf\n", num_threads, termina-empieza);

//  }  
  return 0;
}
