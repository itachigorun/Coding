#include<stdio.h>
#include<stdlib.h>

#define N 2
typedef struct{
    char name[10];
    int num;
    int age;
    float score;
}stu;

int main(){
    FILE *fp;
    int i;
    stu boya[N], boyb[N];
    stu *pa = boya;
    stu *pb = boyb;
    if( (fp=fopen("text.txt","wt+")) == NULL ){
        printf("Cannot open file, press any key exit!");
        getchar();
        exit(1);
    }
    //从键盘读入数据，保存到boya
    printf("Input data:\n");
    for(i=0; i<N; i++,pa++){
        scanf("%s %d %d %f", pa->name, &pa->num, &pa->age, &pa->score);   
    }
   
    //将boya中的数据写入到文件
    for(i=0; i<N; i++,pa++){
        fprintf(fp,"%s %d %d %f\n", pa->name, pa->num, pa->age, pa->score);   
    }
    //重置文件指针
    rewind(fp);
    //从文件中读取数据，保存到boyb
    for(i=0; i<N; i++,pb++){
        fscanf(fp, "%s %d %d %f\n", pb->name, &pb->num, &pb->age, &pb->score);
    }
    
    //将boyb中的数据输出到显示器
    for(i=0; i<N; i++,pb++){
        printf("%s  %d  %d  %f\n", pb->name, pb->num, pb->age, pb->score);
    }
    fclose(fp);
    return 0;
}