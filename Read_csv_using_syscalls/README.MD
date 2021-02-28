# READING CSV USING SYSTEM CALLS
Demonstration to read csv using fgets and then calculate average of the scores of section A and section B using fork().

# Steps to run 
  - Sample [code](Read_csv_using_syscalls/q1.c) file name *q1.c* 
  - Make file contents- (when name of the file is *q1.c*)
```
#Makefile
all: q1 q1.o
q1:q1.o
	gcc q1.o -o q1
	./q1

q1.o:q1.c
	gcc -c q1.c -o q1.o
	gcc -S q1.c -o q1.s
	gcc -E q1.c -o q1.i	
```

  - As the main function is evoked we create a process using fork().
  - Parent function reads the csv file ,computes the average of each student in section B.
  - Child process does the same thing but for section A students.I used a struct called student to store roll no,section,scores in 4 assignments and its
average.
  - Made an array of struct students and computed average differently for both
processes.
  - Removed the storage of the first line i.e label so that the values are stored accordingly.

## Error handling
  - While forking the current process -checked whether fork is being
done properly or not(pid<0)
```
 if (pid < 0) {
      perror("fork() failure\n");
      return 1;
   }
```
  - In the child process ,after all the tasks are done I used exit(0) to avoid
abrupt ending and signalling the parent process about the exit.

  - In the parent process,I used the waitpid() command to wait till the
child process exited then checked it using WIFEXITED(status)
command. ```
     waitpid(pid,&status,0);   
     if(WIFEXITED(status)) ```
## Fgets() instead of read()
  - While using read syscall -i required file descriptor,buff to store ,and its size to be
mentioned so that it can read that amount of bytes from the file.
  - But when i used it i couldn't get the correct amount of size to be sent to the buffer
since each line has different no of bytes requirement as in some columns roll no
was 3 digit and marks in 1 digit.
  - So if i read some amount of bytes for the first line if the second line required one
more or less bytes got affected in the second run of loop so i couldn't extract the
line and its values.Thus,incorrect values get stored into the specific fields of the
struct thereby giving wrong output.
## Syscalls ,arguments,outcomes
  - Read syscall-requires file descriptor
 ```
   read(fd,buff,1024);
   printf("%s",buff );
   write(1,buff,1024)
```
  - Fgets-requires pointer to that file ,size of the input line and the pointer to store
input line. ```while(fgets(temp[i],1024,fd))```
  - Once the line is stored in the array,I used string_token ```strtok()``` to
break it into parts and store it in the respective fields of the struct(here student).
  - Usually open ```int fd= open("data.csv",O_RDONLY)```is used to get file descriptor since I used fgets(), I used fopen to get file pointer.Both take similar arguments name of the file and mode of the file
to be opened as```FILE *fd= fopen("data.csv","r") ```
  - I used the printf function to print the values to the console .

## Assumptions made
  - The input file must contain the first line as a label(student id,section,scores etc).
  - The input file must have only these entries and in the same order as roll
no,section,marks1,marks2,marks3,marks4.
  - The input file is a space separated csv file named as [data.csv](Read_csv_using_syscalls/data.csv).

