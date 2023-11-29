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
    Tabla ( const Tabla& copy );
    Tabla& operator =( const Tabla& );
    double& operator[](int i);
    int getN() const {return sz;}
    friend ostream& operator <<( ostream& , const Tabla& );
    ~Tabla();
};

Tabla::Tabla(): elem{new double[10]}, sz{10} {}
Tabla::Tabla(int s): elem{new double[s]}, sz{s} {}

// Crear una copia
Tabla::Tabla(const Tabla& copy) {
  elem = new double[copy.getN()];
  for (int i=0; i<copy.getN(); i++){
    elem[i] = copy.elem[i];
  }
  sz= copy.getN();
}

// Operador de posicion
double& Tabla::operator[](int i){
  if ( i <0 || sz <= i ) throw out_of_range { " Vector :: operator [] " };
    return elem [ i ];
}
// Operador de asignacion
Tabla& Tabla :: operator =( const Tabla& copy ) {
  return *this;
}
// Operador de imprimir
ostream& operator <<( ostream& outStream , const Tabla& t ) {
  string result;
  for (int i = 0; i < t.sz; i++)
  {
    result+= to_string(*(t.elem+i)) + " ";
  }
  
return outStream <<"[" <<result << "]" << endl ;
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
}