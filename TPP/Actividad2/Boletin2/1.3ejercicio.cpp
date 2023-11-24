#include <iostream>
using namespace std;
 
 void asingar(int *p){//asignar puntero
     *p = 25;
 }
 void asingar(int &r){ // asignarReferencia
     r = 40;
 }
int main(){
   int e = 5;
   int *p = &e;
   int &r = e;

   
   *p=34;
   asingar(p);
   cout <<"valor de puntero pasado por funcion: " << *p << endl; 
   
   r=35;
   asingar(r);
   cout <<"valor de referencia pasado por referencia: " << r << endl; 

   
}