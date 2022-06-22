#ifndef   __TIMERBASE_H_
#define __TIMERBASE_H_
#include"Typedef.h"
#include <stdio.h>
#include<time.h>
#include <sys/time.h>
#include<sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdint.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
typedef struct
{
    UINT16  year;
    UINT16 month;
    UINT16 day;
    UINT16 hour;
    UINT16 min;
    UINT16 sec;
}_time;
int SYSTEMCLOCK_GetClock(_time *t);//获取时间

#endif