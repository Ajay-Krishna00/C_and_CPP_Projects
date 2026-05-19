#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(){
    int server_sock,client_sock,data_client,data_sock;
    struct sockaddr_in server,client,data_addr;
    socklen_t len=sizeof(client);
    char buffer[1024],filename[100],user[50],pass[50];
    int logged=0;
    
    char valid_user[]="admin";
    char valid_pass[]="123";
    
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(2405);
    server.sin_addr.s_addr=INADDR_ANY;
    
    bind(server_sock,(struct sockaddr *)&server,sizeof(server));
    listen(server_sock,5);
    printf("FTP server started\n");
    
    client_sock=accept(server_sock,(struct sockaddr *)&client,&len);
    
    send(client_sock,"220 FTP server ready\n",22,0);
    while(1){
        memset(buffer,0,sizeof(buffer));
        recv(client_sock,buffer,sizeof(buffer),0);
        if(strncmp(buffer,"USER",4)==0){
            sscanf(buffer,"USER %s",user);
            send(client_sock,"Username OK\n",12,0);
        }
        else if(strncmp(buffer,"PASS",4)==0){
            sscanf(buffer,"PASS %s",pass);
            if(!strcmp(user,valid_user) && !strcmp(pass,valid_pass)){
                logged=1;
                send(client_sock,"Login success\n",14,0);
            }
            else{
                send(client_sock,"Login NOT success\n",18,0);
            }
        }
        else if(strncmp(buffer,"PUT",3)==0 && logged){
            sscanf(buffer,"PUT %s",filename);
            
            data_sock=socket(AF_INET,SOCK_STREAM,0);
            data_addr.sin_family=AF_INET;
            data_addr.sin_port=htons(2424);
            data_addr.sin_addr.s_addr=INADDR_ANY;
            
            bind(data_sock,(struct sockaddr *)&data_addr,sizeof(data_addr));
            listen(data_sock,1);
            
            send(client_sock,"ready to receive data\n",22,0);
            
            data_client=accept(data_sock,NULL,NULL);
            
            FILE *fp=fopen(filename,"wb");
            
            int bytes;
            while ((bytes = recv(data_client, buffer, sizeof(buffer), 0)) > 0) {
                fwrite(buffer, 1, bytes, fp);
            }

            fclose(fp);
            close(data_client);
            close(data_sock);
            send(client_sock,"transfer complete\n",18,0);
        }
        else if(strncmp(buffer,"QUIT",4)==0){
            send(client_sock,"Goodbye\n",8,0);
            break;
        }
        else{
            send(client_sock,"Invalid or not logged in\n",25,0);
        }
    }
    close(client_sock);
    close(server_sock);
    return 0;
}