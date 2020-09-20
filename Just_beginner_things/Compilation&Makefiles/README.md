# Compilation at each phase
The process of​ compilation ​ is converting source code(here C code) into object
code(or the binary code which can be understood by the machine) by a
compiler(here gcc).
That process has four steps:
- Preprocessing
- Compiling
- Assembling
- Linking
## Preprocessing Step:
- Removes all comments from source code.
- Includes header files (<xyz.h>)
- Replaces Macros with its values.
- [Output of this this step](Just_beginner_things/Compilation&Makefiles/print.i) has .i extn 
```
$gcc -E print.c -o print.i
```
This command produces a long file containing the full description of the macros and included header files if applicable.

## Compilation Step
- Takes the preprocessed files and create Intermediate Representation
- Some compilers create assembly code itself at this stage
- [Output](Just_beginner_things/Compilation&Makefiles/print.s) has .s extension
```
$gcc -S print.c -o print.s
```
This command produced a file written in assembly code since as we can see the suffix is ” l ” it refers to 32 bit architecture.

## Assembling Step
- IR to object code or binary 
- [Output](Operating-System-in-action/Just_beginner_things/Compilation&Makefilesprint.o) has .o extension
```
$gcc -c print.c -o print.o
```
Object file format is shown below where all the components of the object file are mentioned. Since the output of the object file is machine code it can't be opened .
Every object file comes with a symbol table to decode it.

## Linking Step
- Linking all source codes and header files
- Checks for static and dynamic libraries
- It creates an executable
```
$gcc  print.o -o print
$./print
```
- Output:The a.out format is the original file format for Unix.  It consists of three sections: text,data, and bss, which are for program code, initialized data, and uninitialized data, respectively.  This format is so simple that it doesn't have any reserved place for debugging information.  The only debugging format for a.out is stabs, which is encoded as a set of normal symbols with distinctive attributes.

Once the make command is executed the files were made in the given directory with their following extension.
The commands in makefile are not executed as they are written but are executed according to their dependencies.

All the steps mentioned above are processed through a make file which allows us to do all the steps in a single command.Thus reducing the work and makes the debugging easier and less error prone.
The following was the makefile description.
```
#Makefile
all: print print.o
print:print.o
	gcc print.o -o print

print.o:print.c
	gcc -c print.c -o print.o
	gcc -S print.c -o print.s
	gcc -E print.c -o print.i
```

### TRY IT YOURSELF
- clone the repository 
- navigate to [this folder](Operating-System-in-action/Just_beginner_things/Compilation&Makefiles)
- open this folder in terminal.
- finally run command shown below
```
make
```

