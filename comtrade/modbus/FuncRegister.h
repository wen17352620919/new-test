#ifndef FUNCREGISTER_H_
#define FUNCREGISTER_H_
#include "Typedef.h"
#define  HOLDREG_FUNC_ID                  0   //4001
#define  HOLDREG_FUNC_KEY1                (HOLDREG_FUNC_ID+1)
#define  HOLDREG_FUNC_KEY2                (HOLDREG_FUNC_KEY1+1)
#define  HOLDREG_FUNC_KEY3                (HOLDREG_FUNC_KEY2+1)
#define  HOLDREG_FUNC_KEY4                (HOLDREG_FUNC_KEY3+1)
#define  HOLDREG_FUNC_KEY5                (HOLDREG_FUNC_KEY4+1)
#define  HOLDREG_FUNC_DATA                (HOLDREG_FUNC_ID+6)
#define  HOLDREG_FUNC_SIZE                560
extern UINT16 HoldReg_FuncZone[];
UINT8 HoldRegister_GetFuncData(UINT16 iAddr,UINT8 *pData,UINT16 iLen);
void HoldRegister_SetFuncWord(UINT16 iAddr,UINT8 *pData);
UINT8 HoldRegister_SetMulFuncWord(UINT16 iAddr,UINT8 *pData,UINT16 iLenHR);
#endif