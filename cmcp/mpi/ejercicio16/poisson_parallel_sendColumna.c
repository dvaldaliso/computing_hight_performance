#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

void parallel_jacobi_step(int N, int mlocal, double *x, double *b, double *t, double *local_sum, int rank, int size, MPI_Datatype coltype) {
    int i, j, ld = mlocal + 2;
    
    double local_s = 0.0;
    int right = rank + 1;
    int left = rank - 1;
    
    if (rank < size - 1) {
        MPI_Send(&x[ld-1], 1, coltype, right, 0, MPI_COMM_WORLD);
    }

    if (rank > 0) {
        MPI_Recv(&x[0], 1, coltype, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if (rank > 0) {
        MPI_Send(&x[1], 1, coltype, left, 1, MPI_COMM_WORLD);
    }

    if (rank < size - 1) {
        MPI_Recv(&x[ld], 1, coltype, right, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= mlocal; j++) {
            t[i*ld+j] = (b[i*ld+j] + x[(i+1)*ld+j] + x[(i-1)*ld+j] + x[i*ld+(j+1)] + x[i*ld+(j-1)])/4.0;
            local_s += (x[i * ld + j] - t[i * ld + j]) * (x[i * ld + j] - t[i * ld + j]);
        }
    }

    *local_sum = local_s;
}


void parallel_jacobi_poisson(int N, int mlocal, double *x, double *b, int rank, int size, MPI_Datatype coltype) {
    int i, j, k, ld = mlocal + 2, conv = 0, maxit = 10000;
    double *t, tol = 1e-6, local_sum, global_sum = 0.0;
        

    t = (double *)calloc((N+2) * (mlocal + 2), sizeof(double));

    k = 0;

    while (!conv && k < maxit) {
        parallel_jacobi_step(N, mlocal, x, b, t, &local_sum, rank, size, coltype);

        MPI_Allreduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        conv = (sqrt(global_sum) < tol);

        if (rank == 0) {
            printf("Error en iteración %d: %g\n", k, sqrt(global_sum));
        }

        MPI_Barrier(MPI_COMM_WORLD);

        k = k + 1;
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= mlocal; j++) {
                x[i * ld + j] = t[i * ld + j];
            }
        }
    }

    free(t);
}

int main(int argc, char **argv) {
    int i, j, N = 60, M = 60, ld;
    double *x, *b, h = 0.01, f = 1.5;

    if (argc > 1) {
        N = atoi(argv[1]);
        if (N <= 0) N = 60;
    }
    if (argc > 2) {
        M = atoi(argv[2]);
        if (M <= 0) M = 60;
    }
    ld = M + 2;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    int mlocal = N / size;
    //Creamos nuestro tipo de datos columna
    MPI_Datatype coltype;
   //MPI_Type_vector(count, length, stride, type, newtype)    
    MPI_Type_vector(N, 1, mlocal+2, MPI_DOUBLE, &coltype);
    MPI_Type_commit(&coltype);
    
    MPI_Datatype column_type_resized;
    MPI_Type_create_resized(coltype, 0, sizeof(double), &column_type_resized);
    MPI_Type_commit(&column_type_resized);
    
  

    
    x = (double *)calloc((N+2) * (mlocal + 2), sizeof(double));
    b = (double *)calloc((N+2) * (mlocal + 2), sizeof(double));

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= mlocal; j++) {
            b[i * ld + j] = h * h * f;
        }
    }

    parallel_jacobi_poisson(N, mlocal, x, b, rank, size, coltype);
    
    //para que al final el proceso 0 reciba todas las columnas calculadas por los demás procesos.
   // Crear un tipo de dato derivado para enviar y recibir columnas via


   if (N <= 60) {
    double *X = NULL;
    if (rank == 0) {
        X = (double *)calloc((N+2) * (M + 2), sizeof(double));
    }
    /* &x[1] es lo mismo que x + 1 en c++, como es una direccion de mememoria, 
    es como decirle: 1 posicion a la derecha en la memoria*/
    MPI_Gather(x + 1, mlocal , column_type_resized, X + 1, mlocal, column_type_resized, 0, MPI_COMM_WORLD);
    MPI_Type_free(&column_type_resized);
    if (rank == 0) {
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= M; j++) {
                printf("%g ", X[i * ld + j]);
            }
            printf("\n");
        }
         free(X);
    }
   
}
    free(x);
    free(b);

    MPI_Finalize();

    return 0;
}
