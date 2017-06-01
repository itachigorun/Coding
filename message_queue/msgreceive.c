#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/msg.h>


#define BUFSIZE 1024

typedef struct{
    long int msg_type;
    char text[BUFSIZE];
}msg_st;

int main()
{
    int running = 1;
    int msgid = -1;
    msg_st data;
    long int msgtype = 0;

    //建立消息队列
    msgid = msgget((key_t)1234, 0666|IPC_CREAT);
    if(msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    //从消息队列中获取消息，直到遇到end消息为止
    while(running)
    {
        if(msgrcv(msgid, (void *)&data, BUFSIZE, msgtype, 0) == -1)
        {
            fprintf(stderr,"msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("You wrote: %s\n",data.text);
        //直到遇到end结束
        if(strncmp(data.text, "end", 3) == 0)
            running = 0;
    }
    //删除消息队列
    if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}