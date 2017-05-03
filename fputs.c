#include<stdio.h>
int main()
{
FILE *pFile;
char sentence[10];
printf("enter: ");
fgets(sentence,10,stdin);
pFile =fopen("mylog.txt","a");
fputs(sentence,pFile);
fclose(pFile);
return 0;
}
