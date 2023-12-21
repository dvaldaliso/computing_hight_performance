
all: test_gemm.x

TEST_GEMM = test_gemm.o utils.o

test_gemm.x : $(TEST_GEMM)
	$(LD) -o $@ -no-pie $(LDFLAGS) $(TEST_GEMM) -lm \
            $(TMGLIB) $(LAPACK) $(BLAS)

.c.o :
	$(CC) $(CCFLAGS) -c $<

clean : 
	rm -f *.o *~ core *.x

