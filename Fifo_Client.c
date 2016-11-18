
// fifo client

#include<stdio.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define FIFO1 "fifo.1"
#define FIFO2 "fifo.2"
#define MAXLINE 4096


void client(int readfd,int writefd)
{
	ssize_t n;
	ssize_t len;
	char buf[MAXLINE];

	printf("Enter the file name: Ex : fifo.sh ) ");
	fgets(buf,MAXLINE,stdin);
	len=strlen(buf);
	
	if(buf[len-1]=='\n')
		len--;
	printf("\nWrite file name %s into pipe ",buf);

	write(writefd,buf,len);  

	printf("\nReading from pipe the contents of the filename and display it");

	while((n=read(readfd,buf,MAXLINE))>0)
		write(STDOUT_FILENO,buf,n);
	}

int main(int argc,char** argv){

	int readfd,writefd;
	
	writefd=open(FIFO1,O_WRONLY,0);  
	readfd=open(FIFO2,O_RDONLY,0); 

	client(readfd,writefd); 

	close(readfd);
	close(writefd);
	return 0;
}
