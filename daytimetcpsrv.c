#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


#define MAXLINE 1000
#define LISTENQ 100

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    // fprintf(stderr, "socket");
    if ( ( listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        printf("socket error");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 )
        printf("bind error");

    if ( listen(listenfd, LISTENQ) < 0 )
        printf("listen error");

    for (;;) {
        if ( ( connfd = accept(listenfd, (struct sockaddr *) NULL, NULL) ) < 0 )
            printf("accept error");

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        if ( write(connfd, buff, strlen(buff)) < 0 )
            printf("write error");

        close(connfd);
    }
}
