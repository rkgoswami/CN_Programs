#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>


using namespace std;

int main(int argc, char *argv[])
{
    struct sockaddr_in local;
    struct ip_mreq group;               //+
    
    //Step 1:  Create a datagram socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)&local,sizeof(local));
 
    /*Step 2: Enable SO_REUSEADDR to allow its multiple instances to receive copies of the multicast datagrams.*/
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));        //+

    //Step 3: Intialize the structure members
    local.sin_family = AF_INET;
    local.sin_port = htons(5432);
    local.sin_addr.s_addr = INADDR_ANY;

    //Step 4: Binding
    bind(sockfd, (struct sockaddr*)&local, sizeof(local));

    //Step 5: Join the group
    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");        //+
    group.imr_interface.s_addr = INADDR_ANY;                    //+

    //Step 6: Set the sock options for IP_ADD_MEMBERSHIP
    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) ;  //+

    //Step 7: Recieve the broadcasted message
    char buffer[1024];
    recv(sockfd,buffer,sizeof(buffer),0);
    int l=sizeof(buffer);
    buffer[l]='\0';
    cout<<"\nRecieved Message : "<<buffer<<"\n";
 
    return 0;
}

