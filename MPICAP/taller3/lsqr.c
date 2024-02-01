#include <time.h>
#include <petscksp.h>
#include <petscsys.h>
#include <petscvec.h>
#include <petscmath.h>

static char help[] = "Uses lsqr to reconstruct a CT image using its projections b and its system matrix A.\n\n" 
"Usage: ./lsqr -file A_file_name -fileb b_file_name -filex solution_file_name\n";

#undef __FUNCT__
#define __FUNCT__ "main"
// ejecucion en Kaha
int main(int argc, char **argv)
{
	//profe mnichipr@inf.upv.es
	/*  A COMPLETAR: DECLARACION DE VARIABLES*/
	Mat            A;               /* operator matrix */
	Vec            b;               /* operator matrix */
  	Vec            x;               /* operator matrix */
  
	PetscInt       dim_rows, dim_cols;
  	char           filename[PETSC_MAX_PATH_LEN];
  	char           filenameb[PETSC_MAX_PATH_LEN];
  	char           filenameS[PETSC_MAX_PATH_LEN];
  	PetscViewer    viewer;
	PetscBool flg;
	KSP ksp;

  	PetscReal t1,t2;

	/*  A COMPLETAR: Inicializar PETSc (PetscFunctionBeginUser; PetscInitialize) */
	PetscFunctionBeginUser; // Begin user section
	PetscInitialize(&argc, &argv, (char*)0, help); // Initialize PETSc
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
		PetscCall(VecSetSizes(b, PETSC_DECIDE, dim_rows));
		PetscCall(VecLoad(b,viewer));
		PetscCall(PetscViewerDestroy(&viewer));


	/*	A COMPLETAR: Crear vector x (solucion) inicializado a 0
		EJEMPLO:
	*/	
		PetscCall(VecCreate(PETSC_COMM_WORLD, &x));
		PetscCall(VecSetSizes(x, PETSC_DECIDE, dim_cols));
		PetscCall(VecSetFromOptions(x));
		//PetscCall(VecSet
		PetscReal initial_guess = 0.0;
		PetscCall(VecSet(x, initial_guess));
		

		/*	A COMPLETAR: Configurar solver KSP sin precondicionador, tipo KSPLSQR, 
		FUNCIONES:
		*/
		PC pc;
		KSPSetOperators(ksp, A, NULL);
		KSPGetPC(ksp, &pc);
		PCSetType(pc, PCNONE);
		KSPSetType(ksp, KSPLSQR);
		KSPSetFromOptions(ksp);
		 

		/*	A COMPLETAR: Ejecutar solver KSP 
		FUNCIONES:
		*/
		KSPSolve(ksp, b, x); 
		
		/*	A COMPLETAR: Extraer datos de la solución del solver KSP 
		FUNCIONES:
		Buscar las funciones para extraer el motivo de parada y numero de iteraciones realizadas*/
		KSPConvergedReason reason;
		KSPGetConvergedReason(ksp, &reason); // Get the reason for convergence
		PetscPrintf(PETSC_COMM_WORLD, "Convergence reason: %s\n", KSPConvergedReasons[reason]);

		PetscInt iterations;
		KSPGetIterationNumber(ksp, &iterations); // Get the number of iterations
		PetscPrintf(PETSC_COMM_WORLD, "Number of iterations: %D\n", iterations);	
		/*	A COMPLETAR: Almacenar la solucion en formato MATLAB
		FUNCIONES:
		*/
		PetscViewer fdout;
		PetscViewerASCIIOpen(PETSC_COMM_WORLD, filenameS, &fdout);
		PetscViewerPushFormat(fdout,PETSC_VIEWER_ASCII_MATLAB);
		VecView(x, fdout);
		PetscViewerPopFormat(fdout);
		PetscViewerDestroy(&fdout);


		/*A COMPLETAR: Destruir matrices, vectores y finalizar entorno
		FUNCIONES:
		MatDestroy
		VecDestroy
		KSPDestroy
		PetscFinalize
		*/
		MatDestroy(&A); // Destroy matrix A
		VecDestroy(&b); // Destroy vector b
		VecDestroy(&x); // Destroy vector x
		KSPDestroy(&ksp); // Destroy the solver context

		/*A COMPLETAR: Mostrar datos de tiempos*/
		PetscCall(PetscTime(&t2));
   		PetscCall(PetscPrintf(PETSC_COMM_WORLD," Elapsed Time: %f\n",t2-t1));
		PetscFinalize(); // Finalize the PETSc environment

	return 0;
}

	
	
