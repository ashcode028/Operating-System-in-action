#include <sys/types.h>     /* for pid_t */
#include <unistd.h>        /* for fork */   
#include <stdio.h>         /* for printf */
#include <sys/mman.h>      /* for mmap */
#include <sys/wait.h>      /* for waitpid */
#include <stdlib.h>        /* for exit */
#include <sys/sem.h>       /* for semaphore processing */
#include <string.h>

#define BUF_SIZE 5            /* logical size of buffer */
#define SHARED_MEM_SIZE (BUF_SIZE+2)*sizeof(int) /* size of shared memory */

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

int main (void)
{  
   /* set up shared memory segment */
   caddr_t shared_memory=mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, 
                              MAP_ANONYMOUS | MAP_SHARED, -1, 0);
   if (shared_memory == (caddr_t) -1)
     { perror ("mmap:");
       exit (1);
     }

   int *buffer = (int*) shared_memory; /* logical buffer starts at shared segment */
   int *in  = (int*) shared_memory + BUF_SIZE*sizeof(int);  /* pointer to logical 'in' address for writer */
   int *out = (int*) shared_memory + (BUF_SIZE+1)*sizeof(int);/* pointer to logical 'out' address for reader */

   *in = *out = 0;          /* initial starting points */
   

   int i, j;  
   int data;  /* stored value */

   int semid = sem_init();
   void* shmem = mmap(NULL, 128,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   int semid1 =sem_init();
   char *temp="Hello World";
   pid_t pid;          
   if ( (pid = fork())==-1) 
     { perror ("fork:");  
       exit (1);
     }

   if (pid==0)             
     { /* processing for child == reader */
       printf ("The reader process begins.\n");

       for (i = 0; i < 10; i++)
         {  wait_s(semid, 0);  /* wait semaphore for something used */
            data = buffer[*out];
            *out = (*out + 1) % BUF_SIZE;
            printf ("Reader %d reading from segment1 %d\n", i, data);
            signal_s(semid,1); /* signal semaphore for space available */
            if ((i % 4) == 1)      /* for delays */
              sleep(1); 
           wait_s(semid1, 0);  /* wait semaphore for something used */
            printf ("Reader %d reading from segment2 %s\n", i, (char*)shmem);
            signal_s(semid1,1); /* signal semaphore for space available */
            if ((i % 4) == 1)      /* for delays */
              sleep(1);  
         }
       printf ("Reader done.\n");
     } 
  else 
     { /* processing for parent == writer */
       printf ("The writer process begins.\n");
       
       for (j = 0; j<10; j++)
         {  wait_s(semid,1);/* wait semaphore for space available */
            buffer[*in] = j*j+5;    /* put data in buffer */
            *in = (*in + 1) % BUF_SIZE;
            printf ("Writer %d writes %d to segment1\n",j, j*j+5);
            signal_s(semid, 0); /* signal semaphore for something used */
            if ((j % 3) == 0)     /* for delays */
              sleep(1); 
              
            wait_s(semid1,1);/* wait semaphore for space available */
            memcpy(shmem, temp, sizeof(temp));
            printf ("Writer %d writes %s to segment2\n",j,(char*)shmem);
            signal_s(semid1, 0); /* signal semaphore for something used */
            if ((j % 3) == 0)     /* for delays */
              sleep(1);
          }
       waitpid(pid, NULL, 0);
       printf ("Writer done.\n");  

       /* deallocate shared memory */
       munmap (shared_memory, SHARED_MEM_SIZE);
     

       /* Remove the semaphore from the system and destroy the set of
          semaphores and data structure associated with it. */
       if (semctl (semid, 0, IPC_RMID) < 0)
         {  perror ("Remove semaphore:");
            exit (1);
         }
       if (semctl (semid1, 0, IPC_RMID) < 0)
         {  perror ("Remove semaphore:");
            exit (1);
         }
       printf ("Semaphore cleaned up.\n");
     }
   exit (0);
}
