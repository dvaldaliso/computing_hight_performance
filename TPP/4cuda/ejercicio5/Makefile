
NVCC=nvcc

# Architecture specification
#ARCH=-arch sm_75 # For GPU2.dsic.upv.es
ARCH=-arch sm_35 # For knights.dsic.upv.es

CUDAFLAGS=-lineinfo $(ARCH)

all: SimpleMatrixSum

SimpleMatrixSum: SimpleMatrixSum.cu 
	$(NVCC) SimpleMatrixSum.cu -o SimpleMatrixSum $(CUDAFLAGS) 

clean:
	rm -f *.o SimpleMatrixSum.linkinfo SimpleMatrixSum

