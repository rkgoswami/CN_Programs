//Tcp Server Code

#include<bits/stdc++.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

void tcpConnectionSetUp(int &newSockfd){

	struct sockaddr_in server, client;

	//Step 1: Intialise sockect file discriptor i.e sockfd
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));


	//Step 2: Intialise structure members
	server.sin_family = AF_INET;
	server.sin_port = htons(4001);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: binding
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));

	//Step 4: 
	listen(sockfd,1);
	socklen_t clientLen = sizeof(client);
	newSockfd = accept(sockfd,(struct sockaddr*)&client,&clientLen);

	cout<<"\nServer is connected with client...";
}

int main(){

	cout<<"\n==============================";
	cout<<"\n\tServer";
	cout<<"\n==============================\n";

	//Step 1: Connection Setup
	int newSockfd;
	tcpConnectionSetUp(newSockfd);
	
	//Step 2: Read the file name from Client
	char *buffer = new char[1024];
	recv(newSockfd,buffer,10,0);
	int l = sizeof(buffer);
	buffer[l]='\0';
	cout<<"\nRequested File : "<<buffer<<"\n";

	//Step 3: Read the content of file and send it to client
	char buff[1024];
	FILE *fp = fopen(buffer,"r");

	while(!feof(fp)){
		bzero(buff,sizeof(buff));	
		fgets(buff,1024,fp);
		send(newSockfd,buff,strlen(buff),0);
		puts(buff);
	}

	printf("\n");
 
	return 0;
}
