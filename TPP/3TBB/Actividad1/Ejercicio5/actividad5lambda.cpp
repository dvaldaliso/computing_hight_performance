
#include <stdlib.h>
#include <cfloat>
#include <iostream>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
using namespace std;
using namespace tbb;
//g++ -o programa programa.cpp -ltbb
double Foo( double f ) { 
  double a = f*f; 
  return a;
}

/*long SerialMinIndexFoo( const double a[], size_t n ) {
  double value_of_min = RAND_MAX; 
  long index_of_min = -1; 
  for( size_t i=0; i<n; ++i ) {
    double value = Foo(a[i]); 
    if( value < value_of_min ) {
      value_of_min = value; 
      index_of_min = i;
    }
  } 
  return index_of_min;
}*/


long ParallelMinIndexFoo(const double a[], size_t n) {
	
  	long index_of_min = -1;
	return parallel_reduce(
		blocked_range<size_t>( 0, n),
			0.0,
			[=](const blocked_range<size_t>& r, long index_of_min)->long {
				for( size_t i=r.begin(); i!=r.end(); ++i ){
					 double value = Foo(a[i]); 
					 double value_of_min = RAND_MAX; 
					if( value < value_of_min ) {
						value_of_min = value; 
						index_of_min = i;
					}
				  }
				return index_of_min;
				}
			,
			[]( long x, long y )->long {
				if(x<y){
					return x;
				}
				return y;
			}
		);
}

int main( )  {

  long int n = 1000000;
  double *A = (double *) malloc( n*sizeof(double) );
  for( size_t i=0; i<n; ++i ) A[i] = (double) rand() / RAND_MAX;
  long indice = ParallelMinIndexFoo( A, n );
  cout << "Minimo número = " << A[indice] << endl;

}

