#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 9090
#define MAX_FRAMES 10
#define WINDOW_SIZE 4
#define TIMEOUT 3

typedef struct
{
  int seq;
  char data[32];
} Frame;

int main()
{
  int sockfd;
  struct sockaddr_in serverAddr;
  socklen_t addrLen = sizeof(serverAddr);

  Frame frames[MAX_FRAMES];
  int base = 0, nextSeq = 0;
  int totalFrames = 6;
  int ack;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Create frames
  for (int i = 0; i < totalFrames; i++)
  {
    frames[i].seq = i;
    sprintf(frames[i].data, "DATA-%d", i);
  }

  printf("Go-Back-N Sender Started\n");

  while (base < totalFrames)
  {

    // Send frames within window
    while (nextSeq < base + WINDOW_SIZE && nextSeq < totalFrames)
    {
      printf("Sender: Sending Frame %d\n", frames[nextSeq].seq);
      sendto(sockfd, &frames[nextSeq], sizeof(Frame), 0,
             (struct sockaddr *)&serverAddr, addrLen);
      nextSeq++;
    }

    // Set timeout
    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
               (const char *)&tv, sizeof(tv));

    if (recvfrom(sockfd, &ack, sizeof(int), 0,
                 (struct sockaddr *)&serverAddr, &addrLen) > 0)
    {
      printf("Sender: ACK received for Frame %d\n", ack);
      base = ack + 1;
    }
    else
    {
      // Timeout occurred
      printf("Sender: Timeout! Go-Back-N Retransmission\n");
      nextSeq = base;
    }
  }

  printf("Sender: All frames sent successfully\n");
  close(sockfd);
  return 0;
}
