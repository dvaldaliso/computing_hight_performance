
all: test_ls.x

TEST_LS = test_ls.o utils.o flop_counts.o

test_ls.x : $(TEST_LS)
	$(LD) -o $@ -no-pie $(LDFLAGS) $(TEST_LS) -lm \
            $(TMGLIB) $(LAPACK) $(BLAS)

.c.o :
	$(CC) $(CCFLAGS) -c $<

clean : 
	rm -f *.o *~ core *.x

