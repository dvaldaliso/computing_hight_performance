#include <iostream>
using namespace std;
 
 void asingar(int *p){//asignar puntero
     *p = 25;
 }
 void asingar(int &r){ // asignarReferencia
     r = 40;
 }
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
   
   //Ejercicio3
   *p=34;
   asingar(p);
   cout <<"valor de puntero pasado por funcion: " << *p << endl; 
   
   r=35;
   asingar(r);
   cout <<"valor de referencia pasado por referencia: " << r << endl; 

   
}