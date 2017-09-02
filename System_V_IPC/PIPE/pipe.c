#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define STRING "Hello world!"
#define BUFSIZE 100

int main()
{
    int pipefd[2];
    char buf[BUFSIZE]={0};

    if(pipe(pipefd) == -1)
    {
        printf("Create pipe error\n");
        exit(1);
    }

    if(write(pipefd[1], STRING, strlen(STRING)) < 0)
    {
        printf("Write to pipe error\n");
        exit(1);
    }

    if(read(pipefd[0], buf, BUFSIZE) <0)
    {
        printf("Read error\n");
        exit(1);
    }
    printf("%s\n", buf);

    return 0;
}