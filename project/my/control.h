/*
 * control.h
 *
 *  Created on: 2024年10月23日
 *      Author: 27384
 */

#ifndef CONTROL_H_
#define CONTROL_H_

extern float mid_error_out ;//新加 cpu1

typedef struct
{
    uint8 run;                  //运行标记，0不运行，1运行
    uint16 timer;                //计时器，会一直倒数到0，之后归位
    uint16 itvtime;              //计时器默认值，单位:ms
    void (*taskhood)(void);     //任务函数指针
}TASK_ITEM;


typedef enum
{

    TASK_SERVO,
    TASK_ENC,
    TASK_RECEIVE_DATA,

    TASKS_MAX
}TASK_LIST;


void TaskProcess(void);
void data_init();
void ex_limit(int64* input, const int64 limit);
/*极值限制函数(浮点版)传入地址*/
void ex_limitf(double* input, const double limit);

#define USE_ENCODER 1
#define USE_UART 1
#define USE_SERVO 1
#define USE_TFT180 1
#define USE_KALMAN 0
#define USE_DMA 0
#define USE_MOTOR 1

#endif /* CONTROL_H_ */
