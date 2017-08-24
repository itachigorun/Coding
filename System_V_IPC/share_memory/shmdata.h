#ifndef _SHMDATA_H_
#define _SHMDATA_H_

#define TEXT_SZ 2048
#define BUFSIZE 2048

typedef struct{
    int written;         //作为一个标志，非0表示可读，0表示可写
    char text[TEXT_SZ];  //记录写入和读取的文本
}shared_use_st;

#endif