#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/msg.h>

typedef struct{
    long int msg_type;
    char text[BUFSIZ];
}msg_st;

int main()
{
    int running = 1;
    int msgid = -1;
    msg_st data;
    long int msgtype = 0;

    //建立消息队列
    msgid = msgget((key_t)1234, 0666|IPC_CREAT);
}