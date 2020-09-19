#include<stdio.h>
#include <stdlib.h>
#include<inttypes.h>

int main(int argc,char *argv[]){               //to take inputs from console
int a, b;                                      //two variables
int64_t add(int64_t,int64_t);                 //function defined in nasm assembly-x86-64
if(argc < 3 || argc > 3){                      //to ensure only two argumemts are passed
    printf("Please enter only 2 arguments ");
    return 0;
}
a = atoi(argv[1]);                             //parsing to integers from characters
b = atoi(argv[2]);

printf("Sum: %ld\n",add(a,b));                     //printing the output off add function 
 
return 0;
}
