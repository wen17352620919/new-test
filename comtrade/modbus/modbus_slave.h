#ifndef __MODBUS_SLAVE_H_
#define __MODBUS_SLAVE_H_
#include<stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include"ModbusDef.h"

#define BYTE_SWAP(x)    ((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8))
#define BYTE_UNION(x,y) 	 ((x<<8)|(y&0xff))
#define MODBUS_MIN_LENGTH   		8

/*******************    功能码 ****************/
#define MODBUS_FUNC_1                   0x01	   //
#define MODBUS_FUNC_2                   0x02	   //读开入状态读保护动作信息
#define MODBUS_FUNC_3                   0x03	   //读定值
#define MODBUS_FUNC_4                   0x04	   //读模拟量
#define MODBUS_FUNC_5                   0x05	   //控制开出
#define MODBUS_FUNC_6                   0x06	   //写单定值
#define MODBUS_FUNC_15                  0x0f     //复归信号
#define MODBUS_FUNC_16                  0x10	  //写多定值


typedef struct {
	              UINT8 SLAVE_ADDR;
	              UINT8 FUNC;
	              UINT8 RSV1;
				        UINT8 RSV2;
				        UINT8 NoOfREG_H;
				        UINT8 NoOfREG_L;
               } T_MODBUS_HEAD;
typedef struct {
                 UINT8	SLAVE_ADDR;
				         UINT8  FUNC;
				         UINT8  ADDR_H;
				         UINT8  ADDR_L;
				         UINT8  POINT_H;
				         UINT8  POINT_L;
				         UINT8  CRC_H;
				         UINT8  CRC_L;
               } T_MODBUS_READ_CMD;

typedef struct {
                 UINT8	 SLAVE_ADDR;
				         UINT8  FUNC;
				         UINT8  BYTECOUNT;
				         UINT8  DATA[100];
               } T_MODBUS_READ_RESPONSE;

typedef struct {
	               UINT8	SLAVE_ADDR;
				         UINT8  FUNC;
				         UINT8  ADDR_H;
				         UINT8  ADDR_L;
				         UINT8  DATA_H;
				         UINT8  DATA_L;
				         UINT8  CRC_H;
				         UINT8  CRC_L;
                } T_MODBUS_WRITE_CMD;
typedef struct {
	               UINT8	SLAVE_ADDR;
				         UINT8  FUNC;
				         UINT8  ADDR_H;
				         UINT8  ADDR_L;
				         UINT8  POINT_H;
				         UINT8  POINT_L;
	               UINT8  BYTES;
				         UINT8  DATA[100];
                } T_MODBUS_WRITEMUL_CMD;
typedef struct {
	              UINT8 SLAVE_ADDR;
	              UINT8 FUNC;
	              UINT8 ERR;
               } T_MODBUS_ERR;														 
#define MODBUS_HR_FUNC_ADR       4000
#define MODBUS_HR_FUNC_SIZE      200


/*
01 (0x01)        读线圈 
02 (0x02)        读离散量输入
03 (0x03)        读保持寄存器
04(0x04)         读输入寄存器
05 (0x05)        写单个线圈 
06 (0x06)        写单个寄存器

16 (0x10)        写多个寄存器
*/

UINT16 MODBUS_RespantERR(unsigned char *Modbus_Buffer,unsigned char cERR_Type);//错误处理
UINT16 MODBUS_Fuc1Response(unsigned char *Modbus_Buffer);//modbus功能玛1响应函数
UINT16 MODBUS_Fuc2Response(unsigned char *Modbus_Buffer);//modbus功能玛2响应函数
UINT16 MODBUS_Fuc3Response(unsigned char *Modbus_Buffer);//modbus功能玛3响应函数
UINT16 MODBUS_Fuc4Response(unsigned char *Modbus_Buffer);//modbus功能玛4响应函数
UINT16 MODBUS_Fuc5Response(unsigned char *Modbus_Buffer);//modbus功能玛5响应函数
UINT16 MODBUS_Fuc6Response(unsigned char *Modbus_Buffer);//modbus功能玛6响应函数
UINT16 MODBUS_Fuc16Response(unsigned char *Modbus_Buffer);//modbus功能玛16响应函数



void* modbus_read_screen(void* fd);//线程持续读
uint16_t modbus_screen_deal_data(unsigned char *Modbus_Buffer);//modbus处理

void char_uint16(char buf[],int len,uint16_t  data[]);
#endif // !


