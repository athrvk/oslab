#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int ssock,csock;
    // creating server and client socket discriptor
    int i;
    char ch[5]="exit";
    char ch1[5];
    unsigned int len;
    struct sockaddr_in server,client;
    // creating server & client socket object
    if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
    // creating socket
    {
        perror("socket: ");
        exit(-1);
    }
    server.sin_family=AF_INET;
    server.sin_port=htons(9001);
    // initializing server socket parameters.
    server.sin_addr.s_addr=INADDR_ANY;
    bzero(&server.sin_zero,0);
    // appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
    len=sizeof(struct sockaddr_in);
    if((bind(ssock,(struct sockaddr *)&server,len))==-1)
    // binding port & IP
    {
        perror("bind error: ");
        exit(-1);
    }
    if((listen(ssock,5))==-1)
    // listening for client
    {
        perror("listen error: ");
        exit(-1);
    }
    if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
    // accepting connection
    {
        perror("accept error: ");
        exit(-1);
    }
    while(1)
    {
        // Write your code here
        int a;
        recv(csock,&a,sizeof(a),0);
        printf("%d\n",a);
        a*=a;
        send(csock,&a,sizeof(a),0);
        // End your code here
        
        // To close the connection
        recv(csock,&ch1,sizeof(ch1),0);
        if((i=strcmp(ch,ch1))==0)
        {
            printf("\nclient pressed exit quitting the process\n");
            close(ssock);
            exit(0);
        }
    }
    close(ssock);
}
