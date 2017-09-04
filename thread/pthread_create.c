/* 2017-02-14  */
/* create thread,gcc -o test pthread_create.c -pthread  */
#include <stdio.h>
#include <pthread.h>

int * thread(void *arg)
{
    printf("thread id is %u .\n",(unsigned int)pthread_self());
    return NULL;
}

int main()
{
    pthread_t id;
    printf("Main thread id is %u \n",(unsigned int)pthread_self());
    
    if(!pthread_create(&id,NULL,(void *)thread,NULL))
    {
	    printf("succeed!\n");
	    return 0;
    }
    else
    {
        printf("Fail to Create Thread");
	    return -1;
    }
}
