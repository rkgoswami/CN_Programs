//Tcp Server Code

#include <bits/stdc++.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

void tcpConnectionSetUp(int &newsockfd){

	struct sockaddr_in server, client;

	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(5001);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd,(struct sockaddr *)&server,sizeof(server));

	listen(sockfd,1);
	socklen_t clientLen = sizeof(client);
	newsockfd = accept(sockfd,(struct sockaddr*)&client,&clientLen);

	cout<<"\nServer is connected with client...";
}

void displayStatus(int arr[],int s,int e){
	cout<<"[";
	for (int i = s; i <= e; ++i){
		cout<<" "<<arr[i];
	}
	cout<<" ]";
}

void sendFrame(int newsockfd,int arr[],int s,int e){

	int temp;
	for (int i = s; i < e ; ++i){
		temp = htons(arr[i]);
		send(newsockfd,&temp,sizeof(temp),0);
	}
	cout<<"\n\nFrame sent..\n";
}

void displayWindow(int arr[],int sf,int sn,int sw,int se){

	cout<<"\n";
	displayStatus(arr,0,sf-1);
			
	cout<<"\t\txx[ ";
	displayStatus(arr,sf,sn-1);


	displayStatus(arr,sn,sw);
	cout<<" ]xx\t\t";
	
	if (sw>=se-1)
		cout<<"[ ]";
	else
		displayStatus(arr,sw,se-1);	

	
}

int main(){

	cout<<"\n==============================";
	cout<<"\n\tServer";
	cout<<"\n==============================\n";

	int newsockfd;
	tcpConnectionSetUp(newsockfd);
 
 	int swLen;
	cout<<"\nEnter the sliding window length: ";
	cin>>swLen;


	int frameLen = rand()%(swLen-1)+1;
	cout<<"\nFrame length : "<<frameLen;

	int tcount;
	cout<<"\nEnter the data length to be send: ";
	cin>>tcount;
	//fill the array 
	int arr[tcount];
	int i=0;
	while(i<tcount){
		arr[i]=i;
		i++;
	}

	int temp;
	
	//pointers
	int sf=0;
	int sn = frameLen;
	int sw = swLen-1;
	int se = tcount;
	int val;

	
	while(sn<=se){

		//send the frame and wait for ack
		frameLen = sn-sf;
		if (frameLen==0){
			break;
		}
		//send frame length
		temp = htons(frameLen);
		send(newsockfd,&temp,sizeof(temp),0);
		
		//send frame
		sendFrame(newsockfd,arr,sf,sn);
		
		//display
		displayWindow(arr,sf,sn,sw,se);

		//recieve till sf<sn then resend the frame
		while(sf<sn){
			recv(newsockfd,&temp,sizeof(temp),0);
			val = ntohs(val);
			sf++;
			sw=(sw<se-1)?(++sw):se-1;
			displayWindow(arr,sf,sn,sw,se);
		}

		//update the sf and sn
		if (sn+frameLen < se){
			sf=sn;
			sn=sn+frameLen;
		}
		else{
			sf=sn;
			sn=se;
		}

	}

	printf("\n"); 
	return 0;
}
