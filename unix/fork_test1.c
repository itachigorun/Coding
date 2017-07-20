#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t fpid;
    int count = 0;
    fpid = fork();
    if(fpid < 0)
        printf("error in fork!");
    else if (fpid == 0)
    {
        printf("I am the child process, my process id is %d\n",getpid());
	count++;
    }
    else
    {
        printf("I am the parent process, my process id is %d\n",getpid());
	count++;
    }
    printf("the answer is: %d\n",count);
    return 0;
}
