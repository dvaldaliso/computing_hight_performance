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
    Complejo();//Declaracion de Contructor
    Complejo(T x, T y);//Declaracion de Contructor
    Complejo (Complejo<T>& copy); // Constructor para Crear una copia
    T getModulo();
    //Declaracion de sobrecarga de Operadores
    //Declaracion de sobrecarga de operador para impirmir
    template<typename m> 
    friend ostream& operator <<( ostream& ,const Complejo<m>&);

    // Declaracion de Sobrecarga del operador +=
    Complejo<T>& operator +=(const Complejo<T>&);

    // Declaracion de Sobrecarga del operador -=
    Complejo<T>& operator -=(const Complejo<T>&);

    // Declaracion de Sobrecarga del operador +
    Complejo<T> operator +(const Complejo<T>&);

    // Declaracion de Sobrecarga del operador -
    Complejo<T> operator -(const Complejo<T>&);

    //Declaracion de Sobrecarga del operador de post-incremento (a++)
    Complejo<T> operator ++(int);

    //Declaracion de Sobrecarga del operador de pre-incremento (++a)
    Complejo<T>& operator ++();

     //Declaracion de Sobrecarga del operador de post-disminucion (a++)
    Complejo<T> operator --(int);

    //Declaracion de Sobrecarga del operador de pre-disminucion (++a)
    Complejo<T>& operator --();
    
    //Declaracion de Sobrecarga del operador =
    Complejo<T>& operator =( const Complejo<T>& );
    // inciso 6 
    //inciso 7
    //Declaracion de Sobrecarga del operador()
    Complejo<T>& operator()( T x, T y=0 );
    
};
//Esto se llama inline: implementar los metodos fuera de la clase

//Implementacion Sobrecarga del operador ()
template <typename T>
Complejo<T>& Complejo<T>:: operator ()( T x, T y ) {
        this->setX(x);
        this->setY(y);
        modulo();
  return *this;
}
//Calculo del modulo
template < typename T >
void Complejo<T>::modulo(){
    this->z = sqrt(pow(this->getX(),2) + pow(this->getY(),2));
    //cout <<"x:"<<pow(this->getX(),2)<<" "<<"y:"<<pow(this->getY(),2)<<"="<< this->z << endl;
}

//Implementacion del constructor, default valores.
template < typename T >
Complejo<T>::Complejo(): NumeroR2<T>(0,0) {
    this->modulo();
} 

//Implementacion del constructor, seteado con valores.
template < typename T >
Complejo<T>::Complejo(T x, T y): NumeroR2<T>(x,y) {
    this->modulo();
} 

//Implementacion de constructor para Crear una copia
template < typename T >
Complejo<T>::Complejo(Complejo<T>& copy) {
    this->setX(copy.getX());
    this->setY(copy.getY());
    this->modulo();
}


template < typename T >
T Complejo<T>::getModulo(){
    return z;
}

//Implementacion de sobrecarga de operador para impirmir
template <typename m>
ostream& operator <<( ostream& os, const Complejo<m>& complejo )  {
    os  << complejo.getX() << " + " << complejo.getY() << "i";
    return os;
}

// Implementacion de sobrecarga del operador +=
template <typename T>
Complejo<T>& Complejo<T> :: operator +=( const Complejo<T>& c ) {
      NumeroR2<T>::operator+=( c );
      modulo();
    return *this;
}
// Implementacion de sobrecarga del operador -=
template<class T>
Complejo<T>& Complejo<T>::operator-=( const Complejo<T>& c ) {
    NumeroR2<T>::operator-=( c );
    modulo();
    return *this;
}

//Implementacion de Sobrecarga del operador +
template <typename T>
Complejo<T> Complejo<T> :: operator +(const Complejo<T>& complejo ) {
    NumeroR2<T> t =NumeroR2<T>::operator+(complejo) ;
    Complejo<T>newC(t.getX(),t.getY());
    newC.modulo();
    return newC;
}

//Implementacion Sobrecarga del operador -
template <typename T>
Complejo<T> Complejo<T> :: operator -(const Complejo<T>& complejo ) {
    NumeroR2<T>::operator-( complejo );//Ver como hacer que funcione de esta manera
    modulo();
    return *this;
}

//Implementacion Sobrecarga del operador de post-incremento (a++)
// Se asigna y luego incrementa
template <typename T>
Complejo<T> Complejo<T> :: operator ++(int) {
        Complejo *c = new Complejo( *this );
        NumeroR2<T>::operator++( 0 );
        modulo();              
        return *c;
}

//Implementacion Sobrecarga del operador de pre-incremento (++a)
// Se incrementa y luego se asigna
template <typename T>
Complejo<T>& Complejo<T> :: operator ++() {
    NumeroR2<T>::operator++();
    modulo();
    return *this;
}

// Implementacion Sobrecarga del operador de post-disminucion (a--)
// Se asigna y luego incrementa
template <typename T>
Complejo<T> Complejo<T> :: operator --(int) {
        Complejo *c = new Complejo( *this );
        NumeroR2<T>::operator--(0);
        modulo();
        return *c;
}

//Implementacion Sobrecarga del operador de pre-disminucion (--a)
// Se decrementa y luego se asigna
template <typename T>
Complejo<T>& Complejo<T> :: operator --() {
    NumeroR2<T>::operator--();
    modulo();
    return *this;
}

//Implementacion Sobrecarga del operador =
template <typename T>
Complejo<T>& Complejo<T> :: operator =( const Complejo<T>& copy ) {
        NumeroR2<T>::operator=(copy);
        modulo();
  return *this;
}




int main(){
    //Creamos un objeto complejo y lo asignamos a la variable "a"
    Complejo<double> a( 12.0, 0.0 );
    Complejo<double> b(12,5);
    Complejo<double> c(b);
    Complejo<double> d(12,6);

    //EN LAS OPERACIONES AMBOS NUMERO TIENEN QUE SER DEL MISMO TIPO
    a+=b;
    d = c++;
    Complejo<double> e, f, g;
    e(1.0,3.0);
    f(-11.0);
    g = e + f;
    cout << "e = " << e << endl;
    cout << "f = " << f << endl;
    cout << "g = " << g << endl;
    
    // a
    cout << "a = " << a << endl;
    // b
    cout << "b = " << b << endl;
    // c
    cout << "c = " << c << endl;
    // d
    cout << "d = " << d << endl;
    //Modulo a
    cout << "z = " << a.getModulo() << endl;

    //Modulo b
    cout << "z = " << b.getModulo() << endl;

    //Modulo c
    cout << "z = " << c.getModulo() << endl;


}

operator3129*-