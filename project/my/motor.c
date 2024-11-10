/*
 * motor.c
 *
 *  Created on: 2024��10��26��
 *      Author: 27384
 */

#ifndef MOTOR_C_
#define MOTOR_C_
#include "low_fliter.h"
#include "zf_common_headfile.h"

#define L1 TIM1_PWM_MAP3_CH1_E9
#define L2 TIM1_PWM_MAP3_CH2_E11
#define R1 TIM1_PWM_MAP3_CH3_E13
#define R2 TIM1_PWM_MAP3_CH4_E14

filter_t motorL_current_filter = {0};//�⻷����˲�
filter_t motorR_current_filter = {0};

//Ŀ���ٶ�
float LMotor_TagSpeed = 0.0;
float RMotor_TagSpeed = 0.0;
//ռ�ձ�
int16 LMotor_Duty = 0;
int16 LMotor_Duty_hubu = 0;
int16 RMotor_Duty = 0;
//ռ�ձ�����
int16 LMotor_Duty_arr[5] = {0};
int16 RMotor_Duty_arr[5] = {0};
//�趨ռ�ձ�
int16 LDuty_set = 0;
int16 RDuty_set = 0;


void Motor_init()//ռ�ձ��Ƕ��٣��͵�ƽռ�ٷֱȾ��Ƕ���
{
    pwm_init(L1, 15000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 15KHz ��ʼռ�ձ� 0%
    pwm_init(L2, 15000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 15KHz ��ʼռ�ձ� 0%
    pwm_init(R1, 15000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 15KHz ��ʼռ�ձ� 0%
    pwm_init(R2, 15000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 15KHz ��ʼռ�ձ� 0%

}


//ͨ��Ŀ��ռ�ձȿ��Ƶ���ٶȣ��ó�Ŀ��ռ�ձȵĺ�����task.c��
void motor_control()
{
    for(int i = 4; i > 0; i--)
    {
        LMotor_Duty_arr[i] = LMotor_Duty_arr[i - 1];
        RMotor_Duty_arr[i] = RMotor_Duty_arr[i - 1];
    }

    LMotor_Duty_arr[0] = LMotor_Duty;
    RMotor_Duty_arr[0] = RMotor_Duty;

    int16 LDuty_set = (LMotor_Duty_arr[0]*20 / 100) + (LMotor_Duty_arr[1]*30 / 100)+ (LMotor_Duty_arr[2]*20 / 100)
                        + (LMotor_Duty_arr[3]*20 / 100) + (LMotor_Duty_arr[4]*10 / 100);
    int16 RDuty_set = (RMotor_Duty_arr[0]*20 / 100) + (RMotor_Duty_arr[1]*30 / 100)+ (RMotor_Duty_arr[2]*20 / 100)
                        + (RMotor_Duty_arr[3]*20 / 100) + (RMotor_Duty_arr[4]*10 / 100);

}




#endif /* MOTOR_C_ */
