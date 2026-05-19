#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
  int server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len = sizeof(client_addr);
  char buffer[BUFFER_SIZE];

  // 1. Create socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0)
  {
    perror("Socket failed");
    exit(1);
  }

  // 2. Define server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // 3. Bind socket
  bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // 4. Listen
  listen(server_fd, 1);
  printf("TCP Server listening on port %d...\n", PORT);

  // 5. Accept connection
  client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
  printf("Client connected.\n");

  while (1)
  {
    memset(buffer, 0, BUFFER_SIZE);

    // Receive message
    recv(client_fd, buffer, BUFFER_SIZE, 0);
    printf("Client: %s", buffer);

    // Send reply
    printf("Server: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    send(client_fd, buffer, strlen(buffer), 0);
  }

  close(client_fd);
  close(server_fd);
  return 0;
}
