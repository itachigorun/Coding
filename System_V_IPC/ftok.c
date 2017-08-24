#include<sys/ipc.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, int **argv)
{
    struct stat stat;
    if(argc != 2)
    {
        printf("Please input pathname\n");
        exit(0);
    }
    
    //int stat(const char *file_name, struct stat *buf )  
    stat(argv[1], &stat);
    printf("st_dev: %lx, st_ino: %lx, key: %x\n", (long)stat.st_dev, (long)stat.st_ino, ftok(argv[1], 0x57));

    return 0;
}