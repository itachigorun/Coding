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
/*
    if(mkfifo(argv[1], 0600) < 0)
    {
        printf("mkfifo error\n");
        exit(1);
    }
*/
    if(mknod(argv[1], 0600|S_IFIFO, 0) < 0)
    {
        printf("mknod()");
        exit(1);
    }
    return 0;
}