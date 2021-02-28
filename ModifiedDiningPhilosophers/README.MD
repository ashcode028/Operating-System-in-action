
# Construction of Semaphores using primitives:
   - Dining philosophers problem is implemented using the customised counting semaphore.

I implemented ```my_semaphore``` struct which needs 3 fields: count,mutex,condition variable
```
typedef struct my_semaphore {
  ssize_t value;       /*counter to count*/
  pthread_mutex_t m;     /*mutex to enable mutual exclusion/critical section issues for semaphore*/
  pthread_cond_t cv;     /*condition variable for CPU efficiency and for critical section (sleep and waking up threads)*/
} my_semaphore;

```
  - int type ```value``` to store value of the semaphore
  - pthread_mutex type variable ```m``` to ensure locks in semaphore to ensure mutual
exclusion for critical section issues
  - pthread_cond type variable ```cv``` to ensure there is no starvation and critical section
issues without wasting CPU cycles(also avoids deadlock)

Two primitives are :*wait,signal* -both are wrapped using lock to ensure only one thread is there.

**init function** initialises the fields with default values.
```
int sem_init(my_semaphore *s, int value) {
  s->value = value;                 /* initialize the counter to the given value */
  pthread_mutex_init(&s->m, NULL);   /* initialize a mutex to its default value */
  pthread_cond_init(&s->cv, NULL);/* initialize a condition variable to its default value */
  return 0;
}
```
**signal_print_s** prints the current value of the semaphore .
```
int signal_print_s(my_semaphore *s){
	printf("\nValue of semaphore:%d",(int)s->value);
	return s->value;
}
```
For the blocking variant I have locked using ``` pthread_mutex_lock ``` and for the non-blocking
variant I have used ``` pthread_mutex_trylock ``` rest all the code is the same.
My algorithm is working fine for both the variants
  - **signal_s(blocking) /signal_ns(non_blocking)**-
This is responsible for incrementing the count and to wake up any sleeping thread inside
the condition variable.For efficiency we call ​ pthread_cond_signal ​ only when there are
waiting threads
```
  void signal_s(my_semaphore *s) {
  pthread_mutex_trylock(&s->m);      /*  non blocking lock on the semaphore*/
  s->value++;                        /* increment the counter*/
  if (s->value == 1)                /* condition to pop out from waiting stage*/
  pthread_cond_signal(&s->cv);       /* unblock one thread that is blocked on the condition variable pointed to by cv.*/
  pthread_mutex_unlock(&s->m);   /* unlock the semaphore*/
}
```
  - **wait_s(blocking) /wait_ns(non_blocking)**-
This is responsible for decrement of the value only when its not zero ,till then it waiting
inside the condition variable and mutex is unlocked so
that other threads can enter.
```
  void wait_s(my_semaphore *s) {
  pthread_mutex_trylock(&s->m);   /* non blocking lock on the semaphore*/
  while (s->value == 0) {        /* while the counter is zero unlock the thread and wait  */
    pthread_cond_wait(&s->cv, &s->m); /*release the mutex pointed to by m and to cause the calling thread to block on the condition variable pointed to by cv. */
  }
  s->value--;                         /*decrement the counter*/
  pthread_mutex_unlock(&s->m);   /* unlock the semaphore*/
}
```
## Dining philosophers i have implemented in two ways
  - Philosophers are Semaphores- [here](ModifiedDiningPhilosophers/a4_2019028.c) i check whether my neighbor is eating or not and
then check both the bowls are available or not
and then proceed to eat.
Once i am done eating i notify my neighbors i completed if any one was hungry they will
eat.
  - Resources(forks,bowls) are Semaphores- [here](ModifiedDiningPhilosophers/A4_2019028.c) i check whether the forks,bowls i need
are there or not ,if present i will eat or else will wait in condition variable.
Once I'm done eating I notify that resources are available.

In both the implementation only one philosopher is allowed to enter and eat since both
the bowls should be available simultaneously to eat.
### TRY YOURSELF
- Clone the repo navigate to folder called ModifiedDiningPhilosophers
- Open the folder in terminal and run `make`
## SOURCES:
https://docs.oracle.com/cd/E19683-01/806-6867/6jfpgdcnd/index.html
geeksforgeeks articles, http://cs241.cs.illinois.edu/coursebook/Synchronization#mutex,
wikipedia,
http://www.cs.kent.edu/~ruttan/sysprog/lectures/multi-thread/multi-thread.html#thread_condvar_
example
https://cs61.seas.harvard.edu/wiki/images/1/12/Lec19-Semaphores.pdf
https://github.com/LoyolaChicagoBooks/operatingsystems/blob/master/source/deadlock.rsthttps://legacy.cs.indiana.edu/classes/p415-sjoh/hw/project/dining-philosophers/index.htm
https://xspdf.com/resolution/54548535.html
