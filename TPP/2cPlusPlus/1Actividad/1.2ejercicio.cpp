#include <iostream>
using namespace std;
 
int main(){
   //Ejercicio2
   int e = 5;
   int *p = &e;
   int &r = e;

   *p=13; 
   // r=32;
   cout <<"valor de e: " << e << endl; 
   cout <<"valor del puntero p: " << *p << endl; 
   cout <<"valor de la referencia r: " << r << endl; 
   
}