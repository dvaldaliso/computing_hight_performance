
NVCC        = nvcc
NVCC_FLAGS  = -O3
LD_FLAGS    =
EXE	    = matadd
OBJ	    = matadd.o support.o

default: $(EXE)

matadd.o: matadd.cu support.h
	$(NVCC) -c -o $@ matadd.cu $(NVCC_FLAGS)

support.o: support.cu support.h
	$(NVCC) -c -o $@ support.cu $(NVCC_FLAGS)

$(EXE): $(OBJ)
	$(NVCC) $(OBJ) -o $(EXE) $(LD_FLAGS)

clean:
	rm -rf *.o $(EXE)
