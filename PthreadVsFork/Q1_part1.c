/* Name: Ashita Boyina
   Roll_Number: 2019028 */
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int c= 10;
 int main()
 {
 	pid_t pid;
 	pid=fork();
 	int status;

 	if(pid <0){
 		fprintf(stderr, "Fork failed\n");
 	}
 	else if(pid == 0){
 		//child process
 		while(c!=-90){
 			printf("%d\n",--c );
 		}
 		exit(0);

 	}
 	else{
 		// parent process
 		waitpid(pid,&status,0); //wait for its child to complete
 		while(c<100){
 			printf("%d\n",++c );
 		}
 		

 	}
 	return 0;
 }