/*
 * akm.c
 *
 *  Created on: 2024��10��26��
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "low_fliter.h"
#include "akm.h"
#include "servo.h"
#include "encoder.h"

//�������ǲ�����ر���
//float EDS_Coefficient_Out,EDS_Coefficient_In;
float angle_t=0.0;//�����ǰ�ĽǶȣ���ʼ��Ϊ0��
const float Dif= 1000 / 180;//����ĽǶȻ���
float Dif_array_out[3]={0.0,0.0,0.0};//�洢����ǶȲ������
float Dif_array_in[3]={0.0,0.0,0.0};//�洢����ǶȲ������
const float B_w = 15.5;//�������־�
const float L_l = 15.0;//���������
float tann=0.0;

float speedL_set = 0;//������Ŀ���ٶ�
float speedR_set = 0;//�ҵ����Ŀ���ٶ�

//Ŀ�����
double currentL_set = 0;
double currentR_set = 0;

//��Ϊ����֣���Ϊ�ڲ���
diff_speed_t straight_diff_speed = {0, 0};//ֱ��ʱ���ٶȲ�
diff_speed_t curve_diff_speed = {0, 8};//������ʻʱ���ٶȲ�
diff_speed_t turn_diff_speed = {0, 7};//ת��ʱ���ٶȲ�
diff_speed_t circle_diff_speed = {0, 6.6};//Բ����ʻʱ���ٶȲ�

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ٿ���
//  @param      void
//  @return     void
//  @note       ��������ʽ��  ���֣�V_left=V*(1-(tan��)*B/2L)    ���֣�V_right=V*(1+(tan��)*B/2L)   B/2=7.75   L=21
//-------------------------------------------------------------------------------------------------------------------
//��������ʽ��(��ʵ����Ҫ���ٶȸ��������)
void Differ_speed(float speedset,float EDS_Coefficient_Out,float EDS_Coefficient_In)//�����������Ƕ���������ת���֮���ϵ��
{
     Dif_array_out[2]=Dif_array_out[1];
     Dif_array_out[1]=Dif_array_out[0];

     Dif_array_in[2]=Dif_array_in[1];
     Dif_array_in[1]=Dif_array_in[0];

     //�Ѷ���Ƕ�ƫ����ת��Ϊ����ƫ����
     angle_t = (float)servo_offset / Dif;


     if(angle_t<=-9.1f) {angle_t=-9.1f;}
     if(angle_t>=9.1f) {angle_t=9.1f;}

     Dif_array_out[0]=  B_w / (2*L_l) * (float)tan ((double)EDS_Coefficient_Out * (double)angle_t * 0.017) * Speed_Real;
     Dif_array_in[0]=  B_w / (2*L_l) * (float)tan ((double)EDS_Coefficient_In * (double)angle_t * 0.017) * Speed_Real;

    /************�Բ��ٽ����޷�*****************/
    if(Dif_array_out[0] > EDS_OUT_LIMIT)   Dif_array_out[0] = EDS_OUT_LIMIT;
    if(Dif_array_out[0] < -EDS_OUT_LIMIT)   Dif_array_out[0] = -EDS_OUT_LIMIT;

    if(Dif_array_in[0] > EDS_IN_LIMIT)   Dif_array_in[0] = EDS_IN_LIMIT;
    if(Dif_array_in[0] < -EDS_IN_LIMIT)   Dif_array_in[0] = -EDS_IN_LIMIT;
    /***********************/

     if(angle_t>0)                //��ת
        {
            speedR_set=speedset+(Dif_array_out[0]*0.4f+Dif_array_out[1]*0.4f+Dif_array_out[2]*0.2f);
            speedL_set=speedset-(Dif_array_in[0]*0.4f+Dif_array_in[1]*0.4f+Dif_array_in[2]*0.2f);
        }
        else if (angle_t<0)        //��ת
        {
            speedL_set=speedset-(Dif_array_out[0]*0.4f+Dif_array_out[1]*0.4f+Dif_array_out[2]*0.2f);
            speedR_set=speedset+(Dif_array_in[0]*0.4f+Dif_array_in[1]*0.4f+Dif_array_in[2]*0.2f);
        }
        else
        {
            speedR_set=speedset;
            speedL_set=speedset;
        }
}



