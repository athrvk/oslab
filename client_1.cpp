#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#include <errno.h>
#include <unistd.h>

int letter[26];

int main()
{
  int sock; // client socket discriptor

  // variable
  int a, b, c, i;
  char s[30];
  unsigned int len;
  char ch[3] = "no";
  char passCh[7];
  char hiCh[3] = "Hi";
  char hi[6];
  char chr;
  char ch1[3];

  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  { // client socket is created..
    perror("socket: ");
    exit(-1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10000); // initializing  socket  parameters
  client.sin_addr.s_addr = INADDR_ANY;
  //inet_addr("127.0.0.1");
  bzero(&client.sin_zero, 0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'..

  len = sizeof(struct sockaddr_in);
  if ((connect(sock, (struct sockaddr *)&client, len)) == -1)
  { //conneting to client
    perror("connect: ");
    exit(-1);
  }

  printf("Enter your Password:\n");
  scanf("%s", passCh);
  send(sock, passCh, sizeof(passCh), 0);
  recv(sock, &a, sizeof(a), 0);

  if (a == 1)
  {

    while (1)
    {
      printf("\nSay hi to your server\n");
      scanf("%s", hi);
      send(sock, hi, sizeof(hi), 0);
      recv(sock, &a, sizeof(a), 0);
      if (a == 1)
      {

        printf("\nHello\n");
        printf("Enter your string and a number\n");
        scanf("%s", s);
        scanf("%d", &a);
        send(sock, s, sizeof(s), 0);
        send(sock, &a, sizeof(a), 0);
        recv(sock, &chr, sizeof(chr), 0);
        printf("Required Character is %c\n", chr);
      }
      else
      {
        printf("\nDoesn't understood");
      }

      printf("\nTo exit...press 'no'\n");
      scanf("%s", ch1);

      if ((i = strcmp(ch, ch1)) == 0)
      {
        close(sock);
        exit(0);
      }
    }
  }
  else
  {
    printf("\nWrong Password\n");
    printf("\nExiting\n");
    close(sock);
    exit(0);
  }
}
