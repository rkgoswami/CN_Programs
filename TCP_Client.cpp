//Tcp Server Code

#include<bits/stdc++.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

void tcpConnectionSetUp(int &sockfd){

	struct sockaddr_in server;

	//Step 1: Intialise sockect file discriptor i.e sockfd
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));


	//Step 2: Intialise structure members
	server.sin_family = AF_INET;
	server.sin_port = htons(4001);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: binding
	connect(sockfd,(struct sockaddr *)&server,sizeof(server));

	cout<<"\nClient is connected with server...";
}

int main(){

	cout<<"\n==============================";
	cout<<"\n\tClient";
	cout<<"\n==============================\n";

	int sockfd;
	tcpConnectionSetUp(sockfd);

	char fName[]="file.txt";
	//cout<<"\nEnter the file name to be feched";

	send(sockfd,fName,sizeof(fName),0);
	int l = sizeof(fName);
	fName[l]='\0';
	cout<<"\nRequested File : "<<fName<<"\n";


	//reading the buffer

	char buffer[1024];
	bzero(buffer,sizeof(buffer));

    while( recv(sockfd,buffer,79,0)>0 ) {
        printf("%s",buffer );
        bzero(buffer,strlen(buffer));
    }

    printf("\n");
    return 0;
}
