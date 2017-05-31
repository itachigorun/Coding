#define BUFSIZE 1024

typedef struct{
    long int msg_type;
    char text[BUFSIZE];
}msg_st;