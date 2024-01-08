#include <math.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"
#include "utils.h"
#include "flop_counts.h"


#define max( a, b ) ( (a) > (b) ? (a) : (b) )
#define min( a, b ) ( (a) < (b) ? (a) : (b) )



// ============================================================================
// Declaration of local prototypes.

int test_read_info( 
    int * ndim, int ** mvalues, int ** nvalues, int ** kvalues,
    //// int * nnb, int ** mbvalues, int ** nbvalues,
    int * nexecs, int * print_data, int * check_result, 
    int * seed );

void print_result( char * name, int itest, int m, int n, int k, 
    double texec, double resid );

void data_generate( int m, int n, int k, double * a, int ldim_a, 
       double * b, int ldim_b, int seed );

double compute_residual( int m, int n, int k,
    double * a, int ldim_a, double * x, int ldim_x, double * b, int ldim_b );



// ============================================================================
int main( int argc, char *argv[] ) {
  int    ndim, idim, * mvalues, * nvalues, * kvalues, m, n, k,
         //// nnb, inb, * mbvalues, * nbvalues, mb, nb,
         nexecs, ne, info, print_data, check_result, seed[ 4 ],
         ldim_a, ldim_a_copy, ldim_b, ldim_b_copy, 
         mn, len_wk, itest;
  double t1, t2, ttotal, texec, normb, diff, resid, 
         d_zero = 0.0, d_one = 1.0, d_minus_one = -1.0,
         * a, * a_copy, * b, * b_copy, * wk, returned_wk;

  // Check the number of arguments.
  if ( argc != 1 ) {
    printf( "Usage:  %s\n\n", argv[0] );
    exit( -1 );
  }

  // Read the input arguments.
  info = test_read_info( & ndim, & mvalues, & nvalues, & kvalues,
             //// & nnb, & mbvalues, & nbvalues, 
             & nexecs, & print_data, & check_result, 
             seed );
  if( info != 0 ) {
    printf( "ERROR: a problem in test_read_info.\n" );
    exit( -1 );
  }

  printf( "%%\n" );
  printf( "%% Method                     m     n   " );
  printf( "  k       time       gflops  residual\n" );
  printf( "%% -------------------------------------" );
  printf( "----------------------------------------\n" );
 
  itest = 1; 
  for ( idim = 0; idim < ndim; idim++ ) {
    m = mvalues[ idim ];
    n = nvalues[ idim ];
    k = kvalues[ idim ];

    // ========================================================================
    // Create and generate data: matrices a, b, and c.
    // ========================================================================

    a      = ( double * ) malloc( m * n * sizeof( double ) ); 
    a_copy = ( double * ) malloc( m * n * sizeof( double ) ); 
    b      = ( double * ) malloc( m * k * sizeof( double ) ); 
    b_copy = ( double * ) malloc( m * k * sizeof( double ) ); 
    ldim_a      = m;
    ldim_a_copy = m;
    ldim_b      = m;
    ldim_b_copy = m;
    if( ( a == NULL )||( a_copy == NULL )||
        ( b == NULL )||( b_copy == NULL ) ) {
      printf( "ERROR: Not enough memory.\n" );
      exit( -1 );
    }
    data_generate( m, n, k, a, ldim_a, b, ldim_b, seed[ 0 ] );
    // Make a copy of both matrices since they are overwritten.
    dlacpy_( "All", & m, & n, a, & ldim_a, a_copy, & ldim_a_copy );
    dlacpy_( "All", & m, & k, b, & ldim_b, b_copy, & ldim_b_copy );

 
    // ========================================================================
    // Linear least-squares problem. Variant 1
    // ========================================================================

    // Print initial data.
    if( print_data == 1 ) {
      printf( "\n" );
      print_formatted_matrix( "aini", m, n, a, ldim_a );
      print_formatted_matrix( "bini", m, k, b, ldim_b );
      printf( "\n" );
    }
 
    // Time method.
    ttotal = 0.0;
    for ( ne = 0; ne < nexecs; ne++ ) {

      // Copy original data into a and b, since they are overwritten.
      dlacpy_( "All", & m, & n, a_copy, & ldim_a_copy, a, & ldim_a );
      dlacpy_( "All", & m, & k, b_copy, & ldim_b_copy, b, & ldim_b );

      // Set the workspace length.
      mn = min( m, n );
      len_wk = max( 1, mn + max( mn, k ) );
      //// printf( "Using workspace length: %d\n", len_wk );
      
      // Initial call to obtain workspace size
      int len_wk_opt=-1;
      double wkopt;
      int len_opt;
        // Allocate the workspace.
      //Initial call to obtain workspace size
      dgels_( "No transpose", & m, & n, & k, a, & ldim_a, b, & ldim_b, &wkopt, &len_wk_opt, & info );
      printf( "optimal value %d .\n", wkopt);
      len_opt= (int) wkopt;

      // Allocate the workspace.
      wk  = ( double * ) malloc( ( ( size_t ) len_opt ) * sizeof( double ) ); 
      if( wk == NULL ) {
        printf( "ERROR: Not enough memory.\n" );
        exit( -1 );
      }

      // Perform the computation.
      t1 = omp_get_wtime();
      dgels_( "No transpose", & m, & n, & k, a, & ldim_a, b, & ldim_b, wk, & len_opt, & info );
      t2 = omp_get_wtime();
  
      // Free workspace.
      free( wk );


    }
    ttotal += t2 - t1;
    texec = ttotal / ( ( double ) nexecs );

    // Print final data.
    if( print_data == 1 ) {
      print_formatted_matrix( "afin", m, n, a, ldim_a );
      print_formatted_matrix( "xfin", m, k, b, ldim_b );
      printf( "\n" );
    }

    // Compute residual: || A * X - B ||_F / || B ||_F.
    resid = compute_residual( m, n, k,
                a_copy, ldim_a_copy, b, ldim_b, b_copy, ldim_b_copy );

    // Print results.
    print_result( "llsp_var1", itest, m, n, k, texec, resid );


    // ========================================================================
    // Linear least-squares problem. Variant 2
    // ========================================================================

    // Print initial data.
    if( print_data == 1 ) {
      printf( "\n" );
      print_formatted_matrix( "aini", m, n, a, ldim_a );
      print_formatted_matrix( "bini", m, k, b, ldim_b );
      printf( "\n" );
    }
 
    // Time method.
    ttotal = 0.0;
    for ( ne = 0; ne < nexecs; ne++ ) {

      // Copy original data into a and b, since they are overwritten.
      dlacpy_( "All", & m, & n, a_copy, & ldim_a_copy, a, & ldim_a );
      dlacpy_( "All", & m, & k, b_copy, & ldim_b_copy, b, & ldim_b );

      // Set the workspace length.
      mn = min( m, n );
      len_wk = max( 1, mn + max( mn, k ) );
      //// printf( "Using workspace length: %d\n", len_wk );

      // Allocate the workspace.
      wk  = ( double * ) malloc( ( ( size_t ) len_wk ) * sizeof( double ) ); 
      if( wk == NULL ) {
        printf( "ERROR: Not enough memory.\n" );
        exit( -1 );
      }

      // Perform the computation.
      t1 = omp_get_wtime();
      dgels_( "No transpose", & m, & n, & k, a, & ldim_a, b, & ldim_b,
              wk, & len_wk, & info );
      t2 = omp_get_wtime();
  
      // Free workspace.
      free( wk );
    }
    ttotal += t2 - t1;
    texec = ttotal / ( ( double ) nexecs );

    // Print final data.
    if( print_data == 1 ) {
      print_formatted_matrix( "afin", m, n, a, ldim_a );
      print_formatted_matrix( "xfin", m, k, b, ldim_b );
      printf( "\n" );
    }

    // Compute residual: || A * X - B ||_F / || B ||_F.
    resid = compute_residual( m, n, k,
                a_copy, ldim_a_copy, b, ldim_b, b_copy, ldim_b_copy );

    // Print results.
    print_result( "llsp_var2", itest, m, n, k, texec, resid );



    // Remove dynamic data vectors.
    free( a );
    free( a_copy );
    free( b );
    free( b_copy );

    printf( "\n" );
    itest++;
  }

  // Remove dynamic vectors.
  free( mvalues );
  free( nvalues );
  free( kvalues );
  //// free( mbvalues );
  //// free( nbvalues );

  printf( "%% End of Program\n" );
  return 0;
}

// ============================================================================
int test_read_info( int * ndim, int ** mvalues, int ** nvalues, int ** kvalues,
    //// int * nnb, int ** mbvalues, int ** nbvalues,
    int * nexecs, int * print_data, int * check_result, 
    int * seed ) {
//
  const int MAX_LINE_LENGTH = 1024;
  FILE      * fp;
  char      myLine[ MAX_LINE_LENGTH ];
  int       i, rv;
  char      * rv_pc;

  // Open the file.
  if ( ( fp = fopen( "test.in", "r" ) ) == NULL )
    return -1;

  printf( "%%\n" );

  // Reading number of dimensions to test.
  rv = fscanf( fp, "%d", ndim );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  if( * ndim == 0 ) {
    printf( "ERROR: Number of dimensions is zero.\n" ); 
    return (-1);
  }

  // Creating the vectors to hold the dimensions.
  *mvalues = (int *) malloc( *ndim * sizeof( int ) );
  *nvalues = (int *) malloc( *ndim * sizeof( int ) );
  *kvalues = (int *) malloc( *ndim * sizeof( int ) );

  // Reading the dimensions "m".
  for( i = 0; i < * ndim; i++ ) {
    rv = fscanf( fp, "%d", (*mvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Reading the dimensions "n".
  for( i = 0; i < * ndim; i++ ) {
    rv = fscanf( fp, "%d", (*nvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Reading the dimensions "k".
  for( i = 0; i < * ndim; i++ ) {
    rv = fscanf( fp, "%d", (*kvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Write the dimensions.
  printf( "%% Test %d dimensions:\n", * ndim );
  printf( "%%   m: " );
  for( i = 0; i < * ndim; i++ ) {
    printf( "%4d ", *(*mvalues+i) );
  }
  printf( "\n" );

  printf( "%%   n: " );
  for( i = 0; i < * ndim; i++ ) {
    printf( "%4d ", *(*nvalues+i) );
  }
  printf( "\n" );

  printf( "%%   k: " );
  for( i = 0; i < * ndim; i++ ) {
    printf( "%4d ", *(*kvalues+i) );
  }
  printf( "\n" );

#if 0
  // Reading number of block sizes to test.
  rv = fscanf( fp, "%d", nnb );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  if( * nnb == 0 ) {
    printf( "ERROR: Number of block sizes is zero.\n" ); 
    return (-1);
  }

  // Creating the vectors to hold the dimensions.
  *mbvalues = (int *) malloc( *nnb * sizeof( int ) );
  *nbvalues = (int *) malloc( *nnb * sizeof( int ) );

  // Reading the block sizes "mb".
  for( i = 0; i < * nnb; i++ ) {
    rv = fscanf( fp, "%d", (*mbvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );

  // Reading the block sizes "nb".
  for( i = 0; i < * nnb; i++ ) {
    rv = fscanf( fp, "%d", (*nbvalues+i) );
  }
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
#endif


  // Reading the number of executions.
  rv = fscanf (fp, "%d", nexecs );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  printf( "%% nexecs:          %d\n", * nexecs );

  // Reading whether print data.
  rv = fscanf( fp, "%d", print_data );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  printf( "%% print_data:      %d\n", * print_data );

  // Reading whether check result.
  rv = fscanf( fp, "%d", check_result );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  printf( "%% check_result:    %d\n", * check_result );

  // Reading seeds. Last value must be odd.
  rv = fscanf( fp, "%d", seed );
  rv = fscanf( fp, "%d", seed+1 );
  rv = fscanf( fp, "%d", seed+2 );
  rv = fscanf( fp, "%d", seed+3 );
  rv_pc = fgets( myLine, MAX_LINE_LENGTH, fp );
  if( *( seed+3 ) % 2 == 0 ) {
    printf( "ERROR: Last value of seeds must be odd.\n" ); 
    return (-1);
  }
  printf( "%% Seeds:           %d %d %d %d\n",
          *seed, *(seed+1), *(seed+2), *(seed+3) );

  // Close the file.
  fclose( fp );

  return 0;
}

// ============================================================================
void print_result( char * name, int itest, int m, int n, int k, 
    double texec, double resid ) {
//
  double flops, gflops;

  // Compute gigaflops per second.
  flops = flops_compute_dense_QR( m, n ) + 
          flops_apply_left_Qt_of_dense_QR( m, n, k ) + 
          flops_trsm( m, n, k );
  if( texec != 0.0 ) {
    gflops = flops / ( texec * 1.0e9 );
  } else {
    gflops = -1.0;
  }

  printf( "%-12s ( %2d, 1:6 )=[ %5d %5d %5d %11.3e %9.2lf %8.1le ];\n", 
          name, itest, m, n, k, texec, gflops, resid );
  fflush( stdout );
}

// ============================================================================
void data_generate( int m, int n, int k, double * a, int ldim_a, 
       double * b, int ldim_b, int seed ) {
//
  int    ldim_x;
  double * x, d_one = 1.0, d_zero = 0.0;

  // Allocate auxiliary X.
  x = malloc( ( ( size_t ) n ) * 
              ( ( size_t ) k ) * sizeof( double ) );
  ldim_x = n;
  if( x == NULL ) {
    printf( "ERROR: Not enough memory.\n" );
    exit( -1 );
  }

  // Generate A and X.
  matrix_generate( m, n, a, ldim_a, seed );
  matrix_generate( n, k, x, ldim_x, seed + 1 );

  // Compute:  B = A * X.
  dgemm_( "No transpose", "No transpose", & m, & k, & n, 
          & d_one, a, & ldim_a, x, & ldim_x,
          & d_zero, b, & ldim_b );

  // Free auxiliary X.
  free( x );

  //// print_formatted_matrix( "aini0", m, n, a, ldim_a );
  //// print_formatted_matrix( "xini0", m, k, x, ldim_x );
  //// print_formatted_matrix( "bini0", m, k, b, ldim_b );
}
 
// ============================================================================
double compute_residual( int m, int n, int k,
    double * a, int ldim_a, double * x, int ldim_x, double * b, int ldim_b ) {
// Compute residual: || A * X - B ||_F / || B ||_F.
// Matrices a, x, and b are not overwritten.
  double norm_b, norm_diff, resid, d_one = 1.0, d_minus_one = -1.0,
         * diff;
  int    ldim_diff;
  double dlange_();

  // Allocate auxiliary matrix DIF.
  diff = malloc( ( ( size_t ) m ) * 
                 ( ( size_t ) k ) * sizeof( double ) );
  ldim_diff = m;
  if( diff == NULL ) {
    printf( "ERROR: Not enough memory.\n" );
    exit( -1 );
  }

  // Compute norm of B.
  norm_b = dlange_( "F", & m, & k, b, & ldim_b, NULL );

  // Compute:  DIF = A X - B.
  dlacpy_( "All", & m, & k, b, & ldim_b, diff, & ldim_diff );
  dgemm_( "No transpose", "No transpose", & m, & k, & n, 
          & d_minus_one, a, & ldim_a, x, & ldim_x,
          & d_one, diff, & ldim_diff );

  // Compute norm of DIF.
  norm_diff = dlange_( "F", & m, & k, diff, & ldim_diff, NULL );
  if( norm_b != 0.0 ) {
    resid = norm_diff / norm_b;
  } else {
    resid = -1.0;
  }

  //// print_formatted_matrix( "dif_a", m, n, a, ldim_a );
  //// print_formatted_matrix( "dif_b", m, k, b, ldim_b );
  //// print_formatted_matrix( "dif", m, k, diff, ldim_diff );

  // Free auxiliary X.
  free( diff );

  return resid;
}


