#include<stdio.h>
#include<stdlib.h>
int main()
{
    FILE *fp;
    char ch;
    //判断文件是否成功打开
    if((fp = fopen("text.txt", "w+")) == NULL){
        printf("Cannot open file, press any key to exit!\n");
        getchar();
        exit(1);
    }

    printf("Input a string:\n");
    //每次从键盘读取一个字符并写入文件
    while((ch = getchar())!='\n'){
        fputc(ch, fp);
    }

    fclose(fp);
    return 0;
}