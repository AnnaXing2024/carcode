/*
 * pid.h
 *
 *  Created on: 2024年10月24日
 *      Author: 27384
 */

#ifndef PID_H_
#define PID_H_

typedef struct
{

    float P;         //pid系数
    float I;
    float D;
    float K_FF;     // 前馈增益系数
    float T_FF;     // 前馈时间常数

    float I_range;       // 积分范围限制
    float IOut_limit;   // 积分输出限制


    /* PID 计算相关 */
    float Error;       // 当前误差（当前值 - 目标值）
    float PreError;     // 上一次误差（用于计算微分）
    float PrePreError; // 前一次误差（用于更高阶微分，可能用于防止抖动）

    float Integral;    // 积分项
    float Differ;      // 积分项


    float Pout;        // 比例输出
    float Iout;        // 积分输出
    float Dout;        // 微分输出
    float FFout;        // 前馈输出
    float Output;        // PID控制器最终输出值（P + I + D + FF）


    /*???λ*/
    unsigned char I_EnableFlag;// 积分使能标志，指示是否启用积分计算
} PID_Str ;

//-----------PID------------

extern PID_Str servo_pid;
extern PID_Str angle_pid;
extern PID_Str motorL_pid;
extern PID_Str motorR_pid;
extern PID_Str currentL_pid;
extern PID_Str currentR_pid;


extern void PID_value(void);
extern void PID_init(PID_Str* PID);
extern void PID_Postion_Cal(PID_Str* PID,float target,float measure);         //λ???PID
extern void PID_Increment_cal(PID_Str* PID,float target,float measure);      //?????PID
extern void PID_Param_Switch(PID_Str* Src_PID, PID_Str* Trg_PID);

#endif /* PID_H_ */
