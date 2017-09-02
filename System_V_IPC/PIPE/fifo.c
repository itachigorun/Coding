#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf(stderr, "Argument error\n");
        exit(1);
    }

    if(mkfifo(argv[1], 0600) < 0)    //argv[1]保存创建命名管道的地址
    {
        printf("mkfifo error\n");
        exit(1);
    }

    return 0;
}

/*
unlink(FIFO)删除创建的命名管道文件
*/