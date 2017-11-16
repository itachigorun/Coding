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
int main(int argc, char** argv){  
    int socket_fd, connect_fd;  
    struct sockaddr_in servaddr, getaddr, clientaddr;  
    char buff[4096];  
    int n;
    int len;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
    //serveraddr.sin_addr.s_addr = inet_addr(localip);
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

    printf("======waiting for client's request======\n");  
    while(1){  
        if(connect_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, (socklen_t *)&sizeof(clientaddr)) == -1)
	    {  //如果不关心客户端的地址后两个参数填null
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
            return FAILURE;  
        }  
        
        //接受客户端传过来的数据  
        n = recv(connect_fd, buff, MAXLINE, 0);  
        //向客户端发送回应数据  
        if(!fork()){
            close(socket_fd); //关闭监听socket
            
            /*输出1*/
            memset(buff,0,4096);
            if(inet_aton(buff, &clientaddr.sin_addr)==0)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);
            /*输出2*/
            memset(buff,0,4096);
            if(inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff))==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);
            if(getsockname(connect_fd, (struct sockaddr *)&getaddr, (socklen_t *)&sizeof(getaddr))!=0)
            {
                printf("getsockname err\n");
                close(connect_fd);
                return FAILURE;
            }
            /*输出3*/
            memset(buff,0,4096);
            if(inet_aton(buff, &getaddr.sin_addr) == 0)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);
            /* 输出4 */
            memset(buff,0,4096);
            if(inet_ntop(AF_INET, &getaddr.sin_addr, buff, sizeof(buff))==NULL)
                printf("error\n");
            else
                printf("%s\n",buff);

            if(getpeername(connect_fd, (struct sockaddr *)&getaddr, (socklen_t *)&sizeof(getaddr))!=0)
            {
                printf("getsockname err\n");
                close(connect_fd);
                return FAILURE;
            }
            /* 输出5 */
            memset(buff,0,4096);
            if((buff = inet_ntoa(getaddr.sin_addr)) == NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s",buff);
            /*输出6*/
            memset(buff,0,4096);
            if(inet_pton(AF_INET, buff, &getaddr.sin_addr) != 1)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
                printf("%s\n",buff);


            memset(buff,0,4096);
            if(send(connect_fd, "Hello,you are connected!\n", 26,0) == -1)  
                perror("send error");  
            close(connect_fd);  
            exit(0);  
            }  
        buff[n] = '\0';  
        printf("recv msg from client: %s\n", buff);  
        close(connect_fd);  
    }
    close(socket_fd);  
}
