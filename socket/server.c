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
    int server_sockfd;  //�������׽���
    struct sockaddr_in server_addr;  //�����������ַ�ṹ��
    int server_connectfd;
    char buff[MAXLINE];
    int server_recvmsglen;

    if( (server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    } //0������ݵڶ��������Զ�ѡ��Э��

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family   = AF_INET;    //����Ϊipv4ͨ��
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //������IP��ַ��ϵͳ�Զ���ȡ����IP��ַ
    server_addr.sin_port        = htons(DEFAULT_PORT);     //�������˿ں�
    
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
        //��Ϊnull�������ü�������ip
        printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
        continue;
        }
        
        //���տͻ��˴�����������
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
