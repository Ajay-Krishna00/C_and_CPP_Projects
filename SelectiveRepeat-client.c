#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

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
  int base = 0, nextSeq = 0;

  srand(time(NULL));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Create frames
  for (int i = 0; i < MAX_SEQ; i++)
  {
    frames[i].seq = i;
    sprintf(frames[i].data, "Frame-%d", i);
  }

  while (base < MAX_SEQ)
  {
    // Send frames within window
    while (nextSeq < base + WINDOW_SIZE && nextSeq < MAX_SEQ)
    {
      printf("Sending Frame %d\n", frames[nextSeq].seq);
      sendto(sockfd, &frames[nextSeq], sizeof(Frame), 0,
             (struct sockaddr *)&serverAddr, addrLen);
      nextSeq++;
    }

    // Receive ACK
    int ack;
    recvfrom(sockfd, &ack, sizeof(int), 0,
             (struct sockaddr *)&serverAddr, &addrLen);

    printf("Received ACK for Frame %d\n", ack);
    acked[ack] = 1;

    // Slide window
    while (acked[base])
    {
      base++;
    }
  }

  close(sockfd);
  return 0;
}
