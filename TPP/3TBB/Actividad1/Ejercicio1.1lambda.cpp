#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include <cstdlib>
using namespace tbb;
void Foo( double& f ) {
    unsigned int u = (unsigned int) f;
    f = (double) rand_r(&u) / RAND_MAX;
    f = f*f;
}


void ParallelApplyFoo( double a[], size_t n ) {
    const size_t GrainSize = 1;
    parallel_for( blocked_range<size_t>( 0, n, GrainSize ), [=](const blocked_range<size_t>& r ){
         //const blocked_range<size_t>& r; 
         for( size_t i=r.begin(); i!=r.end(); ++i )
                Foo(a[i]);
        });
}

int main( ) {
  size_t n = 1000;
  double a[n];
  ParallelApplyFoo( a, n );
}