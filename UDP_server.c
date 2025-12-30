#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // 1. Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Bind to address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("UDP Server listening on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message
        recvfrom(sock, buffer, BUFFER_SIZE, 0,
                 (struct sockaddr*)&client_addr, &addr_len);
        printf("Client: %s", buffer);

        // Send reply
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sendto(sock, buffer, strlen(buffer), 0,
               (struct sockaddr*)&client_addr, addr_len);
    }

    close(sock);
    return 0;
}
