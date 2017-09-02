#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

#define STRING "Hello world!"
#deinf BUFSIZE 100

int main()
{
    int pipefd[2];
    pid_t pid;
    char buf[BUFSIZE];
    if(pipe(pipefd) == -1)
    {
        printf("Create pipe error\n");
        exit(1);
    }

    pid = fork();
    if(pid == -1)
    {
        printf("Create fork error\n");
        exit(1);
    }
    if(pid == 0)
    {
        /* this is child */
        close(pipefd[1]);
        printf("Child pid is: %d\n", getpid());
        if(read(pipefd[0], buf, BUFSIZE) < 0)
        {
            printf("read error\n");
            exit(1);
        }
        printf("%s\n", buf);
    }
    else
    {
        /* this is parent */
        close(pipefd[0]);
        printf("Parent pid is:%d\n", getpid());
        snprintf(buf, BUFSIZE, "Message from parent: My pid is: %d", getpid());
        if(write(pipefd[1], buf, strlen(buf)) < 0)
        {
            printf("write error\n");
            exit(1);
        }
        wait(NULL);
    }
    return 0;
}