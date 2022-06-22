#ifndef MY_GPIO_H
#define MY_GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include<pthread.h>
#include<poll.h>
 
#define MSG(args...) printf(args) 

#define AD_NSS1_SET() write(fd118, "1", 1);
#define AD_NSS1_RESET() write(fd118, "0", 1);
#define READ_ADBUSY() read(fd117, busydata, 1);


extern int fd117;//AD_BUSY1，1有效
extern int fd118;//AD_NSS1,0触发
extern uint8_t busydata[10];
extern int gpiooveflag;

/*内部会关闭fd*/
int gpio_export(int pin);//导出gpio节点  
int gpio_unexport(int pin);//删除gpio节点
int gpio_read(int pin);//读gpio
int gpio_write(int pin, int value);//写gpio
int gpio_direction(int pin, int dir) ;//gpio输入输出设置
int gpio_edge(int pin, int edge);//gpio中断设置
int gpio_active(int pin, int act);//gpio极性

void *ReadBusy(void*arg);//线程判断117引脚输入状态

int OpenGpio(int pin,char *ability,int wr);//打开导出的gpio的属性,内部并不会关闭fd

long  testGettimeofday();//返回秒数，相减得到秒数
void  Gettimeofday();//打印秒数

#endif // !MY_GPIO_H