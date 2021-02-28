# Exercises
### Pipes
- Write a C program which forks a child process. The parent process is responsible for accepting an input, and sending it to the child process through a pipe. The child process converts it into upper case, and sends the modified character back to the parent process. The parent process then prints the character received to a console.
```
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
```
### MessageQueues
- Write two C programs, each of which reads the files “para1.txt” and “para2.txt” respectively.Split the text into tokens based on spaces. Create a message queue and use the same message queue to send the individual tokens to a third program. This third program should print the received message as is on the console.
1.  Struct to store message
```
struct msg_buffer {
   long msg_type;
   char msg[500];
} message;
```
2. Create Unique key and message 
```
 key_t my_key;
   int msg_id;
   my_key = ftok("progfile", 65); //create unique key
   msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
   message.msg_type = 1;
```
- Program1 snippet-Sending message in queue-[full here](Intermediate/q2a.c)
```
FILE *fd= fopen("para1.txt","r");
      if(!fd){
      printf("Error in opening the file\n");
      }
      //fgets(buff, 500, fd);
   while(fgets(buff, 500, fd)>0){	
   	char* token = strtok(buff," ");
   	while(token!=NULL){
   		strcpy(message.msg,token);
   		msgsnd(msg_id, &message, sizeof(message), 0);
   		token = strtok(NULL," ");
   	}
   }
   //msgsnd(msg_id, &message, sizeof(message), 0); //send message
   printf("Sent message is : %s \n", message.msg);
```
- Program2 snippet -Sending the message in the queue-[full here](Intermediate/q2b.c)
```
FILE *fd= fopen("para2.txt","r");
      if(!fd){
      printf("Error in opening the file\n");
      }
      //fgets(buff, 500, fd);
   while(fgets(buff, 500, fd)>0){	
   	char* token = strtok(buff," ");
   	while(token!=NULL){
   		strcpy(message.msg,token);
   		msgsnd(msg_id, &message, sizeof(message), 0);
   		token = strtok(NULL," ");
   	}
   }
   //msgsnd(msg_id, &message, sizeof(message), 0); //send message
   printf("Sent message is : %s \n", message.msg);
```
- Program3 snippet to recieve a message from the queue-[full here](Intermediate/q2c.c)
```
key_t my_key;
   int msg_id;
   my_key = ftok("progfile", 65); //create unique key

   msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
   msgrcv(msg_id, &message, sizeof(message), 1, 0); //used to receive message

   printf("Received Message is : %s \n", message.msg);
  // msgctl(msg_id, IPC_RMID, NULL); //destroy the message queue
```

### Sockets
- Repeat the same process, but this time send it using datagram sockets. You can use different sockets to send messages, but the same port number should be used to receive them.
1. Create socket and configure
```
/*Create UDP socket*/
   if((sckid = socket(PF_INET, SOCK_DGRAM, 0))<0)
  	  perror("cannot create socket\n");

  /*Configure settings in address struct*/
  srvAdrs.sin_family = AF_INET;
  srvAdrs.sin_port = htons(8080);
  srvAdrs.sin_addr.s_addr = INADDR_ANY;
  memset(srvAdrs.sin_zero, '\0', sizeof srvAdrs.sin_zero);  
  addr_size = sizeof srvAdrs;
```
- Program1 snippet to send packet to the socket-[full](Intermediate/q3a.c)
```
FILE *fd= fopen("para1.txt","r");
   if(!fd){
      printf("Error in opening the file\n");
    }
    fgets(buff, 500, fd);
    if(sendto(sckid,buff,strlen(buff)+1 ,0,(struct sockaddr*)&srvAdrs,addr_size)<0)
      perror("Sending packets failed");
```
- Program2 snippet to send packet to the socket-[full](Intermediate/q3b.c)
```
FILE *fd= fopen("para2.txt","r");
   if(!fd){
      printf("Error in opening the file\n");
    }
    fgets(buff, 500, fd);
    if(sendto(sckid,buff,strlen(buff)+1 ,0,(struct sockaddr*)&srvAdrs,addr_size)<0)
      perror("Sending packets failed");
```
- Program3 snippet to recieve packet from the socket:-[full](Intermediate/q3c.c)
```
 printf("waiting on port 8080\n");
  nBytes = recvfrom(sckid,buff,500,0,(struct sockaddr *)&srvSt, &addr_size);

  printf("received %d bytes\n", nBytes);
  if (nBytes > 0) {
         buff[nBytes] = 0;
         printf("received message: \"%s\"\n", buff);
   }

```
2. For sockets one socket connects to the host ,other has to wait till it is disabled.While for message queues more than one sender can send to single reciever at once.
### Shared Memory
- Write a program that forks a child and then creates two distinct shared memory segments to communicate with each other. 
- One memory segment is used to write text, while the other segment is used to write numbers.To coordinate the reading and writing, a process always locks (using semaphore or mutexes) both the segments.
```
void wait_s(int semid, int index)
{/*  wait operation  */
  struct sembuf s_ops[1];  /* only one semaphore operation to be executed */
   
   s_ops[0].sem_num = index;/* define operation on semaphore with given index */
   s_ops[0].sem_op  = -1;   /* subtract 1 to value for wait operation */
   s_ops[0].sem_flg = 0;    /* type "man semop" in shell window for details */

   if (semop (semid, s_ops, 1) == -1)
     {  perror ("Wait_s:Semaphore operation:");
        exit (-1);
     }
}

void signal_s(int semid, int index)
{/*signal operation*/
   struct sembuf s_ops[1];  

   s_ops[0].sem_num = index;
   s_ops[0].sem_op  = 1;    
   s_ops[0].sem_flg = 0;   

   if (semop (semid, s_ops, 1) == -1)
     {  perror ("Signal_s:Semaphore operation:");
        exit (-1);
     }
}

int sem_init(void)
{
   int semid;

   /* create new semaphore set of 2 semaphores */
   if ((semid = semget (IPC_PRIVATE, 2, IPC_CREAT | 0644)) < 0)
     {  perror ("semget:");/* 0600 = read/alter by user */
        exit (-1);
     }

   /* BUF_SIZE free spaces in empty buffer */
   if (semctl (semid,1, SETVAL, BUF_SIZE) < 0)
     {  perror ("semctl first:");
        exit (-1);
     }

   /* 0 items in empty buffer */
   if (semctl (semid, 0,SETVAL, 0) < 0) 
     {  perror ("semctl second :");
        exit (-1);
     }
   return semid;
}
```
- You also need to think of a mechanism by which a reader process should know that a memory location has been written to or not.
```
Use in and out buffer pointers to know present pointer for reader and writer
```
```
data = buffer[*out];
            *out = (*out + 1) % BUF_SIZE;
            printf ("Reader %d reading from segment1 %d\n", i, data);
            signal_s(semid,1); /* signal semaphore for space available */
 ```
 ```
 wait_s(semid,1);/* wait semaphore for space available */
            buffer[*in] = j*j+5;    /* put data in buffer */
            *in = (*in + 1) % BUF_SIZE;
            printf ("Writer %d writes %d to segment1\n",j, j*j+5);
            signal_s(semid, 0); /* signal semaphore for something used */
```
- [Full](Intermediate/q4.c)
### Reader-Writer Problem with Synchronization
- Write a C program that involves multiple processes/threads where one of the processes/threads is a writer while there are multiple reader processes. 
- You need to take care of problems related to race conditions using POSIX mutexes and semaphores. The processes may use a shared memory for 8 bytes (64-bits) that could be written to or read from.
- [Full](Intermediate/q5.c)
### Dining philosopher problem
- Write a C program to solve the dining philosopher problem where the philosophers are represented by threads. You need to ensure that your solution is free of deadlocks, i.e. it should be designed such that it avoids/prevents deadlocks.
- [Full](Intermediate/q6.c)
### Deadlock avoidance
- Banker's Algorithm
```
Applying safety algorithm in the given system.(In Bankers' Algorithm)
First calculate the need matrix by subtracting max resources from the allocated resources.
Then calculate work for each process (check need >=work).At first work is available resources.
While calculating we get that p1,p2 has more need than the available.Hence they were kept in waiting.
Resource type A-12
Resource type B-12
Resource type C-8
Resource type D-10
p0,p3 should be assigned since after that every process has need>=work.So sequence after that can be done in any way.
We get the safety sequence as p0,p3,p4,p1,p2.
```
