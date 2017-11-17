#include<stdio.h>  
#include<unistd.h>
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>

#define DEFAULT_PORT 8000  
#define MAXLINE 4096  
#define FAILURE -1
int main(int argc, char** argv)
{  
    int socket_fd, connect_fd;  
    struct sockaddr_in servaddr, getcliaddr, getseraddr, clientaddr;  
    char buff[MAXLINE];  
    int receivelen;
    int len = sizeof(struct sockaddr_in);
    int flag = 1;
    struct linger lingopt;

    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    /*设置socket属性,port可以复用*/
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1)
    {
        printf("setsockopt() SO_REUSEADDR failed, errno=[%d],err desc=[%s]\n", errno, strerror(errno));
        close(socket_fd);
        return FAILURE;
    }
    /*设置socket为KEEPALIVE状态,用于保持网络连接*/
    if (setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) == -1)
    {
        printf("setsockopt() SO_KEEPALIVE failed, errno=[%d],err desc=[%s]\n", errno, strerror(errno));
        close(socket_fd);
        return FAILURE;
    }
    /*设置socket LINGER属性,在socket close时,如有未发送的数据,close将会阻塞*/
    lingopt.l_onoff = 1;
    lingopt.l_linger = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_LINGER, &lingopt, sizeof(lingopt)) == -1)
    {
        printf("setsockopt() SO_LINGER failed, errno=[%d],err desc=[%s]\n", errno, strerror(errno));
        close(socket_fd);
        return FAILURE;
    }

    //初始化  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
    servaddr.sin_addr.s_addr = inet_addr("172.16.1.17");
    servaddr.sin_port = htons(DEFAULT_PORT);      //设置的端口为DEFAULT_PORT  

    //将本地地址绑定到所创建的套接字上  
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  

    //开始监听是否有客户端连接  
    if( listen(socket_fd, 10) == -1){  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  

    /* 获得本地地址 */
    if(getsockname(socket_fd, (struct sockaddr *)&getseraddr, (socklen_t *)&len)!=0)
    {
        printf("getsockname err\n");
        close(socket_fd);
        return FAILURE;
    }
    /* 输出5 */
    memset(buff,0,MAXLINE);
    strcpy(buff,inet_ntoa(getseraddr.sin_addr));
    printf("%s\n",buff);
    
    /*输出6*/
    memset(buff,0,MAXLINE);
    if(inet_ntop(AF_INET, &getseraddr.sin_addr, buff, MAXLINE)==NULL)
    {
        printf("error\n");
        close(socket_fd);
        return FAILURE;
    }
    else
        printf("%s\n",buff);

    printf("======waiting for client's request======\n");  
    while(1){  
        if((connect_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, (socklen_t *)&len)) == -1) 
        //connect_fd = accept(socket_fd, (struct sockaddr*)&NULL, NULL); 不关心客户端的地址后两个参数填null
	    {  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            close(socket_fd);
            return FAILURE;  
        }

        memset(buff,0,MAXLINE);
        //接受客户端传过来的数据  
        receivelen = recv(connect_fd, buff, MAXLINE, 0);  
        //向客户端发送回应数据  
        if(!fork()){
            close(socket_fd); //关闭监听socket

            /* 输出1 */
            memset(buff,0,MAXLINE);
            strcpy(buff,inet_ntoa(clientaddr.sin_addr));
            printf("%s\n",buff);
            
            /*输出2*/
            memset(buff,0,MAXLINE);
            if(inet_ntop(AF_INET, &clientaddr.sin_addr, buff, MAXLINE)==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);
            /* 获得本地地址 */
            if(getsockname(connect_fd, (struct sockaddr *)&getcliaddr, (socklen_t *)&len)!=0)
            {
                printf("getsockname err\n");
                close(connect_fd);
                return FAILURE;
            }
            /* 输出3 */
            memset(buff,0,MAXLINE);
            strcpy(buff,inet_ntoa(getcliaddr.sin_addr));
            printf("%s\n",buff);
            
            /*输出4*/
            memset(buff,0,MAXLINE);
            if(inet_ntop(AF_INET, &getcliaddr.sin_addr, buff, MAXLINE)==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);

            /* 获得客户端地址 */
            if(getpeername(connect_fd, (struct sockaddr *)&getseraddr, (socklen_t *)&len)!=0)
            {
                printf("getsockname err\n");
                close(connect_fd);
                return FAILURE;
            }
            /* 输出5 */
            memset(buff,0,MAXLINE);
            strcpy(buff,inet_ntoa(getseraddr.sin_addr));
            printf("%s\n",buff);
            
            /*输出6*/
            memset(buff,0,MAXLINE);
            if(inet_ntop(AF_INET, &getseraddr.sin_addr, buff, MAXLINE)==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);

            if(send(connect_fd, "Hello,you are connected!\n", 26,0) == -1)  
                perror("send error");  
            /*    
            if(write(connect_fd, "Hello,you are connected!\n", 26) == -1)  
                perror("send error");  
            */    
            close(connect_fd);  
            exit(0);  
            }  
        buff[receivelen] = '\0';  
        printf("recv msg from client: %s\n", buff);  
        close(connect_fd);  
    }
    close(socket_fd);  
}
