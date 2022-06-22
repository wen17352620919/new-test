
#include"modbus_slave.h"
#include"BitState.h"
// #include"Register.h"
#include "my_register.h"
// #include"FuncRegister.h"
#include "serial_485.h"
#include"CRC16.h"
extern int flag;
unsigned char Modbus_Buffer[100];


/*
从机响应
读
设备ID  命令符  数据长度  数据内容   CRC   7size
从机回应的地址和功能码和主机请求命令相同，数据长度和主机的数据长度相同，数据 内容字节数和数据长度有关，字节数 n=数据长度 L*2
写
设备ID  命令符  地址  数据内容   CRC   8size
写多个
设备ID  命令符  地址  写的个数   CRC   8size
1               1               2           2               2
*/

void* modbus_read_screen(void* fd)//线程持续读
{
    int times =0 ;
    int fd_modbus = (int)fd;
    char read_buf[100];
    // change_mod_rs485(fd_modbus,0);
    while(1)
    {
        memset(Modbus_Buffer,0,sizeof(Modbus_Buffer));
         int nread = read(fd_modbus ,Modbus_Buffer ,100);
        if (nread > 0)
        {
            int crc_check = CRC16_Check(Modbus_Buffer,nread);
            printf("read CRC16_Check= %d\r\n",crc_check);
            printf("len = %d\r\n ", nread);
            // //printf("read_buf = %s\r\n ", read_buf);//字符串打印
            // for(int i = 0; i < nread; i++)
            // {
            //     printf("Modbus_Buffer = %02x \t", Modbus_Buffer[i]);//ascall码
            //     //printf("ascal = %02x \t", read_buf[i]);//ascall码
            //     // printf("read buf[%d]   = %d\t" ,i, buf16[i]);
            //     // printf("read buf[%d] = %x\t" ,i, buf16[i]);
            //     printf("\r\n");
            // }
            times++;
            Coil_SetState(Modbus_Buffer[5],1);
            int n = modbus_screen_deal_data(Modbus_Buffer);
            //--------------------------------------------------响应
                int write_size = write(fd_modbus,Modbus_Buffer,n);
                printf("write_size = %d\r\n",write_size);
                for(int i=0;i<n;i++)
                {
                    printf("crc Modbus_Buffer[%d] = %x\r\n",i,Modbus_Buffer[i]);
                }
                printf("----------------------\r\n");   
            //-------------------------------------------------------
            // if(times ==10)
            // {
            //     flag =1;
            //     break;//结束循环，跳出
            // }
            
    }
    }
    close(fd_modbus);
    
}				

/*
函数：将modbus信号处理后返回要发的数据


01 (0x01)        读线圈，一次最多读8个
02 (0x02)        读离散量输入，一次最多读8个
03 (0x03)        读保持寄存器
04(0x04)         读输入寄存器
05 (0x05)        写单个线圈 
06 (0x06)        写单个寄存器

16 (0x10)        写多个寄存器

离散输入和输入寄存器只能读，不能写
读时的数据位为要读的个数
*/
uint16_t modbus_screen_deal_data(unsigned char *Modbus_Buffer)
{
    int len = 10;//要读取的长度
    uint16_t n,crc;
    T_MODBUS_HEAD *pModbusHead=(T_MODBUS_HEAD *)Modbus_Buffer;
    uint8_t data_readmodbus[10];//存储读取到的数据
    uint8_t data_writemodbus[10];//
    switch(pModbusHead->FUNC)
    {

        case MODBUS_FUNC_1:
                        n = MODBUS_Fuc1Response(Modbus_Buffer);
                        break;
        case MODBUS_FUNC_2:
                        n = MODBUS_Fuc2Response(Modbus_Buffer);
                        break;
        case MODBUS_FUNC_3:
                         n = MODBUS_Fuc3Response(Modbus_Buffer);
                        break;
        case MODBUS_FUNC_4:
                        n = MODBUS_Fuc4Response(Modbus_Buffer);
                        break;
        case MODBUS_FUNC_5:
                        n = MODBUS_Fuc5Response(Modbus_Buffer);
                        break;
        case MODBUS_FUNC_6:
                        n = MODBUS_Fuc6Response(Modbus_Buffer);
                        break;
        
        case MODBUS_FUNC_16:
                        n=MODBUS_Fuc16Response(Modbus_Buffer);
                        break;
        default:
                        n=MODBUS_RespantERR(Modbus_Buffer,0x01);
                        break;
    }

    crc=CRC16_Create(Modbus_Buffer,n);
	Modbus_Buffer[n++]=(unsigned char)(crc>>8);
	Modbus_Buffer[n++]=(unsigned char)(crc&0xff);
     
	return n;  
}

void char_uint16(char buf[],int len,uint16_t  data[])
{
	for(int i = 0; i < len; i++)
	{
		data[i] = (uint16_t)buf[i];
	}
}

//================================================================
UINT16 MODBUS_RespantERR(unsigned char *Modbus_Buffer,unsigned char cERR_Type)
{
	T_MODBUS_ERR *pModbusErr=(T_MODBUS_ERR *)Modbus_Buffer;
	pModbusErr->FUNC|=0x80;
	pModbusErr->ERR=cERR_Type;
	return 3;
}    


UINT16 MODBUS_Fuc1Response(unsigned char *Modbus_Buffer)
{
    UINT16 iPoint,iAddr;
    T_MODBUS_READ_RESPONSE *pModbusReadResponse;
    T_MODBUS_READ_CMD *pModbusReadCMD=(T_MODBUS_READ_CMD*)Modbus_Buffer;
    if(pModbusReadCMD->SLAVE_ADDR==0)
        return 0;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
    iPoint=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
        if((iAddr<MODBUS_COIL_ADR)||((iAddr+iPoint)>(MODBUS_COIL_ADR+MODBUS_COIL_SIZE)))
        return MODBUS_RespantERR(Modbus_Buffer,0x02);
    pModbusReadResponse=(T_MODBUS_READ_RESPONSE*)Modbus_Buffer;
    iAddr=iAddr-MODBUS_COIL_ADR;
    pModbusReadResponse->BYTECOUNT=Coil_GetStateByte(iAddr,pModbusReadResponse->DATA,iPoint);
    return 3+pModbusReadResponse->BYTECOUNT;
}


UINT16 MODBUS_Fuc2Response(unsigned char *Modbus_Buffer)
{
    UINT16 iPoint,iAddr;
    T_MODBUS_READ_RESPONSE *pModbusReadResponse;
    T_MODBUS_READ_CMD *pModbusReadCMD=(T_MODBUS_READ_CMD*)Modbus_Buffer;
    if(pModbusReadCMD->SLAVE_ADDR==0)
        return 0;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
    iPoint=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
        if((iAddr<MODBUS_INPUT_ADR)||((iAddr+iPoint)>(MODBUS_INPUT_ADR+MODBUS_INPUT_SIZE)))
        return MODBUS_RespantERR(Modbus_Buffer,0x02);
    //	 if(iAddr>=0x10)
    //		  return 0;
    pModbusReadResponse=(T_MODBUS_READ_RESPONSE*)Modbus_Buffer;
    iAddr=iAddr-MODBUS_INPUT_ADR;
    pModbusReadResponse->BYTECOUNT=InputBit_GetStateByte(iAddr,pModbusReadResponse->DATA,iPoint);
    return 3+pModbusReadResponse->BYTECOUNT;
}

UINT16 MODBUS_Fuc3Response(unsigned char *Modbus_Buffer)
{
    UINT16 iPoint,iAddr;
    T_MODBUS_READ_RESPONSE *pModbusReadResponse;
    T_MODBUS_READ_CMD *pModbusReadCMD=(T_MODBUS_READ_CMD*)Modbus_Buffer;
    if(pModbusReadCMD->SLAVE_ADDR==0)
        return 0;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
    iPoint=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
        pModbusReadResponse=(T_MODBUS_READ_RESPONSE*)Modbus_Buffer;
       
    if((iAddr<MODBUS_HR_ADR)||((iAddr+iPoint)>(MODBUS_HR_ADR+MODBUS_HR_SIZE)))
    return MODBUS_RespantERR(Modbus_Buffer,0x02);
    iAddr-=MODBUS_HR_ADR;
    pModbusReadResponse->BYTECOUNT=my_hold_register_getdata(iAddr,pModbusReadResponse->DATA,iPoint);
    return pModbusReadResponse->BYTECOUNT+3;
}

UINT16 MODBUS_Fuc4Response(unsigned char *Modbus_Buffer)
{
    UINT16 iPoint,iAddr;
    T_MODBUS_READ_RESPONSE *pModbusReadResponse;
    T_MODBUS_READ_CMD *pModbusReadCMD=(T_MODBUS_READ_CMD*)Modbus_Buffer;
    if(pModbusReadCMD->SLAVE_ADDR==0)
        return 0;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
    iPoint=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
    if((iAddr<MODBUS_IR_ADR)||((iAddr+iPoint)>(MODBUS_IR_ADR+MODBUS_IR_SIZE)))
        return MODBUS_RespantERR(Modbus_Buffer,0x02);
    pModbusReadResponse=(T_MODBUS_READ_RESPONSE*)Modbus_Buffer;
    iAddr-=MODBUS_IR_ADR;
    // pModbusReadResponse->BYTECOUNT=InputRegister_GetData(iAddr,pModbusReadResponse->DATA,iPoint);
    pModbusReadResponse->BYTECOUNT=my_input_register_getdata(iAddr,pModbusReadResponse->DATA,iPoint);
    
        //ModbusCAN_ReadInputReg(iAddr,iPoint);
    return pModbusReadResponse->BYTECOUNT+3;
}


UINT16  MODBUS_Fuc5Response(unsigned char *Modbus_Buffer)
{
    UINT16 iData,iAddr;
    T_MODBUS_READ_CMD *pModbusReadCMD=(T_MODBUS_READ_CMD*)Modbus_Buffer;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
    iData=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
    if((iAddr<MODBUS_COIL_ADR||(iAddr<MODBUS_COIL_ADR)||((iAddr)>(MODBUS_COIL_ADR+MODBUS_COIL_SIZE))))
        return MODBUS_RespantERR(Modbus_Buffer,0x02);
        if((iData!=0xff00)&&(iData!=0x0000))
    return MODBUS_RespantERR(Modbus_Buffer,0x03);
        iAddr-=MODBUS_COIL_ADR;
        Coil_SetState(iAddr,iData);
    return 6;
}

UINT16  MODBUS_Fuc6Response(unsigned char *Modbus_Buffer)
{
    UINT16 iAddr,iData;
    T_MODBUS_READ_CMD *pModbusReadCMD=(T_MODBUS_READ_CMD*)Modbus_Buffer;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
     iData=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
    if((iAddr<MODBUS_HR_ADR||(iAddr<MODBUS_HR_ADR)||((iAddr)>(MODBUS_HR_ADR+MODBUS_HR_SIZE))))
        return MODBUS_RespantERR(Modbus_Buffer,0x02);
    my_hold_register_setword(iAddr,iData);
    // if(iAddr<HMI_MODBUS_ADDR)
    // {
    //     if((iAddr<MODBUS_HR_ADR)||(iAddr>=(MODBUS_HR_ADR+MODBUS_HR_SIZE)))
    //         return MODBUS_RespantERR(Modbus_Buffer,0x02);;
    //     iAddr-=MODBUS_HR_ADR;
    //     HoldRegister_SetWord(iAddr,&pModbusReadCMD->POINT_H);
    // }
    // if(iAddr<MODBUS_HR_FUNC_ADR)
    // {
    //      if(iAddr>=(HMI_MODBUS_ADDR+HMI_MODBUS_SIZE))
    //         return MODBUS_RespantERR(Modbus_Buffer,0x02);
    //      iAddr-=HMI_MODBUS_ADDR;
    //     HMIHoldRegister_SetWord(iAddr,&pModbusReadCMD->POINT_H);
    // }						
    // else
    // {
    //     if(iAddr>=(MODBUS_HR_FUNC_ADR+MODBUS_HR_FUNC_SIZE))
    //         return MODBUS_RespantERR(Modbus_Buffer,0x02);;
    //     iAddr-=MODBUS_HR_FUNC_ADR;
    //     HoldRegister_SetFuncWord(iAddr,&pModbusReadCMD->POINT_H);
    // }	
    return 6;
}

UINT16  MODBUS_Fuc16Response(unsigned char *Modbus_Buffer)
{
    UINT16 iAddr,iPoint;
    T_MODBUS_WRITEMUL_CMD *pModbusReadCMD=(T_MODBUS_WRITEMUL_CMD*)Modbus_Buffer;
    iAddr=BYTE_UNION(pModbusReadCMD->ADDR_H,pModbusReadCMD->ADDR_L);
    iPoint=BYTE_UNION(pModbusReadCMD->POINT_H,pModbusReadCMD->POINT_L);
    if((iAddr<MODBUS_HR_ADR||(iAddr<MODBUS_HR_ADR)||((iAddr)>(MODBUS_HR_ADR+MODBUS_HR_SIZE))))
        return MODBUS_RespantERR(Modbus_Buffer,0x02);
    my_hold_register_setMulWord(iAddr,pModbusReadCMD->DATA,iPoint);
    // if(iAddr<HMI_MODBUS_ADDR)
    // {
    //     if((iAddr<MODBUS_HR_ADR)||((iAddr+iPoint)>(MODBUS_HR_ADR+MODBUS_HR_SIZE)))
    // return MODBUS_RespantERR(Modbus_Buffer,0x02);
    //     iAddr-=MODBUS_HR_ADR;
    // HoldRegister_SetMulWord(iAddr,pModbusReadCMD->DATA,iPoint);
    //     return 6;
    // }	
    // if(iAddr<MODBUS_HR_FUNC_ADR)
    // {
    //     if((iAddr+iPoint)>(HMI_MODBUS_ADDR+HMI_MODBUS_SIZE))
    // return MODBUS_RespantERR(Modbus_Buffer,0x02);
    // iAddr-=HMI_MODBUS_ADDR;
    //     HMIHoldRegister_SetMulWord(iAddr,pModbusReadCMD->DATA,iPoint);
    //     return 6;
    // }	
    // else
    // {
    //     if((iAddr+iPoint)>(MODBUS_HR_FUNC_ADR+MODBUS_HR_FUNC_SIZE))
    // return MODBUS_RespantERR(Modbus_Buffer,0x02);;
    //     iAddr-=MODBUS_HR_FUNC_ADR;
    // HoldRegister_SetMulFuncWord(iAddr,pModbusReadCMD->DATA,iPoint);
    //     return 6;
    // }	
    return 6;
}                

