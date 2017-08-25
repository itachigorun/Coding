#include<sys/ipc.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
    struct stat f_stat;
    if(argc != 2)
    {
        printf("Please input pathname\n");
        exit(0);
    }

    stat(argv[1], &f_stat);
    printf("st_dev: %lx, st_ino: %lx, key: %x\n", f_stat.st_dev, f_stat.st_ino, ftok(argv[1], 0x57));

    return 0;
}


/*
#include<sys/stat.h>
#include<unistd.h>
int stat(const char *file_name, struct stat *buf )  
通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
执行成功则返回0，失败返回-1，错误代码存于errno
struct stat {  
    dev_t         st_dev;       //文件的设备编号  
    ino_t         st_ino;       //节点  
    mode_t        st_mode;      //文件的类型和存取的权限  
    nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1  
    uid_t         st_uid;       //用户ID  
    gid_t         st_gid;       //组ID  
    dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号  
    off_t         st_size;      //文件字节数(文件大小)  
    unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)  
    unsigned long st_blocks;    //块数  
    time_t        st_atime;     //最后一次访问时间  
    time_t        st_mtime;     //最后一次修改时间  
    time_t        st_ctime;     //最后一次改变时间(指属性)  
};  

#include<sys/ipc.h>
key_t ftok (const char *pathname, int id);
ftok函数返回key_t值是由三部分组成：
pathname所在文件系统的信息（stat结构的st_dev成员）
pathname在本文件系统内的索引节点号（stat结构的st_ino成员）
id的低序8位（不能为0）
*/


/*
IPC_PRIVATE 建立IPC,key可以为此值
IPC_CREAT  如果没有建立，有不处理
IPC_CREAT|IPC_EXCL  没有则创立，如果有则返回错误
*/