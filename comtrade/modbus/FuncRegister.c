#include "FuncRegister.h"
//#include "CanProtocolApp.h"
//#include "LoopCmd.h"
//#include "Msg.h"
//#include "SetValue.h"
//#include "ADC_Manage.h"
//#include "Version.h"
//#include "Statistics.h"
//#include "Com2Modbus_Msg.h"
//#include "MasterSlave.h"
//#include "Modbus_Slave.h"
//#include "SuddenFault.h"
//#include "admittance.h"
//#include"DataRec.h"
#include <string.h>
#define   FUNC_USERSETVALUE	    1
#define   FUNC_FACTORYSETVALUE  2  
#define   FUNC_DEVPARA          3
#define   FUNC_ADC_RATE         4
#define   FUNC_COM2             5
#define   FUNC_COM3             6
#define   FUNC_TRIPSET          7

#define   FUNC_ZK              12
#define   FUNC_UPSDAONA        13
#define   FUNC_FAULTDATA       14
#define   FUNC_SOE_DISP        15
#define   FUNC_DOE_DISP        16
#define   FUNC_SOE_DEL         17
#define   FUNC_DOE_DEL         18
#define   FUNC_VERSION          19
#define   FUNC_STATIS_DISP      21
#define   FUNC_STATIS_DEL       22
#define   FUNC_COM_TEST         23

#define   FUNC_GZDAONA          24
#define   FUNC_FAULTDATA_DEL    25
//#define   FUNC_UPSDAONA        13
//#define   FUNC_MASTER_TEST      23
//#define   FUNC_SLAVE_TEST       24
//#define   FUNC_COM2_TEST        25
//#define  DEVSTATE_CTMAXSIZE    44
UINT16 HoldReg_FuncZone[HOLDREG_FUNC_SIZE];
void  HoldRegister_Func(void)
      {
				 UINT8 Bytes;
			//    switch(HoldReg_FuncZone[HOLDREG_FUNC_ID])
			// 	    {
			// 		    case FUNC_USERSETVALUE: SetValue_ModbusGetUserSet(HoldReg_FuncZone+HOLDREG_FUNC_DATA);//HoldReg_FuncZone[HOLDREG_FUNC_KEY1]=1;
			// 				                        break;
							
			// 				case FUNC_FACTORYSETVALUE:SetValue_ModbusGetFactorySet(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 				                        break;
							
			// 				case FUNC_DEVPARA:      Bytes=46*sizeof(UINT16);
			// 					                      HoldReg_FuncZone[HOLDREG_FUNC_DATA]=1;
			// 				                        DeviceState_ModbusGet(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,0);
			// 				                        LoopCmd_Can1SetInsertCmd(0x02,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_FUCREG_SYS_DP,&Bytes,1,40);
			// 				                        break;
							
			// 				  FUNC_ADC_RATE:     ADC_ModbusGetRate(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1);// SetValue_ModbusGetCap(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 				                        HoldReg_FuncZone[HOLDREG_FUNC_DATA]=1;
			// 				                        Bytes=16*sizeof(float);
			// 				                        LoopCmd_Can1SetInsertCmd(0x02,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_FUCREG_ADC_DP,&Bytes,1,30);
			// 				                        break;
							
			// 				case FUNC_TRIPSET:      HoldReg_FuncZone[HOLDREG_FUNC_DATA]=1;
			// 				                        SetValue_ModbusGetTripSet(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,0);
			// 				                        break;
							
			// 				case FUNC_COM2:         Bytes=8;
			// 					                      LoopCmd_Can1SetInsertCmd(0x02,DEV_COM_CAN_ID,DEV_COM2_FUNC_DP,&Bytes,1,10);
			// 				                        break;
							
			// 				case FUNC_COM3:         Bytes=8;
			// 					                      LoopCmd_Can1SetInsertCmd(0x02,DEV_COM_CAN_ID,DEV_COM3_FUNC_DP,&Bytes,1,10);
			// 				                        break;
							
			// 				case FUNC_SOE_DISP:     Msg_DisplaySoeFirst(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 				                        break;
							
			// 				case FUNC_DOE_DISP:     Msg_DisplayDoeIndexFirst(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 				                        break;
									
			// 				case FUNC_SOE_DEL:      Msg_DelSoe();
			// 				                        HoldReg_FuncZone[HOLDREG_FUNC_ID]=0;
			// 				                        break;
								
			// 				case FUNC_DOE_DEL:      Msg_DelDoe();
			// 				                        HoldReg_FuncZone[HOLDREG_FUNC_ID]=0;
			// 				                        break;
																			
			// 				case FUNC_FAULTDATA_DEL:RecFile_DelData();
			// 				                        HoldReg_FuncZone[HOLDREG_FUNC_ID]=0;
			// 				                        break;
																			
			// 				case FUNC_VERSION:      Version_Get();
			// 				                        HoldReg_FuncZone[HOLDREG_FUNC_ID]=0;
			// 				                        break;
																			
			// 			  case FUNC_STATIS_DISP: Statistics_WriteEEProm();
			// 					                     Statistics_ModbusGetSet(HoldReg_FuncZone);
			// 				                       HoldReg_FuncZone[HOLDREG_FUNC_ID]=0;
			// 															 break;
																		 
			// 			 case FUNC_STATIS_DEL:   Statistics_ClearEEProm();
            //                          HoldReg_FuncZone[HOLDREG_FUNC_ID]=0;
			// 															 break;
																		
			// 			 case FUNC_FAULTDATA:    //SuddenFault_GetData(&HoldReg_FuncZone[21]);
			// 				                       RecFile_DisplayIndexFirst(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 				                       break;
            //  case FUNC_COM_TEST:  
			// 															break;
             
			// 			 case FUNC_UPSDAONA:     Admittance_GetUPSZK(&HoldReg_FuncZone[20]);
            //                         break;
						 
			// 			 case FUNC_GZDAONA:     Admittance_GetGZZK(&HoldReg_FuncZone[20]);
            //                         break;

            //  case FUNC_ZK:          Admittance_Clear();
            //                         break;						 
            // }							
			}	
			
void HoldRegister_FuncKey1(void)   
     {
			//  switch(HoldReg_FuncZone[HOLDREG_FUNC_ID])
			//    {
			// 		 case  FUNC_USERSETVALUE:SetValue_SetUserValue(HoldReg_FuncZone+HOLDREG_FUNC_DATA,true);//HoldReg_FuncZone[HOLDREG_FUNC_KEY1]=1;
			// 		                         for(int i=0;i<DeviceState.Para.IO_BOARD_NUM;i++)
			// 		                            LoopCmd_Can1SetInsertCmd(0x01,DEV_CAN_ID[i],DEV_CAN_FUCREG_USERSET_DP,(UINT8*)&HoldReg_FuncZone[HOLDREG_FUNC_DATA+2],sizeof(float)*3,12);
			// 				                     break;
						
			// 	  case FUNC_FACTORYSETVALUE:SetValue_SetFactoryValue(HoldReg_FuncZone+HOLDREG_FUNC_DATA,true);
			// 		                          for(int i=0;i<DeviceState.Para.IO_BOARD_NUM;i++)
			// 		                            LoopCmd_Can1SetInsertCmd(0x01,DEV_CAN_ID[i],DEV_CAN_FUCREG_FACTORYSET_DP,(UINT8*)&HoldReg_FuncZone[42],sizeof(float)*5,20);
            //                         break;
					 
			// 	   case  FUNC_DEVPARA:      DeviceState_ModbusSetValue(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1);
			// 		                          memcpy(&HoldReg_FuncZone[90],&HoldReg_FuncZone[40],12);
			// 				                      LoopCmd_Can1SetInsertCmd(0x01,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_FUCREG_SYS_DP,(UINT8*)&HoldReg_FuncZone[50],sizeof(UINT16)*46,40);
			// 		                          break;
					
			// 		 case FUNC_ADC_RATE:     ADC_SetChanelRate1(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1);//SetValue_SetCap(HoldReg_FuncZone+HOLDREG_FUNC_DATA,true);
			// 		                         LoopCmd_Can1SetInsertCmd(0x01,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_FUCREG_ADC_DP,(UINT8*)&HoldReg_FuncZone[30],sizeof(float)*16,40);
			// 				                     break;
					 
			// 		 case FUNC_TRIPSET:      SetValue_ModbusSetTripSet(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1);
			// 			                       break;
					 
			// 		 case FUNC_COM2:         LoopCmd_Can1SetInsertCmd(0x01,DEV_COM_CAN_ID,DEV_COM2_FUNC_DP,(UINT8*)&HoldReg_FuncZone[HOLDREG_FUNC_DATA],sizeof(UINT16)*4,10);
			// 				                     break;
					 
			// 		 case FUNC_COM3:         LoopCmd_Can1SetInsertCmd(0x01,DEV_COM_CAN_ID,DEV_COM3_FUNC_DP,(UINT8*)&HoldReg_FuncZone[HOLDREG_FUNC_DATA],sizeof(UINT16)*4,10);
			// 				                     break;
					 
																	 
			// 	   case FUNC_SOE_DISP:    Msg_DisplaySoe(1,HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 		                        HoldReg_FuncZone[HOLDREG_FUNC_KEY1]=0;
			// 		                        break; 
					 
			// 		 case FUNC_DOE_DISP:    Msg_DisplayDoeIndex(1,HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 		                        HoldReg_FuncZone[HOLDREG_FUNC_KEY1]=0;
			// 		                        break;
																	
			// 		 case FUNC_FAULTDATA:    //SuddenFault_GetData(&HoldReg_FuncZone[21]);
			// 				                    RecFile_DisplayIndex(1,HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 		                        HoldReg_FuncZone[HOLDREG_FUNC_KEY1]=0;
			// 				                    break;
			// 	 } 
		 } 
		 
void HoldRegister_FuncKey2(void)
     {
			 UINT8  Bytes;
		// 	 switch(HoldReg_FuncZone[HOLDREG_FUNC_ID])
		// 	   {
					 
		// 			 case  FUNC_DEVPARA:    memset(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,0x0000,sizeof(UINT16)*100);
		// 			                        Bytes=46*sizeof(UINT16);
		// 						                  DeviceState_ModbusGet(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1);
		// 					                    LoopCmd_Can1SetInsertCmd(0x02,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_FUCREG_SYS_DP,&Bytes,1,40);
		// 				                      break;
					 
		// 			 case FUNC_TRIPSET:     memset(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,0x0000,sizeof(UINT16)*100);
		// 			                        SetValue_ModbusGetTripSet(HoldReg_FuncZone+HOLDREG_FUNC_DATA+1,HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1);
		// 			                        break;
  					                      
		// 			 case  FUNC_SOE_DISP:   Msg_DisplaySoe(2,HoldReg_FuncZone+HOLDREG_FUNC_DATA);
		// 			                        HoldReg_FuncZone[HOLDREG_FUNC_KEY2]=0;
		// 			                        break;
					 
		// 			 case  FUNC_DOE_DISP:   Msg_DisplayDoeIndex(2,HoldReg_FuncZone+HOLDREG_FUNC_DATA);
		// 			                        HoldReg_FuncZone[HOLDREG_FUNC_KEY2]=0;
		// 			                        break;
					 
		// 			 case FUNC_FAULTDATA:   RecFile_DisplayIndex(2,HoldReg_FuncZone+HOLDREG_FUNC_DATA);
		// 			                        HoldReg_FuncZone[HOLDREG_FUNC_KEY2]=0;
		// 					                    break;
					 
		// 			 case FUNC_COM_TEST:    Com2Msg_Test();
		// 			                        break;
					 
		// 			 //case FUNC_FAULTDATA:    SuddenFault_GetData(&HoldReg_FuncZone[21]);
		// 			//		                     break;
					
        //    case FUNC_ADC_RATE:		memset(HoldReg_FuncZone+30,0x0000,sizeof(UINT16)*100);	
        //                           Bytes=16*sizeof(float);
		// 					                    LoopCmd_Can1SetInsertCmd(0x02,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_FUCREG_ADC_DP,&Bytes,1,30);		
        //                           break;																	
		// 		 } 
		 } 
		 
void HoldRegister_FuncKey3(void)
     {
			 UINT8  Bytes;
		// 	 switch(HoldReg_FuncZone[HOLDREG_FUNC_ID])
		// 	   { 
		// 		   case  FUNC_SOE_DISP:   Msg_DisplaySoeFirst(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
		// 			                        HoldReg_FuncZone[HOLDREG_FUNC_KEY3]=0;
		// 			                        break;  
					 
		// 			 case  FUNC_DOE_DISP:   Msg_DisplayDoeIndexFirst(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
		// 			                        HoldReg_FuncZone[HOLDREG_FUNC_KEY3]=0;
		// 			                        break; 
					 
        //    case FUNC_FAULTDATA:   RecFile_DisplayIndexFirst(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
		// 			                        HoldReg_FuncZone[HOLDREG_FUNC_KEY3]=0;
		// 					                    break;
					 
        //   case FUNC_COM3:         MasetrSlave_MasterTest();
        //                           break;	

        //  case FUNC_ADC_RATE:      Bytes=sizeof(float)*16;
		// 				                      LoopCmd_Can1SetInsertCmd(0x02,DEV_CAN_ID[HoldReg_FuncZone[HOLDREG_FUNC_DATA]-1],DEV_CAN_AI_DP,&Bytes,1,40);
		// 			                        break;					 
		// 		 } 
		 } 
		 
void HoldRegister_FuncKey4(void)
     {
			//  switch(HoldReg_FuncZone[HOLDREG_FUNC_ID])
			//    { 
			// 		 case  FUNC_SOE_DISP:   Msg_DisplaySoeLast(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 		                        HoldReg_FuncZone[HOLDREG_FUNC_KEY4]=0;
			// 		                        break;
					 
			// 		 case  FUNC_DOE_DISP:   Msg_DisplayDoeIndexLast(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 		                        HoldReg_FuncZone[HOLDREG_FUNC_KEY4]=0;
			// 		                        break;
					 
			// 		case FUNC_FAULTDATA:   RecFile_DisplayIndexLast(HoldReg_FuncZone+HOLDREG_FUNC_DATA);
			// 		                       HoldReg_FuncZone[HOLDREG_FUNC_KEY4]=0;
			// 				                   break;
					 
			// 		 case FUNC_COM3:        MasetrSlave_SlaveTest();
            //                       break;
			// 	 } 
		 } 
		 
void HoldRegister_FuncKey5(void)
      {
		// 	 UINT32 Index;
		// 	 switch(HoldReg_FuncZone[HOLDREG_FUNC_ID])
		// 	  {
		// 		 case  FUNC_DOE_DISP: memset(&HoldReg_FuncZone[159],0x0000,60);
		// 			                    Index=Msg_GetDoeIndex(&HoldReg_FuncZone[9],HoldReg_FuncZone[HOLDREG_FUNC_KEY5]);
		// 			                    if(Index<0xffffffff)
        //                          Msg_ReadDoeFromEEP(Index,&HoldReg_FuncZone[159]);
		// 													HoldReg_FuncZone[HOLDREG_FUNC_KEY5]=0;
        //                       break;

        //  case FUNC_FAULTDATA: memset(&HoldReg_FuncZone[159],0x0000,200);
		// 			                    Index=RecFile_GetDoeIndex(&HoldReg_FuncZone[9],HoldReg_FuncZone[HOLDREG_FUNC_KEY5]);
		// 			                    if(Index<0xffffffff)
        //                          RecFile_Display(Index,&HoldReg_FuncZone[159]);
		// 													HoldReg_FuncZone[HOLDREG_FUNC_KEY5]=0;
        //                       break;															
		// 	  } 
			}	
UINT8 HoldRegister_GetFuncData(UINT16 iAddr,UINT8 *pData,UINT16 iLen)
      {
				int i;
				UINT16 Data;
				for(i=0;i<iLen;i++)
				   {
						 Data=HoldReg_FuncZone[iAddr];
						 *pData++=((Data>>8)&0x00ff);
						 *pData++=(Data&0x00ff);
						 iAddr++;
					 }
       return 2*iLen;					 
			}	

void HoldRegister_SetFuncWordRun(UINT16 iAddr)
      {
    //  if(iAddr==HOLDREG_FUNC_ID)
	// 	   {
	// 			 memset(&HoldReg_FuncZone[HOLDREG_FUNC_ID+1],0,2*HOLDREG_FUNC_SIZE-10);
	// 			 HoldRegister_Func();
	// 			 return;
	// 		 }				 
	// 		if(iAddr==HOLDREG_FUNC_KEY1)
	// 		  {	
    //      HoldRegister_FuncKey1();
	// 			return;
	// 		  } 
	// 		if(iAddr==HOLDREG_FUNC_KEY2)
	// 		{
	// 			HoldRegister_FuncKey2();
	// 		}	
	// 		if(iAddr==HOLDREG_FUNC_KEY3)
	// 		  {	
    //      HoldRegister_FuncKey3();
	// 			return;
	// 		  } 
	// 		if(iAddr==HOLDREG_FUNC_KEY4)
	// 		{
	// 			HoldRegister_FuncKey4();
	// 		}	
	// 		if(iAddr==HOLDREG_FUNC_KEY5)
	// 		{
	// 			HoldRegister_FuncKey5();
	// 		}	
      }				
void HoldRegister_SetFuncWord(UINT16 iAddr,UINT8 *pData)
     {
			UINT16 Data;
			Data=*pData++;
			Data<<=8;
			Data|=(*pData)&0xff;
			pData++;
			HoldReg_FuncZone[iAddr]=Data;
			//HoldRegister_SetFuncWordRun(iAddr);			
		 }	

UINT8 HoldRegister_SetMulFuncWord(UINT16 iAddr,UINT8 *pData,UINT16 iLenHR)	
      {
			UINT16 i,Data;
			for(i=0;i<iLenHR;i++)
			 {
				Data=*pData++;
			  Data<<=8;
			  Data|=(*pData)&0xff;
			  pData++;
			  HoldReg_FuncZone[iAddr]=Data;	
				iAddr++;
			 }
      return 1;			 
      }					 		 
		 