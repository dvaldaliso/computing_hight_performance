#include <iostream>
#include <ostream>   
using namespace std;

class Tabla
{
private:
    double* elem;
    int sz;
public:
    Tabla ();
    Tabla (int n);

    // Constructor para Crear una copia
    Tabla ( Tabla& copy );
    // Sobrecarga del operador ()
    Tabla& operator =( const Tabla& );
    // Sobrecarga del operador []
    double& operator[](int i);
    int getN() const {return sz;}
    friend ostream& operator <<( ostream& , Tabla& );
    /* function friend: es una funcion que no pertenece a la clase,
         pero que tiene permiso para acceder a sus variables y funciones miembro privadas 
         por medio de los operadores punto (.) y flecha (->)
        */
    ~Tabla();
};
// Constructor por default
Tabla::Tabla(): elem{new double[10]}, sz{10} {}
Tabla::Tabla(int s): elem{new double[s]}, sz{s} {}

// Constructor para Crear una copia
Tabla::Tabla(Tabla& copy): elem{new double[copy.getN()]}, sz{copy.getN()} {
  for (int i=0; i<copy.getN(); i++){
    elem[i] = copy[i];
  }
}

// Sobrecarga del operador de posicion
double& Tabla::operator[](int i){
  if ( i <0 || sz <= i ) throw out_of_range { " Vector :: operator [] " };
    return elem [ i ];
}
// Sobrecarga del operador de asignacion
Tabla& Tabla :: operator =( const Tabla& copy ) {
  double * p = new double [ copy.getN()];
  for ( int i =0; i != copy.getN() ; ++ i )
    p [ i ] = copy.elem [ i ];
  delete [] elem ;  // delete old elements
  elem = p ;
  sz = copy.getN() ;
  return * this ;
}
// Ver la diferencia del const en "Operador de asignacion" y "Operador de imprimir"
// Sobrecarga del operador de imprimir
ostream& operator <<( ostream& os , Tabla& e ) {
   os << "[";
    for (size_t i = 0; i < e.getN(); ++i) {
        os << e[i];
        if (i < e.getN() - 1) {
            os << ", ";
        }
    }
    os << "]"<<endl;
    return os;
}

//Templates: iterators
double* begin( Tabla& x ) {
return x.getN() ? &x[0] : nullptr ;
}
double* end ( Tabla& x ) {
return begin( x )+ x.getN(); // pointer to one - past - last element
}


//Destructor
Tabla::~Tabla(){
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


   Tabla t1; 
   Tabla t2(5);

   for( int i=0; i<t1.getN(); i++ ) { 
     t1[i] = rand() % 100;
   }   
   //para que imprima el t1 implementar friend(funcion amiga)
   cout << "Tabla 1: " << t1; 
   for( int i=0; i<t2.getN(); i++ ) { 
     t2[i] = rand() % 100;
   }   
   cout << "Tabla 2: " << t2; 
   Tabla t3(t2);
   cout << "Tabla 3: " << t3; 
   Tabla t4(5);
   t4 = t1; 
   cout << "Tabla 4: " << t4; 

  //Templates: iterators
  Tabla t5{5};
  for( auto &e : t5 ) {
    e = rand() % 100;
  }
  cout << "Tabla 5: " << t5;


  
}