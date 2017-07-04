/*
 *  去掉字符串左空格  
 */
char *trimLeftSpace(char *str)
{
   char *temp;

   temp = str;

   while (*temp)
   {
      if (*temp == ' ')
         ++temp;
      else
         break;
   }
   if (temp > str)
      strcpy (str, temp);

   return(str);
}

/*
 *  去掉字符串右空格  
 */
char *trimRightSpace(char *str)

    int temp;

    temp = strlen(str);
    if (temp <= 0)
        return(str);
    while ((temp != 0) && (str[temp-1] == ' '))
        temp--;
    str[temp]='\0';
    return(str);

}

/*
 *  去掉字符串前后空格 
 */
char *trimSpace(char *str)
{
    return(trimLeftSpace(trimRightSpace(str)));
}

/*
 * 将传入的字符串转换为全部转换成大写  
 */     
void toUpper(const char *strIn, int len, char *strOut)
{
   int i = 0;

   for( i=0; i < len; i++ )
      strOut[i] = toupper(strIn[i]);

   return;
}

/*
 *     检查字符串是否为空( 只包含字符space, '\t', etc )
 */
int isBlank( const char *str)
{

   while( isspace(*str) ) 
      str++;

   /* 到字符串尾 */
   if( *str == 0 )
      return TRUE;
   else
     return FALSE;
}
