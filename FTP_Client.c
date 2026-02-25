#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define DATA_PORT 2424 

int main() {
    int ctrl_sock, data_sock;
    struct sockaddr_in server, data_addr;
    char buffer[1024], filename[100]; 

    ctrl_sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(2405);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(ctrl_sock, (struct sockaddr *)&server, sizeof(server));

    int n=recv(ctrl_sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    printf("%s", buffer);

    send(ctrl_sock, "USER admin\n", 11, 0);
    n=recv(ctrl_sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    printf("%s", buffer); 

    send(ctrl_sock, "PASS 123\n", 10, 0);
    n=recv(ctrl_sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    printf("%s", buffer);

    printf("Enter file to upload: ");
    scanf("%s", filename);

    sprintf(buffer, "PUT %s\n", filename);
    send(ctrl_sock, buffer, strlen(buffer), 0);
    n=recv(ctrl_sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    printf("%s", buffer);
    data_sock = socket(AF_INET, SOCK_STREAM, 0);
    data_addr.sin_family = AF_INET;
    data_addr.sin_port = htons(DATA_PORT);
    data_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    connect(data_sock, (struct sockaddr *)&data_addr, sizeof(data_addr)); 

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("fopen");
        close(data_sock);
        close(ctrl_sock);
        return 1;
    }

    int bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        send(data_sock, buffer, bytes, 0);
    }


    fclose(fp);
    close(data_sock); 

    n=recv(ctrl_sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = '\0';
    printf("%s", buffer);

    send(ctrl_sock, "QUIT\n", 5, 0);
    close(ctrl_sock);

    return 0;

}
