#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2525

int main()
{
  int server_fd, client_fd;

  struct sockaddr_in server_addr, client_addr;

  socklen_t addr_len = sizeof(client_addr);

  char buffer[1024];

  // Create socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Configure server
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Bind
  bind(server_fd,
       (struct sockaddr *)&server_addr,
        sizeof(server_addr));

  // Listen
  listen(server_fd, 1);

  printf("SMTP Server listening on port %d...\n", PORT);

  // Accept client
  client_fd = accept(server_fd,(struct sockaddr *)&client_addr,&addr_len);

  printf("Client connected\n");

  // SMTP Greeting
  strcpy(buffer, "220 Simple SMTP Server Ready\n");
  send(client_fd, buffer, strlen(buffer), 0);

  while (1)
  {
    memset(buffer, 0, sizeof(buffer));

    recv(client_fd, buffer, sizeof(buffer), 0);

    printf("Client: %s", buffer);

    // HELO
    if (strncmp(buffer, "HELO", 4) == 0)
    {
      strcpy(buffer, "250 Hello Client\n");
    }

    // MAIL FROM
    else if (strncmp(buffer, "MAIL FROM", 9) == 0)
    {
      strcpy(buffer, "250 Sender OK\n");
    }

    // RCPT TO
    else if (strncmp(buffer, "RCPT TO", 7) == 0)
    {
      strcpy(buffer, "250 Recipient OK\n");
    }

    // DATA
    else if (strncmp(buffer, "DATA", 4) == 0)
    {
      strcpy(buffer,"354 Enter message, end with . on line\n");
    }

    // Message End
    else if (strcmp(buffer, ".\n") == 0)
    {
      strcpy(buffer, "250 Message Accepted\n");
    }

    // QUIT
    else if (strncmp(buffer, "QUIT", 4) == 0)
    {
      strcpy(buffer, "221 Goodbye\n");

      send(client_fd,buffer,strlen(buffer),0);

      break;
    }

    else
    {
      strcpy(buffer, "250 OK\n");
    }

    send(client_fd,buffer,strlen(buffer),0);
  }

  close(client_fd);
  close(server_fd);

  return 0;
}