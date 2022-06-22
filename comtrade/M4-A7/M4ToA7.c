#include"M4ToA7.h"
#define rpmsg_model_path "/dev/rp"
extern int read_file_over;//读到的m4数据个数
extern int data_deal_flag;//读完数据的标志

uint16_t buf16[32753];
extern type_M4_data  M4_data;
void *_data;
//开线程运行读取m4数据
void* read_m4_a7(void* args)
{
    int times = 0;
    int pthread_num =0;
    pthread_t pid[100];
    int  fd_rpmsg = open(rpmsg_model_path,O_RDWR,0777);
    if(fd_rpmsg < 0)
    {
        printf("read  fd_rpmsg error  \r\n");
    }
    else
    {
        printf("read  fd_rpmsg ok  \r\n");
    }
    // printf("read_m4_a7 线程 ID<%lu>  fd_rpmsg_read = %d\n", pthread_self(),fd_rpmsg);
    write(fd_rpmsg,"a7 start read",14);//rpmsg必须A7先发一次数据给M4
    while(1)
    {               
        int read_size= read(fd_rpmsg,buf16,32752); 
        if(read_size <0)
        {
            printf("read error\r\n");
        }
        else if (read_size> 1)
        {
            times++;
            printf("times = %d  read_size=%ld\r\n",times,read_size);//接收到的次数
            read_file_over+=read_size;
            data_deal(&read_file_over);
            
            // sleep(2);
            // printf("read ok\r\n");


            //---------------------------------------数据打印，后期去掉
            // int size = read_size/2;
            // for(int i=0;i<size;i++)
            // {
            //         printf("buf16 = %d\r\n",buf16[i]);
            // }
            //--------------------------------------每次单独开线程处理，有bug,会出现创建失败
            // if(pthread_num ==50)
            // {
            //     pthread_num =0;
            // }
            // int ret = pthread_create(&pid[pthread_num++], NULL, data_deal,(void*)read_file_over);
            // if (ret) 
            // {
            //     printf("pthread creat error\n");
            // }
            // else
            // {
            //     printf("pthread creat ok   pthread_num=%d\n",pthread_num);
            // }
            // write(fd_rpmsg,"start",5);//rpmsg必须A7先发一次数据给M4

        }    
    }
}
//m4数据处理函数
void* data_deal(void* args)
{
        switch(buf16[0])
    {
        case 0:
                        printf("case 0\n");
                        break;
        case 1:
                        memcpy(M4_data.U[1],&buf16[2],buf16[1]);
                        break;
        case 2:
                        memcpy(M4_data.U[2],&buf16[2],buf16[1]);
                        break;
        case 3:
                         memcpy(M4_data.U[3],&buf16[2],buf16[1]);
                        break;
        case 4:
                        memcpy(M4_data.U[4],&buf16[2],buf16[1]);
                        break;
        case 5:
                        memcpy(M4_data.U[5],&buf16[2],buf16[1]);
                        break;
        case 6:
                        memcpy(M4_data.U[6],&buf16[2],buf16[1]);
                        break;
        case 100:
                        memcpy(M4_data.I[0],&buf16[2],buf16[1]);
                        break;
        case 101:
                        memcpy(M4_data.I[1],&buf16[2],buf16[1]);
                        break;
        case 102:
                        memcpy(M4_data.I[2],&buf16[2],buf16[1]);
                        break;
        case 103:
                        memcpy(M4_data.I[3],&buf16[2],buf16[1]);
                        break;
        case 104:
                        memcpy(M4_data.I[4],&buf16[2],buf16[1]);
                        break;
        case 105:
                        memcpy(M4_data.I[5],&buf16[2],buf16[1]);
                        break;
        case 106:
                        memcpy(M4_data.I[6],&buf16[2],buf16[1]);
                        break;
        case 107:
                        memcpy(M4_data.I[7],&buf16[2],buf16[1]);
                        break;
        case 108:
                        memcpy(M4_data.I[8],&buf16[2],buf16[1]);
                        break;
        case 109:
                        memcpy(M4_data.I[9],&buf16[2],buf16[1]);
                        break;
        case 110:
                        memcpy(M4_data.I[10],&buf16[2],buf16[1]);
                        break;
        case 111:
                        memcpy(M4_data.I[11],&buf16[2],buf16[1]);
                        break;
        case 112:
                        memcpy(M4_data.I[12],&buf16[2],buf16[1]);
                        break;
        case 113:
                        memcpy(M4_data.I[13],&buf16[2],buf16[1]);
                        break;
        case 114:
                        memcpy(M4_data.I[14],&buf16[2],buf16[1]);
                        break;
        case 115:
                        memcpy(M4_data.I[15],&buf16[2],buf16[1]);
                        break;    
        case 116:
                        memcpy(M4_data.I[16],&buf16[2],buf16[1]);
                        break;         
        case 117:
                        memcpy(M4_data.I[17],&buf16[2],buf16[1]);
                        break;
        case 118:
                        memcpy(M4_data.I[18],&buf16[2],buf16[1]);
                        break;
        case 119:
                        memcpy(M4_data.I[19],&buf16[2],buf16[1]);
                        break;
        case 120:
                        memcpy(M4_data.I[20],&buf16[2],buf16[1]);
                        break;
        case 121:
                        memcpy(M4_data.I[21],&buf16[2],buf16[1]);
                        break;
        case 122:
                        memcpy(M4_data.I[22],&buf16[2],buf16[1]);
                        break;
        case 123:
                        memcpy(M4_data.I[23],&buf16[2],buf16[1]);
                        break;
        case 124:
                        memcpy(M4_data.I[24],&buf16[2],buf16[1]);
                        break;
        case 125:
                        memcpy(M4_data.I[25],&buf16[2],buf16[1]);
                        break;
        case 126:
                        memcpy(M4_data.I[26],&buf16[2],buf16[1]);
                        break;
        case 127:
                        memcpy(M4_data.I[27],&buf16[2],buf16[1]);
                        break;
        case 128:
                        memcpy(M4_data.I[28],&buf16[2],buf16[1]);
                        break;
        case 129:
                        memcpy(M4_data.I[29],&buf16[2],buf16[1]);
                        break;
        case 130:
                        memcpy(M4_data.I[30],&buf16[2],buf16[1]);
                        break;
        case 131:
                        memcpy(M4_data.I[31],&buf16[2],buf16[1]);
                        break;
        case 132:
                        memcpy(M4_data.I[32],&buf16[2],buf16[1]);
                        break;    
        case 133:
                        memcpy(M4_data.I[33],&buf16[2],buf16[1]);
                        break; 
       case 134:
                        memcpy(M4_data.I[34],&buf16[2],buf16[1]);
                        break;    
        case 135:
                        memcpy(M4_data.I[35],&buf16[2],buf16[1]);
                        break; 
    }
    printf("read_file_over = %d\r\n",read_file_over);
    if(read_file_over == 86544)//2404*44，8+36
    {
            read_file_over = 0;
            data_deal_flag = 1;
            printf("over \r\n");

    }
}

//循环发送给m4，测试全双工用
void* write_a7_m4(void*args)
{
    //int t = (int)args;

    char data[44444] = {'\0'};
    int  fd_rpmsg = open(rpmsg_model_path,O_RDWR,0777);
    printf("write_a7_m4 线程 ID<%lu>    fd_rpmsg_write = %d\n", pthread_self(),fd_rpmsg);
    if(fd_rpmsg < 0)
    {
        printf("read  fd_rpmsg error\r\n");
    }
    printf("pthread start\r\n");
    int wtimes = 0;
    while(1)
    {
        write(fd_rpmsg,data,32752);
        wtimes++;
        if(wtimes ==100)
        {
            break;
        }
    }
}




