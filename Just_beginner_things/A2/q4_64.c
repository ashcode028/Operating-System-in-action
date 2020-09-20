#include <stdlib.h>
#include<inttypes.h>
#include<stdio.h>
int64_t _long_add64(int64_t,int64_t,int64_t,int64_t);
//int _long_add32(int,int,int,int);
int main(){
  printf("Sum_64:%ld",_long_add64(4,5,6,8));
  //printf("Sum_32:%d",_long_add32(4,5,6,8));
}
