#include"file.h"


//====================================
void  gettime(char *_time)
{
     time_t time3;
     struct tm *p;
     time3 = time(NULL);
    
    p = localtime(&time3);
   
    sprintf(_time,"%04d-%02d-%02d %02d-%02d-%02d", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                p->tm_hour, p->tm_min, p->tm_sec);

}

/*创建文件夹*/
int dir_create(char *dir,char *path)
{
    char dir_name[255]={0};
    // sprintf(dir_name, "%s", dir);
    strcpy(dir_name,path);
    strcat(dir_name,"/");
    strcat(dir_name,dir);

    int fd = mkdir(dir_name,0777);
    if(fd == -1)
    {
        printf("mkdir error\r\n");
        printf("dir name = %s\r\n",dir_name);
        return -1;
    }
    if(fd == 0)
    {
        printf("mkdir ok\r\n");
        strcat(dir_name,"/");
        return 0;
    }
    
}


//创建文件
void create_comtrade_HDR(char* filename,char *dir)
{      
    char path[100];
    strcpy(path,dir);
    strcat(path,"/");
    strcat(path,filename);
    strcpy(a.HDR_name,filename);

     printf("%s\n",path);
    a.HDR = fopen(path,"wr");
    if(a.HDR==NULL)
    {
        printf("open%serror:%s",path,strerror(errno));
    }

 }
//=====================================
 //创建文件
void create_comtrade_CFG(char* filename,char *dir)
{      
    char path[100];
    strcpy(path,dir);
    strcat(path,"/");
    strcat(path,filename);
    strcpy(a.CFG_name,filename);

     //printf("%s\n",path);
    a.CFG = fopen(path,"wr");
    if(a.CFG==NULL)
    {
        printf("open%serror:%s",path,strerror(errno));
    }

 }
//=====================================
 void create_comtrade_DAT(char* filename,char *dir)
{      
    char path[100];
    strcpy(path,dir);
    strcat(path,"/");
    strcat(path,filename);
    strcpy(a.DAT_name,filename);
     //printf("%s\n",path);
    a.DAT = fopen(path,"wr");
    if(a.DAT==NULL)
    {
        printf("open%serror:%s",path,strerror(errno));
    }
 }
  //====================================
  void create_comtrade_INF(char* filename,char *dir)
  {      
    char path[100];
    strcpy(path,dir);
    strcat(path,"/");
    strcat(path,filename);
    strcpy(a.INF_name,filename);
    
     printf("%s\n",path);
    a.INF = fopen(path,"wr");
    if(a.INF==NULL)
    {
        printf("open%serror:%s",path,strerror(errno));
    }
 }


