#Makefile
all: q1.o checkGreater.o ans
q1.o:q1.asm
	nasm -f elf64 -o q1.o q1.asm	
q1:q1.o
	ld q1.o -o q1
	./q1
	@echo 
checkGreater.o:checkGreater.c
	gcc -c checkGreater.c -o checkGreater.o

ans:q1.o checkGreater.o
	gcc checkGreater.o q1.o -o ans
	./ans
	@echo		

