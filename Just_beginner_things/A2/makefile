#makefile
all: q4_32.o q4a.o ans1 q4_64.o q4b.o ans2
q4_32.o:q4_32.asm
	nasm -f elf32 -o q4_32.o q4_32.asm

q4a.o:q4_32.c
	gcc -c -m32 q4_32.c -o q4a.o

ans1:q4_32.o q4a.o
	gcc -m32 q4_32.o q4a.o -o ans1
	./ans1
	@echo

q4_64.o:q4_64.asm
	nasm -f elf64 -o q4_64.o q4_64.asm

q4b.o:q4_64.c
	gcc -c q4_64.c -o q4a.o

ans2:q4_64.o q4b.o
	gcc q4_64.o q4a.o -o ans2
	./ans2
	@echo
	
