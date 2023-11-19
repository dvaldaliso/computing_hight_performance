#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int isprime(int n) {
 if (n<2) return 0;
 int m = (int)sqrt(n);
 //Es hasta la raiz cuadrada del numero que se quiere saber si es primo
 for (int j=2; j<=m; j++)
 if (n % j==0) return 0;
 return 1;
 }
void main(int argc, char **argv){
int N=5;
/* Extracción de argumentos */
  if (argc > 1) { /* El usuario ha indicado el valor de N */
     if ((N = atoi(argv[1])) < 0) N = 50;
  }
  int isPrime=isprime(N); 
  char result=isPrime?"Is primo":"No es primo";
  printf("%s\n",result);
 
}