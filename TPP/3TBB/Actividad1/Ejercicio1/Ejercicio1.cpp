#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include <cstdlib>
using namespace tbb;
void Foo( double& f ) {
    unsigned int u = (unsigned int) f;
    f = (double) rand_r(&u) / RAND_MAX;
    f = f*f;
}
class ApplyFoo {
    double *const my_a;
    public:
    void operator()( const blocked_range<size_t>& r ) const {
    double *a = my_a;
    for( size_t i=r.begin(); i!=r.end(); ++i )
        Foo(a[i]);
    }
    ApplyFoo( double a[] ) : my_a(a) { }
};


void ParallelApplyFoo( double a[], size_t n ) {
    const size_t GrainSize = 1000;
    parallel_for( blocked_range<size_t>( 0, n, GrainSize ),
    ApplyFoo(a) );
}

int main( ) {
  size_t n = 1000;
  double a[n];
  ParallelApplyFoo( a, n );
}