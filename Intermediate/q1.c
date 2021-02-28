#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


 int main()
 {
 	pid_t pid;
 	int fd1[2];
 	int fd2[2];

 	if(pipe(fd1)==-1){
 		fprintf(stderr,"Pipe1 failed");
 		return 1;
 	}
 	if(pipe(fd2)==-1){
 		fprintf(stderr,"Pipe2 failed");
 		return 1;
 	}
	pid=fork();
 	if(pid <0){
 		fprintf(stderr, "Fork failed\n");

 	}
 	else if(pid == 0){
 		char str2[500];
 		close(fd1[1]);
 		close(fd2[0]);   //close unwanted discripters
 		read(fd1[0], str2,sizeof(str2));
      		for (int i = 0; str2[i]!='\0'; i++) {
      			if(str2[i] >= 'a' && str2[i] <= 'z') {
         			str2[i] = str2[i] -32;
      			}
   		}
      		write(fd2[1], str2, sizeof(str2));
 	
 	}
 	else{

 		char str1[500];
 		//scanf("%[^\n]s", str1);
 		fgets(str1,500,stdin);
 		//str1=getchar();
 		close(fd1[0]);   // close unwanted descriptors
 		close(fd2[1]);
 		write(fd1[1],str1,sizeof(str1));
 		wait(NULL);
 		read(fd2[0], str1, sizeof(str1));
		printf("%s", str1 );

 	}
 	return 0;
 }
