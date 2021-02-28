/*
Name:	Ashita
RollNo:2019028
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>


typedef struct my_semaphore {
  ssize_t value;       /*counter to count*/
  pthread_mutex_t m;     /*mutex to enable mutual exclusion/critical section issues for semaphore*/
  pthread_cond_t cv;     /*condition variable for CPU efficiency and for critical section (sleep and waking up threads)*/
} my_semaphore;

int sem_init(my_semaphore *s, int value) {
  s->value = value;                 /* initialize the counter to the given value */
  pthread_mutex_init(&s->m, NULL);   /* initialize a mutex to its default value */
  pthread_cond_init(&s->cv, NULL);/* initialize a condition variable to its default value */
  return 0;
}
void wait_s(my_semaphore *s) {
  pthread_mutex_trylock(&s->m);   /* non blocking lock on the semaphore*/
  while (s->value == 0) {        /* while the counter is zero unlock the thread and wait  */
    pthread_cond_wait(&s->cv, &s->m); /*release the mutex pointed to by m and to cause the calling thread to block on the condition variable pointed to by cv. */
  }
  s->value--;                         /*decrement the counter*/
  pthread_mutex_unlock(&s->m);   /* unlock the semaphore*/
}

void signal_s(my_semaphore *s) {
  pthread_mutex_trylock(&s->m);      /*  non blocking lock on the semaphore*/
  s->value++;                        /* increment the counter*/
  if (s->value == 1)                /* condition to pop out from waiting stage*/
  pthread_cond_signal(&s->cv);       /* unblock one thread that is blocked on the condition variable pointed to by cv.*/
  pthread_mutex_unlock(&s->m);   /* unlock the semaphore*/
}


int signal_print_s(my_semaphore *s){
	printf("\nValue of semaphore:%d",(int)s->value);
	return s->value;
}
#define LEFT (i+ 4) % 5         /*Availability of right fork */
#define RIGHT i              /*Availability of right fork */
int phil[5] = { 0, 1, 2, 3, 4 }; /*int value of each philosopher*/
my_semaphore me;             /* mututal exclusion for critical section*/
my_semaphore bowls[2];      /*Semaphore for each bowl */ 
my_semaphore forks[5];     /*Semaphore for each fork */ 
void take_food(int i){
	wait_s(&me);               /*enter critical section */
	printf("\nPhilosopher %d entered",i+1);
	wait_s(&forks[LEFT]);       /*see if left fork available */
	wait_s(&forks[RIGHT]);      /*see if right fork available */
	wait_s(&bowls[0]);         /*see if bowl 1 available */
	wait_s(&bowls[1]);           /*see if bowl 2 available */
	//signal_print_s(&forks[LEFT]);
	printf("\nPhilosopher %d is eating with %d and %d fork",i+1,LEFT+1,RIGHT+1);
	signal_s(&me);               /*exit critical section */
}
void leav_food(int i){
	wait_s(&me);                /*enter critical section */
	printf("\nPhilosopher %d left",i+1);
	signal_s(&forks[LEFT]);     /*release left fork  */
	signal_s(&forks[RIGHT]);    /*release right fork  */
	signal_s(&bowls[0]);        /* release bowl 1  */
	signal_s(&bowls[1]);        /* release bowl 2  */
	signal_s(&me);           /*exit critical section */
}
void * philosopher(void * num)
{
	while(1){             /*send threads indefinitely  */
		int i=*(int *)num;       /*convert the arg into required type of parameter */
		sleep(3);              /* delay while sending same type of thread*/
		take_food(i);           
		sleep(0);             /* eat */
		leav_food(i);
	}
}

int main()
{	int i;
	pthread_t tid[5];
	sem_init(&me,4);
	//sem_init(&forks,5);
	//sem_init(&bowls,2);
	 for (i = 0; i < 5; i++) {
        sem_init(&forks[i], 1);  /* initialise fork semaphores  */
	}
	 for (i = 0; i < 2; i++) {
        sem_init(&bowls[i], 1);  /* initialise bowl semaphores  */
	}
	for(i=0;i<5;i++){
		//a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,&phil[i]);       /* create threads  */
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);       /* wait for all threads to complete and join (here not possible)  */
	return 0;
}
