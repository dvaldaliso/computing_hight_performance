#include <iostream>
#include <ostream>   
using namespace std;
//compilacion -> g++ -o actividad3 actividad3.cpp

/* El código desarrollado en la Actividad 3 debe funcionar con el siguiente programa principal. */
/* Si el código está correcto mostrará lo siguiente */
/* a = ( 12, 0 )            */
/* b = ( 0, -11 )           */
/* c = ( 0, 0 )             */
/* d = ( 12, 0 )            */
/* a += b es ( 12, -11 )    */
/* c = ( 12, -22 )          */
/* c = b -a es ( -12, 0 )   */
/* c++ es ( -12, 0 )        */
/* ++c es ( -10, 2 )        */
/* ++a es ( 13, -10 )       */
/* a++ es ( 13, -10 )       */
/* --a es ( 13, -10 )       */
/* a-- es ( 13, -10 )       */
/* b = a-- es ( 0, -11 )    */
/* b = --a es ( 0, -11 )    */
class NumeroR2
{
private:
        double x;
        double y;
public:
        NumeroR2();
        NumeroR2(double x, double y) ;
        NumeroR2 ( NumeroR2& copy );
        ~NumeroR2();

        //Operador para impirmir
        friend ostream& operator <<( ostream& ,const NumeroR2& );
        /* function friend: es una funcion que no pertenece a la clase,
         pero que tiene permiso para acceder a sus variables y funciones miembro privadas 
         por medio de los operadores punto (.) y flecha (->)
        */

        // Sobrecarga del operador +=
        NumeroR2& operator +=(const NumeroR2&);

        // Sobrecarga del operador -=
        NumeroR2& operator -=(const NumeroR2&);
         
         // Sobrecarga del operador +
         NumeroR2 operator +(const NumeroR2&);

         // Sobrecarga del operador -
         NumeroR2 operator -(const NumeroR2&);

         // Sobrecarga del operador de post-incremento (a++)
         NumeroR2 operator ++(int);

        // Sobrecarga del operador de pre-incremento (++a)
         NumeroR2& operator ++();

        // Sobrecarga del operador de post-disminucion (a++)
         NumeroR2 operator --(int);

        // Sobrecarga del operador de pre-disminucion (++a)
         NumeroR2& operator --();
         
         // Sobrecarga del operador =
         NumeroR2& operator =( const NumeroR2& );
};
//Constructor con valores por default 0,0
NumeroR2::NumeroR2(): x{0.0}, y{0.0} {} 

//Constructor con valores seteados
NumeroR2::NumeroR2(double x, double y): x{x}, y{y} {}

// Constructor para Crear una copia
NumeroR2::NumeroR2(NumeroR2& copy): x{copy.x}, y{copy.y} {}

//Operador para impirmir
ostream& operator <<( ostream& os, const NumeroR2& numeroR2 )  {
    os << "(" << numeroR2.x << "," << numeroR2.y << ")";
    return os;
}

// Sobrecarga del operador +=
NumeroR2& NumeroR2 :: operator +=( const NumeroR2& numeroR2 ) {
        this->x+=numeroR2.x;
        this->y+=numeroR2.y;
    return *this;
}
// Sobrecarga del operador -=
NumeroR2& NumeroR2 :: operator -=( const NumeroR2& numeroR2 ) {
        this->x-=numeroR2.x;
        this->y-=numeroR2.y;
    return *this;
}

// Sobrecarga del operador +
NumeroR2 NumeroR2 :: operator +(const NumeroR2& numeroR2 ) {
    NumeroR2 n(this->x+numeroR2.x,
                this->y+numeroR2.y);
    return n;
}
//Se usan flechas para acceder a la variable porque es una referencia; O podemos usarlo como los dos ejemplos anteriores.
// Sobrecarga del operador -
NumeroR2 NumeroR2 :: operator -(const NumeroR2& numeroR2 ) {
    NumeroR2 n(this->x-numeroR2.x,
                this->y-numeroR2.y);
    return n;
}
// Sobrecarga del operador de post-incremento (a++)
// Se asigna y luego incrementa
NumeroR2 NumeroR2 :: operator ++(int) {
        NumeroR2 temp = *this;
        x++;
        y++;                // Incrementa el valor del objeto original
        return temp;
}

// Sobrecarga del operador de pre-incremento (++a)
// Se incrementa y luego se asigna
NumeroR2& NumeroR2 :: operator ++() {
        this->x ++;
        this->y ++;
    return *this;
}

// Sobrecarga del operador de post-disminucion (a--)
// Se asigna y luego incrementa
NumeroR2 NumeroR2 :: operator --(int) {
        NumeroR2 temp = *this;
        x--;
        y--;                // Incrementa el valor del objeto original
        return temp;
}

// Sobrecarga del operador de pre-disminucion (--a)
// Se incrementa y luego se asigna
NumeroR2& NumeroR2 :: operator --() {
        this->x--;
        this->y--;
    return *this;
}
// Sobrecarga del operador =
NumeroR2& NumeroR2 :: operator =( const NumeroR2& copy ) {
        this->x=copy.x;
        this->y=copy.y;
  return *this ;
}



NumeroR2::~NumeroR2()
{
}

int main( int argc, char *argv[] ) {
  
  NumeroR2 a( 12.0, 0.0 ), b( 0.0, -11.0 ), c, d(a);
  
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  cout << "d = " << d << endl;

  a += b;
  cout << "a += b es " << a << endl;

 
  c = a + b;
  cout << "c = a + b = " << c << endl;

  c = b - a;
  cout << "c = b - a = " << c << endl;

  cout << "c++ es " << c++ << endl;
  cout << "++c es " << ++c << endl;
  cout << "++a es " << ++a << endl;
  cout << "a++ es " << a++ << endl;
  cout << "--a es " << --a << endl;
  cout << "a-- es " << a-- << endl;

  cout << "b = a-- es " << b << endl;
  cout << "b = --a es " << b << endl;

}
