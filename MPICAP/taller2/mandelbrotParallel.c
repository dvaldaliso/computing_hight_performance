#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <mpi.h>

typedef struct _MinMax{
   double Min;
   double Max;
} MinMax;

typedef struct {
    int *rowBn;
    int *rowBn2;
} Rows;
 // Obtener nuevo trabajo, seria obtener proxima fila de la matriz con la cual trabajar
double obtener_nuevo_trabajo(
   int pixelY,
   int pixelYmax,
   double ImMin,
   double AltoPixel){
   if (pixelY<pixelYmax)
   {
      return ImMin + pixelY*AltoPixel;
   }
   return -1;
   
  /*for(pixelY=0;pixelY<pixelYmax;pixelY++)
   {
      Cimg=ImMin + pixelY*AltoPixel;
      
   }*/
}

// Esta funcion procesaria la fila, es lo que hace cada proceso
Rows realizar_trabajo_asignado(double Cimg, 
                     int pixelXmax, 
                     double RealMin, 
                     double AnchoPixel,
                     double SumaExponencial,
                     int Iter,
                     int IterMax,
                     int MaxValorTonos,
                     double Salida2
                     ){
    int bn;
    int bn2;                    
    int pixelX;
    double Creal;
    double Zx;         //  Z=Zx+Zy*i  
    double Zy;
    double Zx2, Zy2;
    Rows result;

    // Asignar memoria para los dos arrays
    result.rowBn = (int*)malloc(pixelXmax * sizeof(int));
    result.rowBn2 = (int*)malloc(pixelXmax * sizeof(int));            // Zx2=Zx*Zx, Zy2=Zy*Zy  
    for(pixelX=0;pixelX<pixelXmax;pixelX++)
    {         
       Creal=RealMin + pixelX*AnchoPixel;
       Zx=0.0;         // Valor inicial
       Zy=0.0;
       Zx2=Zx*Zx;
       Zy2=Zy*Zy;
       for (Iter=0;Iter<IterMax && ((Zx2+Zy2)<Salida2);Iter++)
       {
           SumaExponencial += exp( -sqrt(Zx2+Zy2) )/IterMax;   // se mantiene siempre entre (0,1)            
	        Zy=2*Zx*Zy + Cimg;
           Zx=Zx2-Zy2 + Creal;
           Zx2=Zx*Zx;
           Zy2=Zy*Zy;
       }
       if (Iter==IterMax) { /*  interior del conjunto Mandelbrot = negro */    
          bn=0;          
          bn2=0;            
       }
       else { /* exterior del conjunto Mandelbrot = blanco modificado con exp */
          bn = MaxValorTonos - SumaExponencial * 255; 
          bn2 = (Iter +1 - (int)(log(log(sqrt(Zx2+Zy2)) / log(2)) / log(2)))*255;
       }
      //esto es lo que hay q enviar al proceso 0
      //ver como devolver un struct con los siguientes datos
       result.rowBn[pixelX] = bn;
       result.rowBn2[pixelX] = bn2;
     }
   return result;
}
int main(int argc, char **argv)
{

int myrank, ntasks, rank;
#define ETIQUETA_CONTINUAR 1
#define ETIQUETA_TERMINAR 99
MPI_Status status;
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

 int **Crear_matriz(int , int );
 void Liberar_matriz(int **, int );
 MinMax BuscarMinMax(int **, int , int);
 double ctimer(void);

 int pixelX,pixelY;               // Coordenadas de la imagen
 int pixelXmax = 512; 
 int pixelYmax = 512;
 double Cimg;               // Coordenadas de los puntos complejos
 const double RealMinArray[] = {-2, -1.023438, -1.017579, -1.017523, -1.0190739863281251, -1.0184326403503419, -1.0175024721407624, -1.0176950869990224, 0.2720};
 const double RealMaxArray[] = { 1, -0.992188, -1.016968, -1.017493, -1.0178532832031251, -1.0184266798858643, -1.0175010058651026, -1.0173896129032258, 0.3720};
 const double ImMinArray[] = {-1.5, -0.285156, -0.274444, -0.274065, -0.2672003476562500, -0.2667537630310058,  -0.2740544516129032, -0.2772175483870968, 0.4805};
 const double ImMaxArray[] = { 1.5, -0.25,     -0.273758, -0.274032, -0.2658270664062500, -0.2667336466064453,  -0.2740528387096774, -0.2768738924731183, 0.5805}; 
 
 double RealMin=-2.0; 
 double RealMax=1.0;  
 double ImMin=-1.5; 
 double ImMax=1.5; 
 double AltoPixel;
 double Tinicial, Tfinal, Ttotal;

 const int MaxValorTonos=255; 
 FILE *ImgFile, *ImgFile2;
 char ArchivoImagen[]="imgA.pgm";
 char ArchivoImagen2[]="imgB.pgm";
 char *comentario="# ";
 int Iter,i,j;
 int IterMax=1000;
 int dominio=0;
 int **matriz, **matriz2;
 MinMax  min_max_img;


 printf("\n  *************** POSIBLES PARÁMETROS ***************\n");
 printf("  * Ancho imagen: pixelXmax                         *\n");
 printf("  * Alto imagen: pixelYmax                          *\n");
 printf("  * Numero de iteraciones: IterMax                  *\n");
 printf("  * Nombre archivo imagen de salida: ArchivoImagen  *\n");
 printf("  * Intervalo a considerar: dominio                 *\n");  
 printf("  ***************************************************\n\n");

 switch (argc)
 {
        case 6: sscanf(argv[5], "%i", &dominio);
                if (8*(dominio + 1) > sizeof(RealMinArray)){
                   printf("El array de dominios no es tan grande\n");
                   return 0;
                }
                RealMin = RealMinArray[dominio];
                RealMax = RealMaxArray[dominio];
                ImMin = ImMinArray[dominio];
                ImMax = ImMaxArray[dominio];
        case 5: strcpy(ArchivoImagen, argv[4]);
                strcat(ArchivoImagen, "imgA.pgm");
                strcpy(ArchivoImagen2, argv[4]);
                strcat(ArchivoImagen2, "imgB.pgm");
        case 4: sscanf(argv[3], "%i", &IterMax);
        case 3: sscanf(argv[2], "%i", &pixelYmax);
        case 2: sscanf(argv[1], "%i", &pixelXmax);
        case 1: break;
        default: printf("Demasiados parametros\n");
                 return 0;
 }

 printf("  *************** DATOS DE LA EJECUCIÓN ****************************\n");
 printf("  * pixelXmax = %4d, pixelYmax = %4d                             *\n", pixelXmax, pixelYmax);
 printf("  * IterMax = %5d                                                *\n", IterMax);
 printf("  * ArchivoImagen = %15s %15s                *\n", ArchivoImagen, ArchivoImagen2);
 printf("  * Dominio = %2d                                                   *\n", dominio);
 printf("  * Intervalo para X: [%20.15f,%20.15f]  *\n  * Intervalo para Y: [%20.15f,%20.15f]  *\n", RealMin, RealMax, ImMin, ImMax);
 printf("  ******************************************************************\n\n");
 /* Se crea un nuevo archivo y se abre en binario  */
 ImgFile= fopen(ArchivoImagen,"wb"); 
 ImgFile2= fopen(ArchivoImagen2,"wb"); 
 /* Se escribe la cabecera - ASCII  */
 fprintf(ImgFile,"P5\n %s\n %d\n %d\n %d\n",comentario,pixelXmax,pixelYmax,MaxValorTonos);
 fprintf(ImgFile2,"P5\n %s\n %d\n %d\n %d\n",comentario,pixelXmax,pixelYmax,MaxValorTonos);

 
 
 matriz = Crear_matriz(pixelYmax, pixelXmax);
 matriz2 = Crear_matriz(pixelYmax, pixelXmax);
 Tinicial = ctimer();

// parallelizar con mpi todo lo hacen los proceos, cada proceso calcula el for siguiente 
// y le manda un array de ressultados a el proceos 0(padre), luego por el status el padre
// dice que proceso toma la siguente fila
//---------
   //MPI_Type_vector(count, length, stride, type, newtype)

    MPI_Datatype rowType;
    MPI_Type_vector(0, 1, pixelYmax, MPI_DOUBLE, &rowType);
    MPI_Type_commit(&rowType);

    Rows result;

    if (myrank == 0) {
      AltoPixel=(ImMax-ImMin)/(pixelYmax-1);
      for (rank = 1; rank < ntasks; ++rank) { // Inicializar el trabajo de los hijos. Se le manda una unidad de trabajo a cada hijo
      Cimg = obtener_nuevo_trabajo(pixelY, pixelYmax, ImMin, AltoPixel); // Se obtiene un nuevo trabajo para un hijo
      pixelX++;   
      MPI_Send(&Cimg, 1, MPI_DOUBLE, rank, ETIQUETA_CONTINUAR, MPI_COMM_WORLD); // Se manda el trabajo al hijo
      } 
      Cimg = obtener_nuevo_trabajo(pixelY, pixelYmax, ImMin, AltoPixel); // Vamos obteniendo nuevos trabajos y asignándolos a los hijos hasta que se agoten
      while (Cimg != -1) {
         // Recibimos un resultado de un hijo cualquiera (MPI_ANY_SOURCE) y le mandamos trabajo a ese mismo hijo
         // identificandolo por "status.MPI_SOURCE"
         
         MPI_Recv(&result.rowBn, 0, rowType, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         // Recibe la segunda fila
         MPI_Recv(&result.rowBn2, 0, rowType, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         //Terminar no me dio el tiempo
         MPI_Send(&Cimg, 1, MPI_INT, status.MPI_SOURCE, ETIQUETA_CONTINUAR, MPI_COMM_WORLD);
         Cimg = obtener_nuevo_trabajo(pixelY, pixelYmax, ImMin, AltoPixel);
         pixelY++;
      }
      // Si no hay mas trabajos que mandar a los hijos, recogemos los resultados que queden del total de hijos
      for (rank = 1; rank < ntasks; ++rank)
         MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      // Indicamos a los hijos que deben dejar de trabajar mediante el envio de la etiqueta "ETIQUETA_TERMINAR"
      for (rank = 1; rank < ntasks; ++rank)
         MPI_Send(0, 0, MPI_INT, rank, ETIQUETA_TERMINAR, MPI_COMM_WORLD);

   }else {
      while (1) {
      const double Salida=2;    // valor de escape
      double Salida2=Salida*Salida, SumaExponencial;
      double AnchoPixel=(RealMax-RealMin)/(pixelXmax-1); 
      
      // Recibir asignacion de trabajo del padre
      MPI_Recv(&Cimg, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      // Comprobar si la etiqueta de envio me indica que debo parar
      if (status.MPI_TAG == ETIQUETA_TERMINAR) {
         MPI_Finalize();
         finalizar(Tfinal,Ttotal,Tinicial,pixelYmax,pixelXmax,min_max_img,ImgFile,ImgFile2,matriz,matriz2);
         return 0;
      }
      result = realizar_trabajo_asignado(Cimg,
       pixelXmax,RealMin, 
       AnchoPixel,SumaExponencial,
       Iter,IterMax,
       MaxValorTonos,Salida2);
      // Enviar resultados al padre
      MPI_Send(result.rowBn, 1, rowType, 1, 0, MPI_COMM_WORLD);
        // Envía la segunda fila apdre
      MPI_Send(result.rowBn2, 1, rowType, 1, 1, MPI_COMM_WORLD);
      }
      MPI_Finalize();
      finalizar(Tfinal,Ttotal,Tinicial,pixelYmax,pixelXmax,min_max_img,ImgFile,ImgFile2,matriz,matriz2);
      return 0;
  
   }
 } 


void finalizar(
   double Tfinal,
   double Ttotal,
   double Tinicial,
   int pixelYmax,
   int pixelXmax,
   MinMax min_max_img,
   File *ImgFile,
   File *ImgFile2,
   int ** matriz,
   int ** matriz2) {

    Tfinal = ctimer();
    Ttotal = Tfinal-Tinicial;
    printf("\nTiempo: %f segundos\n", Ttotal);
    min_max_img = BuscarMinMax(matriz2,pixelYmax,pixelXmax);
    for (int i=0;i<pixelYmax;i++) {
        for (int j=0;j<pixelXmax;j++) {
            matriz2[i][j] = matriz2[i][j] - min_max_img.Min;
            matriz2[i][j] = matriz2[i][j] * (255.0/(min_max_img.Max-min_max_img.Min));
        }
    }
    min_max_img = BuscarMinMax(matriz2,pixelYmax,pixelXmax);

    for (int pixelY=0;pixelY<pixelYmax;pixelY++) {
        for(int pixelX=0;pixelX<pixelXmax;pixelX++){
           fwrite(&matriz[pixelY][pixelX],1,1,ImgFile);
           fwrite(&matriz2[pixelY][pixelX],1,1,ImgFile2);
        }
    } 
    fclose(ImgFile);
    fclose(ImgFile2);
    Liberar_matriz(matriz,pixelYmax);
    Liberar_matriz(matriz2,pixelYmax);
}

int **Crear_matriz(int fila, int col)
{
    int **ret_val;
    int i;
 
    ret_val = (int **)malloc(sizeof(int *) * fila);
    if (ret_val == NULL) {
        perror("Problemas al dimensionar");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0; i < fila; ++i) {
        ret_val[i] = (int *)malloc(sizeof(int) * col);
        if (ret_val[i] == NULL) {
            perror("Problemas al dimensionar");
            exit(EXIT_FAILURE);
        }
    }
    return ret_val;
}

void Liberar_matriz(int **matriz, int fila)
{
    int i;
 
    for (i = 0; i < fila; ++i)
        free(matriz[i]);
    free(matriz);
}

#include <sys/time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>

static int nclock;
double ctimer(void)
{
   struct timeval tp;
   struct timezone tzp;
   double diff;
   nclock=sysconf(_SC_CLK_TCK);
   gettimeofday(&tp, &tzp);
   diff=(double)tp.tv_sec+(double)tp.tv_usec/1.0e6;
   return diff;
}

MinMax BuscarMinMax(int **array, int fil, int col) {
   MinMax  min_max;
   int index,fila,columna,fila_next,columna_next;
   int n = fil*col; 
   if ( n%2 != 0 ){

     min_max.Min = array[0][0];
     min_max.Max = array[0][0];

     index = 1;
   }
   else{
     if ( array[0][0] < array[0][1] ){
       min_max.Min = array[0][0];
       min_max.Max = array[0][1];
      }
      else {
       min_max.Min = array[0][1];
       min_max.Max = array[0][0];
      }
       index = 2;
   }

   int big, small,i;
   for ( i = index; i < n-1; i = i+2 ){
      fila = i / col;
      columna = i % col;  
      fila_next = fila;
      columna_next = columna + 1;
      if (columna_next == col) {
         fila_next = fila +1;
         columna_next = 0;
      }
      if ( array[fila][columna] < array[fila_next][columna_next] ){
        small = array[fila][columna];
        big = array[fila_next][columna_next];
      }
      else{
        small = array[fila_next][columna_next];
        big = array[fila][columna];
      }
      if ( min_max.Min > small ){
        min_max.Min = small;
      }
      if ( min_max.Max < big ){ 
        min_max.Max = big;
      }
   }
   printf("Minimo = %f, Maximo = %f\n", min_max.Min, min_max.Max);
   return min_max;
}




// Para parallelizarlo utilizamos la idea de Pool siguiente

/*
int main(int argc, char **argv) {
int myrank, ntasks, rank;
#define ETIQUETA_CONTINUAR 1
#define ETIQUETA_TERMINAR 99
MPI_Status status;
MPI_Init(&argc, &argv); MPI_Comm_rank(MPI_COMM_WORLD, &myrank); MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
if (myrank == 0) {
   for (rank = 1; rank < ntasks; ++rank) { // Inicializar el trabajo de los hijos. Se le manda una unidad de trabajo a cada hijo
      work = obtener_nuevo_trabajo(); // Se obtiene un nuevo trabajo para un hijo
      MPI_Send(&work, 1, MPI_INT, rank, ETIQUETA_CONTINUAR, MPI_COMM_WORLD); // Se manda el trabajo al hijo
   }
   work = obtener_nuevo_trabajo(); // Vamos obteniendo nuevos trabajos y asignándolos a los hijos hasta que se agoten
   while (work != NULL) {
      // Recibimos un resultado de un hijo cualquiera (MPI_ANY_SOURCE) y le mandamos trabajo a ese mismo hijo
      // identificandolo por "status.MPI_SOURCE"
      MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      MPI_Send(&work, 1, MPI_INT, status.MPI_SOURCE, ETIQUETA_CONTINUAR, MPI_COMM_WORLD);
      work = obtener_nuevo_trabajo(); 
   }
   // Si no hay mas trabajos que mandar a los hijos, recogemos los resultados que queden del total de hijos
   for (rank = 1; rank < ntasks; ++rank)
      MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
   // Indicamos a los hijos que deben dejar de trabajar mediante el envio de la etiqueta "ETIQUETA_TERMINAR"
   for (rank = 1; rank < ntasks; ++rank)
      MPI_Send(0, 0, MPI_INT, rank, ETIQUETA_TERMINAR, MPI_COMM_WORLD);
}
   else {
      while (1) {
      // Recibir asignacion de trabajo del padre
         MPI_Recv(&work, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         // Comprobar si la etiqueta de envio me indica que debo parar
         if (status.MPI_TAG == ETIQUETA_TERMINAR) {
         MPI_Finalize();
         return 0; }
         result = realizar_trabajo_asignado(work);
         // Enviar resultados al padre
         MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); }
         }
   MPI_Finalize();
return 0;
}
*/

//Comentarions del profe
/*
La nota de vuestra práctica es 7. Como sabéis está incompleta, pero revisando vuestra práctica se nota que habéis trabajado, y con un poco más de tiempo la habrías acabado bien.
Os comento algunas cosas.

La estructura de vuestro código es buena, aunque hay algunos detalles que imposibilitan que funcione.


Principal problema:

- Os habéis liado con el uso de MPI_Type_vector. Entiendo que utilizáis MPI_Type_vector para almacenar una fila de la imagen. 


Pero la sentencia

MPI_Type_vector(0, 1, pixelYmax, MPI_DOUBLE, &rowType);

No hace eso. Con esa sentencia os generáis un tipo de datos con 0 bloques, …, esto no sirve, pues ese tipo de dato no almacena dato alguno.


Se podría crear un tipo de dato con MPI_Type_vector como habéis hecho, pero realmente en este caso las comunicaciones son sencillas y no es necesario, sería suficiente con enviar los elementos de un array, por ejemplo, los procesos hijos podrían tener un código como:



              bn = MaxValorTonos - (SumaExponencial * 255)/IterMax;

              otrobn = (Iter +1 - (int)(log(log(sqrt(Zx2+Zy2)) / log(2)) / log(2)))*255;

//mu As Double = iteration + 1 - _

//    Math.Log(Math.Log(Z.Magnitude)) / log_escape

//    mu = mu / MaxIterations * Colors.Count

         } 

         aux[pixelX] = bn;

         aux2[pixelX] = otrobn;

       } 

       MPI_Send(&pixelY, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);

       MPI_Send(aux, pixelXmax, MPI_INT, 0, pixelY, MPI_COMM_WORLD);

       MPI_Send(aux2, pixelXmax, MPI_INT, 0, pixelY, MPI_COMM_WORLD);

     }

     free(aux);

     free(aux2);



*/



