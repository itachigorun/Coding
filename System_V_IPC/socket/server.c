#include<stdio.h>  
#include<unistd.h>
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>
#include<signal.h>
#include<sys/select.h>
#include<time.h>

#define DEFAULT_PORT 8000  
#define MAXLINE 4096  
#define FAILURE -1
sigset_t sigSet;
#define TIMEOUT 30

void sigChildHandler(int signo)
{
    /*设置信号阻塞*/
    if(sigprocmask(SIG_BLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_BLOCK failed\n");
        exit(1);
    }
    /*解开信号阻塞*/
    if(sigprocmask(SIG_UNBLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_UNBLOCK failed\n");
        exit(1);
    }
}

void sigTermHandler(int signo)
{
    /*设置信号阻塞*/
    if(sigprocmask(SIG_BLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_BLOCK failed\n");
        exit(1);
    }
    /*解开信号阻塞*/
    if(sigprocmask(SIG_UNBLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_UNBLOCK failed\n");
        exit(1);
    }
}

void sigAlarmHandler(int signo)
{
    /*设置信号阻塞*/
    if(sigprocmask(SIG_BLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_BLOCK failed\n");
        exit(1);
    }
    /*解开信号阻塞*/
    if(sigprocmask(SIG_UNBLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_UNBLOCK failed\n");
        exit(1);
    }
}
int main(int argc, char** argv)
{  
    int socket_fd, connect_fd;  
    struct sockaddr_in servaddr, getcliaddr, getseraddr, clientaddr;  
    char buff[MAXLINE];  
    int receivelen;
    int len = sizeof(struct sockaddr_in);
    int flag = 1;
    struct linger lingopt;
    struct sigaction act;

    /* 清空信号 */
    if(sigemptyset(&sigSet) == FAILURE)
    {
        printf("sigemptyset failed\n");
        exit(1);
    }
    /* 添加子进程退出信号 */
    if(sigaddset(&sigSet, SIGCHLD) == FAILURE)
    {
        printf("sigaddset SIGCHLD failed\n");
        exit(1);
    }
    /* 添加退出信号,kill命令默认信号 */
    if(sigaddset(&sigSet, SIGTERM) == FAILURE)
    {
        printf("sigaddset SIGTERM failed\n");
        exit(1);
    }
    /* 添加时钟信号 */
    if(sigaddset(&sigSet, SIGALRM) == FAILURE)
    {
        printf("sigaddset SIGALRM failed\n");
        exit(1);
    }
    /* 阻塞信号处理 */
    if(sigprocmask(SIG_BLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask failed\n");
        exit(1);
    }
    printf("signal set success\n");
    /* 设置子进程信号处理函数 */
    act.sa_handler = sigChildHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &act, NULL) == FAILURE)
    {
        printf("sigaction SIGCHLD failed\n");
        exit(1);
    }
    /* 设置退出信号处理函数 */
    act.sa_handler = sigTermHandler;
    if(sigaction(SIGTERM, &act, NULL) == FAILURE)
    {
        printf("sigaction SIGTERM failed\n");
        exit(1);
    }
    /* 设置时钟信号处理函数 */
    act.sa_handler = sigAlarmHandler;
    if(sigaction(SIGALRM, &act, NULL) == FAILURE)
    {
        printf("sigaction SIGALRM failed\n");
        exit(1);
    }
     /*解开信号阻塞*/
    if(sigprocmask(SIG_UNBLOCK, &sigSet, NULL) == FAILURE)
    {
        printf("sigprocmask SIG_UNBLOCK failed\n");
        exit(1);
    }

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
    //servaddr.sin_addr.s_addr = inet_addr("192.16.1.1");
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
    printf("%s:",buff);
    printf("%d\n",ntohs(getseraddr.sin_port));
    /*输出6*/
    memset(buff,0,MAXLINE);
    if(inet_ntop(AF_INET, &getseraddr.sin_addr, buff, MAXLINE)==NULL)
    {
        printf("error\n");
        close(socket_fd);
        return FAILURE;
    }
    else
    {
        printf("%s:",buff);
        printf("%d\n",ntohs(getseraddr.sin_port));
    }

    printf("======waiting for client's request======\n");  
    while(1){  
        if((connect_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, (socklen_t *)&len)) == -1) 
        //connect_fd = accept(socket_fd, (struct sockaddr*)&NULL, NULL); 不关心客户端的地址后两个参数填null
	    {  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            close(socket_fd);
            return FAILURE;  
        }

        //向客户端发送回应数据  
        if(fork() == 0){
            close(socket_fd); //关闭监听socket

    int iBytesRcved = 0 ;
    int iRet;
    time_t start = 0;
    if( TIMEOUT > 0 )
        start = time(NULL);

    do
    {
      if( TIMEOUT > 0 )
      {
         fd_set events;
         struct timeval tm;
         FD_ZERO(&events);
         FD_SET(connect_fd, &events);
         tm.tv_sec = TIMEOUT;
         tm.tv_usec = 0;
         iRet = select( connect_fd+1, &events, NULL, NULL, &tm);
         if (iRet < 0)
         {
             printf("Socket select is failed: errno=[%d-%s]\n", errno,strerror(errno));
             return FAILURE;
         }
         /* 超时 */
         if (iRet == 0)
         {
            printf("Socket read timeout\n");
            return -2;
         }
         time_t now = time(NULL);
         TIMEOUT = (start + TIMEOUT >= now) ? (TIMEOUT + start - now) : 0;
        }
        receivelen = read(connect_fd, (char*)buff + iBytesRcved, MAXLINE - iBytesRcved);
        if (receivelen == -1)
        {
            printf("read() read() failed, errno=[%d-%s]\n", errno, strerror(errno));
            return FAILURE;
        }

        if( receivelen == 0)
        {
           printf("read() peer disconnect, errno=[%d-%s]\n", errno, strerror(errno));
           /* receivelen为0是由于网络断开需重新建立socket链接*/
           return 1;
        }
        iBytesRcved += receivelen;
   }while( iBytesRcved < MAXLINE );
   

            memset(buff,0,MAXLINE);
            //接受客户端传过来的数据  
            receivelen = recv(connect_fd, buff, MAXLINE, 0);  
            buff[receivelen] = '\0';  
            printf("recv msg from client: %s\n", buff);  

            /* 输出1 */
            memset(buff,0,MAXLINE);
            strcpy(buff,inet_ntoa(clientaddr.sin_addr));
            printf("%s:",buff);
            printf("%d\n",ntohs(getseraddr.sin_port));
            
            /*输出2*/
            memset(buff,0,MAXLINE);
            if(inet_ntop(AF_INET, &clientaddr.sin_addr, buff, MAXLINE)==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
            {
	            printf("%s:",buff);
                printf("%d\n",ntohs(getseraddr.sin_port));
	        }
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
            printf("%s:",buff);
            printf("%d\n",ntohs(getseraddr.sin_port));
            /*输出4*/
            memset(buff,0,MAXLINE);
            if(inet_ntop(AF_INET, &getcliaddr.sin_addr, buff, MAXLINE)==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
            {
	        printf("%s:",buff);
                printf("%d\n",ntohs(getseraddr.sin_port));
            }

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
            printf("%s:",buff);
            printf("%d\n",ntohs(getseraddr.sin_port));
            
            /*输出6*/
            memset(buff,0,MAXLINE);
            if(inet_ntop(AF_INET, &getseraddr.sin_addr, buff, MAXLINE)==NULL)
            {
                printf("error\n");
                close(connect_fd);
                return FAILURE;
            }
            else
            {
	            printf("%s:",buff);
                printf("%d\n",ntohs(getseraddr.sin_port));
	        }

            if(send(connect_fd, "Hello,you are connected!\n", 26,0) == -1)  
                perror("send error");  
            /*    
            if(write(connect_fd, "Hello,you are connected!\n", 26) == -1)  
                perror("send error");  
            */    
            close(connect_fd);  
            exit(0);  
            }  
       
        close(connect_fd);  
    }
    close(socket_fd);  
}
