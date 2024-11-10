/*
 * control.c
 *
 *  Created on: 2024��10��23��
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "control.h"
#include "tim.h"
#include "task.h"
#include "uart.h"
#include "zf_device_mt9v03x_dvp.h"// �¼�

float mid_error_out = 0;//�¼� cpu1

//��ӻ�ɾ���������޸ģ�
//TimeList�������飻
//(*TaskList[TASKS_MAX])����ָ�����飻
//tim.h����������ڣ�
//λ��control.h��TASK_LIST�ṹ�尴˳�������������;
//����˳����뱣��һ�£�


//�������ִ�����ڵ�����
//Ҫ�滮�߳�ʱ��Ļ��� tim.h ����д���궨��
uint16 TimeList[TASKS_MAX]=
{
       task_servo_period,
       task_enc_period,
       task_recerve_data_period,

};

//����ָ�������ź���
void (*TaskList[TASKS_MAX])(void)=
{
         task_servo,
         task_enc,
         task_recerve_data,

};


//����ṹ��
static TASK_ITEM TaskItem[TASKS_MAX];

//ÿ�������ʼ��                      �ṹ��ָ��             ���ִ��һ��                ������
void Task_Item_init(TASK_ITEM *item,uint16 itvtime,void (*taskhood)(void))
{
    item->itvtime=itvtime;
    item->timer=itvtime;
    item->run=0;
    item->taskhood=taskhood;
}


//������Ƶĳ�ʼ��
void data_init()
{

    uint8 i;
    for(i=0;i<TASKS_MAX;i++)
    {
        Task_Item_init(&TaskItem[i], TimeList[i], TaskList[i]);
    }
}

/***************************************************************************
 * �����Ǻ���
 * ����������ڶ�ʱ�ж����棬�ж���������Ϊ1ms
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
 * ����ִ�к���
 * �������ֱ�ӷ���while��1������
***************************************************************************/
void TaskProcess(void)
{

    if(mt9v03x_finish_flag)
    {
    mt9v03x_finish_flag=0;//��ȷ������Ӧ�÷�����ǰ�������
    tft180_show_binary_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W / 2, MT9V03X_H / 2);//��ʾͼ��
    Image_Process(); //����ͼ�����������
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

/*��ֵ���ƺ��� �����ַ*/
void ex_limit(int64* input, const int64 limit)
{
    zf_assert(limit > 0);   //����ֵ�Ǹ�����
    if(*input > limit)   *input = limit;
    if(*input < (-limit)) *input = -limit;
}

/*��ֵ���ƺ���(�����)�����ַ*/
void ex_limitf(double* input, const double limit)
{
    zf_assert(limit > 0);   //����ֵ�Ǹ�����
    if(*input > limit)   *input = limit;
    else if(*input < -limit) *input = -limit;
}

void pit_handler ()
{


    TaskRemarks();


}
