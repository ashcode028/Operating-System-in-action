# Difference between pthreads and fork
  - Demonstration of working of fork and pthread
      - create global variable c
      - increment its value in parent process/thread
      - decrement its value in child process/thread
## Running the code
  - Using fork and checking the value of global variable *c*
  ```
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
  
  ```
  - Using pthread and checking the value of global variable *c*
  ```
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
  ```
## Difference noted:
  - When fork() was used, 9 to -90 was printed by child process and 11 to 100 was printed by parent process.
  - When threads were used,11 to 100 was printed by parent and then by thread from 100 to -90.
  - This happened because in case of fork the resources such as stack,data are not shared while in case of threads code,data, files are shared(each thread has its own stack and registers).
  - Hence, when child thread was made it started from current value of the global variable.
  - In case of fork- since data isnt shared each process runs independent of each other whereas threads can modify and get other threads' data from its shared resources.
  - Usually when child has same task as that of parent fork is used but when child(rather sibling in case of threads) has to complete a sub task of the parent threads are used. 
