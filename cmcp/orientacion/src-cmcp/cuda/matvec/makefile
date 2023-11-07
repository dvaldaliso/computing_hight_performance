
NVCC        = nvcc
NVCC_FLAGS  = -O3
LD_FLAGS    =
EXE	    = matvec
OBJ	    = matvec.o

default: $(EXE)

matvec.o: matvec.cu
	$(NVCC) -c -o $@ matvec.cu $(NVCC_FLAGS)

$(EXE): $(OBJ)
	$(NVCC) $(OBJ) -o $(EXE) $(LD_FLAGS)

clean:
	rm -rf *.o $(EXE)
