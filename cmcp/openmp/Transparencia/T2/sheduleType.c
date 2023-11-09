#include <omp.h>
#include <stdio.h>
int main()
{
 int d, s, g;
 //omp_set_num_threads(2);
//Shedule Parallel
/*#pragma omp parallel for schedule(dynamic,2)
for (d=0; d<12; d++) {
  printf("Dinamyc %d hilo : %d\n", d, omp_get_thread_num());
}*/

/*#pragma omp parallel for schedule(static,2)
for (s=0; s<12; s++) {
  printf("Static %d hilo: %d\n", s, omp_get_thread_num());
} */

/*#pragma omp parallel for schedule(guided)
for (g=0; g<20; g++) {
  printf("Guided %d hilo: %d\n", g, omp_get_thread_num());
}*/
int i,tid,n=8;
int a[n];
#pragma omp parallel for private(tid) schedule(static,2)
for (i = 0; i < n; i ++) {
  tid = omp_get_thread_num();
  a[tid] += i;
  printf("El hilo %d realiza la iteración %d.\n",tid,i);
};
return 0;
}