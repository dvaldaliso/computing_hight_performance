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
#include <iostream>
using namespace std;

class NumeroR2(){
//1.
	private:
		double a; // Atributo q representa numero real
		double b; // Atributo q representa numero real
	public:

		NumeroR2() : a(0.0),b(0.0){} //Constructor por defecto inicializando valores a 0.
		NumeroR2(double c, double d) : a(c), b(d){} //El constructor que recibe como argumento
							//dos números reales que serán las componentes del número.
		NumeroR2(const NumeroR2 copia); // Constructor de copia
//2. Implementar el operador << en primer lugar para poder ir comprobando en la salida la implementación de cada método u operador.
		friend ostream& operator<<(ostream& os, const NumeroR2& numero);
//3. Implementar las operaciones aritméticas habituales de los números sobrecargando los operadores correspondientes:
	// Operador +=
	NumeroR2& operator+=(const NumeroR2& copia) {
		x += copia.a;
		y += copia.b;
		return *this;
	}
	// Operador -=
	NumeroR2& operator-=(const NumeroR2& copia) {
                x -= copia.a;
                y -= copia.b;
                return *this;
        }
	// Operador +
	NumeroR2& operator+(const NumeroR2& copia) {
		return NumeroR2(x + copia.x, y + copia.y);
        }
	// Operador -
	NumeroR2& operator-(const NumeroR2& copia) {
		return NumeroR2(x - copia.x, y - copia.y);
        }
	// Operador ++
	NumeroR2& operator++() {
                ++x;
                ++y;
                return *this;
        }
	// Operador --
	NumeroR2& operator--() {
                --x;
                --y;
                return *this;
        }
	// Operador =
/*	NumeroR2& operator=( const NumeroR2& copia) {
                return (copia.x, copia.y);
        }*/
};

NumeroR2 :: NumeroR2 ( const NumeroR2 & copia ) {
become ( copia.a, copia.b); // NO SE SI ESTARÁ BIEN. Constructor de copia.
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

