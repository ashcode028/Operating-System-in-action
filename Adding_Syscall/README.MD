# Adding a syscall in kernal v5.9
Demonstration
	- follow [this](https://dev.to/jasper/adding-a-system-call-to-the-linux-kernel-5-8-1-in-ubuntu-20-04-lts-2ga8) tutorial to see the basic template of adding a syscall.
	- DO it in a virtual box if in windows or vmware if in linux 
 - Made syscall which takes pid and filename as input.```SYSCALL_DEFINE2(sh_task_info, int, pid,char *,filename)```and prints fields of task_struct in a filename.
 - Task struct of the given pid is found by using find_vpid() function.```task = pid_task(find_vpid(pid), PIDTYPE_PID);```
 - Using that pointer printed out its fields to console using printk() function.
 - Using sprintf function i stored data into a buffer so that i can send it as a pointer to my kernal write.
 - I first converted *user-defined string to kernal-defined string*and then passed it as parameter to filp open so that it can create a file and write to it.```file = filp_open(filen, O_WRONLY|O_CREAT, 00700);```
 - Using kernal_write function i wrote inside the file pointer which i got through filp open.
  ```
 #include<linux/kernel.h>
+#include<linux/init.h>
+#include<linux/sched.h>
+#include<linux/syscalls.h>
+#include <linux/fs.h>
+#include <asm/segment.h>
+#include <asm/uaccess.h>
+#include <linux/buffer_head.h>
+#include <linux/module.h>
+#include <linux/file.h>
+
+SYSCALL_DEFINE2(sh_task_info, int, pid,char *,filename)
+{
+
+  struct task_struct *task;
+  char data[2096];
+  int n=0;
+  task = pid_task(find_vpid(pid), PIDTYPE_PID);
+  if (task == NULL)
+  {
+    // Print the error to the kernel buffer
+    printk(KERN_INFO "Cannot find a process with that PID: %d\n", pid);
+    return -ESRCH;
+  }
+  else
+  {
+     sprintf(data,"Process: %s\nPID_Number: %ld\nProcess Priority: %ld\n Normal Priority: %ld\nStatic Priority: %ld\nRT_Priority: %ld\nProcess State: %ld\nProcess CPU: %ld\nProcess TGID: %ld\nSched Entity on_rq: %ld\nProcess Vruntime: %ld\nProcess exec_start: %ld\nProcess sum_exec_runtime: %ld\nthread_struct sp: %lu\nsigset_t blocked and real_blocked: %lu  %lu\n",task->comm,(long)task->pid,(long)task->prio,(long)task->static_prio,(long)task->normal_prio,(long)task->rt_priority,(long)task->state,(long)task->on_cpu,(long)task->tgid,(long)task->se.on_rq,(long)task->se.vruntime,(long)task->se.exec_start,(long)task->se.sum_exec_runtime,(unsigned long)task->thread.sp,(unsigned long)task->blocked.sig[0],(unsigned long)task->real_blocked.sig[0]);
+	printk(data);
+
+  struct file *file;
+  loff_t *pos = 0;
+  //struct filename *filen=getname(filename);
+  //struct file *file=ERR_CAST(filen);
+  char filen[100];
+  copy_from_user(filen,filename,100);
+  file = filp_open(filen, O_WRONLY|O_CREAT, 00700);
+  if(!file){
+  	printk("SYS_sh_task_info: error in opening file\n");
+        return(-1);
+  }
+  else {
+    kernel_write(file,data,sizeof(data),pos);
+    filp_close(file,NULL);
+  }
+    
+  }
+  return n;
+}
+
```
 - The user should check the available processes pids using ```ps -c ```command and enter it after the prompt.The path of the file is coded in the program,if not present it will automatically print. 
 ```
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
 ```

## Error handling -
  - when task struct related to the given pid is not found.Syscall returns with -1.
  - when couldnt open file ,could write to the file.Syscall return with -1.
  - Error message is printed is printed in both the cases and shown in error log.
  - diff command```sudo diff -Nrq ~/linux-5.9.1/ ~/Desktop/linux-5.9.1 > ~/Documents/Os/OSAssign2/Q2/diff.txt ```
## Sources- 
stackoverflow,[dev.to](https://dev.to/jasper/adding-a-system-call-to-the-linux-kernel-5-8-1-in-ubuntu-20-04-lts-2ga8),medium,kernal documentation,howtoforge..com,lab assignment guidelines of various international institutes(cant remember names).

### TRY YOURSELF
- Clone the repo navigate to folder called Adding_Syscall
- Open the folder in terminal and run `make`
