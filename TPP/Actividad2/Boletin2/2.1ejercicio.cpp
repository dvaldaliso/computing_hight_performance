#include <iostream>
#include <ostream>   
using namespace std;

class Tabla
{
private:
    double* elem;
    int sz;
public:
    Tabla();
    Tabla(int n);
    double& operator[](int i);
    int getN() const {return sz;}
    ~Tabla();
};

Tabla::Tabla(): elem{new double[10]}, sz{10} {}
Tabla::Tabla(int s): elem{new double[s]}, sz{s} {}

double& Tabla::operator[](int i){
    return elem[i];
}

Tabla::~Tabla(){ delete [] elem;}
/* El código desarrollado en la Actividad 2 debe funcionar con el siguiente programa principal */
/* donde getN es el método que permite obtener la dimensión de la Tabla                        */

/* Si el código está correcto mostrará lo siguiente */
/* Tabla 1: [ 83 86 77 15 93 35 86 92 49 21 ]       */
/* Tabla 2: [ 62 27 90 59 63 ]                      */
/* Tabla 3: [ 62 27 90 59 63 ]                      */
/* Tabla 4: [ 83 86 77 15 93 35 86 92 49 21 ]       */

int main() {


   Tabla t1; 
   //Tabla t2(5);

   for( int i=0; i<t1.getN(); i++ ) { 
     t1[i] = rand() % 100;
   }   
   //para que imprima el t1 implementar friend(funcion amiga)
   cout << "Tabla 1: " << t1; 
   /*for( int i=0; i<t2.getN(); i++ ) { 
     t2[i] = rand() % 100;
   }   
   cout << "Tabla 2: " << t2; 
   Tabla t3(t2);
   cout << "Tabla 3: " << t3; 
   Tabla t4(5);
   t4 = t1; 
   cout << "Tabla 4: " << t4; 
*/
}