/*
 * low_fliter.h
 *
 *  Created on: 2024��10��24��
 *      Author: 27384
 */

#ifndef LOW_FLITER_H_
#define LOW_FLITER_H_

#define My_2PI 6.2831853071796//2pi
/* ��ͨ�˲����ṹ�� */
typedef struct
{
    float sample_freq;              //�����ź�Ƶ��
    float cutoff_freq;     //��ֹƵ��
    float alpha;           //�˲�ϵ��
    float pre_out;          //��һ�����
    float now_out;           //��ͨ�˲������
}filter_t;

/*�������˲��ṹ�壨һ�ף�*/
typedef struct
{
    float Last_P;//�ϴι���Э���� ������Ϊ0 ! ! ! ! !
    float Now_P;//��ǰ����Э����
    float out;//�������˲������
    float Kg;//����������
    float Q;//��������Э����
    float R;//�۲�����Э����
}Kalman;



void Low_Filter_Init(filter_t* filter, float sample_freq, float cutoff_freq);
float Low_Filter_Out(filter_t* filter, float sample);

void Kalman_Init(void);
float KalmanFilter(Kalman* kfp, float input);

extern Kalman kfp;

#endif /* LOW_FLITER_H_ */
