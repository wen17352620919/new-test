//由年月日得到星期
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
unsigned char CaculateWeekDay(int y,int m, int d);
int main()
{
    int year = 2022;
    int month = 4;
    int day = 17;

     time_t time3;
     struct tm *p;
     time3 = time(NULL);
    
    p = localtime(&time3);
   
    printf("%d-%d-%d%d:%d:%d\n", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                p->tm_hour, p->tm_min, p->tm_sec);
    printf("week = %d\r\n", p->tm_wday);
   


    uint8_t  _week= CaculateWeekDay(year,month,day);
    printf("_week = %d\r\n", _week);
}



unsigned char CaculateWeekDay(int y,int m, int d)
{
    unsigned char buf;
    if(m==1||m==2)
     {
        m+=12;
        y--;
    }
    int iWeek=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    switch(iWeek)
    {
    case 0: printf("星期一\n");
                buf = 1;
                break;
    case 1: printf("星期二\n"); 
                buf = 2;
                break;
    case 2: printf("星期三\n");
                buf = 3;
                break;
    case 3: printf("星期四\n"); 
                buf = 4;
                break;
    case 4: printf("星期五\n"); 
                buf = 5;
                break;
    case 5: printf("星期六\n");
                buf = 6;
                break;
    case 6: printf("星期日\n");
                buf = 7;
                break;
    default :
                break;
    }
    printf("buf : %x\n",buf);
    return buf;
} 









