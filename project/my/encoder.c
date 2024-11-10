/*
 * encoder.c
 *
 *  Created on: 2024年10月24日
 *      Author: 27384
 */
#include "encoder.h"
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "low_fliter.h"
#include "tim.h"


//左边编码器引脚
//TIM2_ENCOEDER_MAP0_CH1_A0  = 0x1000 | A0,           // 0x 1[TIM2] 0[MAP0] 00[A0 ]
//TIM2_ENCOEDER_MAP0_CH2_A1  = 0x1000 | A1,           // 0x 1[TIM2] 0[MAP0] 01[A1 ]


//TIM4_ENCOEDER_MAP1_CH1_D12 = 0x3100 | D12,          // 0x 3[TIM4] 1[MAP1] 6C[D12]
//TIM4_ENCOEDER_MAP1_CH2_D13 = 0x3100 | D13,          // 0x 3[TIM4] 1[MAP1] 6D[D13]

filter_t encL_filter = {0};//低通滤波
filter_t encR_filter = {0};

/*  参数的配置 */
const float perimeter = 20.4f ; //后轮一圈的周长
const float cycle= (float)task_enc_period / 1000.0f;//0.005f;//测量的时间周期？？
uint32_t wheel_pulse=98;//后轮转一圈编码器的脉冲数  等下改1455


int32 Speed_Left;                                           //左轮速度
int32 Speed_Right;                                      //右轮速度

float Speed_Average;                    //单次比赛的平均速度，单位厘米
float Speed_Real;                       //真实速度（两轮取平均），单位厘米
float Speed_Right_Real;         //右轮真实速度
float Speed_Left_Real;          //左轮真实速度

float Speed_History[2][5];                      //速度记录数组。是个二维数组
float Speed_Filter = 0;                             //速度滤波后的值


void Encoder_init(void)
{
    encoder_quad_init(ENCODER_LEFT_QUADDEC, ENCODER_LEFT_QUADDEC_A, ENCODER_LEFT_QUADDEC_B);
    encoder_quad_init(ENCODER_RIGHT_QUADDEC, ENCODER_RIGHT_QUADDEC_A, ENCODER_RIGHT_QUADDEC_B);

    Low_Filter_Init(&encL_filter, 1000 / task_enc_period, 10);
    Low_Filter_Init(&encR_filter, 1000 / task_enc_period, 10);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       读取速度并处理
// @param       void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Speed_Measure()
{
    //临时变量
    float speed_right_last_temp;
    float speed_right_temp;
    float speed_left_last_temp;
    float speed_left_temp;

    float Speed_Left_Real_t;
    float Speed_Right_Real_t;
    speed_left_last_temp = (float)Speed_Left;
    speed_right_last_temp = (float)Speed_Right;

    speed_left_temp = encoder_get_count(ENCODER_LEFT_QUADDEC);
    speed_right_temp = encoder_get_count(ENCODER_RIGHT_QUADDEC);

//    tft180_show_float(1, 1, speed_left_temp, 2,2);
    //speed_left_temp /= 4;       //这里的4可以再调整，使得真实速度与当前速度更匹配
    //speed_right_temp /= 4;

    Speed_Left = (int32)speed_left_temp;//这个只是编码值
    Speed_Right = (int32)speed_right_temp;//这个只是编码值


//  Change_Limit(&speed_left_temp,&speed_left_last_temp,SPEED_CHANGE_LIMIT);
//  Change_Limit(&speed_right_temp,&speed_right_last_temp,SPEED_CHANGE_LIMIT);

    //转化为真实速度
    Speed_Left_Real_t  = ((float)Speed_Left / (float)wheel_pulse )* perimeter / cycle;
    Speed_Right_Real_t = -((float)Speed_Right / (float)wheel_pulse )* perimeter / cycle;
//    tft180_show_float(1, 16,Speed_Left_Real_t, 2,2);

//    Speed_Real += Speed_Left_Real_t * cycle;

    /*速度平滑滤波*/
    for(int i=0;i<4;i++)
    {
        Speed_History[0][i] = Speed_History[0][i+1];
        Speed_History[1][i] = Speed_History[1][i+1];
    }
    Speed_History[0][4] = (float)Speed_Left_Real_t;
    Speed_History[1][4] = (float)Speed_Right_Real_t;

    Speed_Left_Real = (0.1*Speed_History[0][0] + 0.1*Speed_History[0][1] + 0.1*Speed_History[0][2] + 0.25*Speed_History[0][3] + 0.45*Speed_History[0][4]);
    Speed_Right_Real = (0.1*Speed_History[1][0] + 0.1*Speed_History[1][1] + 0.1*Speed_History[1][2] + 0.25*Speed_History[1][3] + 0.45*Speed_History[1][4]);


    Speed_Left_Real = Low_Filter_Out(&encL_filter, Speed_Left_Real);
    Speed_Right_Real = Low_Filter_Out(&encR_filter, Speed_Right_Real);
    printf("%f,%f,%f\n",speed_right_temp,Speed_Right_Real_t,Speed_Right_Real);
//
//    Speed_Real += Speed_Left_Real;
    Speed_Real = (Speed_Right_Real + Speed_Left_Real)/2.0; //获取平均速度实际值（单位厘米）


    encoder_clear_count(ENCODER_LEFT_QUADDEC);
    encoder_clear_count(ENCODER_RIGHT_QUADDEC);

}





