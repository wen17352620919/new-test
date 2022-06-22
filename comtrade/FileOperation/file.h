#ifndef __FILE_H
#define __FILE_H

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
#include "../comtrade/my_comtrade.h"

#define DIR_PATH "/mnt/hgfs/git/"

typedef struct 
{
    FILE* HDR;//头文件标志符
    FILE* CFG;//配置文件标识符
    FILE* DAT;//数据文件标志符
    FILE* INF;//信息文件标志符

    char HDR_name[100];
    char CFG_name[100];
    char DAT_name[100];
    char INF_name[100];
}comtrade;


void  gettime(char *_time);

int dir_create(char *dir,char *path);
void create_comtrade_HDR(char* filename,char *dir);
void create_comtrade_CFG(char* filename,char *dir);
void create_comtrade_DAT(char* filename,char *dir);
void create_comtrade_INF(char* filename,char *dir);

//void read_file(int fd,cmtr_dat_smpdot *mydata);

extern comtrade a;

#endif