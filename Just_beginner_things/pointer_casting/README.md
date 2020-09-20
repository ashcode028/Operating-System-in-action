# Pointers in C
Given a char array with size=64 .
## Store 8 long int type integers from input stream 
- sample code [pointers.c](Just_beginner_things/pointer_casting/pointers.c)
- Since char x[64] is a pointer itself which points to the first element of continuous memory of 1
byte each.(array pointer)
- As we need to store 8, 64 bit integers(long int). We have to type cast the pointer to long
int type pointer and run a loop 8 times to store it in the array. (8*8bytes=64 bytes=array size).
Each time we increment the pointer it will increase by its size.
Below is the code snippet.
```
char x[64];                   // given array
long int *ptr=(long int*)x;  //type casting the pointer
for(int i=0;i<8;i++){        
 scanf("%ld",ptr+i);
} 
```


## Store 16 int type integers from input stream 
- sample code [pointers2.c](Just_beginner_things/pointer_casting/pointers2.c)
- Again , for 16,32 bit integers we will type cast the array pointer to int type pointer and as they
are 16 of them we need to run the loop 16 times. (16*4bytes=64 bytes=array size)
Below is the code snippet.
```
char x[64];
int *ptr=(int*)x;  //type casting the pointer
for(int i=0;i<16;i++){
 scanf("%d",ptr+i);
```
