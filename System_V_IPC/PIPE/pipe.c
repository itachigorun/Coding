#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define STRING "Hello world!"

int main()
{
    int pipefd[2];
    char buf[BUFSIZE];

    if(pipe(pipefd) == -1)
    {
        printf("Create pipe error\n");
        exit(1);
    }

    if(write)
}