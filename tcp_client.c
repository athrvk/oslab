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
    int sock;
    // client socket discriptor
    unsigned int len;
    int i;
    char ch[5]="exit";
    char ch1[5];
    struct sockaddr_in client;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
    // client socket is created.
    {
        perror("socket: ");
        exit(-1);
    }
    client.sin_family=AF_INET;
    client.sin_port=htons(9001);
    // initializing socket parameters
    client.sin_addr.s_addr=INADDR_ANY;
    bzero(&client.sin_zero,0);
    // appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1)
    //connecting to client
    {
        perror("connect: ");
        exit(-1);
    }
    while(1)
    {
        // Write your code here
        int a;
        scanf("%d",&a);
        send(sock,&a,sizeof(a),0);
        recv(sock,&a,sizeof(a),0);
        printf("double is %d\n",a);
        // End your code here
 
        // to close the connection
        printf("\nTo exit...press 'exit'\n");
        scanf("%s",ch1);
        send(sock,&ch1,sizeof(ch),0);
        if((i=strcmp(ch,ch1))==0)
        {
            close(sock);
            exit(0);
        }
    }
}
