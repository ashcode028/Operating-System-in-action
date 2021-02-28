#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
// structure for message queue
#define delim " ,\t\r\n\a"
char buff[500];
struct msg_buffer {
   long msg_type;
   char msg[500];
} message;
void main() {
   key_t my_key;
   int msg_id;
   my_key = ftok("progfile", 65); //create unique key
   msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
   message.msg_type = 1;
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
}

