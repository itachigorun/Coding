#include<stdio.h>
#include<stdlib.h>
#define N 5
int main()
{
    //从键盘输入的数据放入a，从文件读取的数据放入b
    int a[N], b[N];
    int i, size = sizeof(int);
    FILE *fp;

    if((fp = fopen("text.txt", "rb+")) == NULL){
        printf("Cannot open file, press any key to exit!\n");
        getchar();
        exit(1);
    }

    //从键盘输入数据，并保存到数组a
    for(i = 0; i<N; i++){
        scanf("%d", &a[i]);
    }

    //将数组a的内容写入到文件
    fwrite(a, size, N, fp);
    //将文件中的位置指针重新定位到文件开头
    rewind(fp);
    //从文件读取内容并保存到数组b
    fread(b, size, N, fp);
    //在屏幕上显示数组b的内容
    for(i = 0; i<N; i++){
        printf("%d", b[i]);
    }
    printf("\n");
    fclose(fp);
    return 0;
}