#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<pwd.h>

static void my_alarm(int signo)
{
  struct passwd * rootptr;
  printf("in signal handler\n");
  if((rootptr = getpwnam("root")) == NULL)
      printf("getpwnam(root) error");
  alarm(1);
}

int main()
{
  struct passwd * ptr;
  signal(SIGALRM, my_alarm);
  alarm(1);
  for(;;){
    if((ptr = getpwnam("luffy")) == NULL)
       printf("getpwnam error");
    if(strcmp(ptr->pw_name, "sar") != 0)
       printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
  }

}
