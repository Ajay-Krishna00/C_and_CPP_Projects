#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 9090
#define LOSS_PROBABILITY 30 // %

typedef struct
{
  int seq;
  char data[32];
} Frame;

int main()
{
  int sockfd;
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t addrLen = sizeof(clientAddr);

  int expectedSeq = 0;
  Frame frame;

  srand(time(NULL));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  printf("Go-Back-N Receiver Started\n");

  while (1)
  {
    recvfrom(sockfd, &frame, sizeof(Frame), 0,
             (struct sockaddr *)&clientAddr, &addrLen);

    // Simulate packet loss
    if (rand() % 100 < LOSS_PROBABILITY)
    {
      printf("Receiver: Frame %d LOST\n", frame.seq);
      continue;
    }

    if (frame.seq == expectedSeq)
    {
      printf("Receiver: Received Frame %d : %s\n",
             frame.seq, frame.data);

      sendto(sockfd, &frame.seq, sizeof(int), 0,
             (struct sockaddr *)&clientAddr, addrLen);

      printf("Receiver: ACK sent for Frame %d\n", frame.seq);
      expectedSeq++;
    }
    else
    {
      printf("Receiver: Out-of-order Frame %d discarded\n", frame.seq);

      int lastAck = expectedSeq - 1;
      sendto(sockfd, &lastAck, sizeof(int), 0,
             (struct sockaddr *)&clientAddr, addrLen);

      printf("Receiver: Resent ACK %d\n", lastAck);
    }
  }

  close(sockfd);
  return 0;
}
