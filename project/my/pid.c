/*
 * pid.c
 *
 *  Created on: 2024年10月24日
 *      Author: 27384
 */
#include "pid.h"
#include "math.h"

PID_Str servo_pid;//方向内环
PID_Str angle_pid;//方向外环
PID_Str motorL_pid;
PID_Str motorR_pid;
PID_Str currentL_pid;
PID_Str currentR_pid;

//初始化pid结构体
void PID_init(PID_Str* PID)
{
    PID->P=0;         //参数
    PID->I=0;
    PID->D=0;
    PID->K_FF = 0;
    PID->T_FF = 0;

    PID->I_range=0;       //积分分离范围
    PID->IOut_limit=0;   //积分限幅


    /*不需要配置的*/
    PID->Error=0;       //比例项/误差
    PID->PreError=0;     //上一次误差
    PID->PrePreError=0; //上上次误差

    PID->Integral=0;    //积分项
    PID->Differ=0;      //微分项

    PID->Pout=0;        //比例项输出
    PID->Iout=0;        //积分项输出
    PID->Dout=0;        //微分项输出
    PID->FFout = 0;
    PID->Output=0;       //PID控制器总输出
}

void PID_value(void)
{
    //p = 38.4 * arccot(cot(kout*9.1) - 7.75) = 6464.6644
    servo_pid.P = 5.8 /*14*/;//方向内环

    angle_pid.P = 2.7;//方向外环//1.9
    angle_pid.D = 10/*2.5*/;//2.95


    motorL_pid.P =  0.04;
    motorL_pid.I =  0.0003;
//    motorL_pid.D = 0.001;
    motorL_pid.I_EnableFlag = 1;
    motorL_pid.IOut_limit = 5.0;
    motorL_pid.I_range   = 200;



    motorR_pid.P =  0.04;
    motorR_pid.I =  0.0003;
//    motorR_pid.D = 0.001;
    motorR_pid.I_EnableFlag = 1;
    motorR_pid.IOut_limit = 5.0;
    motorR_pid.I_range   = 200;


    /*已调好*/
    currentL_pid.I = 100;//速度内环
    currentL_pid.P = 2500;
    currentL_pid.I_EnableFlag = 1;
    currentL_pid.IOut_limit = 6000;
    currentL_pid.I_range   = 10;

    currentR_pid.I = 100;
    currentR_pid.P = 2500;
    currentR_pid.I_EnableFlag = 1;
    currentR_pid.IOut_limit = 6000;
    currentR_pid.I_range   = 10;

}
/*****************************************************************************
* 函  数：void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
* 功  能：位置式PID算法
* 参  数：PID: PID控制器的结构体
*         target: 目标值
*         measure: 测量值
* 返回值：无
* 备  注:
*****************************************************************************/
void PID_Postion_Cal(PID_Str* PID, float target, float measure)
{
     /*对历史误差进行保存*/
    PID->PrePreError = PID->PreError;   //更新上上次误差
    PID->PreError = PID->Error;         //更新上次误差

    /*计算误差（比例量）与微分量*/
    PID->Error  = target - measure;              //计算误差
    PID->Differ = PID->Error - PID->PreError;    //计算微分量


    /*计算积分量*/
    if(PID->I_EnableFlag == 1)
    {
        if(PID->Error < (PID->I_range) && PID->Error > -PID->I_range)   //积分分离：只有在误差接近稳态范围时才加入积分控制
        {
            PID->Integral += PID->Error;                        //对误差进行积分

            /*积分项限幅，作用相当于是对积分输出限幅了*/
            if(fabs ((double)(PID->I)) > 0.000001)
            {   /*如果Ki参数不为0.则进入此*/
                if(PID->Integral > PID->IOut_limit/PID->I)  PID->Integral = PID->IOut_limit/PID->I ;
                if(PID->Integral < -PID->IOut_limit/PID->I)  PID->Integral = -PID->IOut_limit/PID->I ;
            }
        }
        else
        {
            PID->Integral = 0;
        }
    }else
    {PID->Integral = 0;}

    /*计算控制量*/
    PID->Pout = PID->P * PID->Error;                        //比例输出
    PID->Iout = PID->I_EnableFlag * PID->I * PID->Integral;  //积分输出
    PID->Dout = PID->D * PID->Differ;                       //微分输出


    PID->Output =  PID->Pout + PID->Iout + PID->Dout;       //比例 + 积分 + 微分 总输出控制量


}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介          pid增量式控制器输出
// 返回类型          PID输出结果
// 使用示例          PID_Increment_Cal(&pid, float target, float measure)
// 备注信息          注意输出结果已经包涵了上次结果
//-------------------------------------------------------------------------------------------------------------------
void PID_Increment_Cal(PID_Str* PID, float target, float measure)
{


   /*计算误差（比例量）与微分量*/
   PID->Error  = target - measure;              //计算误差


    PID->Pout =  PID->P * (PID->Error - PID->PreError);
    PID->Iout = PID->I *  PID->Error;
    PID->Dout = PID->D * (PID->Error - 2*PID->PreError + PID->PrePreError);

    PID->PrePreError = PID->PreError;
    PID->PreError = PID->Error;

    PID->Output += PID->Pout + PID->Iout + PID->Dout;


}
