/*
 * servo.c
 *
 *  Created on: 2024年10月23日
 *      Author: 27384
 */

#ifndef SERVO_C_
#define SERVO_C_

#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "low_fliter.h"
#include "servo.h"

//                              占空比为百分之 duty/PWM_DUTY_MAX *100
//                              PWM_DUTY_MAX在zf_pwm.h文件中 默认为10000
//duty 250---负90度
//duty 1250---90度

 float now_angle;
 float set_angle;

filter_t servo_angle_filter = {0};
//舵机的当前偏移量
int64 servo_offset = 0;
//设置数组存储的是0度时的占空比
int32 servo_offset_arr[3] = {750,750,750};

void servo_init()
{
    pwm_init(TIM3_PWM_MAP3_CH1_C6,100,750);
}

//舵机设置角度
void servo_setangle()
{
//    double duty = 5.56*angle+750;

    int16 offset_temp = servo_offset + 750;

    for(int i = 2; i > 0; i--)
    {
        servo_offset_arr[i] = servo_offset_arr[i - 1];
    }

    servo_offset_arr[0] = offset_temp;
    double duty=(uint32)( (servo_offset_arr[0]*40 / 100)+ (servo_offset_arr[1]*40 / 100)+ (servo_offset_arr[2]*20 / 100));

    pwm_set_duty(TIM3_PWM_MAP3_CH1_C6,duty);

}

#endif /* SERVO_C_ */
