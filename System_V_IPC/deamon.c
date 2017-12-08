/*deamon syndate*/
void deamonInit()
{
	int i;
	pid_t pid;
    struct sigaction sa;

	pid = fork();
	if (pid != 0) exit(0);

	setsid();

	signal(SIGHUP, SIG_IGN);

	pid = fork();
	if (pid != 0) exit(0);


    sa.sa_handler = SIG_IGN;
    sigemptyset($sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0)
        syslog("can't ignore GISHUP");
    if((pid = fork()) < 0)
        syslog("can't fork");
    else if(pid != 0)
        exit(0);
    
  	chdir("/");
	umask(0);
	
	for (i = 0; i < 64; i++) close(i);
	
#if 0
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    if(fd0 != 0 || fd != 1 || fd != 2){
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
#endif



    int fd = open( "/dev/null", O_RDWR );  
    /* 
     * handle failure of open() somehow 
     */  
    dup2( fd, 0 );  
    dup2( fd, 1 );  
    dup2( fd, 2 );  
    if ( fd > 2 )  
    {  
        close( fd );  
    }  


}
