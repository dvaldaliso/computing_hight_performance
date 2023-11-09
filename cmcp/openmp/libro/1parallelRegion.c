
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int main()
{
int nthreads, tid;
#pragma omp parallel num_threads(4) private(tid)
{
tid = omp_get_thread_num();
printf("Hello world from (%d)\n", tid);
if(tid == 0)
{
nthreads = omp_get_num_threads();
printf("number of threads = %d\n", nthreads);
}
} // all threads join master thread and terminates
}
