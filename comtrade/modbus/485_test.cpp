/********************************************************************
* 		copyright (C) 2014 all rights reserved
*			 @file: rs485.c
* 		  @Created: 2014-8-6 14:00
* 	  	   @Author: conway chen
* 	  @Description: test the rs485 function of sending and receiving 
*	  @Modify Date: 2014-8-6 14:00
*********************************************************************/

/*
主机对从机读数据操作
    01            		 03            		00 01           	00 01          			  D5 CA 
 从机地址        功能号          数据地址      读取数据个数       CRC校验
 主机对从机写数据操作
   01            		 06            		00 01           		00 17          98 04 
  从机地址        功能号          数据地址          数据         CRC校验

ttySTM1  调试口
ttySTM6  usart6  PC6 PC7
从机
 */
//=========================================
#include"CRC16.h"
#include "BitState.h" //离散输入和线圈
#include"modbus_slave.h"
#include"serial_485.h" //串口

// #include"Register.h"  //寄存器
#include"TimerBase.h"//时间
#include "my_register.h"


#include <pthread.h>
#define path_touch_screen   "/dev/ttySTM6"

volatile int flag = 0;
//=========================================
int main(int argc, char *argv[])
{

	/* open serial port */
	int fd_modbus_screen = open(path_touch_screen,O_RDWR);
	if (fd_modbus_screen < 0) 
    {
		perror("open failed");
		return -1;
	}
	else 
	{
		printf("open %s ok\r\n",path_touch_screen);
	}
	/* set serial port */
	int i = set_port(fd_modbus_screen, 9600, 8, 'N', 1);
	if (i < 0) 
    {
		perror("set_port failed");
		return -1;	
	}
	else
	{
		printf("set port ok\r\n");
	}
	usleep(40000);
	BitState_Init();
    // HoldRegister_Init();	
	// InputRegister_Init();
	my_input_register_init();
	my_hold_register_init();
	modbus_read_screen((void*)fd_modbus_screen);
	


	
	// HoldRegister_SetWord(1,11);
	// HoldRegister_SetWord(2,14);

	// unsigned char data[] = {1,1,1,4};
	// int n = sizeof(data);
	// uint16_t crc = CRC16_Create(data,4);
	// data[n++]=(unsigned char)(crc>>8);
	// data[n++]=(unsigned char)(crc&0xff);
	// while(1)
	// {
	// 	write(fd_modbus_screen,data,n);
	// 	sleep(1);
	// }



	// pthread_t thread_modbus_screen;
	// int creat_modbus_screen = pthread_create(&thread_modbus_screen, NULL, modbus_read_screen, (void*)fd_modbus_screen);
    // if (creat_modbus_screen) 
    // {
    //     printf("thread_modbus_screen creat error  id=%d\r\n",creat_modbus_screen);

	// 	return -1;	
    // }
    // else
    // {
    //     printf("thread_modbus_screen creat ok\r\n");
    // }
	// while(1)
	// {
	// 	if(flag ==1)
	// 	{
	// 		printf("quit app\r\n");
	// 		break;
	// 	}
	// }



//		usleep(500000);
	/* restore the old configuration */		
	// tcsetattr(fd_modbus, TCSANOW, &oldtio);

	return 0;
}












