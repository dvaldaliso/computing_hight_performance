//#include <stdlib.h>
//#include <mpi.h>
#include <time.h>
#include <petscksp.h>
#include <petscsys.h>
#include <petscvec.h>
#include <petscmath.h>
#include <slepcsys.h>
#include <slepcsvd.h>
#include "petscsys.h"
#include <utmpx.h>

static char help[] = "Computes SVD of sparse matrix.\n\n"
                     "Usage: ./svd -file A_file_name -fileb b_file_name -filex solution_file_name\n";
// ejecucion en Kaha
#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char **argv)
{
   /*  A COMPLETAR: DECLARACION DE VARIABLES*/
	PetscBool flg;

	/*  A COMPLETAR: Inicializar PETSc (PetscFunctionBeginUser; PetscInitialize) */

	/*  A COMPLETAR: Medir tiempos
		EJEMPLO:
	    PetscCall(PetscTime(&t1));
   		...
   		PetscCall(PetscTime(&t2));
   		PetscCall(PetscPrintf(PETSC_COMM_WORLD," Elapsed Time: %f\n",t2-t1));*/

	/*	A COMPLETAR: Leer Datos de entrada: rutas matriz A, vector b y vector x 
		EJEMPLO:
		PetscCall(PetscOptionsGetString(NULL,NULL,"-file",filename,sizeof(filename),&flg));
	    PetscCheck(flg,PETSC_COMM_WORLD,PETSC_ERR_USER_INPUT,"Must indicate a file name with the -file option"); */


	/*	A COMPLETAR: Leer los datos de los ficheros (matriz A, vector b)

		EJEMPLO:
		PetscCall(PetscViewerBinaryOpen(PETSC_COMM_WORLD,filename,FILE_MODE_READ,&viewer));
		PetscCall(MatCreate(PETSC_COMM_WORLD,&A));
		PetscCall(MatSetFromOptions(A));
		PetscCall(MatLoad(A,viewer));
		PetscCall(PetscViewerDestroy(&viewer));*/

	/*	A COMPLETAR: Crear vector x (solucion) inicializado a 0
		EJEMPLO:
		PetscCall(VecCreate(PETSC_COMM_WORLD, &u));
		PetscCall(VecSetSizes(u, PETSC_DECIDE, dim));
		PetscCall(VecSetFromOptions(u));
		PetscCall(VecSet...*/

		/*	A COMPLETAR: Configurar solver SVD 
		FUNCIONES:
		SVDSetOperators
		SVDSetFromOptions */

		/*	A COMPLETAR: Ejecutar solver SVD
		FUNCIONES:
		SVDSolve */
		
		/*	A COMPLETAR: Extraer datos de la solución del solver SVD
		FUNCIONES:
		Buscar las funciones para extraer numero de valores singulares calculados y numero de iteraciones realizadas*/

      /* A COMPLETAR: Bucle FOR para extraer datos de la solución del solver SVD y operación x=V*sigma^-1*Ut*b
      FUNCIONES:
      SVDGetSingularTriplet(svd, i, &sigma, u, v);
      VecDot 
      VecScale
      VecAXPBY */

		/*	A COMPLETAR: Almacenar la solucion en formato MATLAB
		FUNCIONES:
		PetscViewerASCIIOpen(...)
		PetscViewerPushFormat(fdout,PETSC_VIEWER_ASCII_MATLAB);
		VecView(x, fdout);
		PetscViewerPopFormat(fdout);
		PetscViewerDestroy(&fdout);*/

		/*A COMPLETAR: Destruir matrices, vectores y finalizar entorno
		FUNCIONES:
		MatDestroy
		VecDestroy
      SVDDestroy
		PetscFinalize
		*/

		/*A COMPLETAR: Mostrar datos de tiempos*/
		
	return 0;
}
