#include <iostream>
#include <ostream>   
using namespace std;
template < typename T >
class NumeroR2
{
private:
        T x;
        T y;
public:
        NumeroR2();//Declaracion Constructor con valores por default 0,0
        NumeroR2(T x, T y);//Declaracion Constructor con valores seteados
        NumeroR2 (NumeroR2<T>& copy); // Constructor para Crear una copia
        T getX() const;// Obetener la x
        T getY() const;//Obtener la y
        void setX(T x);// Obetener la x
        void setY(T y);//Obtener la y
        //Declaracion de sobrecarga de operador para impirmir
        template<typename m> 
        friend ostream& operator <<( ostream& ,const NumeroR2<m>&);
        /* function friend: es una funcion que no pertenece a la clase,
         pero que tiene permiso para acceder a sus variables y funciones miembro privadas 
         por medio de los operadores punto (.) y flecha (->)
        */
       // Declaracion de Sobrecarga del operador +=
        NumeroR2<T>& operator +=(const NumeroR2<T>&);

        // Declaracion de Sobrecarga del operador -=
        NumeroR2<T>& operator -=(const NumeroR2<T>&);

        // Declaracion de Sobrecarga del operador +
         NumeroR2<T> operator +(const NumeroR2<T>&);

         // Declaracion de Sobrecarga del operador -
         NumeroR2<T> operator -(const NumeroR2<T>&);

         //Declaracion de Sobrecarga del operador de post-incremento (a++)
         NumeroR2<T> operator ++(int);

         //Declaracion de Sobrecarga del operador de pre-incremento (++a)
         NumeroR2<T>& operator ++();

          //Declaracion de Sobrecarga del operador de post-disminucion (a++)
         NumeroR2<T> operator --(int);

         //Declaracion de Sobrecarga del operador de pre-disminucion (++a)
         NumeroR2<T>& operator --();
         
         //Declaracion de Sobrecarga del operador =
         NumeroR2<T>& operator =( const NumeroR2<T>& );


        


};
//Esto se llama inline: implementar los metodos fuera de la clase

//Implementacion de constructor con valores por default 0,0
template < typename T >
NumeroR2<T>::NumeroR2(): x{0.0}, y{0.0} {} 

//Implementacion de constructor con valores seteados
template < typename T >
NumeroR2<T>::NumeroR2(T x, T y): x{x}, y{y} {}

//Implementacion de constructor para Crear una copia
template < typename T >
NumeroR2<T>::NumeroR2(NumeroR2<T>& copy): x{copy.x}, y{copy.y} {}

//Obtener la x
template < typename T >
T NumeroR2<T>::getX() const {
    return this->x;
}

//Obtener la y
template < typename T >
T NumeroR2<T>::getY() const {
    return this->y;
}
//Modificar x
template <typename T>
void NumeroR2<T>:: setX(T x){
    this->x = x;
}

//Modificar y
template <typename T>
void NumeroR2<T>:: setY(T y){
    this->y = y;
}
//Implementacion de sobrecarga de operador para impirmir
template <typename m>
ostream& operator <<( ostream& os, const NumeroR2<m>& numeroR2 )  {
    os << "(" << numeroR2.x << "," << numeroR2.y << ")";
    return os;
}
// Implementacion de sobrecarga del operador +=
template <typename T>
NumeroR2<T>& NumeroR2<T> :: operator +=( const NumeroR2<T>& numeroR2 ) {
        this->x+=numeroR2.x;
        this->y+=numeroR2.y;
    return *this;
}

// Implementacion de Sobrecarga del operador -=
template <typename T>
NumeroR2<T>& NumeroR2<T> :: operator -=( const NumeroR2<T>& numeroR2 ) {
        this->x-=numeroR2.x;
        this->y-=numeroR2.y;
    return *this;
}

//Implementacion de Sobrecarga del operador +
template <typename T>
NumeroR2<T> NumeroR2<T> :: operator +(const NumeroR2<T>& numeroR2 ) {
    NumeroR2<T> n(this->x+numeroR2.x,
                this->y+numeroR2.y);
    return n;
}

//Implementacion Sobrecarga del operador -
template <typename T>
NumeroR2<T> NumeroR2<T> :: operator -(const NumeroR2<T>& numeroR2 ) {
    NumeroR2<T> n(this->x-numeroR2.x,
                this->y-numeroR2.y);
    return n;
}

//Implementacion Sobrecarga del operador de post-incremento (a++)
// Se asigna y luego incrementa
template <typename T>
NumeroR2<T> NumeroR2<T> :: operator ++(int) {
        NumeroR2<T> temp = *this;
        x++;
        y++;                // Incrementa el valor del objeto original
        return temp;
}

//Implementacion Sobrecarga del operador de pre-incremento (++a)
// Se incrementa y luego se asigna
template <typename T>
NumeroR2<T>& NumeroR2<T> :: operator ++() {
        this->x ++;
        this->y ++;
    return *this;
}

// Implementacion Sobrecarga del operador de post-disminucion (a--)
// Se asigna y luego incrementa
template <typename T>
NumeroR2<T> NumeroR2<T> :: operator --(int) {
        NumeroR2<T> temp = *this;
        x--;
        y--;                // Incrementa el valor del objeto original
        return temp;
}

//Implementacion Sobrecarga del operador de pre-disminucion (--a)
// Se decrementa y luego se asigna
template <typename T>
NumeroR2<T>& NumeroR2<T> :: operator --() {
        this->x--;
        this->y--;
    return *this;
}

//Implementacion Sobrecarga del operador =
template <typename T>
NumeroR2<T>& NumeroR2<T> :: operator =( const NumeroR2<T>& copy ) {
        this->x=copy.x;
        this->y=copy.y;
  return *this ;
}
