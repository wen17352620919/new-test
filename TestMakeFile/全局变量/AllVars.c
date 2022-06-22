#include "AllVars.h"
/*
    测试目的：全局变量重复赋值
*/
uint8_t path[100];

int AllVars_Test()
{
    AllVars_Print("1.txt");
    AllVars_Print("1111.txt");
    AllVars_Print("1.txt");
/*
结果
path: 1.txt
path: 1111.txt
path: 1.txt
*/
}


void AllVars_Print(uint8_t *buf)
{
    strcpy(path, buf);
    printf("path: %s\r\n",path);

}









