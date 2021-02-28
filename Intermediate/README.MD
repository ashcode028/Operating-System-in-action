# Exercises
### Pipes
- Write a C program which forks a child process. The parent process is responsible for accepting an input, and sending it to the child process through a pipe. The child process converts it into upper case, and sends the modified character back to the parent process. The parent process then prints the character received to a console.
### MessageQueues
- Write two C programs, each of which reads the files “para1.txt” and “para2.txt” respectively.Split the text into tokens based on spaces. Create a message queue and use the same message queue to send the individual tokens to a third program. This third program should print the received message as is on the console.
### Sockets
- Repeat the same process, but this time send it using datagram sockets. You can use different sockets to send messages, but the same port number should be used to receive them.
### Shared Memory
- Write a program that forks a child and then creates two distinct shared memory segments to communicate with each other. One memory segment is used to write text, while the other segment is used to write numbers.To coordinate the reading and writing, a process always locks (using semaphore or mutexes) both the segments. You also need to think of a mechanism by which a reader process should know that a memory location has been written to or not.
### Reader-Writer Problem with Synchronization
- Write a C program that involves multiple processes/threads where one of the processes/threads is a writer while there are multiple reader processes. You need to take care of problems related to race conditions using POSIX mutexes and semaphores. The processes may use a shared memory for 8 bytes (64-bits) that could be written to or read from.
### Dining philosopher problem
- Write a C program to solve the dining philosopher problem where the philosophers are represented by threads. You need to ensure that your solution is free of deadlocks, i.e. it should be designed such that it avoids/prevents deadlocks.
### Deadlock avoidance
- Banker's Algorithms
