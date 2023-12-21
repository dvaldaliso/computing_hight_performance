#include <iostream>
#include <string>
#include "NumeroR2.hpp"
using namespace std;
template<typename T>
class Complejo: public NumeroR2<T> 
{
private:
    T z;
public:
    Complejo(T x, T y);//Declaracion de Contructor
    //Declaracion de Operadores
    
};
//Implementacion del constructor
template < typename T >
Complejo<T>::Complejo(T x, T y): NumeroR2<T>(x,y) {} 

int main(){
    //Creamos un objeto complejo y lo asignamos a la variable "c"
    Complejo<double> a( 12.0, 0.0 );

    cout << "a = " << a << endl;
}

