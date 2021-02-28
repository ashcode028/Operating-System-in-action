#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h>
#include<string.h>
#define delim " ,\t\r\n\a"


typedef struct student{
   int rollno;
   char section[1];
   int marks1;
   int marks2;
   int marks3;
   int marks4;
   float avg;

}stud;


int main() {


   pid_t pid = fork();
   int status;

   if (pid < 0) {
      perror("fork() failure\n");
      return 1;
   }
   // Child process
   if (pid == 0) {

      FILE *fd= fopen("data.csv","r");
            //int fd= open("data.csv",O_RDONLY);
      if(!fd){
      printf("Error in opening the file\n");
      return 0;
      }
   
      int rows=0;
      int i=0;
      stud scores[402];
      char temp[400][70];
      while(fgets(temp[i],1024,fd)){   //read(fd,buff,1024)
         //printf("%s",buff );    //write(1,buff,1024)
         rows++;
         if(rows != 1){
            temp[i][strlen(temp[i]) -1 ]='\0';
            i++;
         }
      }
      int total =i;
      //close(fd);
      fclose(fd);
      for(int i=0;i<total;i++){
         int cols=0;
         char *token = strtok(temp[i],delim);
         while(token) {
            //printf("%d",cols);
            if(cols == 0)  
               scores[i].rollno=atoi(token);
 
            if(cols == 1){
               strcpy(scores[i].section,token);
            }
            
             if(cols == 2)
               scores[i].marks1=atoi(token);
            
            if(cols == 3)  
               scores[i].marks2=atoi(token);
            
            if(cols == 4)  
               scores[i].marks3=atoi(token);
            
            if(cols == 5)
               scores[i].marks4=atoi(token);
         
             token = strtok(NULL,delim);
             cols++;
         }
         if(strcmp(scores[i].section,"A")==0){
            scores[i].avg=(scores[i].marks1+scores[i].marks2+scores[i].marks3+scores[i].marks4)/4;
            printf("roll_no:%d  section:%s  scores: %d %d %d %d  average: %0.2f\n",scores[i].rollno,scores[i].section,
            scores[i].marks1,scores[i].marks2,scores[i].marks3,scores[i].marks4,scores[i].avg);
         }
      }
      exit(0);     
   }

      else {  
         //pid_t wpid;
         //int status;
         waitpid(pid,&status,0);
         
         if(WIFEXITED(status)){
            FILE *fd= fopen("data.csv","r");
            //int fd= open("data.csv",O_RDONLY);
            if(!fd){
            printf("Error in opening the file\n");
            return 0;
            }
            int rows=0;
            int i=0;
            stud scores[402];
            char temp[400][70];
            while(fgets(temp[i],1024,fd)){   //read(fd,buff,1024)
               //printf("%s",buff );    //write(1,buff,1024)
               rows++;
               if(rows != 1){
                  temp[i][strlen(temp[i]) -1 ]='\0';
                  i++;
               }
            }
            int total =i;
            //close(fd);
            //fclose(fd);
            for(int i=0;i<total;i++){
               int cols=0;
               char *token = strtok(temp[i],delim);
               while(token) {
                  //printf("%d",cols);
                  if(cols == 0)  
                     scores[i].rollno=atoi(token);
 
                  if(cols == 1){
                     strcpy(scores[i].section,token);
                  }
            
                  if(cols == 2)
                     scores[i].marks1=atoi(token);
            
                  if(cols == 3)  
                     scores[i].marks2=atoi(token);
            
                  if(cols == 4)  
                     scores[i].marks3=atoi(token);
            
                  if(cols == 5)
                     scores[i].marks4=atoi(token);
                  token = strtok(NULL,delim);
                  cols++;
               }
               if(strcmp(scores[i].section,"B")==0){
                  scores[i].avg=(scores[i].marks1+scores[i].marks2+scores[i].marks3+scores[i].marks4)/4;
                  printf("roll_no:%d  section:%s  scores: %d %d %d %d  average: %0.2f\n",scores[i].rollno,scores[i].section,
                  scores[i].marks1,scores[i].marks2,scores[i].marks3,scores[i].marks4,scores[i].avg);
               }
            }
            fclose(fd);
         }

      }   
   return 0;
}
