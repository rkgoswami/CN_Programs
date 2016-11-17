//Tcp Server Code

#include <bits/stdc++.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>



using namespace std;
struct sockaddr_in server, client;

void UdpConnectionSetUp(int &sockfd){

	
	//Step 1: Intialise sockect file discriptor i.e sockfd
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	//Step 2: Intialise structure members
	server.sin_family = AF_INET;
	server.sin_port = htons(4008);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: binding
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));

}

int main(){

	cout<<"\n==============================";
	cout<<"\n\tUdp Server";
	cout<<"\n==============================\n";

	int sockfd;
	UdpConnectionSetUp(sockfd);

	//Recieve
	char *buffer;
	socklen_t clientLen = sizeof(struct sockaddr);
	recvfrom(sockfd,buffer,10,0,(struct sockaddr *)&client,&clientLen);
	int l = sizeof(buffer);
	buffer[l]='\0';
	cout<<"\nRecived message : "<<buffer<<"\n";

	//Send
	bzero(buffer,sizeof(buffer));	
	cout<<"\nEnter the message : ";
	cin>>buffer;
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,sizeof(struct sockaddr));


	return 0;
}
