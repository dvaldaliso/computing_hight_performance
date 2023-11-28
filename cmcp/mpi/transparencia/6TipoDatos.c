#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
//Esto envia la ultima columna de la matriz
 int main(int argc, char* argv[])
{
   int size,rango;
   int rows = 3;
   int cols = 4;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);

   // Lo dejo asi para que sea mas ilustrativo, deberia ser con calloc  
   double x[12]={1,2,3,4,5,6,7,8,9,10,11,12};
   double y[12]={0,0,0,0,0,0,0,0,0,0,0,0};
   MPI_Datatype coltype;
   //MPI_Type_vector(count, length, stride, type, newtype)
   MPI_Type_vector(rows, 1, cols, MPI_DOUBLE, &coltype);
   MPI_Type_commit(&coltype);
   if (rango==0){
      printf("%lf %lf %lf\n",y[0],y[1],y[2]);
      MPI_Send(&x[3], 1, coltype, 1, 999, MPI_COMM_WORLD);
   }else if (rango==1){
      MPI_Recv(&y, 3, MPI_DOUBLE, 0, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%lf %lf %lf\n",y[0],y[1],y[2]);
   }
   //El envio y la recpeccion no tienen que ser exactamente del mismo tamaño, solo que lo que se envie
   //sea mas pequeño o igual que lo que se reciba

   MPI_Barrier(MPI_COMM_WORLD);
   MPI_Type_free(&coltype);

    return 1;
}


