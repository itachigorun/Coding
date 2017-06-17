#include<stdio.h>
#include<stdlib.h>

#define N 2
typedef struct{
    char name[10]; //姓名
    int num;  //学号
    int age;  //年龄
    float score;  //成绩
}stu;

int main()
{
    FILE *fp;
    int i;
    stu boya[N], boyb[N];
    stu *pa = boya;
    stu *pb = boyb;
    if( (fp=fopen("text.txt", "wb+")) == NULL ){
        printf("Cannot open file, press any key to exit!\n");
        getchar();
        exit(1);
    }
    //从键盘读入数据，保存到boya
    printf("Input data:\n");
    for(i=0; i<N; i++,pa++){
        scanf("%s %d %d %f", pa->name, &pa->num,&pa->age, &pa->score);
    }

    //将数组 boya 的数据写入文件
    fwrite(boya, sizeof(stu), N, fp);
    //将文件指针重置到文件开头
    rewind(fp);
    //从文件读取数据并保存到数据 boyb
    fread(boyb, sizeof(stu), N, fp);
    //输出数组 boyb 中的数据
    for(i=0; i<N; i++,pb++){
        printf("%s  %d  %d  %f\n", pb->name, pb->num, pb->age, pb->score);
    }
    fclose(fp);
    return 0;
}