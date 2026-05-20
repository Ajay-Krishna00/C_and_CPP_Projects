#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2525

int main()
{
  int sock;

  struct sockaddr_in server_addr;

  char buffer[1024];

  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);

  // Configure server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

  // Connect
  connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));

  // Receive greeting
  recv(sock, buffer, sizeof(buffer), 0);

  printf("Server: %s", buffer);

  while (1)
  {
    memset(buffer, 0, sizeof(buffer));

    printf("Enter SMTP Command: ");
    fgets(buffer, sizeof(buffer), stdin);

    send(sock,buffer,strlen(buffer),0);

    memset(buffer, 0, sizeof(buffer));

    recv(sock,buffer,sizeof(buffer),0);

    printf("Server: %s", buffer);

    if (strncmp(buffer, "221", 3) == 0)
      break;
  }

  close(sock);

  return 0;
}