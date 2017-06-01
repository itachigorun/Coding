#ifndef _HEAD_H
#define _HEAD_H

#define BUFSIZE 1024

typedef struct{
    long int msg_type;
    char text[BUFSIZE];
}msg_st;

#endif