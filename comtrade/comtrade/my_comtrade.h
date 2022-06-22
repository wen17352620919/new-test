#ifndef  __MY_COMTRADE_H
#define __MY_COMTRADE_H

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


 /*
* 关于comtrade文件配置文件的宏定义。
 * 在此采用预定义最大个数方法，避免动态内存管理的问题。
 *
* 相关字符串最大字符个数
* 模拟量端口最大个数
* 数字量量端口最大个数
* 采样率最大个数
*/

#define  CMTR_STRING_MAX_LENGTH         60
#define  CMTR_ANALOG_MAX_COUNT          1200
 #define  CMTR_DIGIT_MAX_COUNT               1200
#define  CMTR_SMPRATE_MAX_COUNT         8

 /*

*cmtr_cfg_analog - 配置文件模拟量信息
* @index: 模拟量端口序号（只是编号，解析时不做序号用）；
 * @name: 模拟量端口名称；
 * @phase: 模拟量端口相标识,值如（A、B、C、N等）；
 * @element：标识（还未知，待补充），一般为空；
* @unit: 模拟量端口数值的单位，该单位常用来区分该端口是电流还是电流，值如：kV、V、A、mA等；
 * @factor_a: 系数a，一般为整数，可以是浮点数；
* @factor_b: 系数b，一般为整数，可以是浮点数；
* @offset_time: 时间偏移,指第一个点的时间偏移量，一般为0；
* @smp_min: 通道的最小采用值，一般为整数,
 * @smp_max: 通道的最大采用值，一般为整数,
 *
* 通道采样的实际值计算方法：实际值 = factor_a * smp_value + factor_b；所以根据该公式，可以计算
* 通道的最小值为：factor_a * smp_min + factor_b，最大值为：factor_a * smp_max + factor_b。
 ** 注：本来smp_min、smp_max为两个字节的一个数据（即最大为65535），但不同厂家会生成很大的四字节数据，
*   所以采用s32类型；factor_a、factor_b用double类型，用float可能会丢精度；为了提供解析程序的适
*    应性，以适应国内各种变态的有标准不遵循的厂家的仪器生成的cmtr文件。
*/

typedef struct  
{
    int index;//模拟量端口序号
    uint8_t name[CMTR_STRING_MAX_LENGTH];//模拟量端口名称；
    uint8_t phase[CMTR_STRING_MAX_LENGTH];//模拟量端口相标识
     uint8_t element[CMTR_STRING_MAX_LENGTH];
     uint8_t unit[CMTR_STRING_MAX_LENGTH];//模拟量端口数值的单位
    double factor_a;//系数a
     double factor_b;//系数b
    short offset_time;//时间偏移
    int smp_min;//smp_min
    int smp_max;//smp_max
    int ct1;//ct变比1次值
    int ct2;//ct变比2次值
    uint8_t flag[1]; //P或M
}cmtr_cfg_analog;


 /*
* cmtr_cfg_digit - 配置文件数字量信息
* @index: 数字量端口序号（只是编号，解析时不做序号用）；
* @name: 数字量端口名称；
* @state: 数字量起始状态值，一般为1或者0，很少情况下会为2；
*
*/
typedef struct  {
    short index;//数字量端口序号
    uint8_t name[CMTR_STRING_MAX_LENGTH];//数字量端口名称
    short state;//数字量起始状态值
}cmtr_cfg_digit;

/*
 * cmtr_cfg_smprate_info - 配置文件采样点信息
 * @rate: 采样率，一般为整数，也有小数表示的；
 * @point: 该采样率下采样的点数，为整数；
*/
typedef struct  {
    float rate; //采样率
    int point;//该采样率下采样的点数，为整数；

}cmtr_cfg_smprate;


/*
* cmtr_cfg_info - 配置文件信息。
* @station_name: 厂站名称；
 * @kymograph_id: 录波器编号；
 * @analog_count: 模拟量个数；
* @digit_count: 数字量个数；
* @analogs: 模拟量信息；
* @digits: 数字量信息；
* @frequency: 基本频率，一般为额定频率，指的是电网频率；
* @smprate_count: 采样率个数；
* @smprates: 采样率信息；
* @begin_time: 录波开始时间；
* @end_time: 录波结束时间；
 * @file_type: 数据文件类型，可以“ASCII”和“Binary”，ASCII类型为dat文件可以用记事本打开看详
 细的采样信息；binary格式的只能用特殊的工具查看，为二进制数据文件；
*/
typedef struct  {
    uint8_t station_name[CMTR_STRING_MAX_LENGTH];//厂站名称
    uint8_t kymograph_id[CMTR_STRING_MAX_LENGTH];//录波器编号
    int analog_count;//模拟量个数
    int digit_count;//数字量个数
    cmtr_cfg_analog analogs[CMTR_ANALOG_MAX_COUNT];//
    cmtr_cfg_digit digits[CMTR_DIGIT_MAX_COUNT];
    int frequency;//电网频率
    int smprate_count;//采样率个数
    //cmtr_cfg_smprate smprates[CMTR_SMPRATE_MAX_COUNT]; //采样率信息
    int rate; //采样率
    int point;//该采样率下采样的点数，为整数；
    uint8_t begin_time[CMTR_STRING_MAX_LENGTH];//录波开始时间
    uint8_t end_time[CMTR_STRING_MAX_LENGTH];//录波结束时间
    uint8_t file_type[CMTR_STRING_MAX_LENGTH];//数据文件类型
}cmtr_cfg_info;

/*
* cmtr_dat_smpdot - 数据文件中的采样点数据信息.
* @index: 端口序号（只是编号，解析时不做序号用）；
* @time: 采样点采样时间偏移量，单位微妙；
* @analogs: 模拟量信息，一般为有符号整数
* @digits: 数字量信息，为有符号整数；
*/

 typedef struct {
    int index;//端口序号
    int time;//采样点采样时间偏移量，单位微妙
    int analogs[CMTR_ANALOG_MAX_COUNT];//模拟量信息，一般为有符号整数//大小为数字量个数
    int digits[CMTR_DIGIT_MAX_COUNT];//数字量信息，为有符号整数
}cmtr_dat_smpdot;


/*
* write_cmtr_cfg_info - 写cmtr配置文件.
 * @pfd:  输入输出参数，地址
 * @cfg：输入参数，cmtr(cfg文件)结构体
 * @counter:  输出参数，写入的字节计数器；
 * 返回当前pfd指针,写失败返回NULL
 */

int write_cmtr_cfg_info(FILE *fd,cmtr_cfg_info *cfg,int *counter);
/*
 * write_cmtr_dat_smpdot_ascii - 写cmtr采样点数据信息(ascii格式).
* @pfd:  输入输出参数，地址
* @analog_count: 输入参数，模拟量个数；
* @digit_count: 输入参数，数字量个数；
* @dot:  输入参数，采样点信息；
* @counter:  输出参数，写入的字节计数器；
* 返回当前pfd指针,写失败返回NULL
*/
int write_cmtr_dat_smpdot_ascii(FILE *pfd,int analog_count, int digit_count,cmtr_dat_smpdot *dot,int* counter);
 int write_cmtr_dat_smpdot_binary(FILE *pfd, int analog_count, int digit_count,cmtr_dat_smpdot *dot, int* counter);
int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen,
		char *outbuf, size_t outlen) ;

int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

int write_file_utf(FILE *fd,void *src,int len,int *counter);

int write_file_gdb(FILE *fd,void *src,int len,int *counter);


 #endif // !__MY_COMTRADE_H

