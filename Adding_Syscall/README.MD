# Adding a syscall in kernal v5.9

I have made syscall which takes pid and filename as input.
I found out task struct of the given pid by using find_vpid() function.
Using that pointer I printed out its fields to console using printk() function.
Using sprintf function i stored data into a buffer so that i can send it as a pointer to my kernal write.
I first converted user defined string to kernal defined string and then passed it as parameter to filp open so that it can create a file and write to it.
Using kernal_write function i wrote inside the file pointer which i got through filp open.

The user should check the available processes pids using ps -c command and enter it after the prompt.The path of the file is coded in the program,if not present it will automatically print. 
Error handling -
1.)when task struct related to the given pid is not found.Syscall returns with -1.
2.)when couldnt open file ,could write to the file.Syscall return with -1.
Error message is printed is printed in both the cases and shown in error log.

Sources- stackoverflow,dev.to,medium,kernal documentation,howtoforge..com,lab assignment guidelines of various international institutes(cant remember names).
diff command used-sudo diff -Nrq ~/linux-5.9.1/ ~/Desktop/linux-5.9.1 > ~/Documents/Os/OSAssign2/Q2/diff.txt
