/*
 * control.c
 *
 *  Created on: 2024年10月23日
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "control.h"
#include "tim.h"
#include "task.h"
#include "uart.h"
#include "zf_device_mt9v03x_dvp.h"// 新加

float mid_error_out = 0;//新加 cpu1

//添加或删除任务须修改：
//TimeList周期数组；
//(*TaskList[TASKS_MAX])函数指针数组；
//tim.h添加任务周期；
//位于control.h的TASK_LIST结构体按顺序加上任务名字;
//任务顺序必须保持一致；


//存放任务执行周期的数组
//要规划线程时间的话在 tim.h 中先写个宏定义
uint16 TimeList[TASKS_MAX]=
{
       task_servo_period,
       task_enc_period,
       task_recerve_data_period,

};

//函数指针数组存放函数
void (*TaskList[TASKS_MAX])(void)=
{
         task_servo,
         task_enc,
         task_recerve_data,

};


//定义结构体
static TASK_ITEM TaskItem[TASKS_MAX];

//每个任务初始化                      结构体指针             多久执行一次                任务函数
void Task_Item_init(TASK_ITEM *item,uint16 itvtime,void (*taskhood)(void))
{
    item->itvtime=itvtime;
    item->timer=itvtime;
    item->run=0;
    item->taskhood=taskhood;
}


//任务机制的初始化
void data_init()
{

    uint8 i;
    for(i=0;i<TASKS_MAX;i++)
    {
        Task_Item_init(&TaskItem[i], TimeList[i], TaskList[i]);
    }
}

/***************************************************************************
 * 任务标记函数
 * 这个函数放在定时中断里面，中断周期设置为1ms
***************************************************************************/
void TaskRemarks(void)
{
//    uart_write_string(UART_2, "TaskRemarks");
    uint8 i;
    for(i=0;i<TASKS_MAX;i++)
    {

        if(TaskItem[i].timer > 0)
        {
//            uart_write_string(UART_2, "timer > 0");
            TaskItem[i].timer--;
            if(TaskItem[i].timer==0)
            {
//                uart_write_string(UART_2, "run");
                TaskItem[i].timer=TaskItem[i].itvtime;
                TaskItem[i].run=1;
            }
        }
    }
}
/***************************************************************************
 * 任务执行函数
 * 这个函数直接放在while（1）里面
***************************************************************************/
void TaskProcess(void)
{

    if(mt9v03x_finish_flag)
    {
    mt9v03x_finish_flag=0;//不确定该行应该放在最前还是最后
    tft180_show_binary_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W / 2, MT9V03X_H / 2);//显示图像
    Image_Process(); //整个图像处理的主函数
    }


    mid_error_out = ImageStatus.Det_True;

    uint8 i;
    for(i=0;i<TASKS_MAX;i++)
    {
        if(TaskItem[i].run)
        {

            TaskItem[i].taskhood();
            TaskItem[i].run=0;
        }
    }
}

/*极值限制函数 传入地址*/
void ex_limit(int64* input, const int64 limit)
{
    zf_assert(limit > 0);   //限制值是个正数
    if(*input > limit)   *input = limit;
    if(*input < (-limit)) *input = -limit;
}

/*极值限制函数(浮点版)传入地址*/
void ex_limitf(double* input, const double limit)
{
    zf_assert(limit > 0);   //限制值是个正数
    if(*input > limit)   *input = limit;
    else if(*input < -limit) *input = -limit;
}

void pit_handler ()
{


    TaskRemarks();


}
