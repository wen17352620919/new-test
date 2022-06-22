#include "my_comtrade.h"
char buf[100];
/*
写文件GDB格式
fd 文件句柄
src 要写的数据
len 要写的长度
counter 写的长度
*/
int write_file_gdb(FILE *fd,void *src,int len,int *counter)
{
    if(fd==NULL)
    {
        return -1;
    }
    //utf8转GDB2312,不转则打开中文乱码
    u2g(src, len, buf, sizeof(buf));
    //写文件   
    int  ret = fwrite(buf, 1,strlen(buf),fd);
    if (-1 == ret) 
    {
        printf("Error: write file failed!\n");
    }
    (*counter)+=(len); 
    return ret;
}
/*
写文件utf格式(正常写,不含转换程序)
fd 文件句柄
src 要写的数据
len 要写的长度
counter 写的长度
*/
int write_file_utf(FILE *fd,void *src,int len,int  *counter)
{
    if(fd==NULL)
    {
        return -1;
    }
    int  ret = fwrite(src, 1,strlen(src),fd);
    if (-1 == ret) 
    {
        printf("Error: write file failed!\n");
    }
    (*counter)+=(len); 
    return ret;
}
                                                                                                                                      
/*
字符串中转函数，由u2g和g2u函数调用
from_charset 被转换的格式
to_charset  要转换的格式
inbuf 要转换的数据
inlen 要转换的数据长度
outbuf 存放被转换的数据
outlen 被转换的数据长度
*/
int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen,
		char *outbuf, size_t outlen) 
{
    iconv_t cd;
    int rc;
    char **pin = &inbuf;
    char **pout = &outbuf; 
    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    int ret = iconv(cd,pin,&inlen,pout,&outlen);
    if (ret==-1) return -1;
    iconv_close(cd);
    return ret;
}
/*
utf-8转gb2312程序
inbuf 要转换的数据
inlen 要转换的数据长度
outbuf 存放被转换的数据
outlen 被转换的数据长度
*/
int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}
/*
gb2312转utf-8程序
inbuf 要转换的数据
inlen 要转换的数据长度
outbuf 存放被转换的数据
outlen 被转换的数据长度
*/
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}
/*
写cmtr配置文件
fd 文件句柄
cfg 配置信息结构体
counter 写的字节数
*/

int write_cmtr_cfg_info(FILE *fd,cmtr_cfg_info *cfg,int *counter)
{
    int strlenr = 0;
    int strmaxl = CMTR_STRING_MAX_LENGTH * 13;
    char* strline = (char *)malloc(strmaxl);
    int index = 0;
    FILE *_fd = fd;
    /*站名，录波编号*/
    memset(strline, '\0', strmaxl);
    strlenr = sprintf(strline, "%s,%s\n", cfg->station_name,cfg->kymograph_id);  
    write_file_gdb(fd,strline,strlenr,counter);
   /*通道总数，模拟通道数，数字通道数*/
    memset(strline, '\0', strmaxl);
    strlenr = sprintf(strline, "%d,%dA,%dD\n", cfg->analog_count + cfg->digit_count, cfg->analog_count, cfg->digit_count);
    write_file_gdb(fd,strline,strlenr,counter);
    /*写模拟量*/
    for (index = 0; index < cfg->analog_count; index++) {
                 memset(strline, '\0', strmaxl);

                 strlenr = sprintf(strline, "%d,%s,%s,%s,%s,%lf,%lf,%d,%d,%d,%d,%d,%s\n",
                                    
                                   cfg->analogs[index].index+1,//通道编号

                                   cfg->analogs[index].name,//通道名称

                                   cfg->analogs[index].phase,//通道相

                                   cfg->analogs[index].element,

                                   cfg->analogs[index].unit,//模拟量端口数值的单位

                                   cfg->analogs[index].factor_a,//系数a

                                   cfg->analogs[index].factor_b,//系数b

                                   cfg->analogs[index].offset_time,//时间偏移

                                   cfg->analogs[index].smp_min,//此模拟量采样记录数据最小值

                                   cfg->analogs[index].smp_max,//此模拟量采样记录数据最大值
                                   
                                   cfg->analogs[index].ct1,//ct变比1次值

                                   cfg->analogs[index].ct2,//ct变比2次值

                                   cfg->analogs[index].flag);//P或S，表明通道转换因子方程fCoefA * X + fCoefB得到的值还原为一次（P）还是二次（S）值的标识
                                    
                    write_file_gdb(fd,strline,strlenr,counter);
    }
    /*写数字量*/
    for (index = 0; index < cfg->digit_count; index++) {

                 memset(strline, '\0', strmaxl);

                 strlenr = sprintf(strline, "%d,%s,%d\n",

                                    cfg->digits[index].index,//数字量端口序号

                                    cfg->digits[index].name,//数字量端口名称

                                    cfg->digits[index].state);//数字量起始状态值

                  write_file_gdb(fd,strline,strlenr,counter);

    }
    /*写电网频率*/
        memset(strline, '\0', strmaxl);
        strlenr = sprintf(strline, "%d\n", cfg->frequency);
        write_file_gdb(fd,strline,strlenr,counter);
    
    /*采样率个数*/
        memset(strline, '\0', strmaxl);
        strlenr = sprintf(strline, "%d\n", cfg->smprate_count);
        write_file_gdb(fd,strline,strlenr,counter);

    /*采样率和采样点数*/
    memset(strline, '\0', strmaxl);
        strlenr = sprintf(strline, "%d,%d\n", cfg->rate,cfg->point);
        write_file_gdb(fd,strline,strlenr,counter);

    /*写开始和结束时间*/
        memset(strline, '\0', strmaxl);
        strlenr = sprintf(strline, "%s\n", cfg->begin_time);
        write_file_gdb(fd,strline,strlenr,counter);
        memset(strline, '\0', strmaxl);
        strlenr = sprintf(strline, "%s\n", cfg->end_time);
    /*写文件类型，ASCALL*/
        write_file_gdb(fd,strline,strlenr,counter);
        strlenr = sprintf(strline, "%s\n", cfg->file_type);
        write_file_gdb(fd,strline,strlenr,counter);

        free(strline);
    return 1;
}
/*
以ascall码格式写数据文件
pfd 文件句柄
analog_count 模拟量个数
digit_count 数字量个数
dot 数据文件中的采样点数据信息
counter 写的字节数
*/
int write_cmtr_dat_smpdot_ascii(FILE *pfd,int analog_count, int digit_count,cmtr_dat_smpdot *dot,int* counter)
{
        int strlenr = 0;
        
         int strmaxl = CMTR_STRING_MAX_LENGTH;//相关字符串最大字符个数

         char* strline = (char *)malloc(strmaxl);

         int index = 0;
         FILE *curr_pfd = pfd;
        /*写序号，采样时间*/
        memset(strline, '\0', strmaxl);
         strlenr = sprintf(strline, "%d,%d", dot->index, dot->time);
         write_file_utf(curr_pfd, strline, strlenr, counter);
        /*写模拟量值*/
         for (index = 0; index < analog_count; index++) {
                 memset(strline, '\0', strmaxl);
                 strlenr = sprintf(strline, ",%d", dot->analogs[index]);
                 write_file_utf(curr_pfd, strline, strlenr, counter);
         }
        /*写数字量值*/
         for (index = 0; index < digit_count; index++) {
                 memset(strline, '\0', strmaxl);
                strlenr = sprintf(strline, ",%d", dot->digits[index]);
                 write_file_utf(curr_pfd, strline, strlenr, counter);
         }
        /*写文件结尾*/
        memset(strline, '\0', strmaxl);
        strlenr = sprintf(strline, "\n");
        write_file_utf(curr_pfd, strline, strlenr, counter);
         free(strline);
    return 1;
}


/*
二进制格式写数据文件(测试未通过)
pfd 文件句柄
analog_count 模拟量个数
digit_count 数字量个数
dot 数据文件中的采样点数据信息
counter 写的字节数
*/
 int write_cmtr_dat_smpdot_binary(FILE *pfd, int analog_count, int digit_count,cmtr_dat_smpdot *dot, int* counter)
 {

    int16_t data16 = 0x00;
    int32_t data32 = 0x00;
    int oldnum = 0;
    int16_t datatp = 0x00;
    int index = 0;

    FILE *curr_pfd = pfd;

    oldnum = (*counter);

    data32 = dot->index;

    write_file_utf(curr_pfd, &data32, 4, counter);
    if ((*counter) <= oldnum) 
    {
        return 0;
    }

    oldnum = (*counter);

    data32 = dot->time;

    write_file_utf(curr_pfd, &data32, 4, counter);

    if ((*counter) <= oldnum) 
    {
        return 0;
    }

    for (index = 0; index < analog_count; index++) 
    {  
        oldnum = (*counter);
        datatp = (int16_t)(dot->analogs[index]);
        data16 = datatp;
        write_file_utf(curr_pfd, &data16, 2, counter);
        if ((*counter) <= oldnum) 
        {
            return 0;
        }
    }
    data16 = 0x0000;
    for (index = 0; index < digit_count; index++) {

        if (dot->digits[index]) {
        data16 |= (0x0001 << (index % 16));

    }

    if (((index % 16) == 0) && (index != 0)) {

        oldnum = (*counter);

        data16 = data16;

        write_file_utf(curr_pfd, &data16, 2, counter);

        if ((*counter) <= oldnum) {

            return 0;

        }
    }
    }

    if (((index % 16) != 1) && (index != 0)) {

        oldnum = (*counter);

        data16 = data16;

        write_file_utf(curr_pfd, &data16, 2, counter);
        if ((*counter) <= oldnum) {

            return 0;
    }
    }
    return 1;

}