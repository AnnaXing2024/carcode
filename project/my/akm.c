/*
 * akm.c
 *
 *  Created on: 2024年10月26日
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "low_fliter.h"
#include "akm.h"
#include "servo.h"
#include "encoder.h"

//阿克曼角差速相关变量
//float EDS_Coefficient_Out,EDS_Coefficient_In;
float angle_t=0.0;//舵机当前的角度，初始化为0。
const float Dif= 1000 / 180;//舵机的角度换算
float Dif_array_out[3]={0.0,0.0,0.0};//存储输出角度差的数组
float Dif_array_in[3]={0.0,0.0,0.0};//存储输入角度差的数组
const float B_w = 15.5;//车辆的轮距
const float L_l = 15.0;//车辆的轴距
float tann=0.0;

float speedL_set = 0;//左电机的目标速度
float speedR_set = 0;//右电机的目标速度

//目标电流
double currentL_set = 0;
double currentR_set = 0;

//左为外侧轮，右为内侧轮
diff_speed_t straight_diff_speed = {0, 0};//直行时的速度差
diff_speed_t curve_diff_speed = {0, 8};//曲线行驶时的速度差
diff_speed_t turn_diff_speed = {0, 7};//转弯时的速度差
diff_speed_t circle_diff_speed = {0, 6.6};//圆形行驶时的速度差

//-------------------------------------------------------------------------------------------------------------------
//  @brief      差速控制
//  @param      void
//  @return     void
//  @note       阿克曼公式法  内轮：V_left=V*(1-(tanα)*B/2L)    外轮：V_right=V*(1+(tanα)*B/2L)   B/2=7.75   L=21
//-------------------------------------------------------------------------------------------------------------------
//阿克曼公式法(其实把需要的速度给算出来了)
void Differ_speed(float speedset,float EDS_Coefficient_Out,float EDS_Coefficient_In)//后两个参数是舵机打角与轮转向角之间的系数
{
     Dif_array_out[2]=Dif_array_out[1];
     Dif_array_out[1]=Dif_array_out[0];

     Dif_array_in[2]=Dif_array_in[1];
     Dif_array_in[1]=Dif_array_in[0];

     //把舵机角度偏移量转换为轮子偏移量
     angle_t = (float)servo_offset / Dif;


     if(angle_t<=-9.1f) {angle_t=-9.1f;}
     if(angle_t>=9.1f) {angle_t=9.1f;}

     Dif_array_out[0]=  B_w / (2*L_l) * (float)tan ((double)EDS_Coefficient_Out * (double)angle_t * 0.017) * Speed_Real;
     Dif_array_in[0]=  B_w / (2*L_l) * (float)tan ((double)EDS_Coefficient_In * (double)angle_t * 0.017) * Speed_Real;

    /************对差速进行限幅*****************/
    if(Dif_array_out[0] > EDS_OUT_LIMIT)   Dif_array_out[0] = EDS_OUT_LIMIT;
    if(Dif_array_out[0] < -EDS_OUT_LIMIT)   Dif_array_out[0] = -EDS_OUT_LIMIT;

    if(Dif_array_in[0] > EDS_IN_LIMIT)   Dif_array_in[0] = EDS_IN_LIMIT;
    if(Dif_array_in[0] < -EDS_IN_LIMIT)   Dif_array_in[0] = -EDS_IN_LIMIT;
    /***********************/

     if(angle_t>0)                //左转
        {
            speedR_set=speedset+(Dif_array_out[0]*0.4f+Dif_array_out[1]*0.4f+Dif_array_out[2]*0.2f);
            speedL_set=speedset-(Dif_array_in[0]*0.4f+Dif_array_in[1]*0.4f+Dif_array_in[2]*0.2f);
        }
        else if (angle_t<0)        //右转
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



