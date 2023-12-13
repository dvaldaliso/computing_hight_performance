
#include <cstdio>
#include <cstdlib>
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"
#include <cstdlib>
using namespace tbb;

//g++ -o programa programa.cpp -ltbb
double Foo( double f ){ 
  unsigned int u=(unsigned int)f; 
  double a = (double) rand_r(&u)/RAND_MAX; 
  a = a*a; 
  return a; 
}

double ParallelSumFoo(  double a[], size_t n ) {
  const int GrainSize=1;
 return parallel_reduce( blocked_range<size_t>(0, n, GrainSize), 
  0.0,
  [=](const blocked_range<size_t>& r, double sum)->double {
    for( size_t i=r.begin(); i!=r.end(); ++i )
        sum += Foo(a[i]);
    return sum;  
  },
  [] (double x, double y)->double {return x+y;} 
  );
}
int main( ) {
  size_t n = 10000;
  double a[n];
  double sumas = ParallelSumFoo( a, n );
  printf("Sumas = %f\n",sumas);
}


