#include "my_register.h"
#define my_input_register_size 720
#define my_hold_register_size 100

int my_input_register[my_input_register_size];
int my_hold_register[my_hold_register_size];

void my_input_register_init()
{
    for(int i=0;i<my_input_register_size;i++)
    {
        my_input_register[i] = i;
    }   
}

void my_hold_register_init()
{
    for(int i=0;i<my_hold_register_size;i++)
    {
        my_hold_register[i] = i;
    }   
}

UINT8 my_input_register_getdata(UINT16 iAddr,UINT8 *pData,UINT16 iLen)
{
        int i;
        UINT16 Data;
        for(i=0;i<iLen;i++)
        {
                Data=my_input_register[iAddr];
                *pData++=((Data>>8)&0x00ff);//16字节拆成两个8字节
                *pData++=(Data&0x00ff);
                iAddr++;
        } 
        return 2*iLen;
 }		


 UINT8 my_hold_register_getdata(UINT16 iAddr,UINT8 *pData,UINT16 iLen)
{
        int i;
        UINT16 Data;
        for(i=0;i<iLen;i++)
        {
                Data=my_hold_register[iAddr];
                *pData++=((Data>>8)&0x00ff);
                *pData++=(Data&0x00ff);
                iAddr++;
        } 
        return 2*iLen;
 }		

 void my_hold_register_setword(UINT16 iAddr,UINT16  Data)
 {
     my_hold_register[iAddr] = Data;
 }

 UINT8 my_hold_register_setMulWord(UINT16 iAddr,UINT8 *pData,UINT16 iLenHR)
 {
    UINT16 i,Data;
    if((iAddr+iLenHR)>my_hold_register_size)//两个8字节合成一个16字节
                return 0;
    for(i=0;i<iLenHR;i++)
    {
        Data=*pData++;
        Data<<=8;
        Data|=(*pData)&0xff;
        pData++;
        my_hold_register[iAddr]=Data;	
        iAddr++;
    }
    return 1;	
 }