#ifndef BITSTATE_H_
#define BITSTATE_H_
//#include"stm32f4xx.h"
#include"Typedef.h"


#define  COIL_SIZE             60 //开出板    0-15   测量板 16-31 通信板 32-47
#define  COIL_COM_BOARD_ADDR   0
#define  COIL_COM_BOARD_SIZE   16
#define INPUTBIT_SIZE         64
#define INPUTBIT_COM_BOARD    0
#define INPUTBIT_COM_SIZE     16

#define INPUTBIT_SIGNAL_RST   0
#define INPUTBIT_TV_BR        16
#define INPUTBIT_DEV_ALARM    17

#define INPUTBIT_DEV_BIT      18
#define INPUTBIT_ML_BIT        2
#define INPUTBIT_JX_BIT        1 
#define INPUTBIT_LOCK_BIT      11
// #define  InputBit_SetState(iInputAdr,iState) InputState[iInputAdr]=iState
// #define  InputBit_GetState(iInputAdr)        InputState[iInputAdr] 
// #define  Coil_GetState(iCoilAdr)             CoilState[iCoilAdr] 
// #define  Coil_SetBit(iCoilAdr,iState)       CoilState[iCoilAdr]=iState



void BitState_Init();

int Coil_SetState(UINT16 iAddr,UINT16 OnState);//设置单个线圈

UINT8 Coil_GetStateByte(UINT16 iCoilAdr,UINT8 *pData,UINT16 iCoilLen);//读线圈,长度不能大于8
UINT8 InputBit_GetStateByte(UINT16 iInputAdr,UINT8 *pData,UINT16 iBitLen);//读离散输入


extern UINT16 InputState[];
extern UINT16 CoilState[];
extern UINT16 InputAlarm[];
#endif
