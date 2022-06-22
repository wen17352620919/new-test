#include"Register.h"

//#include"PhaseSelectLine.h"
//#include"FaultManage.h"

#include"string.h"

//#include"ActiveIoTr.h"

//#include"FaultManage.h"

struct Io_BoardData_t Io_BoardData[IOBOARD_SIZE];
UINT16 *HoldRegister[HOLDREGISTER_SIZE]={0};
UINT16 *InputRegister[INPUTREGISTER_SIZE] = {0};




UINT16  TmpHoldReg;	
UINT16  Trip_Ctrl;
void HoldRegister_Init(void)
{
        // UINT32 i,n=0;
        // HoldRegister[n++]=&m_Rtc.DateTime.second;
        // HoldRegister[n++]=&m_Rtc.DateTime.minute;
        // HoldRegister[n++]=&m_Rtc.DateTime.hour;
        // HoldRegister[n++]=&m_Rtc.DateTime.day;
        // HoldRegister[n++]=&m_Rtc.DateTime.month;
        // HoldRegister[n++]=&m_Rtc.DateTime.year;  
        // HoldRegister[n++]=(UINT16*)&m_Rtc.RTC_Cal;
        // HoldRegister[n++]=&Trip_Ctrl;//8
        // HoldRegister[n++]=&DeviceState.HMI_Update;
        // HoldRegister[n++]=&DeviceState.HMI_Update1;
        // HoldRegister[n++]=&DeviceState.UPS_Trip;
        // for(i=0;i<MAX_IO_SIZE;i++)
        // HoldRegister[n++]=&DeviceState.Para.LineName[i];
        uint16_t data=1;
        for(int i=0;i<HOLDREGISTER_SIZE;i++)
            HoldRegister[i] = &data;

} 

void InputRegister_Init(void)
{
    uint16_t data=1;
    for(int i=0;i<INPUTREGISTER_SIZE;i++)
        InputRegister[i] = &data;
}

UINT8 HoldRegister_GetData(UINT16 iAddr,UINT8 *pData,UINT16 iLen)
{
        int i;
        UINT16 Data;
        for(i=0;i<iLen;i++)
            {
                    Data=*HoldRegister[iAddr];
                    *pData++=((Data>>8)&0x00ff);
                    *pData++=(Data&0x00ff);
                    iAddr++;
                } 
        return 2*iLen;
}
bool HoldRegister_SetEEP(UINT16 iAddr)
{
    // if((iAddr>=HOLDREG_SYS_DT)&&(iAddr<(HOLDREG_SYS_DT+HOLDREG_SYS_DT_SIZE)))
    //     {
    //         m_Rtc.W_Second=Time2000_mktime(&m_Rtc.DateTime);
    //         RTC_WriteRTCComBoard();
    //         return true;	
    //     }	
    // if(iAddr==HOLDREG_SYS_DT_CAL)
    //     {
    //         SetValue_SetRTC((UINT16*)&m_Rtc.RTC_Cal);
    //         RTC_WriteRTCCalComBoard();
    //         return true;
    //     }	
    return false;
    }	
			
void HoldRegister_SetWordRun(UINT16 iAddr)
{
    // if(HoldRegister_SetEEP(iAddr))
    //     return;
    // if(iAddr==HOLDREG_TRIP_CTRL)
    // {
    //     IoBoard_InsertCmdDoActive(Trip_Ctrl);
    //     return;
    // }	
}				
void HoldRegister_SetWord(UINT16 iAddr,UINT16 Data)
{
    // UINT16 Data;
    // Data=*pData++;
    // Data<<=8;
    // Data|=(*pData)&0xff;
    // pData++;
    // HoldRegister[iAddr]=&Data;

    //HoldRegister_SetWordRun(iAddr);			
}	
UINT8 HoldRegister_SetMulWord(UINT16 iAddr,UINT8 *pData,UINT16 iLenHR)
{
    UINT16 i,Data;
    if((iAddr+iLenHR)>HOLDREGISTER_SIZE)
                return 0;
    for(i=0;i<iLenHR;i++)
    {
        Data=*pData++;
        Data<<=8;
        Data|=(*pData)&0xff;
        pData++;
        *HoldRegister[iAddr]=Data;	
        iAddr++;
    }
    return 1;			 
}	 					 
UINT8 InputRegister_GetData(UINT16 iAddr,UINT8 *pData,UINT16 iLen)
{

        int i;
        UINT16 Data;
        for(i=0;i<iLen;i++)
        {
                printf("i = %d\r\n",i);
                Data=*InputRegister[iAddr];
                *pData++=((Data>>8)&0x00ff);
                *pData++=(Data&0x00ff);
                iAddr++;
        } 
        return 2*iLen;
 }						

		 
			 
