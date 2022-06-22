#include "BitState.h"

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include<time.h>

UINT16 CoilState[COIL_SIZE];//线圈状态
UINT16 InputState[INPUTBIT_SIZE];//离散输入

//--------------------------------------------------------------
void BitState_Init()
{
	
	  UINT16 i;
      for(i=0;i<COIL_SIZE;i++)
         CoilState[i]=0;
		
      for(i=0;i<INPUTBIT_SIZE;i++)
        InputState[i]=1;				 
}

UINT8 Byte_GetStateBit(UINT16 *pBitState,UINT16 iCoilAdr,UINT8 *pData,UINT16 iCoilLen)
{
    UINT16 i;
    UINT8  Bit=0x01,Byte=0,Data=0;
    while(1)
    {
            for(i=0;i<8;i++)
            {
                if(pBitState[iCoilAdr++]!=0)
                    Data|=Bit;
                iCoilLen--;
                if(iCoilLen==0)
                    break;
                    Bit<<=1;
            }
        *pData++=Data;
        Byte++;						 
        if(iCoilLen==0)
        {
            return Byte;		
        }			 
        Data=0;
        Bit=0x01;
    } 				 
}
//TIMER_t Com_Tim,Cap_Tim;		
UINT8 Coil_GetStateByte(UINT16 iCoilAdr,UINT8 *pData,UINT16 iCoilLen)
{
	
			return Byte_GetStateBit(CoilState,iCoilAdr,pData,iCoilLen);
}	

int Coil_SetState(UINT16 iAddr,UINT16 OnState)
     {
		// 	UINT32 RelayID;
		// 	if(iAddr>=COIL_SIZE)
		// 		 return 0;
		//   if((iAddr>=COIL_COM_BOARD_ADDR)&&(iAddr<(COIL_COM_BOARD_ADDR+COIL_COM_BOARD_SIZE)))
		// 	  {
		// 		 RelayID=0x00000001<<(iAddr-COIL_COM_BOARD_ADDR);
		// 		//  if(OnState)
		// 		//   ComBoard_InsertCmdDoActive(RelayID);
		// 		//  else
		// 		// 	 ComBoard_InsertCmdDoNonActive(RelayID);
		// 		 return 1;
		// 		}	
			if(OnState)
			  CoilState[iAddr]=1;
			else
				CoilState[iAddr]=0;
			
			return 1;

		 } 
		 
UINT8 InputBit_GetStateByte(UINT16 iInputAdr,UINT8 *pData,UINT16 iBitLen)
{
			return Byte_GetStateBit(InputState,iInputAdr,pData,iBitLen); 	
}	


