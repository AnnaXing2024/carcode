/*
 * task.c
 *
 *  Created on: 2024年10月26日
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "servo.h"
#include "encoder.h"
#include "uart.h"
#include "task.h"
#include "pid.h"
#include "control.h"
#include "zf_device_mt9v03x_dvp.h"
//方向内环
void task_servo()
{

    PID_Postion_Cal(&servo_pid, set_angle, now_angle);
    tft180_show_float(1, 140, mid_error_out, 2, 4);

    servo_offset = Low_Filter_Out(&servo_angle_filter, -servo_pid.Output);
    servo_setangle();


}

void task_enc()
{
//    uart_write_string(UART_2, "task_enc");
    Speed_Measure();
}

void task_recerve_data()
{

    usart_receive();
}


void task_speed_cal()//速度内环
{

}

