#ifndef MODBUSDEF_H_
#define MODBUSDEF_H_
#include "BitState.h"
#include "Register.h"
#define MODBUS_COIL_ADR          0
#define MODBUS_COIL_SIZE         COIL_SIZE
#define MODBUS_INPUT_ADR         0
#define MODBUS_INPUT_SIZE        INPUTBIT_SIZE

#define MODBUS_HR_ADR            0							 
#define MODBUS_HR_SIZE           HOLDREGISTER_SIZE  //控制寄存器
#define MODBUS_IR_ADR            0							 
#define MODBUS_IR_SIZE           (INPUTREGISTER_SIZE+10) //输入寄存器

#define MODBUS_FRAME_MS        (UINT32)(30*MS)	
#endif