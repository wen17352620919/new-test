#include "ptr_arry.h"
/*
测试原因：1、测试定义打印函数
                       2、测试指针数组缓存数据(rp驱动程序内无法使用队列和堆栈的函数)


*/

#define MSG(args...) printf(args) 
#define MSG2(args) printf(args) //只能带一个参数

/*
测试2种定义Msg的不同
结果：MSG可以带参数，MSG2不能带参数
*/
void TestMsg()
{
    /*msg函数验证*/
    int n[10]={1,2,3,4,5,6,7,8,9,0};
    MSG("error\r\n");
    MSG2("error\r\n");
    MSG("%d\r\n",n[0]);
}


//测试的结构体
typedef struct
{
    void *ip[10];//指针数组
    int  num[10];//存的数组内容字节数
    int count;//存的次数
	int lock;//锁
}_myptr;

//定义结构体对象
static _myptr  myptr;

//模仿m4调用驱动程序
int ptrcall(void *ptr,int size)
{
    /*记录调用次数*/
    myptr.count++;
    /*记录传递的数组与数组元素个数*/
    myptr.ip[myptr.count] = ptr;
    myptr.num[myptr.count] = size;
    
}

/*打印数据，模仿read函数*/
void printf_ptr(void *ptr,int size)
{
    int len = size;
	int *ptr_int = (int *) ptr;//若传输类型为uint16_t,则uint16_t *ptr_int = (uint16_t *) data;
    while(len--)
    {
            printf("data = %d\n",*ptr_int++);
    }
}

//模仿读驱动程序函数
void  do_ptr()
{
    while (1)
    {
            /*判断是否有数组传入，有则打印并清除，模仿读走数据*/
            if(myptr.count!=0)
            {
                printf_ptr(myptr.ip[myptr.count],myptr.num[myptr.count]);
                myptr.count--;
            }
            else
            {
                break;
            }
    }
    printf("over\r\n");
}




/*
测试函数
*/
void Test_ptr()
{
    int  b[10] = {0,1,2,3,4,5,6};
    int c[10] = {99,98,97,96,95,94,93,92,91};

    ptrcall(b,7);
    
    ptrcall(c,9);
    do_ptr();
}
























