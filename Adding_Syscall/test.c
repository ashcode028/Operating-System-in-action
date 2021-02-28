/* Name: Ashita
   Roll_Number: 2019028 */
#include <stdio.h>
#include <linux/kernel.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  // Get args from terminal and call my syscall with that PID.
	char * p="final.txt";
	//int pid=1024;
	int pid;
	printf("Enter an pid aftr checking pids from 'ps -c' command: ");
	scanf("%d", &pid);
	long int Check = syscall(440,pid,p);
	printf("System call sh_task_info returned %ld\n", Check);
	return 0;
}
