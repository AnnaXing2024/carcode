/*
 * encoder.h
 *
 *  Created on: 2024��10��24��
 *      Author: 27384
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "low_fliter.h"

extern float perimete; //����һȦ���ܳ�
extern const float cycle;//0.005f;��
extern uint32_t wheel_pulse;//����תһȦ��������������  ���¸�1455

#define ENCODER_LEFT_QUADDEC                 (TIM2_ENCOEDER)
#define ENCODER_LEFT_QUADDEC_A               (TIM2_ENCOEDER_MAP0_CH1_A0)
#define ENCODER_LEFT_QUADDEC_B               (TIM2_ENCOEDER_MAP0_CH2_A1)


#define ENCODER_RIGHT_QUADDEC                 (TIM4_ENCOEDER)
#define ENCODER_RIGHT_QUADDEC_A               (TIM4_ENCOEDER_MAP1_CH1_D12)
#define ENCODER_RIGHT_QUADDEC_B               (TIM4_ENCOEDER_MAP1_CH2_D13)

extern float Speed_Average;                    //���α�����ƽ���ٶȣ���λ����

extern float Speed_Right_Real;         //������ʵ�ٶ�
extern float Speed_Left_Real;          //������ʵ�ٶ�

extern float Speed_Real;                       //��ʵ�ٶȣ�����ȡƽ��������λ����

extern filter_t encL_filter;//��ͨ�˲�
extern filter_t encR_filter;

extern void Encoder_init(void);
//extern void Encoder_get(void);
extern void Speed_Measure(void);


#endif /* ENCODER_H_ */
