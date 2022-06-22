#ifndef CRC16_H_
#define CRC16_H_

#include"Typedef.h"
UINT16 CRC16_Create(unsigned char *puchMsg, UINT16 usDataLen);
UINT16 CRC16_CreateInit(unsigned char *puchMsg, UINT16 usDataLen,UINT16 iCRCInit);
bool CRC16_Check(unsigned char *puchMsg, UINT16 usDataLen);
#endif
