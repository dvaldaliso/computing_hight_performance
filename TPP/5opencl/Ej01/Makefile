
ifndef CC
	CC = gcc
endif

include ../make.inc

COMMON_DIR = ../C_common

# Check our platform and make sure we define the APPLE variable
# and set up the right compiler flags and libraries
PLATFORM = $(shell uname -s)
ifeq ($(PLATFORM), Darwin)
	LIBS = -framework OpenCL
endif

DeviceInfo: DeviceInfo.c
	$(CC) $^ $(CCFLAGS) $(LIBS) -I $(COMMON_DIR) -I $(OPENCL_INC) -o $@


clean:
	rm -f DeviceInfo
