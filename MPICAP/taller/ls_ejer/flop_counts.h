
double flops_compute_dense_QR( int m, int n );

double flops_apply_left_Qt_of_dense_QR( int m, int n, int k );

double flops_apply_right_Q_of_dense_QR( int m, int n, int k );


double flops_compute_td_QR( int m, int n );

double flops_apply_left_Qt_of_td_QR( int m, int n, int k );

double flops_apply_right_Q_of_td_QR( int m, int n, int k );


double flops_trsm( int m, int n, int k );

double flops_gemm( int m, int n, int k );


double flops_utv( int m, int n, int q );


