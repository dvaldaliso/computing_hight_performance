
#include <cstdio>
#include <cstdlib>

double Foo( double f ){ 
  unsigned int u=(unsigned int)f; 
  double a = (double) rand_r(&u)/RAND_MAX; 
  a = a*a; 
  return a; 
}

double SerialSumFoo( double a[], size_t n ){ 
  double sum = 0; 
  for( size_t i=0; i!=n; ++i ) 
    sum += Foo( a[i] ); 
  return sum; 
}

int main( ) {
  size_t n = 10000;
  double a[n];
  double sumas = SerialSumFoo( a, n );
  printf("Sumas = %f\n",sumas);
}


