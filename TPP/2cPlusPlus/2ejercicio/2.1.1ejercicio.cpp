#include <iostream>
#include <ostream>   
using namespace std;




template < typename T >
class Tabla {
  private :
    T* elem ; // points to an array of sz elements of type T
    int sz ;
  public :
    Tabla ( int s );
    ~ Tabla ();
    T& operator []( int i );
    //const T& operator[]( int i ) const ;
    friend ostream& operator<<(ostream& os,  Tabla<T>& e)  {
   os << "[";
    for (size_t i = 0; i < e.getN(); ++i) {
        os << e[i];
        if (i < e.getN() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
    int getN() const { return sz ; }
};

template < typename T >
Tabla <T>:: Tabla ( int s ) {
  if (s <0) throw length_error { " Vector :: Vector ( int s ) " };
  elem = new T [ s ];
  sz = s ;
}
template < typename T >
T& Tabla <T>:: operator []( int i ) {
  if ( i <0 || sz <= i )
  throw out_of_range { " Vector :: operator [] " };
  return elem [ i ];
}

//Templates: iterators
template < typename T >
T* begin( Tabla<T>& x ) {
return x.getN() ? &x[0] : nullptr ;
}

template < typename T >
T* end ( Tabla <T>& x ) {
return begin( x )+ x.getN(); // pointer to one - past - last element
}




//Destructor
template < typename T >
Tabla<T>:: ~ Tabla(){
  cout << " destroy " << sz << endl ;
   delete [] elem;
   }
/* El código desarrollado en la Actividad 2 debe funcionar con el siguiente programa principal */
/* donde getN es el método que permite obtener la dimensión de la Tabla                        */

/* Si el código está correcto mostrará lo siguiente */
/* Tabla 1: [ 83 86 77 15 93 35 86 92 49 21 ]       */
/* Tabla 2: [ 62 27 90 59 63 ]                      */
/* Tabla 3: [ 62 27 90 59 63 ]                      */
/* Tabla 4: [ 83 86 77 15 93 35 86 92 49 21 ]       */

int main() {


   
  Tabla<double> t5{5};
  //Templates: iterators
  for( auto &e : t5 ) {
    e = rand() % 100;
  }
  cout << "Tabla 5: " << t5;

  
}