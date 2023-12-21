#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>


double d_mono_clock( void );

#if 0
double etime( void );

double dsecnd(void );
#endif

int rnd_uniform_int( int n );

double rnd_uniform_double( void );

double rnd_uniform_double_between_1and1( void );

void vector_generate( int n, double * x, int seed );

void matrix_generate( int m, int n, double * a, int ldim_a, int seed );

void print_vector( char * name, int n, double * x );

void print_matrix( char * name, int m, int n, double * a, int ldim_a );

void print_formatted_matrix( char * name, int m, int n, 
    double * a, int ldim_a );

double vector_diff( int n, double * x, double * y );

void vector_set_to_zero( int n, double * x );

void copy_matrix( int m, int n, 
    double * a, int ldim_a, double * b, int ldim_b );

double matrix_diff( int m, int n, 
    double * a, int ldim_a, double * b, int ldim_b );


