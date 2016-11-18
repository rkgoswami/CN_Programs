
//fifo  server
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

void server(int readfd,int writefd)
{
	int fd;
	ssize_t n;
	char buf[MAXLINE+1];

	printf("\nReading from pipe the filename: ");
	n=read(readfd,buf,MAXLINE);
	buf[n]='\0';
	printf(" %s  ",buf);
 
	fd=open(buf,O_RDONLY);
	printf("\nReading from pipe the contents of the file and writing to client: ");

	while((n=read(fd,buf,MAXLINE))>0){
		write(writefd,buf,n);
		write(STDOUT_FILENO,buf,n);
	}
	close(fd);
}

int main(int argc,char** argv){
	
	int readfd,writefd;
	printf("\nCreating pipe...");

   	mkfifo(FIFO1, 0666);
   	mkfifo(FIFO2, 0666);

	readfd=open(FIFO1,O_RDONLY,0);
	writefd=open(FIFO2,O_WRONLY,0);

	server(readfd,writefd);
_	exit(0);

}

