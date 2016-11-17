# include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int main (int argc, char *argv[ ])
{
    struct in_addr localInterface;                      //+
    struct sockaddr_in group; 
    
    //Step 1: Create a datagram socket on which to send.
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)&group,sizeof(group));

    //Step 2: Initialize the group sockaddr structure with a multicast address
    group.sin_family = AF_INET;
    group.sin_addr.s_addr = inet_addr("226.1.1.1");         //+ 
    group.sin_port = htons(5432);

    //Step 3: Set local Interface address
    localInterface.s_addr = INADDR_ANY;                 //+

    //Step 4: Set options for socket for IP_MULTICAST_IF
    setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface) ); //+

    //Step 5: Send a Multicast message to group
    char msg[] = "Hello .. Clients !!";
    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&group, sizeof(group) );
    
    return 0;
}

