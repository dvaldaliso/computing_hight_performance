#include <omp.h>
#include <stdio.h>
int main()
{
  int i, istart, N, iend, nthr, myid;
  int *a, *b;
  #pragma omp parallel private(myid, i, istart, iend)
  {
    nthr = omp_get_num_threads();
    myid = omp_get_thread_num();
    printf("procesos: %d currentProcess: %d\n", nthr,myid);
    /*istart = myid*N / nthr;
    iend = (myid+1)*N / nthr;
    if (myid == nthr-1) iend = N;
    for (i=istart; i<iend; i++) {
      a[i] = a[i] + b[i];
    }*/
  }
return 0;
}