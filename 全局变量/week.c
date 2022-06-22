//由年月日得到星期
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
uint8_t path[100];
int main()
{
myprintf("1.txt");
myprintf("1111.txt");
myprintf("1.txt");

}


void myprintf(uint8_t *buf)
{
    strcpy(path, buf);
    printf("path: %s\r\n",path);

}









