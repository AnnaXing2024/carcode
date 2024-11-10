/*
 * low_fiter.c
 *
 *  Created on: 2024年10月24日
 *      Author: 27384
 */

#include "low_fliter.h"

// 初始化低通滤波器
void Low_Filter_Init(filter_t* filter,float sample_freq,float cutoff_freq)
{
    filter->sample_freq = sample_freq;
    filter->cutoff_freq = cutoff_freq;
    filter->pre_out = 0.0f;
    filter->now_out = 0.0f;
    if(filter->sample_freq <= 0.0f || filter->cutoff_freq <= 0.0f)
        filter->alpha=1;  //滤波已经无意义了
    else
    {
        float dt = 1.0f/filter->sample_freq;  //得到采样周期
      float rc = 1.0f/(My_2PI*filter->cutoff_freq); //通过截至频率计算RC的值
      filter->alpha = dt/(dt+rc);
        filter->alpha<0.0f?filter->alpha=0:(filter->alpha>1.0f?filter->alpha=1:filter->alpha);
        //对系数限幅
    }
}

//得到此次输出值
float Low_Filter_Out(filter_t* filter,float sample)
{
    filter->pre_out = filter->now_out;
    filter->now_out = filter->alpha*sample + (1.0f - filter->alpha)*filter->pre_out;
    return filter->now_out;
}

Kalman kfp;

void Kalman_Init()
{
    kfp.Last_P = 0.02;
    kfp.Now_P = 0;
    kfp.out = 0;
    kfp.Kg = 100;
    kfp.Q = 7e-5;
    kfp.R = 3e-4;
}

/**
 *卡尔曼滤波器
 *@param    Kalman *kfp 卡尔曼结构体参数
 *              float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float KalmanFilter(Kalman *kfp,float input)
{
   //预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
   kfp->Now_P = kfp->Last_P + kfp->Q;


   //卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
   kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);


   //更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
   kfp->out = kfp->out + kfp->Kg * (input -kfp->out);//因为这一次的预测值就是上一次的输出值


   //更新协方差方程: 本次的系统协方差付给 kfp->LastP 为下一次运算准备。
   kfp->Last_P = (1-kfp->Kg) * kfp->Now_P;


   return kfp->out;
}
