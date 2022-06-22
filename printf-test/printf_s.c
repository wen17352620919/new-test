#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define u8 uint8_t


typedef struct {
	u8	fsize;			/* File size */
	u8	fdate;			/* Last modified date */
	u8	ftime;			/* Last modified time */
	u8	fattrib;		/* Attribute */
	u8	fname[13];		/* Short file name (8.3 format) */
} FILINFO;
void test(u8 *data,int len);
u8 test_2ptr(FILINFO *fifo);
int main()
{
    // uint8_t buf[1024] = "hello word";
    // uint8_t buf2[1024] = {11,12,13,14,1,16,17,18,230};
    // u8 buff[1024]={0};
    //-------------------
    // u8 a=1;
    // sprintf(buff,"%d",a);
    // printf(&buff);
    //---------------------
    // printf(&buf);
    //----------------------
    // test(buf2,9);
    //----------------------
     FILINFO fifo[100];
     FILINFO a;
     int num = test_2ptr(&a);
       printf("%s\r\n",a.fname);
     printf("%s\r\n",(&a+1)->fname);
    // int num = test_2ptr(fifo);
    // for(int i=0; i<num; i++)
    //     printf("%s\r\n",fifo[i].fname);
    return 0;
}



void test(u8 *data,int len)
{
    u8 buff[1024];
    for(int i=0;i<len;i++)
    {
            sprintf(buff,"%d",data[i]);
            printf(&buff);

            printf("\r\n");
    }
    // printf(&buff);

}
//指针测试
u8 test_2ptr(FILINFO *fifo)
{
    strcat(fifo[0].fname,"1.txt");
     strcat(fifo[1].fname,"2.txt");
     return 2;
}












