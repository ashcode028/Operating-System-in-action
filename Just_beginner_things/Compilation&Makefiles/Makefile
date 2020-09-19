#Makefile
all: print print.o
print:print.o
	gcc print.o -o print

print.o:print.c
	gcc -c print.c -o print.o
	gcc -S print.c -o print.s
	gcc -E print.c -o print.i
