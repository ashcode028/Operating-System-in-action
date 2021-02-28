#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int sckid, nBytes;
  char buff[500];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage srvSt;
  socklen_t addr_size;
  /*Create UDP socket*/
  if((sckid = socket(PF_INET, SOCK_DGRAM, 0))<0)
  	  perror("cannot create socket\n");

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); 
  /*Bind socket with address struct*/
  if(bind(sckid, (struct sockaddr *) &serverAddr, sizeof(serverAddr))<0)
  	perror("bind failed");
  	
  addr_size = sizeof srvSt;

/* Recieve packets*/
  printf("waiting on port 8080\n");
  nBytes = recvfrom(sckid,buff,500,0,(struct sockaddr *)&srvSt, &addr_size);

  printf("received %d bytes\n", nBytes);
  if (nBytes > 0) {
         buff[nBytes] = 0;
         printf("received message: \"%s\"\n", buff);
   }

  return 0;
}
