#include<stdio.h>
int main()
{
    FILE *fp;
    char ch;

    //判断文件是否成功打开
    if((fp = fopen("text.txt", "r")) == NULL){
        printf("Cannot open file, press any key to exit!");
        getchar();
        exit(1);
    }

    //每次读取一个字节，直到读取完毕
    while((ch = fgetc(fp)) != EOF){
        putchar(ch);
    }
    putchar('\n'); //输出换行符

    if(ferror(fp)){
        puts("读取失败");
    }else{
        puts("读取成功");
    }

    fclose(fp);
    return 0;
}