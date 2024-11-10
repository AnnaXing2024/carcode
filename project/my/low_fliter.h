/*
 * low_fliter.h
 *
 *  Created on: 2024年10月24日
 *      Author: 27384
 */

#ifndef LOW_FLITER_H_
#define LOW_FLITER_H_

#define My_2PI 6.2831853071796//2pi
/* 低通滤波器结构体 */
typedef struct
{
    float sample_freq;              //输入信号频率
    float cutoff_freq;     //截止频率
    float alpha;           //滤波系数
    float pre_out;          //上一次输出
    float now_out;           //低通滤波器输出
}filter_t;

/*卡尔曼滤波结构体（一阶）*/
typedef struct
{
    float Last_P;//上次估算协方差 不可以为0 ! ! ! ! !
    float Now_P;//当前估算协方差
    float out;//卡尔曼滤波器输出
    float Kg;//卡尔曼增益
    float Q;//过程噪声协方差
    float R;//观测噪声协方差
}Kalman;



void Low_Filter_Init(filter_t* filter, float sample_freq, float cutoff_freq);
float Low_Filter_Out(filter_t* filter, float sample);

void Kalman_Init(void);
float KalmanFilter(Kalman* kfp, float input);

extern Kalman kfp;

#endif /* LOW_FLITER_H_ */
