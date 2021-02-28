#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#define SHM_SIZE 8 /* make it a 8byte hared memory segment */
char *data;
sem_t mutex,mutex_w;
pthread_t writerthreads[10],readerthreads[102];
int readercount = 0;

void *writer(void* param)
{   char *temp="Please Wait";
    int i=(int)param;
    printf("%d Writer is trying to enter\n",i);
    sem_wait(&mutex_w);
    
    printf("Writer %d writing to segment: \"%s\"\n", i,temp);
    strncpy(data,temp, SHM_SIZE);
    sem_post(&mutex_w);
    printf("%d Writer is leaving\n",i);
    return NULL;
}

void *reader(void* param)
{
    int i=(int)param;
    sem_wait(&mutex);
    readercount++;
    if(readercount==1)
        sem_wait(&mutex_w);
    sem_post(&mutex);
    printf("%d reader is inside\n",i);
    printf("Reader %d reading from segment:\"%s\"\n", i,data);
    usleep(3);
    sem_wait(&mutex);
    readercount--;
    if(readercount==0)
    {
        sem_post(&mutex_w);
    }
    sem_post(&mutex);
    printf("%d Reader is leaving\n",i);
    return NULL;
}


int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    int mode;
    /* make the key: */
    if ((key = ftok("hello.txt", 'R')) == -1) /*Here the file must exist */ 
	{
        perror("ftok");
        exit(1);
    }

    /*  create the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }
    int i;
    int n2=5;
    int n1[n2];
    sem_init(&mutex,0,1);
    sem_init(&mutex_w,0,1);
    for(i=0;i<n2;i++)
    {
        pthread_create(&writerthreads[i],NULL,writer,(void *)i);
        pthread_create(&readerthreads[i],NULL,reader,(void *)i);
    }
    for(i=0;i<n2;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }


    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    /* delete the segment: 
    if (shmctl(shmid,IPC_RMID,NULL) == -1) {
        perror("shmdt");
        exit(1);
    }
    */
    return 0;
}

