#include <omp.h>
#include <stdio.h>
int main()
{
 int myid;
 #pragma omp parallel private(myid)
  {
    myid = omp_get_thread_num();
    if (myid==0) {
      /* Task 1 */
      printf("Tarea 1\n");
    } else if (myid==1) {
      /* Task 2 */
      printf("Tarea 2\n");
    }
    #pragma omp barrier
    if (myid==0) {
       /* Task 3 */
      printf("Tarea 3\n");
    }
  }
return 0;
}