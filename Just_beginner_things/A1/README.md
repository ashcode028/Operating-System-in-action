# Testing 
Demonstration to show standlone assembly codes can be called the same way as assembly rountines are called.

## Steps to run standlone assembly
- Sample code [q1.asm](Just_beginner_things/A1/q1.asm)
- Under .text section entry point should be mentioned.If the ``_start`` is not mentioned under .text then add it using `` global _start``.
- start acts as a main function in assembly.
- mov parameters to rsi,rdi (default registers to pass arguments)
- call checkgreater.
- the ouput of the function is done by `write syscall`
```
_print1:			    ;label to print 1 if x>y
	mov rax,1		    ;write syscall
	mov rdi,0
	mov rsi,msg1
	mov rdx,1
	syscall
	call _exit		   ;exit syscall to avoid segmentation fault
	ret 
```
- to return from jump instructions properly `exit syscall` is used.
```
_exit:      
       mov rax,60		;syscall to exit
       mov rdi,0
       syscall
       ret 

```
- instead of labels ,macros can also be used if you dont want to use registers as medium to pass arguments but macros can be called from C program.
Calling macros from start as -`checkGreater 4,3`
```
%macro checkGreater 2		;macro definition name and no of parameters
	mov rax,%1		        ;load 1st parameter to rax
	cmp rax,%2		        ;compare with second parameter
	jg  _print1		        ;if greater jump to label print1
  jmp _print0		        ;else jump to label print2
%endmacro  			        ;end of macro

```
- Make file contents should be
```
#Makefile
all: q1.o q1
q1.o:q1.asm
	nasm -f elf64 -o q1.o q1.asm	
q1:q1.o
	ld q1.o -o q1
	./q1
	@echo 
```
## Steps to call assembly routine from C


Make file changes
```
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
```
