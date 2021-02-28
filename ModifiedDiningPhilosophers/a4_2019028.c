/*
Name:	Ashita
RollNo:2019028
*/

#include <pthread.h> 
#include <stdio.h> 
#include<unistd.h>
typedef struct my_semaphore {
  ssize_t value;    /*counter to count*/
  pthread_mutex_t m;   /*mutex to enable mutual exclusion/critical section issues for semaphore*/
  pthread_cond_t cv;    /*condition variable for CPU efficiency and for critical section (sleep and waking up threads)*/
} my_semaphore;

int pm_init(my_semaphore *s, int value) {
  s->value = value;                   /* initialize the counter to the given value */
  pthread_mutex_init(&s->m, NULL); /* initialize a mutex to its default value */
  pthread_cond_init(&s->cv, NULL);/* initialize a condition variable to its default value */
  return 0;
}
void wait_s(my_semaphore *s) {
  pthread_mutex_lock(&s->m);            /* blocking lock on the semaphore so that only one thread enters*/
  while (s->value == 0) {                /* while the counter is zero unlock the thread and wait  */
    pthread_cond_wait(&s->cv, &s->m); /*release the mutex pointed to by m and to cause the calling thread to block on the condition variable pointed to by cv. */
  }
  s->value--;                       /*decrement the counter*/
  pthread_mutex_unlock(&s->m);          /* unlock the semaphore*/
}

void signal_s(my_semaphore *s) {
  pthread_mutex_lock(&s->m);         /*blocking lock on the semaphore*/
  s->value++;                        /*increment the count*/
  if (s->value == 1)                 /* call only when necessary,if any waiting threads are there*/
  pthread_cond_signal(&s->cv);    /*unblock one thread that is blocked on the condition variable pointed to by cv.*/
  /* A woken thread must acquire the lock, so it will also have to wait until we call unlock*/
  pthread_mutex_unlock(&s->m);    /* unlock the semaphore*/
}

void wait_ns(my_semaphore *s) {
  pthread_mutex_trylock(&s->m);   /* non blocking lock on the semaphore*/
  while (s->value == 0) {             /* while the counter is zero unlock the thread and wait  */
    pthread_cond_wait(&s->cv, &s->m); /*release the mutex pointed to by m and to cause the calling thread to block on the condition variable pointed to by cv. */
  }
  s->value--;                         /*decrement the counter*/
  pthread_mutex_unlock(&s->m);   /* unlock the semaphore*/
}

void signal_ns(my_semaphore *s) {
  pthread_mutex_trylock(&s->m);      /* non blocking lock on the semaphore*/
  s->value++;                        /* increment the counter*/
  if (s->value == 1)                /* condition to pop out from waiting stage*/
  pthread_cond_signal(&s->cv);       /* unblock one thread that is blocked on the condition variable pointed to by cv.*/
  pthread_mutex_unlock(&s->m);   /* unlock the semaphore*/
}

int signal_print_s(my_semaphore *s){
	printf("Value of semaphore:%d\n",(int)s->value);/* print value of semaphore*/
	return s->value;
}

#define THINKING 2 /*State of philosopher*/
#define HUNGRY 1  /*State of philosopher*/
#define EATING 0 /*State of philosopher*/
#define N 5 /*NO of forks or philosphers*/
#define RIGHT (i+ 1) % N /* right neighbor */
#define LEFT (i+ 4) % N /*left neighbor */

int phil[N] = { 0, 1, 2, 3, 4 }; /*int value of each philosopher*/
int pflag[N];  /*State  of each philosopher*/
my_semaphore mutex; /* mututal exclusion for critical section*/
my_semaphore forks[N];  /*Semaphore for each fork or philosopher */ 
  
void test(int i) 
{ 
    if (pflag[i] == HUNGRY && pflag[LEFT] != EATING && pflag[RIGHT] != EATING) {   /*Check are both available */ 
        pflag[i] = EATING; /*set that philospher is eating now */
        sleep(2); 
        printf("Philosopher %d takes fork %d and %d\n",i + 1, LEFT + 1, i + 1); /*print acquired forks*/
        signal_s(&forks[i]); /*wake up hungry philosphers */
    } 
} 
void take_fork(int i) 
{ 
    wait_s(&mutex);  /*enter critical section */
    pflag[i] = HUNGRY; /*set that philospher is hungry  */
    test(i);          /*try to get both forks */
    signal_s(&mutex); /*exit critical section */
    wait_s(&forks[i]); /*block if forks were not available */
    sleep(1); 
} 

void put_fork(int i) 
{ 
    wait_s(&mutex); /*enter critical section */
    pflag[i] = THINKING;  /*set that philospher is thinking */
    test(LEFT);         /*see if left neighbor can eat */
    test(RIGHT);       /*see if right neighbor can eat */
    signal_s(&mutex); /*exit critical section */
} 
  
void* philospher(void* num) 
{ 
    while (1) { /*send threads indefinitely  */
      int* i = num; /*convert the arg into required type of parameter */
		  sleep(1);   /* delay while sending same type of thread*/
      take_fork(*i); /* acquire forks or block */
      sleep(0);   /* eat */
      put_fork(*i); /* put back both forks and check whether neighbors are hungry */
    } 
} 
  
int main() 
{ 
    int i;
    pthread_t tid[N]; /* declare threads  */
    pm_init(&mutex, 1); /* initialise semaphores  */
  
    for (i = 0; i < N; i++) {
        pm_init(&forks[i], 0);  /* initialise semaphores  */
	}
    for (i = 0; i < N; i++) { 
		//a[i]=i;
        pthread_create(&tid[i], NULL, philospher, &phil[i]);  /* create threads  */
    } 
  
    for (i = 0; i < N; i++) {
        pthread_join(tid[i], NULL); /* wait for all threads to complete and join (here not possible)  */
  	}
} 