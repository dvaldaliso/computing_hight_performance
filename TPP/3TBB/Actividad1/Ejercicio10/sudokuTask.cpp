#include <stdio.h>
#include "sudoku.h"
#include "tbb/task_group.h"
using namespace std;
using namespace tbb;
// g++ -fopenmp -o sudoku sudoku.cpp init_sudoku.c libsudoku_knights.o ctimer.c
int main( int argc, char *argv[] ) {
  int mascara[81];
  int sol[81];
  int i, j;

  printf("sudoku inicial: \n");
  init_sudoku("normal",sol);
  prin_sudoku(sol);

  for( i = 1; i <= 9; i++ ) {
    for( j = 1; j <= 9; j++ ) {
       mascara(i,j) = sol(i,j) != 0;
    }
  }

  sudoku_sol( 1, 1, sol, mascara );

  return 0;
}

void sudoku_sol( int i, int j, int sol[81], int mascara[81] ) {
   int k;

   if( mascara(i, j) == 0 ) {
      for( k = 1; k <= 9; k++ ) {
         task_group g;
         sol( i, j ) = k;
         if( es_factible( i, j, sol ) ) {
            if( i == 9 && j == 9 ) {
               printf("Solucion: \n");
               prin_sudoku(sol);
            }
            if( i < 9 && j == 9 ) {
               g.run( [&]{sudoku_sol ( i+1, 1, sol, mascara );} );
            }
            if( i <= 9 && j < 9 ) {
                g.run( [&]{sudoku_sol ( i, j+1, sol, mascara );} );
            }
         }
         g.wait();
      }
      sol(i, j) = 0;
   } else {
      task_group g1;
      if( i == 9 && j == 9 ) {
         printf("Solucion: \n");
         prin_sudoku(sol);
      }
      if( i < 9 && j == 9 ) {
        g1.run( [&]{sudoku_sol ( i+1, 1, sol, mascara );} );
      }
      if( i <= 9 && j < 9 ) {
        g1.run( [&]{sudoku_sol (i , j+1, sol, mascara);} );
      }
	g1.wait();
   }
}
