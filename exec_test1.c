#include<unistd.h>
#include<stdio.h>

int main()
{
    char * envp[] = {"PATH=/tmp", "USER=itachigorun", "STATUS=testing", NULL};
    char * argv_execv[] = {"echo", "excuted by execv", NULL};
    char * argv_execvp[] = {"echo", "executed by execvp", NULL};
    char * argv_execve[] = {"env", NULL};
    
    if(fork() == 0)
        if(execl("/bin/echo", "echo", "executed by execl", NULL) < 0)
	    printf("Err on execl");

    if(fork() == 0)
        if(execlp("echo", "echo", "executed by execlp", NULL) < 0)
	    printf("Err on execl");

    if(fork() == 0)
        if(execle("/usr/bin/env", "env", NULL, envp) < 0)
	    printf("Err on execl");
    
    if(fork() == 0)
        if(execv("/bin/echo",argv_execv) < 0)
	    printf("Err on execl");
    
    if(fork() == 0)
        if(execvp("echo",argv_execvp) < 0)
	    printf("Err on execl");
    
    if(fork() == 0)
        if(execve("/usr/bin/env", argv_execve, envp) < 0)
	    printf("Err on execl");

return 0;
}
