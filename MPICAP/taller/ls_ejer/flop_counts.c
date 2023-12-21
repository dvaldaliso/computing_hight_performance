// ============================================================================
// flop_counts:
//   Version:  0.07
//   Date:     2021-01-04
// ============================================================================
#include <stdio.h>
#include <assert.h>
#include "flop_counts.h"

#define min( a, b ) ( (a) < (b) ? (a) : (b) )

#undef SHOW_RATIOS


// ============================================================================
// Declaration of local macros and prototypes.

//// #define THRESHOLD 1.60
#define THRESHOLD 2.00


// ============================================================================
double flops_compute_dense_QR( int m, int n ) {
  double  num_flops, d_m, d_n, d_k;
#ifdef SHOW_RATIOS
  int     i;
  double  num_flops2, d_i, maxi, mini, ratio;
  int     min_mn;
#endif

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = min( d_m, d_n );
  //// // Expression for m >= n.
  //// num_flops = 2.0 * d_m * d_n * d_n - 2.0 * d_n * d_n * d_n / 3.0;
  // General expression, where k = min(m,n).
  num_flops = 4.0 * d_m * d_n * d_k 
              - 2.0 * d_k * d_k * ( d_m + d_n ) 
              + d_k * d_k * d_k * 4.0 / 3.0;

#ifdef SHOW_RATIOS
  min_mn = min( m, n );
  num_flops2 = 0.0;
  for( i = 0; i < min_mn; i++ ) {
    d_i = ( double ) i;
    num_flops2 += 4.0 * ( d_m - d_i ) * ( d_n - d_i );
  }
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  printf( "%% Ratio1: %5d %5d       %le \n", m, n, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}

// ============================================================================
double flops_apply_left_Qt_of_dense_QR( int m, int n, int k ) {
  double  num_flops, d_m, d_n, d_k;
#ifdef SHOW_RATIOS
  int     i;
  double  num_flops2, d_i, maxi, mini, ratio;
#endif

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = ( double ) k;
  num_flops = 4.0 * d_m * d_n * d_k - 2.0 * d_k * d_k * d_n;

#ifdef SHOW_RATIOS
  num_flops2 = 0.0;
  for( i = 0; i < k; i++ ) {
    d_i = ( double ) i;
    num_flops2 += 4.0 * ( d_m - d_i ) * d_n;
  }
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  printf( "%% Ratio2: %5d %5d %5d %le \n", m, n, k, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}

// ============================================================================
double flops_apply_right_Q_of_dense_QR( int m, int n, int k ) {
  double  num_flops, d_m, d_n, d_k;
#ifdef SHOW_RATIOS
  int     i;
  double  num_flops2, d_i, maxi, mini, ratio;
#endif

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = ( double ) k;
  num_flops = 4.0 * d_m * d_n * d_k - 2.0 * d_k * d_k * d_m;

#ifdef SHOW_RATIOS
  num_flops2 = 0.0;
  for( i = 0; i < k; i++ ) {
    d_i = ( double ) i;
    num_flops2 += 4.0 * d_m * ( d_n - d_i );
  }
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  printf( "num_flops:  %le\n", num_flops );
  printf( "num_flops2: %le\n", num_flops2 );
  printf( "%% Ratio3: %5d %5d %5d %le \n", m, n, k, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}


// ============================================================================
double flops_compute_td_QR( int m, int n ) {
  double  num_flops, d_m, d_n;
#ifdef SHOW_RATIOS
  int     k, i;
  double  num_flops2, maxi, mini, ratio, d_i;
#endif

  d_m = ( double ) m;
  d_n = ( double ) n;
  num_flops = 4.0 * d_m * d_n * d_n - 2.0 * d_m * d_n * d_n;

#ifdef SHOW_RATIOS
  num_flops2 = 0.0;
  k = min( m, n );
  for( i = 0; i < n; i++ ) {
    d_i = ( double ) i;
    num_flops2 += 4.0 * d_m * ( d_n - d_i );
  }
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  //// printf( "m,n: %d %d\n", m, n );
  //// printf( "num_flops: %le\n", num_flops );
  //// printf( "num_flops2: %le\n", num_flops2 );
  printf( "%% Ratio4: %5d %5d       %le \n", m, n, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}

// ============================================================================
double flops_apply_left_Qt_of_td_QR( int m, int n, int k ) {
  double  num_flops, d_m, d_n, d_k;
#ifdef SHOW_RATIOS
  int     i;
  double  num_flops2, maxi, mini, ratio;
#endif

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = ( double ) k;
  num_flops = 4.0 * d_m * d_n * d_k;

#ifdef SHOW_RATIOS
  num_flops2 = 0.0;
  for( i = 0; i < k; i++ ) {
    num_flops2 += 4.0 * d_m * d_n;
  }
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  printf( "%% Ratio5: %5d %5d %5d %le \n", m, n, k, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}

// ============================================================================
double flops_apply_right_Q_of_td_QR( int m, int n, int k ) {
  double  num_flops, d_m, d_n, d_k;
#ifdef SHOW_RATIOS
  int     i;
  double  num_flops2, maxi, mini, ratio;
#endif

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = ( double ) k;
  num_flops = 4.0 * d_m * d_n * d_k;

#ifdef SHOW_RATIOS
  num_flops2 = 0.0;
  for( i = 0; i < k; i++ ) {
    num_flops2 += 4.0 * d_m * d_n;
  }
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  printf( "%% Ratio6: %5d %5d %5d %le \n", m, n, k, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}


// ============================================================================
double flops_trsm( int m, int n, int k ) {
  double  num_flops, d_m, d_n, d_k;

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = ( double ) k;
  num_flops = d_m * d_n * d_k;

  assert( num_flops >= 0.0 );
  return  num_flops;
}

// ============================================================================
double flops_gemm( int m, int n, int k ) {
  double  num_flops, d_m, d_n, d_k;

  d_m = ( double ) m;
  d_n = ( double ) n;
  d_k = ( double ) k;
  num_flops = 2.0 * d_m * d_n * d_k;

  assert( num_flops >= 0.0 );
  return num_flops;
}


// ============================================================================
double flops_utv( int m, int n, int q ) {
  double  num_flops;
#ifdef SHOW_RATIOS
  int     i, nb, actual_nb;
  double  num_flops2, nf_gemm, maxi, mini, ratio;
  int     min_mn;
#endif

  if( q == 0 ) {
    num_flops = 3.0 * flops_compute_dense_QR( m, n );
  } else if( q == 1 ) {
    num_flops = 4.0 * flops_compute_dense_QR( m, n );
  } else if( q == 2 ) {
    num_flops = 5.0 * flops_compute_dense_QR( m, n );
  } else {
    num_flops = -1.0;
  }

#ifdef SHOW_RATIOS
  min_mn = min( m, n );
  num_flops2 = 0.0;
  nb = 32;
  for( i = 0; i < min_mn; i += nb ) {
    actual_nb = min( nb, min_mn - i );
    // Power iteration.
    num_flops2 += ( 1 + 2 * q ) * flops_gemm( m - i, n - i, actual_nb );
    // Right transformations.
    num_flops2 += flops_apply_right_Q_of_dense_QR( m, n - i, actual_nb );
    // Left transformations.
    num_flops2 += flops_apply_left_Qt_of_dense_QR( m - i, n - i, actual_nb );
  }
  printf( "num_flops:  %le\n", num_flops );
  printf( "num_flops2: %le\n", num_flops2 );
  maxi  = max( num_flops, num_flops2 );
  mini  = min( num_flops, num_flops2 );
  ratio = ( mini == 0.0 ? -1.0 : maxi / mini );
  printf( "%% Ratio7: %5d %5d       %le \n", m, n, ratio );
  assert( ( ratio == -1.0 )||( ratio < THRESHOLD ) );
#endif

  assert( num_flops >= 0.0 );
  return num_flops;
}


