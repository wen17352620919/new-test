//由年月日得到星期
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "1.h"
uint8_t path[100]="1.txt";
int len=1;

static u8 paths[100]="2.txt";
static int lens=2; 
int main()
{
//     uint8_t path[100]="1.txt";
// int len=1;

// static u8 paths[100]="2.txt";
// static int lens=2; 
    myprintf(path,len);
    myprintf(paths,lens);
    printf("path= = %s\r\n",path);
    printf("path= = %s\r\n",paths);
}












