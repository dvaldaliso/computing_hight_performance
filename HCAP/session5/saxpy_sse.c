#define LIM 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <xmmintrin.h>
#include <immintrin.h>

float randfloat() 
{ 
    float r= (float)(rand());
    float div =(float)(1-RAND_MAX);
    return r/div; 
} 




int main(){
  
float y[LIM],x[LIM],yc[LIM],a;
int i,j;
a=2.0;

for (i=0;i<LIM;i++)
{x[i]=-randfloat();
 y[i]=-randfloat();
  yc[i]=y[i];
}



 printf("vector y inicial \n ");
for (i=0;i<LIM;i++)
  {//printf("%f ",x[i]);
   printf("%f ",y[i]);
  }
  printf("\n ");

//saxpy
for (i=0;i<LIM;i++)
 y[i]=a*x[i]+y[i];
  
 printf("vector y tras saxpy escalar: \n ");

for (i=0;i<LIM;i++)
  {//printf("%f ",x[i]);
   printf("%f ",y[i]);
  }
 
for (i=0;i<LIM;i++)
  y[i]=yc[i];

  printf("\n ");

//Poner aqui version de saxpy con SSE 

 printf("vector y tras saxpy sse: \n ")  ;

for (i=0;i<LIM;i++)
  {//printf("%f ",x[i]);
   printf("%f ",y[i]);
  }
}
