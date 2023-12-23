#include <iostream>
#include <string>
#include "NumeroR2.hpp"
#include <cmath>
#include <algorithm>    // std::for_each
#include <vector>
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
    Complejo (const Complejo<T>& copy); // Constructor para Crear una copia
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
Complejo<T>::Complejo(const Complejo<T>& copy) {
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

template <typename T>
void modulod (Complejo<T> c ) {
    cout << c.getModulo() << endl;
}

template <typename T>
class functor {
    public:
        void operator() (Complejo<T> &c) { cout << c.getModulo() << endl; }
};
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

    
    vector<Complejo<double>> listComplejo;
    listComplejo.push_back(e);
    listComplejo.push_back(a);
    listComplejo.push_back(b);
    listComplejo.push_back(d);
    listComplejo.push_back(c);
    listComplejo.push_back(f);

    vector<Complejo<double>>::iterator ptr; 

    cout << "The vector iterator elements are : "; 
    for (ptr = listComplejo.begin(); ptr != listComplejo.end(); ptr++) 
        cout << *ptr << " "<<endl; 

    cout << "The vector foreach elements are : "; 
     for(Complejo<double> a : listComplejo)
    {
    	cout<<a<<" mod:"<<a.getModulo()<< endl;
    }
    //Falta el 9 for_each
    cout << "The vector foreach elements are : "; 
    cout << "myvector function contains:"<<endl;
    for_each (listComplejo.begin(), listComplejo.end(), modulod<double>);

   

    // using object as comp
    sort (listComplejo.begin(), listComplejo.end(), [=](Complejo<double> i, Complejo<double> j){return i.getModulo()<j.getModulo();});

    cout << "The vector foreach elements are : "; 
    cout << "myvector object contains:"<<endl;
    for_each (listComplejo.begin(), listComplejo.end(), functor<double>());
}
