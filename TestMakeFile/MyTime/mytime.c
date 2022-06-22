#include "mytime.h"


//返回s数，调用2次相减得过去的s数
long  testGettimeofday()
{
    struct timeval t1;
    gettimeofday(&t1, NULL);


    return t1.tv_sec;

}


//打印s数和ms
void  Gettimeofday()
{
    struct timeval t1;
    gettimeofday(&t1, NULL);

    printf(" sec = %ld\r\n", t1.tv_sec);

    printf(" usec = %ld\r\n",t1.tv_usec );

}
//非高精度时间间隔判断,s级别
void TimeSpace_s()
{
        time_t t_start,t_end;
        t_start =time(NULL) ;
        sleep(3);
        t_end =time(NULL) ;
        printf("time: %.0f s\n",difftime(t_end,t_start)) ;//difftime计算两个时刻之间的时间差
        return ;
}
//高精度时间间隔判断，us级
void TimeSpace_us()
{
        struct timeval start, end;
        gettimeofday( &start,NULL );
        sleep(3);
        gettimeofday( &end,NULL );
        int timeuse =1000000 * ( end.tv_sec -start.tv_sec) + end.tv_usec -start.tv_usec;
        printf("time: %d us\n",timeuse);
        return ;
}


long long getSystemTime()
{
    struct timeb t;
    ftime(&t);
    return 1000 *t.time +t.millitm;
}
//高精度时间间隔判断，ms级
void TimeSpace_ms()
{
        long  long start=getSystemTime();
        sleep(3);
        long long end=getSystemTime();
     
        printf("time: %lld ms\n",end-start);
        return ;
}


void MyTime_Demo()
{

      TimeSpace_us();
  TimeSpace_ms();
    /*****************时间测试******************/
//     Gettimeofday();
//     long t1 = testGettimeofday();
//     long t2 = 0;
//     while(1)
//     {
//          t2 = testGettimeofday();
//          if(t2-t1>10)
//          {
//              break;
//          }
//     }
// Gettimeofday();
    /*字符串操作*/
    // char gpiox[40]="/sys/class/gpio/gpio";
    // snprintf(gpiox, sizeof(gpiox), "%d", 17);  
    // strcat(gpiox,"/value");
    // printf("%s\r\n",gpiox);//17/value
}