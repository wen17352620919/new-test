

#include "comtrade/my_comtrade.h"
#include  "FileOperation/file.h"
#include"TEST/test_data.h"
#include"M4-A7/M4ToA7.h"


/*
11.16
增加rp驱动将void*转回uint16_t的打印
增加循环创建线程
增加读取文件并判断存入结构体
bug  
线程开辟太多时会无法创建新线程
进程退出，线程还在运行---------加return

rp无法卸载


11.17测试
只开读线程，M4发送32752  一直运行无问题

只开写线程，A7发送32752，M4只接收，报错，cut here，以修复，修改驱动内接收的字符数组大小

只开写线程，A7发送32752，M4发送接收都开

修改驱动支持16位数据发送

验证rpmsg回调没执行完，m4之后发送不会成功

问题：读会丢数据，驱动屏蔽掉打印出问题，写太频繁,暂时解决办法，a7收一次，给m4发一次，m4才能继续发
[  468.317804] rp virtio0.rpmsg-client-sample.-1.0: timeout waiting for a tx buffer
[  468.323805] rp virtio0.rpmsg-client-sample.-1.0: rpmsg_send failed: -512


11.23 用户态测试
A7给M4发可以超过496字节，M4给A7发不能超过496字节
5.26
rp中增加了100条缓冲，速度过快还是会丢失数据

*/




volatile int read_file_over;//读到的m4数据个数
volatile int data_deal_flag;//读完数据的标志

comtrade a;
type_M4_data  M4_data;//M4发过来的结构体
void test_demo();
void data_do(char  buf[],cmtr_dat_smpdot* mydata);
void read_file(FILE *fd_dat,cmtr_dat_smpdot *mydata,cmtr_cfg_info *cfg);
void system_start();
void system_stop();

//---------测试程序声明
void data_init(type_M4_data *data);
void test_write(cmtr_dat_smpdot  *dat_data,type_M4_data *data,int len);
//------------
int main()
{
    //char filename[50] ;
    //gettime(filename);
    // int len = strlen(filename);
    // printf("%d\r\n",len);
    // int dir_flag = dir_create(filename);//创建文件夹
    // if(dir_flag >=0)
    // {
    //         create_comtrade_DAT(filename);
    //         create_comtrade_INF(filename);
    //         create_comtrade_HDR(filename);
    //         create_comtrade_CFG(filename);
    // }

    
    //开线程读
    printf("main start \r\n");
    system_start();
    sleep(3);//加载驱动及启动m4需要时间

    // //----------------------------------持续监听m4程序
    pthread_t pid_M4_A7,pid_A7_M4;
    int ret = pthread_create(&pid_M4_A7, NULL, read_m4_a7, NULL);
    if (ret) 
    {
        printf("pid_M4_A7 creat error\r\n");
    }
    else
    {
        printf("pid_M4_A7 creat ok\r\n");
    }

    // ret = pthread_create(&pid_A7_M4, NULL, write_a7_m4, NULL);
    // if (ret) 
    // {
    //     printf("pid_A7_M4 creat error\r\n");
    // }
    // else
    // {
    //     printf("pid_A7_M4 creat ok\r\n");
    // }
    // while(1)
    // {

    // }
    
    // test_demo();
    // printf("============\r\n");
   
    return 0;
}

void test_demo()
{
    char filename[50] ;
    char path[50] = "/mnt/hgfs/myir/file_write_test";
    gettime(filename);
    strcpy(filename,"3.9");
    int dir_flag = dir_create(filename,path);
    if(dir_flag >=0)
    {
        char dirpath[50] = {0};
        strcpy(dirpath,path);
        strcat(dirpath,"/");
        strcat(dirpath,filename);
        char cfgname[50]={0};
        char datname[50]={0};

    
        strcat(cfgname,"3.9.cfg");

        strcat(datname,"3.9.dat");
        create_comtrade_CFG(cfgname,dirpath);
        create_comtrade_DAT(datname,dirpath);
        printf("creat file ok\r\n");
        cmtr_cfg_info cfg;
        cmtr_dat_smpdot dot;
        cfg_init(&cfg);
        int counter = 0;
        write_cmtr_cfg_info(a.CFG,&cfg,&counter);//写cmtr配置文件
        fclose(a.CFG);
        printf("counter = %d\n",counter);
        read_file(a.DAT,&dot,&cfg);        
        fclose(a.DAT);
    }
     

}


//分解字符串，以','为分割线
void data_do(char  buf[],cmtr_dat_smpdot* mydata)
{
    char *ptr =(char*) ",";
    char *p;
    
    p = strtok(buf, ptr);
    mydata->index = atoi(p);

    p = strtok(NULL,ptr);
    mydata->time = atoi(p);
    int i=0;
    while((p = strtok(NULL, ptr)))
    {
        mydata->analogs[i++] = atoi(p);//字符串转整形
    }
}

//第一次测试，读取数据文件并按自己的函数写入
void read_file(FILE* fd_dat,cmtr_dat_smpdot *mydata,cmtr_cfg_info *cfg)
{
     int fd;
    fd = open("/home/wen/test/ascall_2bin/B.dat", O_RDWR);
    FILE * fp = NULL;
    //-------------------------------
    fp = fdopen(fd,"a+");//文件描述符与 FILE ， fileno()为fp->fd
    char buf[1024];
    int size = 1024;
    int counter=0;
    
    while(fgets(buf, size, fp)!=NULL)
    {
            if(buf[1]=='\n')//回车为\r
            {

            }
            else
            {             
                data_do(buf,mydata);

                 write_cmtr_dat_smpdot_ascii(fd_dat,cfg->analog_count,cfg->digit_count,mydata,&counter);
                //  write_cmtr_dat_smpdot_binary(fd_dat,cfg->analog_count,cfg->digit_count,mydata,&counter);
            }     
    }
    close(fd);
}

//m4程序启动函数
void system_start()
{
        system("echo 8 > /proc/sys/kernel/printk");//开打印
        system("insmod rp.ko");//加载驱动
        // system("ifconfig eth0 192.168.137.219");//设置网络
        // system("echo rpmsg_CM4.elf > /sys/class/remoteproc/remoteproc0/firmware");//加载m4固件
        // system("echo Dmaspi_CM4.elf > /sys/class/remoteproc/remoteproc0/firmware");//加载m4固件 

        // system("echo start > /sys/class/remoteproc/remoteproc0/state");//开始运行m4程序
}
//m4程序退出函数
void system_stop()
{
    // system("echo stop > /sys/class/remoteproc/remoteproc0/state");//停止m4程序
    system("rmmod rp");//卸载驱动
    system("    rmmod rpmsg_client_sample");//卸载驱动
}



//测试将m4结构体写入dat文件,len为多少个1200数据    
void test_write(cmtr_dat_smpdot  *dat_data,type_M4_data *data,int len)
{
    int counter = 0;
    FILE *fd = fopen("/mnt/hgfs/git/11.17.dat", "wr");
    if(fd<0)
    {
        printf("creat dat error\r\n");
    }
    else
    {
        printf("creat file \r\n");
    }

    for(int i=0; i<1200; i++)
    {
        dat_data->index = i+1;
        dat_data->time = 78*i;
        for(int j=0;j<len;j++)
        {
                dat_data->analogs[j]= data->U[j][i];
        }
        write_cmtr_dat_smpdot_ascii(fd,5,0,dat_data,&counter);
    }
}

void data_init(type_M4_data *data)
{

	// data->flag = 1;
	// data->len = sizeof(type_M4_data);
	// int Am = 1000;

	// for(int i=0;i<8;i++)
	// {
	// 	for(int j=0;j<1200;j++)
	// 	{
	// 		data->U[i][j] = Am*sin(2*6.28/120);
	// 		// data->U[i][j] = j;
	// 	}
	// 	Am = 2*Am;
	// }
	// Am = 1000;
	// for(int i=0;i<36;i++)
	// {
	// 	for(int j=0;j<1200;j++)
	// 	{
	// 		 data->I[i][j] = Am*sin(2*6.28/120);
    //         // data->I[i][j] = j;
	// 	}
	// 	Am = Am+2000;
	// }
}

    /*用户态测试*/
    // char data[44444] = {'\0'};
    // int  fd_rpmsg = open("/dev/ttyRPMSG0",O_RDWR,0777);
    // printf("write_a7_m4 线程 ID<%lu>    fd_rpmsg_write = %d\n", pthread_self(),fd_rpmsg);
    // if(fd_rpmsg < 0)
    // {
    //     printf("read  fd_rpmsg error\r\n");
    // }
    // printf("pthread start\r\n");
    // int size =490;
    // while(1)
    // {
    //     write(fd_rpmsg,data,size);
    //     sleep(1);
    //     size++;
    // }

