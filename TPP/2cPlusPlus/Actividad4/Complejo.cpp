#include <iostream>
#include <string>
#include "NumeroR2.hpp"
#include <cmath>
using namespace std;
// g++ -o Complejo Complejo.cpp -lm
template<typename T>
class Complejo: public NumeroR2<T> 
{
private:
    T z;
    void modulo();
public:
    Complejo(T x, T y);//Declaracion de Contructor
    T getModuloResult();
    //Declaracion de Operadores
    
};
//Esto se llama inline: implementar los metodos fuera de la clase
//Implementacion del constructor
template < typename T >
Complejo<T>::Complejo(T x, T y): NumeroR2<T>(x,y) {} 

//Calculo del modulo
template < typename T >
void Complejo<T>::modulo(){
    z = sqrt(pow(this->getX(),2) + pow(this->getY(),2));
}
template < typename T >
T Complejo<T>::getModuloResult(){
    this->modulo();
    return z;
}

int main(){
    //Creamos un objeto complejo y lo asignamos a la variable "a"
    Complejo<double> a( 12.0, 0.0 );

    cout << "a = " << a << endl;
    cout << "z = " << a.getModuloResult() << endl;
}

