#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Funcion f(x) de la cual se quiere calcular la integral */
double f(double x)
{
   //return pow(10*x-14.0/3.0,3)-150*x+120;
   return M_PI/2.0*sin(x*M_PI);
}

/* Calculo de la integral de la funcion f */
double calcula_integral(double a, double b, int n)
{
   double h, s=0, result;
   int i;

   h=(b-a)/n;

   #pragma omp parallel for reduction(+:s)
   for (i=0; i<n; i++) {
      s+=f(a+h*(i+0.5));
   }

   result = h*s;
   return result;
}

int main(int argc, char *argv[])
{
   double a, b, result;
   int n;

   if (argc>1) n=atoi(argv[1]);
   else n=1000;
   a=0;
   b=1;

   result = calcula_integral(a,b,n);

   printf("Valor de la integral = %.12f\n", result);

   return 0;
}
