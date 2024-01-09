
#include <stdio.h>
#include <stdlib.h>
#include "tbb/parallel invoke.h".

size_t fib( size_t n ) {
  size_t i, j;
  if (n<2)
    return n;
  else {
    i=fib(n-1);
    j=fib(n-2);
    return i+j;
  }
}

size_t fib1( size_t n ) {
  /* Implementad la version con parallel_invoke  */
  size_t i, j;
  if (n<2) 
     return n; 
   else { 
         parallel_invoke( [&]{i=fib(n-1);},  
                          [&]{j=fib(n-2);} ); 
         return i+j; 
   } 
}

size_t fib2( size_t n ) {
  /* Implementad la version con task_group  */
  size_t i, j; 
   if (n<2) 
     return n; 
   else { 
         task_group g;
         g.run([&]{i=fib(n-1);}); 
         g.run([&]{j=fib(n-2);}); 
         g.wait();
         return i+j; 
   }
}

int main( int argc, char *argv[] ) {

  int n;
  size_t m;
  if( argc<2 ) {
    printf("Usage: %s n\n",argv[0]);
    exit(0);
  }
  sscanf(argv[1],"%d",&n);

  m = fib( (size_t)n );
  printf("m = %ld\n",m);
  m = fib1( (size_t)n );
  printf("m = %ld\n",m);
  m = fib2( (size_t)n );
  printf("m = %ld\n",m);
}

