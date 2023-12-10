CC      = gcc
CFLAGS  = -Wall -O3
LDFLAGS =
LIBS    =

mandel: mandel.o misc.o
	$(CC) -fopenmp -o $@ mandel.o misc.o $(LDFLAGS) $(LIBS)

