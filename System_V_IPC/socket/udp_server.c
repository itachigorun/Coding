#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>  
#include<arpa/inet.h>

#define UDP_SERVER_PORT 2234
#define MAX_MSG_SIZE 256

void udpser_init(int * sockfd)
{
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(UDP_SERVER_PORT);

    if(-1 == (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("create socket failed\n");
        exit(1);
    }

    if(-1 == (bind(*sockfd, (struct sockaddr *)&server, sizeof(server))))
    {
        printf("bind error\n");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    unsigned char message[MAX_MSG_SIZE];
    int recv_len = 0;
    char addr_p[30]={0};
    char *sndbuf = "Hello! I am OK.\n";
    struct sockaddr_in client;
    int client_len = sizeof(struct sockaddr_in);
    int sockfd;

    udpser_init(&sockfd);
    recv_len = recvfrom(sockfd, message, sizeof(message), 0, (struct sockaddr *)&client, &client_len);
    if(recv_len < 0)
    {
        printf("recvfrom error\n");
        exit(1);
    }

    inet_ntop(AF_INET, &client.sin_addr, addr_p, sizeof(addr_p));
    printf("client IP is %s, port is %d\n", addr_p, ntohs(client.sin_port));
    message[recv_len] = '\0';
    printf("server received %d byte:%s\n", recv_len, message);

    if(sendto(sockfd, sndbuf, strlen(sndbuf),0, (struct sockaddr*)&client, client_len) < 0)
    {
        printf("sento error\n");
        exit(1);
    }

    return 0;
}
