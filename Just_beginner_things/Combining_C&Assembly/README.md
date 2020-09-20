# Combining C and Assembly

In this tutorial ,we will learn about calling ASM rountine from C program.
This routine takes arguments from user(cmd args) and prints their sum.
Expecting you got to know about basic gcc compilation and makefiles by now.If not check [this] first.(Just_beginner_things/Compilation&Makefiles/README.md)

## C code description
- Code [prog.c](Just_beginner_things/Combining_C&Assembly/prog.c)
- takes input from console
- since input from console is in character,it parses it into integers.
- The add function is written in assembly language which takes two parameters
given by the user.(func definition - line 7, func calling -line 15 )
- finally prints the output on the console using printf function.
- The calling convention used is x-86_64

## Assembly Code
- Code [check.asm](Just_beginner_things/Combining_C&Assembly/check.asm) 
- The parameters are taken through registers (default are rsi,rdi for x86_64).
- The add function adds the arguments and the result is stored in rax which is the
default register to return.
- This code is compiled and converted into object code through nasm assembler
command.
-This code will show error if it's loaded or linked alone to create an
executable since it doesn't have _start label(like main function in c)
-To get the output from both the files while linking(or creating an executable) we
have to compile it together.

## Makefile description.
- Makefile needs targets and its dependencies,the commands below tagets get executed
when their dependencies are resolved(or available).
- Here we need to create (check.asm)’s object file so that we can link it to the
prog.c while creating an executable.
- @echo -used to print on the console (here, used to tell the user how to enter the
arguments)
```
#Makefile
all:answer check.o

check.o:check.asm
	nasm -f elf64 check.asm -o check.o
answer:check.o prog.c
	gcc prog.c check.o -o answer
	@echo Please enter the command ./answer x y
```

## Input /Output
- handles negative inputs and positive inputs
- handles the case where user enters less number of arguments
- handles the case where user enters more number of argument

### TRY IT YOURSELF
- clone the repository
- navigate to [this folder](Just_beginner_things/Combining_C&Assembly/)
- Finally execute it using `` make ``command by opening the folder in terminal.
