/*
 * pid.c
 *
 *  Created on: 2024��10��24��
 *      Author: 27384
 */
#include "pid.h"
#include "math.h"

PID_Str servo_pid;//�����ڻ�
PID_Str angle_pid;//�����⻷
PID_Str motorL_pid;
PID_Str motorR_pid;
PID_Str currentL_pid;
PID_Str currentR_pid;

//��ʼ��pid�ṹ��
void PID_init(PID_Str* PID)
{
    PID->P=0;         //����
    PID->I=0;
    PID->D=0;
    PID->K_FF = 0;
    PID->T_FF = 0;

    PID->I_range=0;       //���ַ��뷶Χ
    PID->IOut_limit=0;   //�����޷�


    /*����Ҫ���õ�*/
    PID->Error=0;       //������/���
    PID->PreError=0;     //��һ�����
    PID->PrePreError=0; //���ϴ����

    PID->Integral=0;    //������
    PID->Differ=0;      //΢����

    PID->Pout=0;        //���������
    PID->Iout=0;        //���������
    PID->Dout=0;        //΢�������
    PID->FFout = 0;
    PID->Output=0;       //PID�����������
}

void PID_value(void)
{
    //p = 38.4 * arccot(cot(kout*9.1) - 7.75) = 6464.6644
    servo_pid.P = 5.8 /*14*/;//�����ڻ�

    angle_pid.P = 2.7;//�����⻷//1.9
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


    /*�ѵ���*/
    currentL_pid.I = 100;//�ٶ��ڻ�
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
* ��  ����void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
* ��  �ܣ�λ��ʽPID�㷨
* ��  ����PID: PID�������Ľṹ��
*         target: Ŀ��ֵ
*         measure: ����ֵ
* ����ֵ����
* ��  ע:
*****************************************************************************/
void PID_Postion_Cal(PID_Str* PID, float target, float measure)
{
     /*����ʷ�����б���*/
    PID->PrePreError = PID->PreError;   //�������ϴ����
    PID->PreError = PID->Error;         //�����ϴ����

    /*����������������΢����*/
    PID->Error  = target - measure;              //�������
    PID->Differ = PID->Error - PID->PreError;    //����΢����


    /*���������*/
    if(PID->I_EnableFlag == 1)
    {
        if(PID->Error < (PID->I_range) && PID->Error > -PID->I_range)   //���ַ��룺ֻ�������ӽ���̬��Χʱ�ż�����ֿ���
        {
            PID->Integral += PID->Error;                        //�������л���

            /*�������޷��������൱���ǶԻ�������޷���*/
            if(fabs ((double)(PID->I)) > 0.000001)
            {   /*���Ki������Ϊ0.������*/
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

    /*���������*/
    PID->Pout = PID->P * PID->Error;                        //�������
    PID->Iout = PID->I_EnableFlag * PID->I * PID->Integral;  //�������
    PID->Dout = PID->D * PID->Differ;                       //΢�����


    PID->Output =  PID->Pout + PID->Iout + PID->Dout;       //���� + ���� + ΢�� �����������


}


//-------------------------------------------------------------------------------------------------------------------
// �������          pid����ʽ���������
// ��������          PID������
// ʹ��ʾ��          PID_Increment_Cal(&pid, float target, float measure)
// ��ע��Ϣ          ע���������Ѿ��������ϴν��
//-------------------------------------------------------------------------------------------------------------------
void PID_Increment_Cal(PID_Str* PID, float target, float measure)
{


   /*����������������΢����*/
   PID->Error  = target - measure;              //�������


    PID->Pout =  PID->P * (PID->Error - PID->PreError);
    PID->Iout = PID->I *  PID->Error;
    PID->Dout = PID->D * (PID->Error - 2*PID->PreError + PID->PrePreError);

    PID->PrePreError = PID->PreError;
    PID->PreError = PID->Error;

    PID->Output += PID->Pout + PID->Iout + PID->Dout;


}
