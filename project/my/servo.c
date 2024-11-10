/*
 * servo.c
 *
 *  Created on: 2024��10��23��
 *      Author: 27384
 */

#ifndef SERVO_C_
#define SERVO_C_

#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "low_fliter.h"
#include "servo.h"

//                              ռ�ձ�Ϊ�ٷ�֮ duty/PWM_DUTY_MAX *100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ10000
//duty 250---��90��
//duty 1250---90��

 float now_angle;
 float set_angle;

filter_t servo_angle_filter = {0};
//����ĵ�ǰƫ����
int64 servo_offset = 0;
//��������洢����0��ʱ��ռ�ձ�
int32 servo_offset_arr[3] = {750,750,750};

void servo_init()
{
    pwm_init(TIM3_PWM_MAP3_CH1_C6,100,750);
}

//������ýǶ�
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
