#include"TimerBase.h"
#include <time.h>
//_time t;
int SYSTEMCLOCK_GetClock(_time  *t)
{
    struct timeval vt;
    struct timezone zt;
    struct tm *p;
    gettimeofday(&vt,&zt);
    p = localtime(&vt.tv_sec);
    printf("time = %d-%d-%d %d:%d:%d.%ld\n", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                p->tm_hour, p->tm_min, p->tm_sec,vt.tv_usec);

    uint32_t Delayms = vt.tv_usec/1000;
  
  //--------------------------------------
    t->year = p->tm_year+1900 ;
    t->month = p->tm_mon+1;
    t->day = p->tm_mday;
    t->hour = p->tm_hour;
    t->min = p->tm_min;
    t->sec = p->tm_sec;


  //  printf("%d\n",Delayms);
    return Delayms;
}