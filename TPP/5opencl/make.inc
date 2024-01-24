CCFLAGS=-O3 -std=c99 -ffast-math #-lm

OPENCL_ROOT:=/opt/cuda/targets/x86_64-linux
#OPENCL_ROOT:=/opt/intel/opencl-1.2-6.4.0.37
#OPENCL_ROOT:=/usr/local/cuda-10.1/targets/x86_64-linux
OPENCL_LIBS:= $(OPENCL_ROOT)/lib
OPENCL_INC:= $(OPENCL_ROOT)/include

LIBS:= -L$(OPENCL_LIBS) -lOpenCL #-fopenmp
