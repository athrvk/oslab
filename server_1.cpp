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
  char pass[7] = "Anurag";
  char passCh[7];
  char s[30];
  char chr;
  char hiCh[30];
  char hi[3] = "hi";
  int n;
  int i;
  // creating server and clinet socket discriptor
  int a, b, c;
  unsigned int len;

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

  len = sizeof(struct sockaddr_in);

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
  recv(csock, passCh, sizeof(passCh), 0);
  printf("%s", passCh);
  if ((i = strcmp(passCh, pass)) == 0)
  {
    a = 1;
  }
  else
  {
    a = 0;
  }
  send(csock, &a, sizeof(a), 0);
  if (a == 1)
  {
    printf("\nCorrect Password");
    while (1)
    {
      recv(csock, hiCh, sizeof(hiCh), 0);
      if (i = strcmp(hiCh, hi) == 0)
      {
        printf("\nReceived Hi");
        send(csock, &a, sizeof(a), 0);
        recv(csock, s, sizeof(s), 0);
        recv(csock, &n, sizeof(n), 0);
        int maxm = -1;
        int found = 0;
        for (i = 0; s[i] != '\0'; i++)
        {
          letter[s[i] - 'a']++;
          if (letter[s[i] - 'a'] == n)
          {
            char str = s[i];
            send(csock, &str, sizeof(str), 0);
            found = 1;
            break;
          }
          if (letter[s[i] - 'a'] > maxm)
          {
            chr = s[i];
            maxm = letter[s[i] - 'a'];
          }
        }
        if (!found)
        {
          send(csock, &chr, sizeof(chr), 0);
        }
        memset(letter, 0, sizeof(letter));
      }
      else
      {
        a = 0;
        send(csock, &a, sizeof(a), 0);
      }
    }
  }

  close(ssock);
}
