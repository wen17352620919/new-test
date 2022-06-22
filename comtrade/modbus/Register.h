#ifndef  _REGISTER_H_
#define _REGISTER_H_
#include"Typedef.h"
#include<stdio.h>
//----------------------------------------------------------------
#define BOARD_IO_SIZE 100
#define IOBOARD_SIZE 100
//----------------------------------------------------------------


#define HOLDREGISTER_SIZE    100
#define INPUTREGISTER_SIZE   720
#define INPUTREGISTER_CAN_ADR            100        
#define  HOLDREG_SYS_DT                   0
#define  HOLDREG_SYS_DT_SIZE              6
#define  HOLDREG_SYS_DT_CAL            ((HOLDREG_SYS_DT+HOLDREG_SYS_DT_SIZE))
#define  HOLDREG_TRIP_CTRL              (HOLDREG_SYS_DT_CAL+1)
struct Io_Z_t {float R,X;};
struct Io_BoardData_t {
			 struct Io_Z_t Zo2[BOARD_IO_SIZE];
	     UINT32 AllSetValue_CRC;
	     UINT16 Device_ERROR;
	     float Io2[BOARD_IO_SIZE];
	     float Ang[BOARD_IO_SIZE];
	     float Io1[BOARD_IO_SIZE];
	     struct Io_Z_t Zo1[BOARD_IO_SIZE];
	      UINT16 DIDO;    
};
extern struct Io_BoardData_t Io_BoardData[IOBOARD_SIZE];
extern UINT16 *HoldRegister[];
extern UINT16 *InputRegister[];
void HoldRegister_Init(void);//控制寄存器初始化
void InputRegister_Init(void);//输出寄存器初始化
UINT8 HoldRegister_GetData(UINT16 iAddr,UINT8 *pData,UINT16 iLen);//控制寄存器取数据
void HoldRegister_SetWord(UINT16 iAddr,UINT16  Data);//控制寄存器写单个数据

UINT8 HoldRegister_SetMulWord(UINT16 iAddr,UINT8 *pData,UINT16 iLenHR);//
UINT8 InputRegister_GetData(UINT16 iAddr,UINT8 *pData,UINT16 iLen);//输入寄存器取数据
#endif