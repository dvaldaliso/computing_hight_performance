PETSC_DIR=/opt/petsc-3.20
SLEPC_DIR=/opt/slepc-3.20

PETSC_ARCH=arch-linux-gnu-c-opt

include ${SLEPC_DIR}/lib/slepc/conf/slepc_common


svd: svd.o
	-${CLINKER} -o svd svd.o ${SLEPC_SVD_LIB}
	${RM} svd.o
 
lsqr: lsqr.o
	-${CLINKER} -o lsqr lsqr.o ${PETSC_KSP_LIB}
	${RM} lsqr.o