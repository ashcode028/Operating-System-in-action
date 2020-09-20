
#include<stdio.h>

void main(){

char x[64];
long int *ptr=(long int*)x;  //type casting the pointer
for(int i=0;i<8;i++){
 scanf("%ld",ptr+i);
} 

}
