#ifndef  __M4TOA7_H
#define __M4TOA7_H
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include<stdint.h>
#include <iconv.h>
#include <ctype.h>
#include <pthread.h>

typedef struct
{
	uint16_t flag;
	uint16_t len;
	uint16_t U[8][1200];
	uint16_t I[36][1200];
}type_M4_data;

void* read_m4_a7(void* args);
void* data_deal(void* args);
void* write_a7_m4(void*args);
#endif