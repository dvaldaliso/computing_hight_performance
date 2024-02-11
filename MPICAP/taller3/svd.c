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
	PetscReal t1,t2;
	Mat            A;               /* operator matrix */
	Vec            b;               /* operator matrix */
  	Vec            x;               /* operator matrix */
	PetscInt       dim_rows, dim_cols;
	PetscViewer    viewer;
	char           filename[PETSC_MAX_PATH_LEN];
  	char           filenameb[PETSC_MAX_PATH_LEN];
  	char           filenameS[PETSC_MAX_PATH_LEN];
	/*  A COMPLETAR: Inicializar PETSc (PetscFunctionBeginUser; PetscInitialize) */
	PetscFunctionBeginUser; // Begin user section
	PetscInitialize(&argc, &argv, (char*)0, help); 
  	SlepcInitialize(&argc, &argv, (char*)0, help);

	/*  A COMPLETAR: Medir tiempos
		EJEMPLO:
	*/	
	    PetscCall(PetscTime(&t1));
   	
   		
	/*	A COMPLETAR: Leer Datos de entrada: rutas matriz A, vector b y vector x 
		EJEMPLO:
		*/
	PetscCall(PetscOptionsGetString(NULL,NULL,"-file",filename,sizeof(filename),&flg));
	PetscCheck(flg,PETSC_COMM_WORLD,PETSC_ERR_USER_INPUT,"Must indicate a file name with the -file option");
	PetscCall(PetscOptionsGetString(NULL,NULL,"-fileb",filenameb,sizeof(filenameb),&flg));
	PetscCheck(flg,PETSC_COMM_WORLD,PETSC_ERR_USER_INPUT,"Must indicate a file name with the -file option");
	PetscCall(PetscOptionsGetString(NULL,NULL,"-files",filenameS,sizeof(filenameS),&flg));
	PetscCheck(flg,PETSC_COMM_WORLD,PETSC_ERR_USER_INPUT,"Must indicate a file name with the -file option");


	/*	A COMPLETAR: Leer los datos de los ficheros (matriz A, vector b)

		EJEMPLO:
	*/	
	PetscCall(PetscViewerBinaryOpen(PETSC_COMM_WORLD,filename,FILE_MODE_READ,&viewer));
	PetscCall(MatCreate(PETSC_COMM_WORLD,&A));
	PetscCall(MatSetFromOptions(A));
	PetscCall(MatLoad(A,viewer));
	PetscCall(PetscViewerDestroy(&viewer));

	MatGetSize(A, &dim_rows, &dim_cols); 

	PetscCall(PetscViewerBinaryOpen(PETSC_COMM_WORLD,filenameb,FILE_MODE_READ,&viewer));
	PetscCall(VecCreate(PETSC_COMM_WORLD,&b));
	PetscCall(VecLoad(b,viewer));
	PetscCall(PetscViewerDestroy(&viewer));

	/*	A COMPLETAR: Crear vector x (solucion) inicializado a 0
		EJEMPLO:
	.*/	
	PetscCall(VecCreate(PETSC_COMM_WORLD, &x));
	PetscCall(VecSetSizes(x, PETSC_DECIDE, dim_cols));
	PetscCall(VecSetFromOptions(x));
	//PetscCall(VecSet
	PetscReal initial_guess = 0.0;
	PetscCall(VecSet(x, initial_guess));
	/*	A COMPLETAR: Configurar solver SVD 
	FUNCIONES:
	SVDSetOperators
	SVDSetFromOptions */
	SVD svd;
	SVDCreate(PETSC_COMM_WORLD, &svd); // Create the SVD solver context
	SVDSetOperators(svd, A, NULL); // Set the operator matrix for the SVD solver
	SVDSetFromOptions(svd); 
	/*	A COMPLETAR: Ejecutar solver SVD
	FUNCIONES:
	SVDSolve */
	SVDSolve(svd);
	/*	A COMPLETAR: Extraer datos de la solución del solver SVD
	FUNCIONES:
	Buscar las funciones para extraer numero de valores singulares calculados y numero de iteraciones realizadas*/
	PetscInt nsv;
	SVDGetConverged(svd, &nsv); 
	PetscPrintf(PETSC_COMM_WORLD, "Number of singular values computed: %D\n", nsv);
	 
	PetscInt iterations;
	SVDGetIterationNumber(svd, &iterations);
	PetscPrintf(PETSC_COMM_WORLD, "Number of iterations: %D\n", iterations);
    /* A COMPLETAR: Bucle FOR para extraer datos de la solución del solver SVD y operación x=V*sigma^-1*Ut*b
    FUNCIONES:
    SVDGetSingularTriplet(svd, i, &sigma, u, v);
    VecDot 
     VecScale
     VecAXPBY */
	 PetscScalar sigma;
	 PetscScalar dot_product;
	 PetscScalar scale_factor;
     Vec u, v;
//	 MatCreateVecs(A, NULL, &u); 
//     MatCreateVecs(A, NULL, &v); 
		
	 for (PetscInt i = 0; i < nsv; i++) {
		 SVDGetSingularTriplet(svd, i, &sigma, NULL, NULL); 

		MatCreateVecs(A, NULL, &u); 
		MatCreateVecs(A, NULL, &v); 

         SVDGetSingularTriplet(svd, i, &sigma, u, v); // Get the i-th singular triplet
         VecDot(b, u, &dot_product); 
         scale_factor = 1.0 / sigma; 
         dot_product /= sigma;
		 VecScale(v, scale_factor); 

    	 VecAXPBY(x, dot_product, 1.0, v);
	}

		/*	A COMPLETAR: Almacenar la solucion en formato MATLAB
		FUNCIONES:
		PetscViewerASCIIOpen(...)
		PetscViewerPushFormat(fdout,PETSC_VIEWER_ASCII_MATLAB);
		VecView(x, fdout);
		PetscViewerPopFormat(fdout);
		PetscViewerDestroy(&fdout);*/
		PetscViewer fdout;
		PetscViewerASCIIOpen(PETSC_COMM_WORLD, filenameS, &fdout); // Open a viewer for ASCII file
		PetscViewerPushFormat(fdout, PETSC_VIEWER_ASCII_MATLAB); // Set the output format to MATLAB

		// View the solution vector x
		VecView(x, fdout);

		PetscViewerPopFormat(fdout); // Restore the previous output format
		PetscViewerDestroy(&fdout); 
		/*A COMPLETAR: Destruir matrices, vectores y finalizar entorno
		FUNCIONES:
		*/
		MatDestroy(&A); // Destroy matrix A
		VecDestroy(&b); // Destroy vector b
		VecDestroy(&x); // Destroy vector x
		VecDestroy(&u); // Destroy vector u
		VecDestroy(&v); // Destroy vector v
		
   		PetscCall(PetscTime(&t2));
		PetscCall(PetscPrintf(PETSC_COMM_WORLD," Elapsed Time: %f\n",t2-t1));

		SlepcFinalize();
		PetscFinalize();
		

		/*A COMPLETAR: Mostrar datos de tiempos*/
		
	return 0;
}
