
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
class SumFoo {
  double* my_a;
  public:
  double my_sum;
  void operator()( const blocked_range<size_t>& r ) {
  double *a = my_a;
  double sum = my_sum;
  size_t end = r.end();
  for( size_t i=r.begin(); i!=end; ++i )
    sum += Foo(a[i]);
    my_sum = sum;
  }
  SumFoo( SumFoo& x, split ) : my_a(x.my_a), my_sum(0) { }
  void join( const SumFoo& y ) {my_sum+=y.my_sum;}
  SumFoo( double a[] ) : my_a(a), my_sum(0) { }
};

double ParallelSumFoo(  double a[], size_t n ) {
  const int GrainSize=1;
  SumFoo sf(a);
  parallel_reduce( blocked_range<size_t>(0,n,GrainSize), sf );
  return sf.my_sum;
}
int main( ) {
  size_t n = 10000;
  double a[n];
  double sumas = ParallelSumFoo( a, n );
  printf("Sumas = %f\n",sumas);
}


