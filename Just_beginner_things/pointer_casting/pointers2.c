#include<stdio.h>

void main(){

char x[64];
int *ptr=(int*)x;  //type casting the pointer
for(int i=0;i<16;i++){
 scanf("%d",ptr+i);
} 

}
