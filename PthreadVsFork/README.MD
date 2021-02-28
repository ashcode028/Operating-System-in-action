# Difference between pthreads and fork
  - When fork() was used, 9 to -90 was printed by child process and 11 to 100 was printed by parent process.
  - When threads were used,11 to 100 was printed by parent and then by thread from 100 to -90.
  - This happened because in case of fork the resources such as stack,data are not shared while in case of threads code,data, files are shared(each thread has its own stack and registers).
  - Hence, when child thread was made it started from current value of the global variable.
  - In case of fork- since data isnt shared each process runs independent of each other whereas threads can modify and get other threads' data from its shared resources.
  - Usually when child has same task as that of parent fork is used but when child(rather sibling in case of threads) has to complete a sub task of the parent threads are used. 
