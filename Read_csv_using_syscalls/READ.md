
# READING CSV USING SYSTEM CALLS
As the main function is evoked we create a process using fork().
Parent function reads the csv file ,computes the average of each student in section B.
Child process does the same thing but for section A students.I used a struct called student to store roll no,section,scores in 4 assignments and its
average.
I made an array of struct students and computed average differently for both
processes.
I removed the storage of the first line i.e label so that the values are stored accordingly.

## Error handling
  - While forking the current process -checked whether fork is being
done properly or not(pid<0)
  - In the child process ,after all the tasks are done I used exit(0) to avoid
abrupt ending and signalling the parent process about the exit.
  - In the parent process,I used the waitpid() command to wait till the
child process exited then checked it using WIFEXITED(status)
command.
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
  - Fgets-requires pointer to that file ,size of the input line and the pointer to store
input line. Once the line is stored in the array,I used string_token (strtok())to
break it into parts and store it in the respective fields of the struct(here student).
  - Usually open -is used to get file descriptor since I used fgets(), I used fopen to
get file pointer.Both take similar arguments name of the file and mode of the file
to be opened as(fopen-”r”.”w” ; open- O_RDONLY,O_WRONLY etc) .
  - I used the printf function to print the values to the console .

## Assumptions made
  - The input file must contain the first line as a label(student id,section,scores etc).
  - The input file must have only these entries and in the same order as roll
no,section,marks1,marks2,marks3,marks4.
  - The input file is a space separated csv file named as “data.csv”.