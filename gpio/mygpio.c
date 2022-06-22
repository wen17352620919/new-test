#include "mygpio.h"


int fd117;//AD_BUSY1，1有效
int fd118;//AD_NSS1,0触发
uint8_t busydata[10];
int gpiooveflag;



int gpio_export(int pin)  
{  
    char buffer[64];  
    int len;  
    int fd;  
    fd = open("/sys/class/gpio/export", O_WRONLY);  

    if (fd < 0) {  
        MSG("Failed to open export for writing!\r\n");  
        return(-1);  
    }  
    len = snprintf(buffer, sizeof(buffer), "%d", pin);  
    if (write(fd, buffer, len) < 0) {  
        MSG("Failed to export gpio!\r\n");  
        return -1;  
    }       
    close(fd);  
    return 0;  
}  


int gpio_unexport(int pin)  
{  
    char buffer[64];  
    int len;  
    int fd;  
    fd = open("/sys/class/gpio/unexport", O_WRONLY);  
    if (fd < 0) {  
        MSG("Failed to open unexport for writing!\r\n");  
        return -1;  
    }  
 	len = snprintf(buffer, sizeof(buffer), "%d", pin);  
    if (write(fd, buffer, len) < 0) {  
        MSG("Failed to unexport gpio:%d\r\n",pin);  
        return -1;  
    }       
    close(fd);  
    return 0;  
} 

int gpio_read(int pin)  
{  
    char path[64];  
    char value_str[3];  
    int fd;  
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);  
    fd = open(path, O_RDONLY);  
    if (fd < 0) {  
        MSG("Failed to open gpio value for reading!\r\n");  
        return -1;  
    }  
    if (read(fd, value_str, 3) < 0) {  
        MSG("Failed to read value!\r\n");  
        return -1;  
    }  
    close(fd);  
    return (atoi(value_str));//字符串转整形
}  

//value: 0-->LOW, 1-->HIGH
int gpio_write(int pin, int value)  
{  
    static const char values_str[] = "01";  
    char path[64];  
    int fd;  
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        MSG("Failed to open gpio value for writing!\r\n");  
        return -1;  
    }  
    if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0) {  
        MSG("Failed to write value!\r\n");  
        return -1;  
    }  
    close(fd);  
    return 0;  
}


/*
设置输入输出
dir: 0-->IN, 1-->OUT
*/
int gpio_direction(int pin, int dir)  
{  
    static const char dir_str[] = "in\0out";  
    char path[64];  
    int fd;  
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        MSG("Failed to open gpio direction for writing!\r\n");  
        return -1;  
    }  
    if (write(fd, &dir_str[dir == 0 ? 0 : 3], dir == 0 ? 2 : 3) < 0) {  
        MSG("Failed to set direction!\r\n");  
        return -1;  
    }  
    close(fd);  
    return 0;  
}  

// none表示引脚为输入，不是中断引脚

// rising表示引脚为中断输入，上升沿触发

// falling表示引脚为中断输入，下降沿触发

// both表示引脚为中断输入，边沿触发

// 0-->none, 1-->rising, 2-->falling, 3-->both

int gpio_edge(int pin, int edge)

{
	// const char dir_str[] = "none\0rising\0falling\0both"; 
	char ptr[10];
	char path[64];  
    int fd; 
	switch(edge){

		case 0:
            strcpy(ptr,"none");
		break;
		case 1:
            strcpy(ptr,"rising");
		break;
		case 2:
            strcpy(ptr,"falling");
		break;
		case 3:
            strcpy(ptr,"both");
		break;
		default:
            strcpy(ptr,"none");
	} 
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/edge", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        MSG("Failed to open gpio edge for writing!\r\n");  
        return -1;  
    }  
    if (write(fd, ptr, strlen(ptr)) < 0) {  
        MSG("Failed to set edge!\r\n");  
        return -1;  
    }  
    close(fd);  
    return 0;  
}



/*
设置极性
act: 0- 0-low,1-high
act: 1- 1-low,0-high
*/
int gpio_active(int pin, int act)  
{  
    static const char act_str[] = "01";  
    char path[64];  
    int fd;  
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/active_low", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        MSG("Failed to open gpio active_low  for writing!\r\n");  
        return -1;  
    }  
    if (write(fd, &act_str[act == 0 ? 0 : 1], 1) < 0) {  
        MSG("Failed to set active_low!\r\n");  
        return -1;  
    }  
    close(fd);  
    return 0;  
}  

long  testGettimeofday()
{
    struct timeval t1;
    gettimeofday(&t1, NULL);


    return t1.tv_sec;

}
void  Gettimeofday()
{
    struct timeval t1;
    gettimeofday(&t1, NULL);

    printf(" sec = %ld\r\n", t1.tv_sec);

    printf(" usec = %ld\r\n",t1.tv_usec );

}

/*
ability取值
value:值
edge:中断方式
direction:方向

wr:读写权限，定义为gpio中断则只能为O_RDONLY
*/

int OpenGpio(int pin,char *ability,int wr)
{

    char gpiox[40]="";
    snprintf(gpiox, sizeof(gpiox), "/sys/class/gpio/gpio%d", pin);  
    strcat(gpiox,"/value");
    int myfd;
    if (0 > (myfd = open(gpiox, wr))) 
    {
        perror("open error");
        printf("%d\r\n",__LINE__);
    }
    return myfd;
}









