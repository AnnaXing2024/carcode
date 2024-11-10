/*
 * encoder.h
 *
 *  Created on: 2024年10月24日
 *      Author: 27384
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "low_fliter.h"

extern float perimete; //后轮一圈的周长
extern const float cycle;//0.005f;？
extern uint32_t wheel_pulse;//后轮转一圈编码器的脉冲数  等下改1455

#define ENCODER_LEFT_QUADDEC                 (TIM2_ENCOEDER)
#define ENCODER_LEFT_QUADDEC_A               (TIM2_ENCOEDER_MAP0_CH1_A0)
#define ENCODER_LEFT_QUADDEC_B               (TIM2_ENCOEDER_MAP0_CH2_A1)


#define ENCODER_RIGHT_QUADDEC                 (TIM4_ENCOEDER)
#define ENCODER_RIGHT_QUADDEC_A               (TIM4_ENCOEDER_MAP1_CH1_D12)
#define ENCODER_RIGHT_QUADDEC_B               (TIM4_ENCOEDER_MAP1_CH2_D13)

extern float Speed_Average;                    //单次比赛的平均速度，单位厘米

extern float Speed_Right_Real;         //右轮真实速度
extern float Speed_Left_Real;          //左轮真实速度

extern float Speed_Real;                       //真实速度（两轮取平均），单位厘米

extern filter_t encL_filter;//低通滤波
extern filter_t encR_filter;

extern void Encoder_init(void);
//extern void Encoder_get(void);
extern void Speed_Measure(void);


#endif /* ENCODER_H_ */
