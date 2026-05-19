#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_SEQ 8
#define LOSS_PROBABILITY 30 // %

typedef struct
{
  int seq;
  char data[20];
} Frame;

int main()
{
  int sockfd;
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t addrLen = sizeof(clientAddr);

  Frame buffer[MAX_SEQ];
  int received[MAX_SEQ] = {0};

  srand(time(NULL));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  while (1)
  {
    Frame frame;
    recvfrom(sockfd, &frame, sizeof(Frame), 0,
             (struct sockaddr *)&clientAddr, &addrLen);

    // Simulate packet loss
    if (rand() % 100 < LOSS_PROBABILITY)
    {
      printf("Frame %d LOST\n", frame.seq);
      continue;
    }

    printf("Received Frame %d : %s\n", frame.seq, frame.data);

    if (!received[frame.seq])
    {
      buffer[frame.seq] = frame;
      received[frame.seq] = 1;
    }

    // Send ACK
    sendto(sockfd, &frame.seq, sizeof(int), 0,
           (struct sockaddr *)&clientAddr, addrLen);
    printf("ACK sent for Frame %d\n", frame.seq);
  }

  close(sockfd);
  return 0;
}
