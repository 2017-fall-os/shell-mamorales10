all: ./test

test: test.o mytoc.o helpFuncts.o
	cc test.o mytoc.o helpFuncts.o -o test

test.o: test.c mytoc.h helpFuncts.h
	cc -c test.c

mytoc.o: mytoc.c mytoc.h
	cc -c mytoc.c

helpFuncts.o: helpFuncts.c helpFuncts.h
	cc -c helpFuncts.c
clean:
	rm *.o test
