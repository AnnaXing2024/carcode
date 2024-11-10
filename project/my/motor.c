/*
 * motor.c
 *
 *  Created on: 2024年10月26日
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

filter_t motorL_current_filter = {0};//外环输出滤波
filter_t motorR_current_filter = {0};

//目标速度
float LMotor_TagSpeed = 0.0;
float RMotor_TagSpeed = 0.0;
//占空比
int16 LMotor_Duty = 0;
int16 LMotor_Duty_hubu = 0;
int16 RMotor_Duty = 0;
//占空比数组
int16 LMotor_Duty_arr[5] = {0};
int16 RMotor_Duty_arr[5] = {0};
//设定占空比
int16 LDuty_set = 0;
int16 RDuty_set = 0;


void Motor_init()//占空比是多少，低电平占百分比就是多少
{
    pwm_init(L1, 15000, 0);                                                // 初始化 PWM 通道 频率 15KHz 初始占空比 0%
    pwm_init(L2, 15000, 0);                                                // 初始化 PWM 通道 频率 15KHz 初始占空比 0%
    pwm_init(R1, 15000, 0);                                                // 初始化 PWM 通道 频率 15KHz 初始占空比 0%
    pwm_init(R2, 15000, 0);                                                // 初始化 PWM 通道 频率 15KHz 初始占空比 0%

}


//通过目标占空比控制电机速度，得出目标占空比的函数在task.c中
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
