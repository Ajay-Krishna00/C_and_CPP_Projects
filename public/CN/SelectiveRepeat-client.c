#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080
#define MAX_SEQ 8
#define WINDOW_SIZE 4

typedef struct
{
  int seq;
  char data[20];
} Frame;

int main()
{
  int sockfd;

  struct sockaddr_in serverAddr;

  socklen_t addrLen = sizeof(serverAddr);

  Frame frames[MAX_SEQ];

  int acked[MAX_SEQ] = {0};

  int base = 0;
  int nextSeq = 0;

  // Socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // Timeout setup
  struct timeval tv;

  tv.tv_sec = 2;
  tv.tv_usec = 0;

  setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));

  // Server address
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);

  inet_pton(AF_INET,"127.0.0.1",&serverAddr.sin_addr);

  // Create frames
  for (int i = 0; i < MAX_SEQ; i++)
  {
    frames[i].seq = i;

    sprintf(frames[i].data,"Frame-%d",i);
  }

  while (base < MAX_SEQ)
  {
    // Send frames inside window
    while (nextSeq < base + WINDOW_SIZE &&nextSeq < MAX_SEQ)
    {
      printf("Sending Frame %d\n",frames[nextSeq].seq);
      sendto(sockfd,&frames[nextSeq],sizeof(Frame),0,(struct sockaddr *)&serverAddr,addrLen);
      nextSeq++;
    }

    int ack;

    // Receive ACK
    if (recvfrom(sockfd,&ack,sizeof(int),0,(struct sockaddr *)&serverAddr,&addrLen) < 0)
    {
      printf("\nTimeout!\n");
      // Resend only unacked frames
      for (int i = base; i < nextSeq; i++)
      {
        if (!acked[i])
        {
          printf("Resending Frame %d\n",frames[i].seq);
          sendto(sockfd,&frames[i],sizeof(Frame),0,(struct sockaddr *)&serverAddr,addrLen);
        }
      }

      continue;
    }

    printf("Received ACK for Frame %d\n", ack);
    acked[ack] = 1;

    // Slide window
    while (acked[base])
    {
      base++;
    }
  }
  printf("\nAll frames acknowledged\n");
  close(sockfd);
  return 0;
}