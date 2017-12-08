/* 字符串转换为秒数 */
void shiftTimefromGPS(const char *pTime ,time_t *pGmt)
{
	char			tmpStr[5];
	char			tmpTime[15];
	struct tm 		ltm;

	memset(tmpTime,0,15);
	memcpy(tmpTime, pTime, 14);

	memset(&ltm,0,sizeof(ltm));
	/*HH24MiSSYYYYMMDD */
	/* hour */
	memset(tmpStr,0,5);
	memcpy(tmpStr,tmpTime, 2);
	ltm.tm_hour  = atoi(tmpStr);
	/* min */
	memset(tmpStr,0,5);
	memcpy(tmpStr,tmpTime + 2, 2);
	ltm.tm_min  = atoi(tmpStr) ;
	/* second*/
	memset(tmpStr,0,5);
	memcpy(tmpStr,tmpTime + 4, 2);
	ltm.tm_sec  = atoi(tmpStr) ;
	/* year */
	memset(tmpStr,0,5);
	memcpy(tmpStr,tmpTime + 6,4);
	ltm.tm_year = atoi(tmpStr) - 1900;
	/* month */
	memset(tmpStr,0,5);
	memcpy(tmpStr,tmpTime + 10, 2);
	ltm.tm_mon  = atoi(tmpStr) - 1;
	/* day */
	memset(tmpStr,0,5);
	memcpy(tmpStr,tmpTime + 12, 2);
	ltm.tm_mday  = atoi(tmpStr) ;

	*pGmt = mktime(&ltm);
}

/* ---------------------------------------------------------------- */
/* 此函数会返回从公元 1970 年1 月1 日的UTC 时间从0 时0 分0 秒算起到现在所经过的秒数 */
    int seconds = time((time_t*)NULL);
    printf("%d\n", seconds);

    time_t now;
    time(&now);  
    printf("Today's date and time: %s",ctime(&now));  /* 返回一字符串表示目前当地的时间日期。 */


/* ------------------------------------------------------------------------------- */
struct tm {
int tm_sec; /* 秒 – 取值区间为[0,59] */
int tm_min; /* 分 - 取值区间为[0,59] */
int tm_hour; /* 时 - 取值区间为[0,23] */
int tm_mday; /* 一个月中的日期 - 取值区间为[1,31] */
int tm_mon; /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
int tm_year; /* 年份，其值等于实际年份减去1900 */
int tm_wday; /* 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推 */
int tm_yday; /* 从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推 */
int tm_isdst; /* 夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时，tm_isdst()为负。*/
}

    time_t now;
    struct tm *tm_now;
    time(&now);
    tm_now = localtime(&now);  /* 将时间数值变换成本地时间 */
    printf("now datetime: %d-%d-%d %d:%d:%d\n",
            tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, 
            tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);



    time_t now;
    struct tm *timenow;
    time(&now);
	timenow = gmtime(&now); /* 此函数返回的时间日期未经时区转换，而是UTC时间 */
	printf("%s", asctime(timenow);  /* 将UTC时间转换,返回的字符串是一个ASCII码字符集的字符串 */


/* ------------------------------------------------------------------------------------------ */
#include<sys/time.h>
#include<unistd.h>

struct timeval
{
    time_t      tv_sec;     /* 秒（seconds） */
    suseconds_t tv_usec;    /* 微秒（microseconds） */
};
struct timezone
{
  int tz_minuteswest; //和Greenwich 时间差了多少分钟
  int tz_dsttime; //日光节约时间的状态
};

    struct timeval sTimeVal;
	struct timezone sTimeZone;
    gettimeofday(&sTimeVal, &sTimeZone);   /* 取得当前时间和时区 */
    //gettimeofday(&sTimeVal, NULL);

    gTimeVal.tv_sec = *pGmt;
    if (settimeofday(&gTimeVal, &sTimeZone) == -1)  /* root设置时间 */
	{
		syslog( LOG_ERR, "%m:%s", "Error in settimeofday minus" );
		return -1;
	}