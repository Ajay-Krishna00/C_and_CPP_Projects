#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3000

void main()
{

  int server;
  struct sockaddr_in server_addr;
  int frames[] = {0, 1, 2, 3, 4};
  int ack = 999;
  int i = 0;

  struct timeval tv;
  tv.tv_sec = 2;
  tv.tv_usec = 0;

  server = socket(AF_INET, SOCK_STREAM, 0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(server, (struct sockaddr *)&server_addr, sizeof(server_addr));

  setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

  while (i < 5)
  {

    printf("Sending frame: %d\n", frames[i]);
    send(server, &frames[i], sizeof(frames[i]), 0);

    if (recv(server, &ack, sizeof(ack), 0) < 0)
    {
      printf("Timeout! Resending frame");
      continue;
    }

    printf("Ack %d recieved\n", ack);

    if (ack == frames[i])
    {
      i++;
    }
    else
    {
      printf("Resending frame\n");
    }
    //        sleep(1);
  }
  close(server);
}