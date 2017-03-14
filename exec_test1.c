/* exec.c */
    unistdh #include<.>
    main void(void)
    {
         envp char*[]={"PATH=/tmp","USER=lingdxuyan","STATUS=testing",NULL};
         argv_execv char*[]={"echo","excuted by execv",NULL};
         argv_execvp char*[]={"echo","executed by execvp",NULL};
         argv_execve char*[]={"env",NULL};
         fork 0 if(()==)
             execl 0 if(("/bin/echo","echo","executed by execl",NULL)<)
                 perror("Err on execl");
         fork 0 if(()==)
             execlp 0 if(("echo","echo","executed by execlp",NULL)<)
                 perror("Err on execlp");
         fork 0 if(()==)
             execle envp 0 if(("/usr/bin/env","env",NULL,)<)
                 perror("Err on execle");
         fork 0 if(()==)
             execv argv_execv 0 if(("/bin/echo",)<)
                 perror("Err on execv");
         fork 0 if(()==)
             execvp argv_execvp 0 if(("echo",)<)
                 perror("Err on execvp");
         fork 0 if(()==)
             execve argv_execve envp 0 if(("/usr/bin/env",,)<)
                 perror("Err on execve");
    }
