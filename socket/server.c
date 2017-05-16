#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define DEFAULT_PORT 8000
int main()
{
    int server_sockfd;  //服务器套接字
    struct sockaddr_in server_addr;  //服务器网络地址结构体
    int server_connectfd;
    char buff[MAXLINE];
    int server_recvmsglen;

    if( (server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    } //0代表根据第二个参数自动选择协议

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family   = AF_INET;    //设置为ipv4通信
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //服务器IP地址，系统自动获取本机IP地址
    server_addr.sin_port        = htons(DEFAULT_PORT);     //服务器端口号
    
    if(bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    if(listen(server_sockfd, LISTENQ) == -1){
        printf("listen socket error: %d(errno: %d)\n", strerrnr(errno), errno);
        exit(0);
    }

    printf("=========waiting for client's request==============\n");
    while(1){
        if((server_connectfd = accept(server_sockfd, (struct sockaddr*)NULL, NULL)) == -1) {
        //设为null，不设置监听对象ip
        printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
        continue;
        }
        
        //接收客户端传过来的数据
        server_recvmsglen = recv(server_sockfd, buff, MAXLINE, 0);
        if(!fork()){
            if(send(server_connectfd, "Hello, you are connected!\n", 26, 0) == -1)
                perror("send error");
            close(server_connectfd);
            exit(0);
        }
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        close(server_connectfd);
    }
    close(server_sockfd);
    
    return 0;
}
