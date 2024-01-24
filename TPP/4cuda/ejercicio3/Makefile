
NVCC=nvcc

ARCH=
CUDAFLAGS=-lineinfo $(ARCH)

all: TransferenceExample

TransferenceExample: TransferenceExample.cu 
	$(NVCC) TransferenceExample.cu -o TransferenceExample $(CUDAFLAGS) 

clean:
	rm -f *.o TransferenceExample.linkinfo TransferenceExample

