#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>  

#define UDP_SERVER_PROT 2234
#define UDP_SERVER_IP   "192.168.159.136"
#define MAX_SIZE 256
int main(int argc, char * argv[])
{
    struct sockaddr_in server;
    int sockfd, len = 0;
    int server_len = sizeof(struct sockaddr_in);
    char * sendStr = "I am a client\n";
    char buf[MAX_SIZE];
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(UDP_SERVER_PROT);
    server.sin_addr.s_addr = inet_addr(UDP_SERVER_IP);

    if(sendto(sockfd, sendStr, strlen(sendStr), 0, (struct sockaddr *)&server, server_len) < 0)
    {
        printf("sendto error\n");
        exit(1);
    }
    bzero(buf, sizeof(buf));

    len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server, &server_len);
    if(len < 0)
    {
        printf("recvfrom error\n");
        exit(1);
    }
    
    printf("Receive from server: %s\n", buf);

    return 0;
}
