#include "1.h"
#include <string.h>



void myprintf(u8 *data,int len)
{
    printf("str = %s\r\n",data);
    memset(data,0,6);
    printf("len = %d\r\n",len);

}










