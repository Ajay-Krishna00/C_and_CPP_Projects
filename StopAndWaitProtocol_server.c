#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 3000

void main()
{

  int server, client;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  int frame;
  int ack, expected = 0;

  server = socket(AF_INET, SOCK_STREAM, 0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server, 1);

  printf("Server Waiting\n");
  addr_size = sizeof(client_addr);
  client = accept(server, (struct sockaddr *)&client_addr, &addr_size);
  while (1)
  {

    int t = recv(client, &frame, sizeof(frame), 0);
    if (t == 0)
    {
      printf("Client closed\n");
      break;
    }
    if (frame == expected)
    {
      printf("Frame %d recieved\n", frame);
      ack = expected;
      expected++;
    }
    else
    {
      printf("Duplicate recieved\n");
      ack = expected - 1;
    }
    if (rand() % 100 > 50)
    {
      printf("not sending ack\n");
    }
    else
    {
      send(client, &ack, sizeof(ack), 0);
      printf("Ack %d sent\n", ack);
    }
  }

  close(server);
  close(client);
}