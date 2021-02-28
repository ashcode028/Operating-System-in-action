#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int sckid, nBytes;
  char buff[1024];
  struct sockaddr_in srvAdrs;
  socklen_t addr_size;

  /*Create UDP socket*/
   if((sckid = socket(PF_INET, SOCK_DGRAM, 0))<0)
  	  perror("cannot create socket\n");

  /*Configure settings in address struct*/
  srvAdrs.sin_family = AF_INET;
  srvAdrs.sin_port = htons(8080);
  srvAdrs.sin_addr.s_addr = INADDR_ANY;
  memset(srvAdrs.sin_zero, '\0', sizeof srvAdrs.sin_zero);  
  addr_size = sizeof srvAdrs;
  
   FILE *fd= fopen("para2.txt","r");
   if(!fd){
      printf("Error in opening the file\n");
    }
    fgets(buff, 500, fd);
    if(sendto(sckid,buff,strlen(buff)+1 ,0,(struct sockaddr*)&srvAdrs,addr_size)<0)
      perror("Sending packets failed");

  return 0;
}
