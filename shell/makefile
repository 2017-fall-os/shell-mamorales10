all: ./test

test: test.o mytoc.o
	cc test.o mytoc.o -o test

test.o: test.c mytoc.h
	cc -c test.c

mytoc.o: mytoc.c mytoc.h
	cc -c mytoc.c

clean:
	rm *.o test
