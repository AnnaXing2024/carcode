/*
 * pid.h
 *
 *  Created on: 2024��10��24��
 *      Author: 27384
 */

#ifndef PID_H_
#define PID_H_

typedef struct
{

    float P;         //pidϵ��
    float I;
    float D;
    float K_FF;     // ǰ������ϵ��
    float T_FF;     // ǰ��ʱ�䳣��

    float I_range;       // ���ַ�Χ����
    float IOut_limit;   // �����������


    /* PID ������� */
    float Error;       // ��ǰ����ǰֵ - Ŀ��ֵ��
    float PreError;     // ��һ�������ڼ���΢�֣�
    float PrePreError; // ǰһ�������ڸ��߽�΢�֣��������ڷ�ֹ������

    float Integral;    // ������
    float Differ;      // ������


    float Pout;        // �������
    float Iout;        // �������
    float Dout;        // ΢�����
    float FFout;        // ǰ�����
    float Output;        // PID�������������ֵ��P + I + D + FF��


    /*???��*/
    unsigned char I_EnableFlag;// ����ʹ�ܱ�־��ָʾ�Ƿ����û��ּ���
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
extern void PID_Postion_Cal(PID_Str* PID,float target,float measure);         //��???PID
extern void PID_Increment_cal(PID_Str* PID,float target,float measure);      //?????PID
extern void PID_Param_Switch(PID_Str* Src_PID, PID_Str* Trg_PID);

#endif /* PID_H_ */
