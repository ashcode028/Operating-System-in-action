#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5 
#define LEFT i
#define RIGHT (i+1) % N 
sem_t room;
sem_t forks[5];
void * philosopher(void * num)
{
	int i=*(int *)num;

	sem_wait(&room);
	printf("\nPhilosopher %d has entered room",i+1);
	sem_wait(&forks[LEFT]);
	sem_wait(&forks[RIGHT]);

	printf("\nPhilosopher %d is eating with %d and %d fork",i+1,LEFT,RIGHT);
	sleep(2);

	sem_post(&forks[RIGHT]);
	sem_post(&forks[LEFT]);
	printf("\nPhilosopher %d is thinking",i+1);
	sem_post(&room);
}


int main()
{
	int i,a[5];
	pthread_t tid[5];
	
	sem_init(&room,0,4);
	
	for(i=0;i<5;i++)
		sem_init(&forks[i],0,1);
		
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
	return 0;
}
