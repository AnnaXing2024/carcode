/*
 * low_fiter.c
 *
 *  Created on: 2024��10��24��
 *      Author: 27384
 */

#include "low_fliter.h"

// ��ʼ����ͨ�˲���
void Low_Filter_Init(filter_t* filter,float sample_freq,float cutoff_freq)
{
    filter->sample_freq = sample_freq;
    filter->cutoff_freq = cutoff_freq;
    filter->pre_out = 0.0f;
    filter->now_out = 0.0f;
    if(filter->sample_freq <= 0.0f || filter->cutoff_freq <= 0.0f)
        filter->alpha=1;  //�˲��Ѿ���������
    else
    {
        float dt = 1.0f/filter->sample_freq;  //�õ���������
      float rc = 1.0f/(My_2PI*filter->cutoff_freq); //ͨ������Ƶ�ʼ���RC��ֵ
      filter->alpha = dt/(dt+rc);
        filter->alpha<0.0f?filter->alpha=0:(filter->alpha>1.0f?filter->alpha=1:filter->alpha);
        //��ϵ���޷�
    }
}

//�õ��˴����ֵ
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
 *�������˲���
 *@param    Kalman *kfp �������ṹ�����
 *              float input ��Ҫ�˲��Ĳ����Ĳ���ֵ�����������Ĳɼ�ֵ��
 *@return �˲���Ĳ���������ֵ��
 */
float KalmanFilter(Kalman *kfp,float input)
{
   //Ԥ��Э����̣�kʱ��ϵͳ����Э���� = k-1ʱ�̵�ϵͳЭ���� + ��������Э����
   kfp->Now_P = kfp->Last_P + kfp->Q;


   //���������淽�̣����������� = kʱ��ϵͳ����Э���� / ��kʱ��ϵͳ����Э���� + �۲�����Э���
   kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);


   //��������ֵ���̣�kʱ��״̬����������ֵ = ״̬������Ԥ��ֵ + ���������� * ������ֵ - ״̬������Ԥ��ֵ��
   kfp->out = kfp->out + kfp->Kg * (input -kfp->out);//��Ϊ��һ�ε�Ԥ��ֵ������һ�ε����ֵ


   //����Э�����: ���ε�ϵͳЭ����� kfp->LastP Ϊ��һ������׼����
   kfp->Last_P = (1-kfp->Kg) * kfp->Now_P;


   return kfp->out;
}
