#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PORT "1305"
int main(int argc, char *argv[])
{
    int a,b;

//getaddressinfo with server PASSIVE

    struct addrinfo hints, *result, *p;
    //top level
    memset(&hints,0,sizeof hints);
    hints.ai_family=AF_INET;
    hints.ai_protocol=0;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
//low level
    if ((a=getaddrinfo(NULL,PORT,&hints,&result))!=0)
    {
        printf("Error Getaddressinfo\n");
    }
    else
    {
        printf("Getaddressinfo...OK\n");
    }
//create the socket
    int sockfd1;
    //top level
    if((sockfd1=socket(result->ai_family,result->ai_socktype,result->ai_protocol))==-1)
    {
        printf("Error socket loading\n");
    }
    else
    {
        printf("Socket...OK\n");
    }
//bind
    //low level
    if (b=bind(sockfd1,result->ai_addr,result->ai_addrlen)==-1)
    {
        printf("Error socket binding\n");
    }
    else
    {
        printf("Bind...OK\n");
    }
//listen for max 10 connections
    listen(sockfd1,10);
//accept
    int sockld1;
    struct sockaddr clientaddr;
    socklen_t c=sizeof clientaddr;
    char str[INET_ADDRSTRLEN];
    while(1)
    {

        if((sockld1=accept(sockfd1,&clientaddr,&c))==-1)
        {
            printf("Error accepting connection\n");
            continue;
        }
        else
        {

//nightmare casting to get sin_addr and inetntop
            struct sockaddr_in * clientaddr_inp;
            clientaddr_inp=(struct sockaddr_in *) &clientaddr;
            inet_ntop(clientaddr.sa_family,&(clientaddr_inp->sin_addr),str,INET_ADDRSTRLEN);
            printf("Accepting connection ...OK\nConnecting to %s...\n",str);
        }
//send
        char * messagesd ="Welcome to the server. Send your message";
        if((send(sockld1,messagesd,strlen(messagesd),0))<strlen(messagesd))
        {
            printf("Warning:not all of the welcome message has been sent...\n");
        };

//receive
        char messagerc[1000];
        while(1)
        {
            if((recv(sockld1,messagerc,strlen(messagerc),0))<1)
            {
                printf("Server faces an error receiving bytes...");
                break;
            }
            else
            {
                printf("%s",messagerc);
                fflush(stdout);
            }
        }

    }

    return 0;

}
