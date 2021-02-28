# Operating-System-in-action
This repository has all codes  and its explainations with "TRY IT YOURSELF SECTION".
For all those who love scripting,linux(kernal) programming or for those trying to explore it.
Assembly codes,makefiles,linux commands and much more to know more about the internals of OS.
This will be updated fully by december 2020.
Hope you all learn with me.
Any changes/updates are welcomed.

### Requirements-
* linux os
* gcc compiler
* nasm assembler
* qemu 
* Vmware-with linux instaled
- Rest can be installed as we require..You are ready to go.

### Beginners:
- [GCC and makefiles](Just_beginner_things/Compilation&Makefiles/README.md)
- [C and Assembly](Just_beginner_things/Combining_C&Assembly/README.md)
- [C and Assembly2](Just_beginner_things/A1/README.md)
- [Pointer Casting in C](Just_beginner_things/pointer_casting/README.md)
- [Differences In calling conventions 32 bit and 64 bit assembly codes](Just_beginner_things/A2/README.md)
### [Intermediate](Intermediate):
  1. **Pipes**-Write a C program which forks a child process. The parent process is responsible for accepting an input, and sending it to the child process through a pipe. The child process converts it into upper case, and sends the modified character back to the parent process. The parent process then prints the character received to a console.
  2. **MessageQueues**-Write two C programs, each of which reads the files “para1.txt” and “para2.txt” respectively.Split the text into tokens based on spaces. Create a message queue and use the same message queue to send the individual tokens to a third program. This third program should print the received message as is on the console.
  3. **Sockets**-Repeat the same process, but this time send it using datagram sockets. You can use different sockets to send messages, but the same port number should be used to receive them.
  4. **Shared Memory**-Write a program that forks a child and then creates two distinct shared memory segments to communicate with each other. One memory segment is used to write text, while the other segment is used to write numbers.To coordinate the reading and writing, a process always locks (using semaphore or mutexes) both the segments. You also need to think of a mechanism by which a reader process should know that a memory location has been written to or not.
  5. **Reader-Writer Problem with Synchronization**-Write a C program that involves multiple processes/threads where one of the processes/threads is a writer while there are multiple reader processes. You need to take care of problems related to race conditions using POSIX mutexes and semaphores. The processes may use a shared memory for 8 bytes (64-bits) that could be written to or read from.
  6. **Dining philosopher problem**-Write a C program to solve the dining philosopher problem where the philosophers are represented by threads. You need to ensure that your solution is free of deadlocks, i.e. it should be designed such that it avoids/prevents deadlocks.
  7. **Deadlock avoidance**-Banker's Algorithms
  
### Advanced:
  1. [Adding a systemcall](Adding_Syscall/README.MD)
  2. [DiningPhilosophers using Semaphores-customised](ModifiedDiningPhilosophers/README.MD)
  3. [Parsing csv files using syscalls](Read_csv_using_syscalls/README.MD)
  4. [Threads Vs Processes](PthreadVsFork/README.MD)
  5. [Creating own Bootloader](Bootloader/README.MD)
  6. [Creating own Rudimentary Text Editor](Rudimentary_text_editor/README.MD)
