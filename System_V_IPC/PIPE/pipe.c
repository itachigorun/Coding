#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define STRING "Hello world!"
#define BUFSIZE 100

int main()
{
    int pipefd[2];
    char buf[BUFSIZE];

    if(pipe(pipefd) == -1)
    {
        printf("Create pipe error\n");
        exit(1);
    }

    if(write(pipefd[1], buf, BUFSIZE) <0)
    {
        printf("Write error\n");
        exit(1);
    }
    printf("%s\n", buf);

    return 0;
}