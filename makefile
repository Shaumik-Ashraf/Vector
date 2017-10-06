all: test.o vector_s.o
	gcc -o test.exe test.o vector_s.o

test.o: test.c vector_s.h
	gcc -c test.c

vector.o: vector_s.c vector_s.h
	gcc -c vector_s.c
