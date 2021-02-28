#Makefile
all: q1 q1.o
q1:q1.o
	gcc q1.o -o q1
	./q1

q1.o:q1.c
	gcc -c q1.c -o q1.o
	gcc -S q1.c -o q1.s
	gcc -E q1.c -o q1.i	

