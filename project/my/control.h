/*
 * control.h
 *
 *  Created on: 2024��10��23��
 *      Author: 27384
 */

#ifndef CONTROL_H_
#define CONTROL_H_

extern float mid_error_out ;//�¼� cpu1

typedef struct
{
    uint8 run;                  //���б�ǣ�0�����У�1����
    uint16 timer;                //��ʱ������һֱ������0��֮���λ
    uint16 itvtime;              //��ʱ��Ĭ��ֵ����λ:ms
    void (*taskhood)(void);     //������ָ��
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
/*��ֵ���ƺ���(�����)�����ַ*/
void ex_limitf(double* input, const double limit);

#define USE_ENCODER 1
#define USE_UART 1
#define USE_SERVO 1
#define USE_TFT180 1
#define USE_KALMAN 0
#define USE_DMA 0
#define USE_MOTOR 1

#endif /* CONTROL_H_ */
