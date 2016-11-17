//Tcp Server Code

#include <bits/stdc++.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void UdpConnectionSetUp(int &sockfd,struct sockaddr_in &server){


	//Step 1: Intialise sockect file discriptor i.e sockfd
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	//Step 2: Intialise structure members
	server.sin_family = AF_INET;
	server.sin_port = htons(4008);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

}

int main(){

	cout<<"\n==============================";
	cout<<"\n\tUdp Client";
	cout<<"\n==============================\n";

	int sockfd;
	struct sockaddr_in server;
	UdpConnectionSetUp(sockfd,server);

	char buffer[1024];

	//Send
	cout<<"\nEnter the message : ";
	cin>>buffer;
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&server,sizeof(struct sockaddr));
	
	//Recieve
	bzero(buffer,sizeof(buffer));	
	socklen_t serverLen = sizeof(struct sockaddr);
	recvfrom(sockfd,buffer,10,0,(struct sockaddr *)&server,&serverLen);
	int l = sizeof(buffer);
	buffer[l]='\0';
	cout<<"\nRecieved message : "<<buffer<<"\n";
}
