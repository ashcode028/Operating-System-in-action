#Makefile
all:answer check.o

check.o:check.asm
	nasm -f elf64 check.asm -o check.o
answer:check.o prog.c
	gcc prog.c check.o -o answer
	@echo Please enter the command ./answer x y

