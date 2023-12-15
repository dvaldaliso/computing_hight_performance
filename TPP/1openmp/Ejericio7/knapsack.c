
/* 
 * Problema de la mochila.
 * Versión con algoritmo de backtracking
 *
 * Pedro Alonso
 * septiembre 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include "ctimer.h"

int *w;
double *p;

/** @brief Algoritmo para resolver el problema de la mochila.
 *  @param piedras (input): Cantidad de piedras disponibles. 
 *  @param c (input):       Capacidad de la mochila.
 *
 *  @return: Valor alcanzado por la mochila. 
 *
 *  Parámetros externos referenciados por esta función:
 *  @param w (input):       Array con los pesos de n piedras.
 *  @param p (input):       Array con los valores de n piedras.
 */

double knapsack( int piedras, int c ) {
  double valor;
  if( c < 0 ) { /* Si ha excedido la capacidad de la mochila */
    valor = -DBL_MAX;
  } else {
    if( piedras == 0 ) { /* Si no hay piedras con las que probar */
      valor = 0;
    } else {
      piedras--;
      double valor_sin_piedra, valor_con_piedra;
      valor_sin_piedra = knapsack( piedras, c );
      valor_con_piedra = knapsack( piedras, c-w[piedras] ) + p[piedras];
      valor = valor_sin_piedra > valor_con_piedra ?  valor_sin_piedra : valor_con_piedra;
    }
  }
  return valor;
}

/** @brief Algoritmo para resolver el problema de la mochila.
 *  @param piedras (input): Cantidad de piedras disponibles. 
 *  @param c (input):       Capacidad de la mochila.
 *  @param valor (output):  Valor alcanzado por la mochila. 
 *  @param s (output):      Array de piedras (1 si la piedra está en la mochila, 0 en caso contrario).
 *
 *  Parámetros externos referenciados por esta función:
 *  @param w (input):       Array con los pesos de n piedras.
 *  @param p (input):       Array con los valores de n piedras.
 */

void knapsackv( int piedras, int c, double *valor, int s[] ) {
  if( c < 0 ) { /* Si ha excedido la capacidad de la mochila */
    *valor = -DBL_MAX;
  } else {
    if( piedras == 0 ) { /* Si no hay piedras con las que probar */
      *valor = 0;
    } else {
      piedras--;
      double valor_sin_piedra;
      knapsackv( piedras, c, &valor_sin_piedra, s );
      double valor_con_piedra;
      int s1[piedras];
      knapsackv( piedras, c-w[piedras], &valor_con_piedra, s1 );
      valor_con_piedra += p[piedras];
      if( valor_sin_piedra > valor_con_piedra ) {
        *valor = valor_sin_piedra;
        s[piedras] = 0;
      } else {
        *valor = valor_con_piedra;
        for( int i=0; i<piedras; i++ ) s[i] = s1[i];
        s[piedras] = 1;
      }
    }
  }
}

int main( int argc, char *argv[] ) {
  if( argc<3 ) {
    fprintf(stderr,"Uso: %s piedras capacidad [vector_solución(si/no)] \n",argv[0]);
    return -1;
  }
  double valor;
  int capacidad;
  int n, c;
  sscanf(argv[1],"%d",&n);
  sscanf(argv[2],"%d",&c);
  printf("Problema de la mochila con %d piedras y capacidad = %d\n",n,c);
  w = (int*) malloc(n*sizeof(int));
  p = (double*) malloc(n*sizeof(double));
  int solucion[n];

  /* Generando pesos y valores aleatoriamente */
  for( int i=0; i<n; i++ ) {
    w[i] = rand() % 10;
    p[i] = (double) rand() / RAND_MAX;
  }
#ifdef CHECK
  printf("Pesos = [");
  for( int i=0; i<n; i++ ) {
    printf("%5d",w[i]);
  }
  printf("   ]\n");
  printf("Valores = [");
  for( int i=0; i<n; i++ ) {
    printf("%6.2f",p[i]);
  }
  printf("   ]\n");
#endif

  double elapsed, ucpu, scpu;

  printf("Computando por backtracking...\n");
  valor = 0;
  capacidad = c;
  bool vector = argc > 3 && !strcmp(argv[3],"si") ? true : false;
  if( vector ) memset(solucion,0,n*sizeof(int));
  ctimer( &elapsed, &ucpu, &scpu );
  if( vector ) 
    knapsackv( n, c, &valor, solucion );
  else valor = knapsack( n, c );
  ctimer( &elapsed, &ucpu, &scpu );

#ifdef CHECK
  if( vector ) {
    printf("Solucion = [");
    for( int i=0; i<n; i++ ) {
      printf("%2d",solucion[i]);
    }
    printf(" ]\n");
  }
#endif
  printf("Valor = %f\n",valor);
  if( vector ) {
    int peso = 0;
    for( int i=0; i<n; i++ ) peso += solucion[i]?w[i]:0;
    printf("Capacidad restante = %d\n",capacidad-peso);
  }
  printf("Tiempo: %g s\n",elapsed);

  free(w);
  free(p);
  return 0;
}

