/*
 * imglast.h
 *
 *  Created on: 2024��1��18��
 *      Author: 86139
 */

#ifndef IMG_H_
#define IMG_H_
#include "zf_common_headfile.h"

/*******************�궨��*********************/
//------------������Ҫ�����Ĳ���--------------//
#define USELESS_H                           0                   //��ֵ��ͼ��ײ����ںڱ�(���˲���ϵͳ��ڱ߲�������)
#define IMG_W                               MT9V03X_W           //����ͼ�����ͼ��Ŀ��
#define IMG_H                               MT9V03X_H           //(MT9V03X_H - USELESS_H)   //����ͼ�����ͼ��ĸ߶ȣ���ȥ�ڱߣ�
#define IMG_MIDDLE                          (IMG_W /2)          //����ͼ�����ͼ����е�

#define THREAD_MAX                          /*200*/ 185                     //��ֵ����ֵ����
#define THREAD_MIN                          /*30*/  100                     //��ֵ����ֵ����

#define ROUNDABOUT_DISCERN_COUNTS       4                           //ʶ���뻷��ʱ��Ҫ��׽ĳ������ͼ���֡������Ҫ���ݳ��ٵ�����
#define ROUNDABOUT_STATE1_TO_IN_COUNTS  4
#define ROUNDABOUT_IN_TO_OUT_COUNTS     30                               //�����ڲ�ʶ�������Ҫ��֡������Ҫ���ݳ��ٵ�����

#define USEFUL_FOR_LOSELINE                 3               //Ѱ�Ҷ����е�����
#define USEFUL_FOR_CROSS                    6               //Ѱ��ʮ�ֹյ�����
#define USEFUL_LINE_PRESET                  9
#define USEFUL_LINE_PRESET_FOR_ROUNDABOUT   5

//------------������Ҫ�����Ĳ���--------------//
#define RIGHT_DIR                       0                                   //�ұߣ������ұߣ�
#define LEFT_DIR                        1                                   //��ߣ�������ߣ�

#define IMG_WHITE                       255                                 //��ֵ�������У���ɫ��255��ʾ
#define IMG_BLACK                       0                                   //��ֵ�������У���ɫ��0��ʾ


/*----------------������ע�⣺ͷ�ļ��еı����ͺ���ֻ�����ⲿ�ļ���Ҫ�õ���-------------------*/


/*---------------------����ֵ��������------------------------*/
extern uint8 img_thread;                                //��ֵ����ֵ
extern uint8 Binary_Image[MT9V03X_H][MT9V03X_W];        //��ֵ���������

/*---------------------����ֵ��������------------------------*/

/*-------------------��ͼ������Ԥ�����----------------------*/


/*------------����ߣ������꣩���������-----------*/
extern int boundary_left[IMG_H];                            //��߽������
extern int boundary_right[IMG_H];                           //�ұ߽������
extern int middle_line[IMG_H];                              //���ߺ����꣨ÿ������Ԫ�ش洢ĳһ�е����ߺ����꣩

extern int Road_Refer_Left[IMG_H] ;               //�ο�·����߽������
extern int Road_Refer_Right[IMG_H] ;              //�ο�·���ұ߽������
extern int Road_Width[IMG_H] ;                    //�ο�·��·��

/*--------------------���߱���--------------------*/
extern int firstloseline_left;                                    //��ߵ�һ�ζ�����
extern int firstloseline_right;                                   //�ұߵ�һ�ζ�����

extern int finalloseline_right;                               //�ұ����ն�����
extern int finalloseline_left;                                //������ն�����

extern int finalloseline;                                 //������Ч��

extern int loserightflag;                                 //�ж��ұ��Ƿ��� 1���ж���
extern int loseleftflag;                                  //�ж�����Ƿ��� 1���ж���

extern int lost_right_flag[IMG_H];                            //��¼�ұ߶����У�����Ϊ1������Ϊ0
extern int lost_left_flag[IMG_H];                             //��¼��߶����У�����Ϊ1������Ϊ0

/*-------------------��ͼ������Ԥ�����----------------------*/

/*--------------------������Ԫ��ʶ���-----------------------*/
/*-------------------�������ýṹ�壿��--------------------*/
/*----------��־λ-----------*/
extern uint8 flag_send;
/*----------��־λ-----------*/
/*--------------------���Ԫ��--------------------*/
/*----------��־λ-----------*/
extern u8 left_turn_flag;                                                           //��ת��־λ
extern u8 right_turn_flag;                                                      //��ת��־λ

/*--------------------ʮ��Ԫ��--------------------*/
/*----------��־λ-----------*/
extern u8 cross_full_flag;                                                      //ȫʮ�ֱ�־λ         1Ϊʶ��ʮ��
extern u8 cross_half_flag;                                                      //�ϰ�ʮ�ֱ�־λ 1Ϊʶ��Ϊ�ϰ�ʮ��
extern int left_turn_cross_flag;           //ʶ��������ʮ��·�ڵı�־λ
extern int right_turn_cross_flag;          //ʶ��������ʮ��·�ڵı�־λ
extern int L_Down_Pointx , L_Down_Pointy ; //���¹յ��������
extern int L_Up_Pointx , L_Up_Pointy ;//���Ϲյ��������
extern int R_Down_Pointx , R_Down_Pointy ; //���¹յ��������
extern int R_Up_Pointx , R_Up_Pointy ;//���Ϲյ��������
extern int cross_time;
extern int cross_after_turn_flag ;          //б��ʮ�ֺ�Ĳ��߱�־����ʱб��ʮ�ֱ�־��1ת0�ĺ�֡�����������־Ϊ1��
extern bool left_cross_end_frame_flag ;//������������ʮ�֣���������ʮ�ֽ����󣬿�ʼ֡�����ı�־���Էſ�ʮ��������
extern int left_cross_end_frame_count ; //����ʮ�ֽ���֡����ֵ

extern bool right_cross_end_frame_flag ;//������������ʮ�֣���������ʮ�ֽ����󣬿�ʼ֡�����ı�־���Էſ�ʮ��������
extern int right_cross_end_frame_count ; //����ʮ�ֽ���֡����ֵ

/*---------�������----------*/

/*--------------------����Ԫ��--------------------*/
#define USE_ROUNDABOUT_FSM                          1                //�Ƿ�ʹ��״̬���ĺ궨��
extern int Roundabout_size;//Բ����С����ʼΪ0,1ΪС��2Ϊ��
extern int state_continue_frame_count;
extern int time_in;

#if USE_ROUNDABOUT_FSM

//����״̬��״̬ö��(ö��Ԫ���м��ö������)
typedef enum
{
    State1_Roundabout_Distern_1st_Repariline,
    State2_Roundabout_To_In_2nd_Repairline,
    State3_Roundabout_To_In_3th_Repairline,
    State4_Roundabout_In,
    State5_Roundabout_To_Out_Repairline,
    State6_Roundabout_Reset
} Roundabout_FSM;

extern Roundabout_FSM  Left_Roundabout_State;//�󻷵�״̬��״̬ö�ٱ���
extern Roundabout_FSM  Right_Roundabout_State;//�һ���״̬��״̬ö�ٱ���
#endif

/*-----------------------��-----------------------*/
extern int LEFT_Roundabout_State_step;
/*------���뻷����Ϊ��λˢ�µı���-----*/
/*----------������������������---------*/
extern u8  left_roundabout_flag ;   //�󻷵��ܱ�־λ
extern u8  if_left_roundabout_recog ;
extern int LEFR_Roundabout_State_step;
//�뻷֮ǰʶ�𻷵�
extern bool left_roundabout_discerning;//�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
extern int left_roundabout_discern_flag_count;//�󻷵��뻷֮ǰ����ʶ��֡��������
extern bool left_roundabout_only_up_point_flag; //�󻷵�ֻ���Ϲյ��ж��뻷��־������������
extern int left_roundabout_only_up_point_count; //�󻷵�ֻ���Ϲյ��ж��뻷֡��������������������
extern int left_roundabout_state1_repairline_count ; //�󻷵���һ�׶β���֡���������ڸ����жϵ�һ�׶εĽ���
extern bool left_roundabout_state1_repairline_to_end ; //�󻷵���һ�׶β��߼���������־
//�뻷����
extern int left_roundabout_state2_left_repairline_count ; //�󻷵���һ���ڶ����ɽ׶���߽粹��֡����������Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ�������
extern bool left_roundabout_in_left_repair_line ;//�󻷵�����ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern int left_roundabout_in_left_repair_line_count ; //�󻷵�����ʱ��߽粹�߼���������ÿ��һ֡��߽�ײ�������Ҫ���ߣ���+1��
extern bool left_roundabout_in_right_repair_line ;  //�󻷵�����ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern bool left_roundabout_in_change_angle ;   //ǿ��Ǳ�־���뻷���ڣ�
extern int left_roundabout_to_in_count ;  //�󻷵����������ļ������������ұ߽�ײ����ٶ���ʱ����ϴ�����(>0)���жϳɹ����뻷���ڲ���
//���ڴ���
extern bool left_roundabout_in_flag ;  //�󻷵��ɹ����뻷���ڲ���־λ
extern int left_roundabout_in_to_out_count ; //�󻷵��ڲ�ʶ�����֡�����������жϳ���������֮һ��
extern int right_break_point_y_to_out ;     //����ʱ�ҹյ㣬���ڳ������
//��������
extern bool left_roundabout_to_out_flag ;  //�󻷵����������ֱ�־λ
extern int left_roundabout_to_out_flag_count ; //�󻷵����������־λ��������
extern bool left_roundabout_out_left_repair_line ; //�󻷵�����ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern bool left_roundabout_out_right_repair_line ; //�󻷵�����ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern bool left_roundabout_out_flag ;   //�󻷵������ɹ���־

/*--------��֡Ϊ��λˢ�µı���--------*/
/*----�����뻷��һ�׶Σ�ʶ�𻷵���----*/
extern bool find_roundabout_left_down ; //�󻷵��¹յ�ʶ���־
extern bool find_roundabout_left_up ; //�󻷵��Ϲյ�ʶ���־
extern bool find_roundabout_left_up_only ; //�󻷵�ֻ�ҵ��Ϲյ��־
extern int roundabout_left_down_y;     //�󻷵����¹յ�������
extern int roundabout_left_down_x ;     //�󻷵����¹յ������
extern int roundabout_left_up_y ;     //�󻷵����Ϲյ�������
extern int roundabout_left_up_x ;     //�󻷵����Ϲյ������
extern float right_boundary_slope ;     //�ұ���б��
extern int lefty;//�󻷵�˺�ѵ�
extern int state_continue_frame_count ;//����ĳһ��״̬����ת֡����ֵ��������ĳ��ֵ����ֱ�ӽ�״̬��Ϊ��ʼ״̬��


/*-----------------------��-----------------------*/
extern u8  if_right_roundabout_recog ;  //if_right_roundabout_recog Ĭ��Ϊ1���������ˡ�ֻ��һ�λ�����ʱ�����ڻ���ʶ�𲢴��������0��

/*------���뻷����Ϊ��λˢ�µı���-----*/
/*----------������������������---------*/
extern u8  right_roundabout_flag ;  //�һ����ܱ�־λ
extern int RIGHT_Roundabout_State_step;//�����ñ�־λ
//�뻷֮ǰʶ�𻷵�
extern bool right_roundabout_discerning ; //�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
extern int right_roundabout_discern_flag_count ; //�һ����뻷֮ǰ����ʶ��֡��������
extern bool right_roundabout_only_up_point_flag ; //�һ���ֻ���Ϲյ��ж��뻷��־������������
extern int right_roundabout_only_up_point_count; //�һ���ֻ���Ϲյ��ж��뻷֡��������������������
extern int right_roundabout_state1_repairline_count ; //�һ�����һ�׶β���֡���������ڸ����жϵ�һ�׶εĽ���
extern bool right_roundabout_state1_repairline_to_end ; //�һ�����һ�׶β��߼���������־
//�뻷����
extern int right_roundabout_state2_right_repairline_count ; //�һ�����һ���ڶ����ɽ׶��ұ߽粹��֡����������Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ���ұ���
extern bool right_roundabout_in_right_repair_line ; //�һ�������ʱ�ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern int right_roundabout_in_right_repair_line_count; //�һ�������ʱ�ұ߽粹�߼���������ÿ��һ֡�ұ߽�ײ�������Ҫ���ߣ���+1��
extern bool right_roundabout_in_left_repair_line ; //�һ�������ʱ��߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern bool right_roundabout_in_change_angle ; //ǿ��Ǳ�־���뻷���ڣ�
extern int right_roundabout_to_in_count ; //�һ������������ļ�������������߽�ײ����ٶ���ʱ����ϴ�����(>0)���жϳɹ����뻷���ڲ���
//���ڴ���
extern bool right_roundabout_in_flag ; //�һ����ɹ����뻷���ڲ���־λ
extern int right_roundabout_in_to_out_count ; //�һ����ڲ�ʶ�����֡�����������жϳ���������֮һ��
extern int left_break_point_y_to_out ;           //����ʱ��յ㣬���ڳ������
//��������
extern bool right_roundabout_to_out_flag ; //�һ������������ֱ�־λ
extern int right_roundabout_to_out_flag_count ; //�һ������������־λ��������
extern bool right_roundabout_out_right_repair_line ;    //�һ�������ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern bool right_roundabout_out_left_repair_line ;     //�һ�������ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
extern bool right_roundabout_out_flag ;          //�һ����ɹ�������־//����һ��


/*--------��֡Ϊ��λˢ�µı���--------*/
/*----�����뻷��һ�׶Σ�ʶ�𻷵���----*/
extern bool  find_roundabout_right_down ; //�һ����¹յ�ʶ���־
extern bool  find_roundabout_right_up ; //�һ����Ϲյ�ʶ���־
extern bool find_roundabout_right_up_only ; //�һ���ֻ�ҵ��Ϲյ��־
extern int roundabout_right_down_y ;     //�һ������¹յ�������
extern int roundabout_right_down_x ;     //�һ������¹յ������
extern int roundabout_right_up_y ;     //�һ������Ϲյ�������
extern int roundabout_right_up_x ;     //�һ������Ϲյ������
extern float left_boundary_slope ;     //�����б��
extern int righty;//�һ���˺�ѵ�




/*--------------------ֱ��Ԫ��--------------------*/
extern int straight_flag;
void detectStraightRoad();//�б�ֱ������
extern int  startline_flag_delay;//ʶ�������ߺ�ļ�ʱ
/*--------------------������Ԫ��ʶ���-----------------------*/


/*---------------------����Ч���йء�------------------------*/
extern int useful_line_initial ;                             //��ʼ��Ч�У������ն�����
extern int useful_line_further ;                             //��Զ�����У�����Ԫ���ж�
extern int useful_line;                                             //��ȡ��Ч��
extern int left_roundabout_useful_line ;                        //����Ч��
extern int right_roundabout_useful_line ;                        //�һ���Ч��
extern int left_roundabout_useful_line ;                     //����Ч��
extern int right_roundabout_useful_line ;                     //�һ���Ч��
extern int cross_useful_line ;                              //ʮ��·����Ч��

/*---------------------����Ч���йء�------------------------*/
extern int maxRow ;
extern int maxLength ;
/*------------------����ȡ��������ƫ���---------------------*/
extern float middle_error;                                  //���µĵ�ǰ��������ƫ��
extern float middle_error_filter;                           //�˲���ĵ�ǰ��������ƫ��
extern uint8 middle_error_last;
extern int error_else;
extern uint8 middle_error_2;
extern int error_all;
/*------------------����ȡ��������ƫ���---------------------*/

/*------------------��·�ϡ�---------------------*/
extern int brick_down_x;
extern int brick_down_y;
extern int brick_up_x;
extern int brick_up_y;
extern int brick_down_left_flag;
extern int brick_up_left_flag;
extern int brick_down_right_flag;
extern int brick_up_right_flag;
extern int brick_left_flag;
extern int brick_right_flag;
extern int brick_time;
extern int brick_end_left;
extern int brick_end_right;
extern int brick_time_end;
extern int judge_2;
/*------------------��·�ϡ�---------------------*/
/*�ⲿ�ļ�����*/
void Image_Recognition();//ͼ��ʶ��������

/*ֻ��image.c���ã���Ҫ�����ſ��Ե���*/
void array_set_uniform(int array[], int value, int start, int end);//����ֵͳһ���ú���

void Get_Binary_Image(void);//��ö�ֵ��ͼ������
int otsuthreshold(uint8 *image);//��򷨻�ö�ֵ����ֵ
int IterativeThSegment(uint8 * image);//ȫ����ֵ��������ö�ֵ����ֵ

int findchange(int startx, int direction, int row, int color_change, int fail_boundary, int left, int right);//���������䣨�߽磩����
int findlose(int direction, int arrayfind[], int row);//�ж϶��ߺ���

int middleadjust(int middle_old, int row);//���ߵ�������
void findboundary(int firstx, int downy, int upy);//�ѱ��ߣ���ȷ�����ߣ�����
int find_one_boundary(int now_row, int last_middle_point);//�����ѱ����Ӻ���

int findfirstlose(int downy, int upy, int direction);//Ѱ�ҵ�һ�ζ����к���
int findfinallose(int firstlosey, int upy, int direction);//Ѱ�����ն����к���
void findloseline(int firstlosedown, int firstloseup, int finalloseup);//ȷ�������к���
float cross_bw_judge(int left_down, int left_up, int right_down, int right_up);//����ͼ��ڵ�ռ�ȣ�����ʮ��·�ڼ�⣩
void repair_line(int down_y, int down_x, int up_y, int up_x, int dir);//���ұ߽粹�ߺ�������Ҫ����ʮ��·�ڲ��ߣ�
void repair_middline(int downx, int downy, int upx, int upy);//����������������
void re_midline();//�������ұ߽���д���ߺ���

void Road_Refer_Generate(); //���ɲο�·��
void turn_recog();//���ʶ������
void cross_recog();//ʮ��ʶ������
void left_roundabout_recog();//�󻷵�ʶ������
void right_roundabout_recog();//�һ���ʶ������

void left_roundabout_recog_by_FSM();                   //ʶ���󻷵���״̬��ģʽ��
void right_roundabout_recog_by_FSM();                  //ʶ���һ�����״̬��ģʽ��
void CAM_Outside_Detect();//����������
void loseline_adjust();
u8 Dynamic_useful_line();//������Ч�к���
float Middle_Error();//������������ƫ��
float Middle_Error_temp2();

void flag_send_get();

void find_startline();//������
void find_brick();//Ѱ��ש��
void repair_middline_2(int down_y, int up_y,int dir ,int num);

#endif /* IMG_H_ */
