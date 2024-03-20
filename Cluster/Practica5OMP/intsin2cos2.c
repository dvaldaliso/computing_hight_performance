
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  double area, integral, x;
  double inf, sup, inc;
  int i,n;
  
  if (argc != 4) {
    scanf("%lf\n",&inf);
    scanf("%lf\n",&sup);
    scanf("%d",&n);
//    printf ("Uso: integral inf sup n\n");
  } else {
    inf=atof(argv[1]);
    sup=atof(argv[2]);
    n=atof(argv[3]);
   }
//    printf ("inf %lf\n", inf);
//    printf ("sup %lf\n", sup);
//    printf ("n %d\n", n);


    inc=(sup-inf)/n;

    area = 0.0;
  
    x = inf;
    while(x<=sup) {
//	area += 4.0/(1.0+x*x);
//    printf ("%farea\n", area);
        area += sin(x)*sin(x)+cos(x)*cos(x);
//        area += (x*x*x*x*x)-(2*x*x*x*x)+(3*x*x*x)-(10*x*x)+5;
        x = x+inc;
	
      }
    integral = area*inc; 
    printf ("%f\n", integral);
//  }  
  return 0;
}
