#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main(int argc, char ** argv)
{
    int client_sockfd, n, client_recvmsglen;
    char recvline[MAXLINE], sendline[MAXLINE];
    char buff[MAXLINE];
    struct sockaddr_in client_addr;

    if(argc != 2){
        printf("usage: ./client <ipaddress>\n");
        exit(0);
    }

    if((client_recvmsglen = socket(AF_INET, SOCK_STREAM, 0)) <0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    bzero(&client_sockfd, sizeof(client_sockfd));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port   = htons(8000);
    if(inet_pton(AF_INET, argv[1], &client_addr.sin_addr) <= 0){
        printf("inet_pton error for %s\n", argv[1]);
        exit(0);
    }

    if(connect(client_sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0){
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    printf("send msg to server: \n");
    fgets(sendline, 4096, stdin);
    if(send(client_sockfd, sendline, strlen(sendline), 0) < 0){
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    if(client_recvmsglen = recv(client_sockfd, buff, MAXLINE, 0)) == -1){
        perror("recv error");
        exit(1);
    }
    buff[client_recvmsglen] = '\0';
    printf("Received : %s ",buff);
    close(client_sockfd);
    
    return 0;
}