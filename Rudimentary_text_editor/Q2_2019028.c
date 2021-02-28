#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include<termios.h> 
#include<string.h>
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

struct Node                
{
	char s[200];                            
	int index;
	struct Node*prev,*next;            
};
struct Node *head;
void add_n(char t[],struct Node *q)        //function to add a new node after a node q
{
	struct Node*p=(struct Node*)malloc(sizeof(struct Node));
	struct Node *temp=q->next;
	strcpy(p->s,t);
	p->prev=q;
	p->next=q->next;

	if((q->next)!=NULL)        //adding the node to the list by manipulating pointers 	accordingly
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
void TEcommand(void)                        //function to print the list of editer commands
{
printf("\nSelect any command to edit\n");
printf("C :edit the current line\n");
printf("S :save changes\n");
}
void save(FILE *fp)                            //function to save the file
{
	struct Node *temp=head->next;
	while(temp!=NULL)
	{
	fprintf(fp,"%s",temp->s);                    //writing the linked list contents to file
	temp=temp->next;
	}
}

void edit_n(struct Node *p)                    //function to edit a line
{
	printf("Original line:\n%s",p->s);
	printf("New line:\n");
	gets(p->s);                            
	printf("Line edited\n");
}
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

int main(int argc, char *argv[])
    {
    	printf("\nMy Editor  \n");
    	                 /* l_type   l_whence  l_start  l_len  l_pid   */
    	struct flock fl = { F_WRLCK, SEEK_SET, 0,       0,     0 };
    	int fd;
        fl.l_pid = getpid();
    	char c;
    	char file[120];
    	FILE *fp;
    	head=(struct Node*)malloc(sizeof(struct Node));          
	(head->next)=(head->prev)=NULL;                //initialization
	(head->index)=0;
    	if (argc > 1) 
    		fl.l_type = F_RDLCK;
    	printf("\nFollowing options \n");
    	printf("R :open/creates a new file for editing\n");
		printf("Q :Quit\n");
	
		c=getch();                            
		switch(c)                            
		{
		case 'r' :
		case 'R' :
			printf("\nEnter the file name you want to open :");
			scanf("%s",file);
			getch();
			if ((fd = open(file, O_RDWR | O_CREAT)) == -1) {
    				perror("open");
    				exit(1);
    			}
    			fp=fopen(file,"rw");
			break;
		case 'q' :
		case 'Q' :
			system("clear");
			exit(1);
			break;
		}
    	printf("Warning Already opened...\n");   
    	if (fcntl(fd, F_SETLKW, &fl) == -1) {
    		perror("fcntl");
    		exit(1);
    	}
    	printf("locked file\n");
    	struct Node *buff=head; 
    	char buf[120]; 
	while((fgets(buf,201,fp))!=NULL)                //taking input from file
	{
		add_n(buf,buff);
		buff=buff->next;
	}
	print_n();                            
	TEcommand();
	struct Node *temp=head->next; 
	if(temp!=NULL)
		printf("Current cursor %d\n",temp->index);    
	else
		temp=head;
	c=getch();
	switch(c)                       
	{
		case 'c' :
		case 'C' :
			edit_n(temp);            
			break;
		case 's' :
		case 'S' :                   
			save(fp);
			break;
	}
    	
    	fl.l_type = F_UNLCK;  /* set to unlock same region */
    
    	if (fcntl(fd, F_SETLK, &fl) == -1) {
    		perror("fcntl");
    		exit(1);
    	}
    
    	printf("Unlocked.\n");
    
    	close(fd);
	return 0;
}
    


