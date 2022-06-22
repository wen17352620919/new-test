#ifndef __SERIAL_485_
#define __SERIAL_485_
#include <stdio.h>
#include <termios.h>
#include <linux/ioctl.h>
#include <linux/serial.h>
#include <asm-generic/ioctls.h> /* TIOCGRS485 + TIOCSRS485 ioctl definitions */
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include<sys/ioctl.h>
#include<stdint.h>

//---------------------------------------------------------------------
typedef enum {DISABLE = 0, ENABLE} RS485_ENABLE_t;
//---------------------------------------------------------------------
int set_port(int fd, int nSpeed, int nBits, char nEvent, int nStop);//设置端口


//----------------------------------------------------------------------------------暂未使用
int rs485_enable(const int fd, const RS485_ENABLE_t enable);
int change_mod_rs485(int fd,int value);  //read=0,write=1,
#endif