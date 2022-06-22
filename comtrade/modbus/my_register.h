#ifndef __MY_REGISTER_H
#define __MY_REGISTER_H
#include"Typedef.h"
#include<stdio.h>

void my_input_register_init();
void my_hold_register_init();
UINT8 my_input_register_getdata(UINT16 iAddr,UINT8 *pData,UINT16 iLen);//输入寄存器读
 UINT8 my_hold_register_getdata(UINT16 iAddr,UINT8 *pData,UINT16 iLen);//控制寄存器读

 void my_hold_register_setword(UINT16 iAddr,UINT16  Data);//控制寄存器写单个数据

UINT8 my_hold_register_setMulWord(UINT16 iAddr,UINT8 *pData,UINT16 iLenHR);//控制寄存器写多个数据
extern int my_input_register[];
extern int my_hold_register[];
#endif // 