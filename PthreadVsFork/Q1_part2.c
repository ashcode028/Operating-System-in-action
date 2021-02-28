/* Name: Ashita
   Roll_Number: 2019028 */
#include <unistd.h> 
#include <pthread.h>
#include<stdio.h>
#include<stdlib.h> 

int c=10;

void *child() 
{ 

    printf("Inside Thread\n"); 
    while(c!=-91){
 			printf("IN CHILD %d\n",c );
 			c-=1;
 	} 
    return NULL; 
} 
int main()
{
	pthread_t tid;

	 
	while(c!=100){
		c+=1;
 		printf("IN PARENT %d\n",c );
 			
 	} 
 	printf("Creating  Thread\n"); 
	pthread_create(&tid,NULL,child,NULL);
	printf("Joining Thread\n"); 
	pthread_join(tid, NULL);
	printf("Joined Thread\n"); 
	return 0;
}
