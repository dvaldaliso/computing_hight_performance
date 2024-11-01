#include "mpi.h"
#include <stdio.h>

#define MAXV 10000

int main(int argc, char *argv[])
{

    int idproc, numprocs;
    double a[MAXV], b[MAXV], /* vectores operando */
        prod,                /* producto escalar */
        datoa, datob,        /* datos recibidos en cada proc */
        dato;                /* producto enviado al 0 */
    int vsize,               /* tam vectores */
        cadaproc,            /* lo que le toca a cada proc */
        resto,               /* el resto lo har�el cero */
        i, j, k;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idproc);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (idproc == 0){
        printf("Tam. vectores (menor que %d):", MAXV);
        scanf("%d", &vsize);
        printf("\nGenerando datos...\n");
        for (i = 0; i < vsize; i++)
        {
            a[i] = (double)i;
            b[i] = (double)i;
        }
        cadaproc = vsize / (numprocs - 1);
        resto = vsize % (numprocs - 1);
    }

    /* broadcast */
    MPI_Bcast(&cadaproc, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (idproc == 0)
    {
        k = 0;
        for (i = 1; i < numprocs; i++)
        {
            for (j = 0; j < cadaproc; j++)
            {
                /* Enviamos a cada procesador los datos que le tocan */
                MPI_Send(&a[k], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
                MPI_Send(&b[k], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
                printf("Send: src %d dst %d dato %f\n", idproc, i, a[k]);
                printf("Send: src %d dst %d dato %f\n", idproc, i, b[k]);
                k++;
            }
        }
        /* el resto lo hace el cero */
        prod = 0;
        for (j = 0; j < resto; j++)
        {
            prod = prod + (a[k] * b[k]);
            k++;
        }
    }
    else
    {
        printf("Recv: dst %d src %d dato %d\n", idproc, status.MPI_SOURCE, cadaproc);
        prod = 0;
        for (j = 0; j < cadaproc; j++)
        {
            /* Recibimos cada elemento del vector que nos toca, multiplicamos y acumulamos */
            MPI_Recv(&datoa, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&datob, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
            printf("Recv: dst %d src %d dato %f\n", idproc, status.MPI_SOURCE, datoa);
            printf("Recv: dst %d src %d dato %f\n", idproc, status.MPI_SOURCE, datob);
            prod = prod + datoa * datob;
        }
    }

    MPI_Reduce(&prod, &dato, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (idproc == 0)
    {
        printf("El producto escalar es %f\n", dato);
    }

    MPI_Finalize();
    return 0;
}
