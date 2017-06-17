#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE *fp;
    char str[102]={0};
    char strTemp[100]={0};
    if((fp=fopen("text.txt", "a+")) == NULL){
        printf("Cannot open file, press any key to exit!\n");
        getchar();
        exit(1);
    }

    printf("Input a string:\n");
    fgets(strTemp, sizeof(strTemp), stdin);
    strcat(str, "\n");
    strcat(str, strTemp);
    fputs(str, fp);
    fclose(fp);

    return 0;
}