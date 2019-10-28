#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

int letter[26];
int main()
{

  int ssock, csock;

  // creating server and clinet socket discriptor

  struct sockaddr_in server, client;
  // creating server & client socket object

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    // creating socket
    perror("socket: ");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(10000);

  // initializing server socket parameters..
  server.sin_addr.s_addr = INADDR_ANY;

  //inet_addr("127.0.0.1");
  bzero(&server.sin_zero, 0);

  //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'..

  unsigned int len = sizeof(struct sockaddr_in);

  if ((bind(ssock, (struct sockaddr *)&server, len)) == -1)
  {
    // binding port & IP
    perror("bind error: ");
    exit(-1);
  }

  if ((listen(ssock, 5)) == -1)
  {
    // listening for client
    perror("listen error: ");
    exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
  {
    // accepting connectn
    perror("accept error: ");
    exit(-1);
  }
  // int a;
  // send(csock, &a, sizeof(a), 0);
  // recv(csock, &a, sizeof(a), 0);
  while (1)
  {
    // int a;
    // send(csock, &a, sizeof(a), 0);
    // recv(csock, &a, sizeof(a), 0);
    char in[100];
    recv(csock, &in, sizeof(in), 0);
    int n = strlen(in);
    if (n == 39)
    {
      bool zero[8];
      memset(zero, 0, sizeof(zero));
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < 4; j++, i++)
        {
          if (in[i] != '0')
          {
            zero[i / 5] = -1;
            break;
          }
        }
      }

      for(int i=0; i<8; i++)
      {
        if(zero[i] == 0)
        {
          
        }
      }
    }
  }

  close(ssock);
}
