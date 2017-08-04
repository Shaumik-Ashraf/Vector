all: test.o vector.o
	gcc -o main.exe test.o vector.o

test.o: test.c vector.h
	gcc -c test.c

vector.o: vector.c vector.h
	gcc -c vector.c
