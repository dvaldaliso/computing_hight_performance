// ============================================================================
// File utils.c:
//   Version:  0.02
//   Date:     2021-12-27
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#if 0
#include <sys/times.h>
#include <unistd.h>
#endif
#include "utils.h"


// ============================================================================
double d_mono_clock( void ) {
// Returns the time elapsed since some moment in the past.
  struct timespec ts;
  double          t;

  //// if( clock_gettime( CLOCK_MONOTONIC_COARSE, & ts ) == -1 ) {
  if( clock_gettime( CLOCK_MONOTONIC_RAW, & ts ) == -1 ) {
    perror( "ERROR in clock_gettime with CLOCK_MONOTONIC.\n" );
    exit( EXIT_FAILURE );
  }
  t = ( ( double ) ts.tv_sec ) + 1.0e-9 * ( ( double ) ts.tv_nsec );

  //// printf( "ts.tv_sec:   %ld\n", ts.tv_sec );
  //// printf( "ts.tv_nsec:  %ld\n", ts.tv_nsec );
  //// printf( "t:           %lf\n", t );

  return t;
}

#if 0
// ============================================================================
double etime( void ) {
// Returns the time elapsed since some moment in the past.
  clock_t     ct;
  struct tms  t;

  ct = times( & t );

  if ( ct == ( clock_t ) -1 ) {
    return 0.0;
  } else {
    return( ( ( double ) ct ) /
            ( ( double ) sysconf( _SC_CLK_TCK ) ) );
  }
}

// ============================================================================
double dsecnd( void ) {
// Returns the addition of the user and system time (elapsed since some 
// moment in the past) of the current process.
  clock_t     ct;
  struct tms  t;

  ct = times( & t );

  if ( ct == ( clock_t ) -1 ) {
    return 0.0;
  } else {
    return( ( ( double ) ( t.tms_utime + t.tms_stime ) ) /
            ( ( double ) sysconf( _SC_CLK_TCK ) ) );
  }
}
#endif

// ============================================================================
int rnd_uniform_int( int n ) {
// Generates a integer random number between 0 and n-1.
  // return (int) ( ((double) n) * ((double) rand()) / ( RAND_MAX + 1.0 ) );
  return rand() % n;
}

// ============================================================================
double rnd_uniform_double( void ) {
// Generates a double random number between 0.0 and 1.0.
  return ( ( double ) rand() ) / ( ( double ) RAND_MAX );
}

// ============================================================================
double rnd_uniform_double_between_1and1( void ) {
// Generates a double random number between -1.0 and 1.0.
  return ( ( double ) rand() ) / ( ( double ) RAND_MAX ) * 2.0 - 1.0;
}

// ============================================================================
void vector_generate( int n, double * x, int seed ) {
// Generates a vector "x" of doubles.
  int i;

  srand( seed );
  for( i = 0; i < n; i++ ) {
    x[ i ] = rnd_uniform_double_between_1and1();
  }
}

// ============================================================================
void matrix_generate( int m, int n, double * a, int ldim_a, int seed ) {
// Generates an m-by-n matrix "a" of doubles.
  int i, j;

  srand( seed );
  for( i = 0; i < m; i++ ) {
    for( j = 0; j < n; j++ ) {
      a[ i + j * ldim_a ] = rnd_uniform_double();
    }
  }
}

// ============================================================================
void print_vector( char * name, int n, double * x ) {
// Prints a vector "x" of doubles.
  int i;

  for( i = 0; i < n; i++ ) {
    printf( "%s( %d ) = %e\n", name, i+1, x[ i ] );
  }
}

// ============================================================================
void print_matrix( char * name, int m, int n, double * a, int ldim_a ) {
// Prints a matrix "a" of doubles.
  int i, j;

  for( i = 0; i < m; i++ ) {
    for( j = 0; j < n; j++ ) {
      printf( "%s( %d, %d ) = %e\n", name, i+1, j+1, a[ i + j * ldim_a ] );
    }
  }
}

// ============================================================================
void print_formatted_matrix( char * name, int m, int n, 
    double * a, int ldim_a ) {
// Prints a matrix "a" of doubles nicely formatted.
  int i, j;

  printf( "%s = [\n", name );
  for( i = 0; i < m; i++ ) {
    printf( "  " );
    for( j = 0; j < n; j++ ) {
      printf( "%e ", a[ i + j * ldim_a ] );
    }
    printf( "\n" );
  }
  printf( "];\n" );
}

// ============================================================================
double vector_diff( int n, double * x, double * y ) {
// Computes || x - y ||_2 / || y ||_2.
  double diff, nrmy, result;
  int    i;

  diff = 0.0;
  nrmy = 0.0;
  for( i = 0; i < n; i++ ) {
    diff += ( x[ i ] - y[ i ] )*( x[ i ] - y[ i ] );
    nrmy += y[ i ]*y[ i ];
  }

  if( nrmy == 0.0 ) {
    result = sqrt( diff );
  } else {
    result = sqrt( diff ) / sqrt( nrmy );
  }
  return result;
}

// ============================================================================
void vector_set_to_zero( int n, double * x ) {
// Sets vector x to zero.
  int    i;

  for( i = 0; i < n; i++ ) {
    x[ i ] = 0.0;
  }
}


// ============================================================================
void copy_matrix( int m, int n, 
    double * a, int ldim_a, double * b, int ldim_b ) {
// Copy a into b.
  int    i, j;

  for( i = 0; i < m; i++ ) {
    for( j = 0; j < n; j++ ) {
      b[ i + j * ldim_b ] = a[ i + j * ldim_a ];
    }
  }
}

// ============================================================================
double matrix_diff( int m, int n, 
    double * a, int ldim_a, double * b, int ldim_b ) {
// Computes || a - b ||_F / || a ||_F.
  double aij, bij, diff, nrma, result;
  int    i, j;

  diff = 0.0;
  nrma = 0.0;
  for( i = 0; i < m; i++ ) {
    for( j = 0; j < n; j++ ) {
      aij = a[ i + j * ldim_a ];
      bij = b[ i + j * ldim_b ];
      diff += ( aij - bij )*( aij - bij );
      nrma += aij * aij;
    }
  }

  if( nrma == 0.0 ) {
    result = sqrt( diff );
  } else {
    result = sqrt( diff ) / sqrt( nrma );
  }
  return result;
}




