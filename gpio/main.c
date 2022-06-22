#include "mygpio.h"

int gpioin = 117;//pg2 = 98 ,117
int gpioout = 118;
/*
        持续读输入无法触发，改为中断判断
        size = read(fd117, busydata, 1);
        if(busydata[0]==1)
        {
            busydata[0]=0;
            printf("ADBUSY = 1\r\n");
        }

        中断会一直触发
*/

void *ReadBusy(void*arg)
{
    int ret;
    struct pollfd fds[1];
    char buff[10];
    unsigned char cnt = 0;
    fds[0].fd = fd117;
    fds[0].events  = POLLPRI;//POLLIN
    int size = 0;
    char val;
    read(fds[0].fd, &val, 1);//先读取一次清除状态
    while(1)
    {
        /*中断方法*/
        ret = poll(fds,1,-1);//
        if( ret == -1 )
        MSG("poll error %d\r\n",__LINE__);
        if( fds[0].revents & POLLPRI)//fds[1].events == fds[1].revents
        {
            printf(" poll ok\r\n");
            ret = lseek(fd117,0,SEEK_SET);//在循环中不重新open节点去读写gpio需要在每次操作前使用
            if( ret == -1 )
            MSG("lseek error  %d\r\n",__LINE__);
        
            if (0 > read(fds[0].fd, &val, 1)) //清除，否则会一直触发
            {
                perror("read error");
                exit(-1);
            }
            //gpio_write(44, cnt++%2);
            printf("**********************************\n");
        }
        usleep(5);
        /*重新发信号*/
        gpio_write(gpioout,1);
        gpio_write(gpioout,0);

        if(gpiooveflag==1)
        {
            break;
        }
    }
    gpiooveflag = 2;
        
}

int main()
{
    int gpio_fd, ret;

    /*删除之前的节点*/
    gpio_unexport(gpioin);
    gpio_unexport(gpioout);
 
    
    //gpio118 init
    gpio_export(gpioout);
    gpio_direction(gpioout, 1);//output out
    gpio_active(gpioout, 0);
    gpio_write(gpioout, 1);
    
    //gpio117 init
    gpio_export(gpioin);
    gpio_direction(gpioin, 0);//input in
    gpio_active(gpioin, 0);
    gpio_edge(gpioin,1);


    //打开对应gpio节点的value,返回设备描述符，便于进行下一步操作
    fd117 = OpenGpio(gpioin,"value",O_RDONLY);
    fd118 = OpenGpio(gpioout,"value",O_WRONLY);
    //创建线程读取输入信号
    pthread_t pid_adbusy;    
    ret = pthread_create(&pid_adbusy, NULL, ReadBusy, NULL);
    if (ret) 
    {
        printf("pthread_create error\n");
    }
    sleep(2);
    gpio_write(gpioout,1);
    gpio_write(gpioout,0);
    while(1)
    {
        // sleep(1);
        // printf("Nss start\r\n");
        // gpio_write(gpioout,1);
        // gpio_write(gpioout,0);
    }

    //记录时间，到达一定时间程序退出
    // long t1,t2;
    // t1 = testGettimeofday();

     while(1)
    {
        // ret = poll(fds,1,0);
        // if( ret == -1 )
        // MSG("poll\n");
        // if( fds[0].revents & POLLPRI)
        // {
        //     ret = lseek(gpio_fd,0,SEEK_SET);
        //     if( ret == -1 )
        //     MSG("lseek\n");
        
        //     //gpio_write(44, cnt++%2);
        //     printf("**********************************\n");
        // }
        // usleep(5);
    }

    // while(1)
    // {
        // //持续给fpga发信号
        // ret = lseek(fd118,0,SEEK_SET);//在循环中不重新open节点去读写gpio需要在每次操作前使用
        // if( ret == -1 )
        // {
        //     MSG("lseek\n");
        // }     
        //  AD_NSS1_SET();
        // AD_NSS1_RESET();
        //  t2 = testGettimeofday();
        //  if(t2-t1>60)
        //  {
        //      gpiooveflag=1;
        //      printf("gpiooveflag=1\r\n");
        //  }
        //   if(t2-t1>100)
        //   {
        //       gpiooveflag=2;
        //   }
        //  if(gpiooveflag==2)
        //  {
        //      close(fd118);
        //      close(fd117);
        //      break;
        //  }
        //  printf("t2-t1 = %ld\n", t2-t1);
        // sleep(2);
    // }
    // printf("over gpio\r\n");

    return 0;
}


















