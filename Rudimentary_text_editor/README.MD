# Rudimentary Text Editor
It has basic functionality such as opening,saving,editing a line in the files.

I have made doubly linked list to implement the edit and save functionality of the editor .
```
struct Node                
{
	char s[200];                            
	int index;
	struct Node*prev,*next;            
};
```
For the working of the getch operator from the terminal i have used termios.h for handling terminal I/O.
Handled using struct called getch
```
int getch()                            //terminal I/O
{
	struct termios oldt,newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
```
1. ```tcgetattr``` — get the parameters associated with the terminal
2. Attribute selection- ```TCSANOW```-Change attributes immediately.
3. Flags disabled-
     - ```ECHO```        Enable echo.
     - ```ICANON```      Canonical input (erase and kill processing).

**addnode**
	- function to add a new node after a node q
```
void add_n(char t[],struct Node *q)        //function to add a new node after a node q
{
	struct Node*p=(struct Node*)malloc(sizeof(struct Node));
	struct Node *temp=q->next;
	strcpy(p->s,t);
	p->prev=q;
	p->next=q->next;

	if((q->next)!=NULL)        //adding the node to the list by manipulating pointers accordingly
	{
	((q->next)->prev)=p;
	while(temp!=NULL)
	{
	(temp->index)++;        //incrementing the index of the later nodes

	temp=temp->next;
	}
	}
	q->next=p;
	p->index = q->index + 1;                    //setting the index of the new node
}
```
**editcommands**
	- All the available options for the text editor
```

void edit_n(struct Node *p)                    //function to edit a line
{
	printf("Original line:\n%s",p->s);
	printf("New line:\n");
	gets(p->s);                            
	printf("Line edited\n");
}
```
**save**
	- function to save the file
	- writing the linked list contents to file
```
void save(FILE *fp)                            //function to save the file
{
	struct Node *temp=head->next;
	while(temp!=NULL)
	{
	fprintf(fp,"%s",temp->s);               //writing the linked list contents to file
	temp=temp->next;
	}
}
```
**editnode**
	- function to edit a line
```

void edit_n(struct Node *p)                    //function to edit a line
{
	printf("Original line:\n%s",p->s);
	printf("New line:\n");
	gets(p->s);                            
	printf("Line edited\n");
}
```
**printlist**
	- function to print all the lines stored in the buffer
```
void print_n(void)            //function to print all the lines stored in the buffer
{
	struct Node *temp=head;
	system("clear");
	while(temp->next!=NULL)
	{
	temp=temp->next;
	printf("%d %s\n",temp->index,temp->s);            
	}
}

```

I used **advisory record locks**-```fcntl``` for locking the file and to print the warning if opened simultanously
This lock waits till the lock is unlocked.
```
printf("Warning Already opened...\n");   
    	if (fcntl(fd, F_SETLKW, &fl) == -1) {
    		perror("fcntl");
    		exit(1);
    	}
    	printf("locked file\n");
```
We get notifications of getting unclocked but not for acquiring lock.
### TRY YOURSELF
- Clone the repo navigate to folder called Rudimentary_text_editor
- Open the folder in terminal and run `make`
- Shell Script:
```
#!/bin/bash
xterm -e bash -c "./editor test.txt; bash" &
xterm -e bash -c "./editor test.txt; bash" &
```

## Sources-
  https://gavv.github.io/articles/file-locks/#test-program
  http://www.qnx.com/developers/docs/7.0.0/#com.qnx.doc.neutrino.lib_ref/topic/f/fcntl.html
  https://man7.org/linux/man-pages/man0/termios.h.0p.html
  https://codeworldtechnology.wordpress.com/2009/07/02/program-to-make-a-text-editor-in-c/
  https://www.cs.utah.edu/~germain/PPS/Topics/C_Language/file_IO.html
  https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html
