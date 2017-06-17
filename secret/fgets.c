#include<stdio.h>
#include<stdlib.h>
#define N 101

int main()
{
    FILE *fp;
    char str[N];
    if((fp = fopen("text.txt", "r")) == NULL){
        printf("Cannot open file, press any key to exit!\n");
        getchar();
        exit(1);
    }
        while(fgets(str, N, fp) != NULL){
            printf("%s", str);
        }
        fclose(fp);
        return 0;
    
}