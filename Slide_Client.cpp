#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

void tcpConnectionSetUp(int &sockfd){

	struct sockaddr_in server;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(5001);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sockfd,(struct sockaddr *)&server,sizeof(server));

	cout<<"\nClient is connected with server...";
}

void recvFrame(int sockfd,int arr[],int s,int n){

	int temp;
	for (int i = s; i < n ; ++i){
		recv(sockfd,&temp,sizeof(temp),0);
		arr[i] = ntohs(temp);
	}
	cout<<"\nFrame recieved..\n";
}

void waiting(int n){
	for (int i = 0; i < n; ++i){
		cout<<"\a";
	}
}

int main(){

	cout<<"\n==============================";
	cout<<"\n\tClient";
	cout<<"\n==============================\n";

	int sockfd;
	tcpConnectionSetUp(sockfd);
	cout<<"\nConnected...";

	int temp;
	int cnt = 0;
	int arr[100];

	
	int FrameLen;
	int k=0;
	while(1){

		//recieve frame length
		recv(sockfd,&temp,sizeof(temp),0);
		FrameLen = ntohs(temp);
		cout<<"\nFrameLen = "<<FrameLen;

		//recieve the frame
		recvFrame(sockfd,arr,cnt,cnt+FrameLen);
		cnt += FrameLen;  

		//send ack for recieved frame one at a time
		while(k<cnt){
			waiting(100);
			temp = htons(k);
			send(sockfd,&temp,sizeof(temp),0);
			cout<<"\nAcknowledge sent for "<<k;
			k++;
		}
		cout<<"\n";
	}


    printf("\n");
    return 0;
}
