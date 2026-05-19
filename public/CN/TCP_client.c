#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
  int sock;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];

  // 1. Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);

  // 2. Define server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  // 3. Connect to server
  connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  printf("Connected to TCP server.\n");

  while (1)
  {
    // Send message
    printf("Client: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    send(sock, buffer, strlen(buffer), 0);

    // Receive reply
    memset(buffer, 0, BUFFER_SIZE);
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Server: %s", buffer);
  }

  close(sock);
  return 0;
}
