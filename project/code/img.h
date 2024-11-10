/*
 * imglast.h
 *
 *  Created on: 2024年1月18日
 *      Author: 86139
 */

#ifndef IMG_H_
#define IMG_H_
#include "zf_common_headfile.h"

/*******************宏定义*********************/
//------------可能需要调整的参数--------------//
#define USELESS_H                           0                   //二值化图像底部存在黑边(用了操作系统后黑边不存在了)
#define IMG_W                               MT9V03X_W           //用于图像处理的图像的宽度
#define IMG_H                               MT9V03X_H           //(MT9V03X_H - USELESS_H)   //用于图像处理的图像的高度（截去黑边）
#define IMG_MIDDLE                          (IMG_W /2)          //用于图像处理的图像的中点

#define THREAD_MAX                          /*200*/ 185                     //二值化阈值上限
#define THREAD_MIN                          /*30*/  100                     //二值化阈值下限

#define ROUNDABOUT_DISCERN_COUNTS       4                           //识别入环岛时需要捕捉某特征的图像的帧数（需要根据车速调整）
#define ROUNDABOUT_STATE1_TO_IN_COUNTS  4
#define ROUNDABOUT_IN_TO_OUT_COUNTS     30                               //环岛内部识别出环需要的帧数（需要根据车速调整）

#define USEFUL_FOR_LOSELINE                 3               //寻找丢线行的上限
#define USEFUL_FOR_CROSS                    6               //寻找十字拐点上限
#define USEFUL_LINE_PRESET                  9
#define USEFUL_LINE_PRESET_FOR_ROUNDABOUT   5

//------------可能需要调整的参数--------------//
#define RIGHT_DIR                       0                                   //右边（或往右边）
#define LEFT_DIR                        1                                   //左边（或往左边）

#define IMG_WHITE                       255                                 //二值化数组中，白色用255表示
#define IMG_BLACK                       0                                   //二值化数组中，黑色用0表示


/*----------------！！！注意：头文件中的变量和函数只包含外部文件需要用到的-------------------*/


/*---------------------↓二值化变量↓------------------------*/
extern uint8 img_thread;                                //二值化阈值
extern uint8 Binary_Image[MT9V03X_H][MT9V03X_W];        //二值化后的数组

/*---------------------↑二值化变量↑------------------------*/

/*-------------------↓图像搜线预处理↓----------------------*/


/*------------存放线（横坐标）的数组变量-----------*/
extern int boundary_left[IMG_H];                            //左边界横坐标
extern int boundary_right[IMG_H];                           //右边界横坐标
extern int middle_line[IMG_H];                              //中线横坐标（每个数组元素存储某一行的中线横坐标）

extern int Road_Refer_Left[IMG_H] ;               //参考路径左边界横坐标
extern int Road_Refer_Right[IMG_H] ;              //参考路径右边界横坐标
extern int Road_Width[IMG_H] ;                    //参考路径路宽

/*--------------------搜线变量--------------------*/
extern int firstloseline_left;                                    //左边第一次丢线行
extern int firstloseline_right;                                   //右边第一次丢线行

extern int finalloseline_right;                               //右边最终丢线行
extern int finalloseline_left;                                //左边最终丢线行

extern int finalloseline;                                 //最终有效行

extern int loserightflag;                                 //判断右边是否丢线 1是有丢线
extern int loseleftflag;                                  //判断左边是否丢线 1是有丢线

extern int lost_right_flag[IMG_H];                            //记录右边丢线行，丢线为1，否则为0
extern int lost_left_flag[IMG_H];                             //记录左边丢线行，丢线为1，否则为0

/*-------------------↑图像搜线预处理↑----------------------*/

/*--------------------↓赛道元素识别↓-----------------------*/
/*-------------------（考虑用结构体？）--------------------*/
/*----------标志位-----------*/
extern uint8 flag_send;
/*----------标志位-----------*/
/*--------------------弯道元素--------------------*/
/*----------标志位-----------*/
extern u8 left_turn_flag;                                                           //左转标志位
extern u8 right_turn_flag;                                                      //右转标志位

/*--------------------十字元素--------------------*/
/*----------标志位-----------*/
extern u8 cross_full_flag;                                                      //全十字标志位         1为识别到十字
extern u8 cross_half_flag;                                                      //上半十字标志位 1为识别为上半十字
extern int left_turn_cross_flag;           //识别到左弯入十字路口的标志位
extern int right_turn_cross_flag;          //识别到左弯入十字路口的标志位
extern int L_Down_Pointx , L_Down_Pointy ; //左下拐点横纵坐标
extern int L_Up_Pointx , L_Up_Pointy ;//左上拐点横纵坐标
extern int R_Down_Pointx , R_Down_Pointy ; //右下拐点横纵坐标
extern int R_Up_Pointx , R_Up_Pointy ;//右上拐点横纵坐标
extern int cross_time;
extern int cross_after_turn_flag ;          //斜入十字后的补线标志（此时斜入十字标志由1转0的后几帧，若补线则标志为1）
extern bool left_cross_end_frame_flag ;//若出现了弯入十字，则在弯入十字结束后，开始帧计数的标志（以放宽十字条件）
extern int left_cross_end_frame_count ; //弯入十字结束帧计数值

extern bool right_cross_end_frame_flag ;//若出现了弯入十字，则在弯入十字结束后，开始帧计数的标志（以放宽十字条件）
extern int right_cross_end_frame_count ; //弯入十字结束帧计数值

/*---------坐标变量----------*/

/*--------------------环岛元素--------------------*/
#define USE_ROUNDABOUT_FSM                          1                //是否使用状态机的宏定义
extern int Roundabout_size;//圆环大小，初始为0,1为小，2为大
extern int state_continue_frame_count;
extern int time_in;

#if USE_ROUNDABOUT_FSM

//环岛状态机状态枚举(枚举元素中间用逗号相隔)
typedef enum
{
    State1_Roundabout_Distern_1st_Repariline,
    State2_Roundabout_To_In_2nd_Repairline,
    State3_Roundabout_To_In_3th_Repairline,
    State4_Roundabout_In,
    State5_Roundabout_To_Out_Repairline,
    State6_Roundabout_Reset
} Roundabout_FSM;

extern Roundabout_FSM  Left_Roundabout_State;//左环岛状态机状态枚举变量
extern Roundabout_FSM  Right_Roundabout_State;//右环岛状态机状态枚举变量
#endif

/*-----------------------左-----------------------*/
extern int LEFT_Roundabout_State_step;
/*------以入环次数为单位刷新的变量-----*/
/*----------按环岛处理流程排序---------*/
extern u8  left_roundabout_flag ;   //左环岛总标志位
extern u8  if_left_roundabout_recog ;
extern int LEFR_Roundabout_State_step;
//入环之前识别环岛
extern bool left_roundabout_discerning;//用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
extern int left_roundabout_discern_flag_count;//左环岛入环之前环岛识别帧计数条件
extern bool left_roundabout_only_up_point_flag; //左环岛只有上拐点判断入环标志，出环才重置
extern int left_roundabout_only_up_point_count; //左环岛只有上拐点判断入环帧计数条件，出环才重置
extern int left_roundabout_state1_repairline_count ; //左环岛第一阶段补线帧计数，用于辅助判断第一阶段的结束
extern bool left_roundabout_state1_repairline_to_end ; //左环岛第一阶段补线即将结束标志
//入环处理
extern int left_roundabout_state2_left_repairline_count ; //左环岛第一至第二过渡阶段左边界补线帧计数条件：为了下一阶段更好的过渡，在下一阶段的前几帧仍然补左边线
extern bool left_roundabout_in_left_repair_line ;//左环岛进环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
extern int left_roundabout_in_left_repair_line_count ; //左环岛进环时左边界补线计数条件（每有一帧左边界底部丢线需要补线，则+1）
extern bool left_roundabout_in_right_repair_line ;  //左环岛进环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
extern bool left_roundabout_in_change_angle ;   //强打角标志（入环后期）
extern int left_roundabout_to_in_count ;  //左环岛进环结束的计数条件（当右边界底部不再丢线时，结合此条件(>0)，判断成功进入环岛内部）
//环内处理
extern bool left_roundabout_in_flag ;  //左环岛成功进入环岛内部标志位
extern int left_roundabout_in_to_out_count ; //左环岛内部识别出环帧计数条件（判断出环的条件之一）
extern int right_break_point_y_to_out ;     //出环时右拐点，用于出环打角
//出环处理
extern bool left_roundabout_to_out_flag ;  //左环岛出环处理部分标志位
extern int left_roundabout_to_out_flag_count ; //左环岛出环处理标志位计数变量
extern bool left_roundabout_out_left_repair_line ; //左环岛出环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
extern bool left_roundabout_out_right_repair_line ; //左环岛出环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
extern bool left_roundabout_out_flag ;   //左环岛出环成功标志

/*--------以帧为单位刷新的变量--------*/
/*----用于入环第一阶段（识别环岛）----*/
extern bool find_roundabout_left_down ; //左环岛下拐点识别标志
extern bool find_roundabout_left_up ; //左环岛上拐点识别标志
extern bool find_roundabout_left_up_only ; //左环岛只找到上拐点标志
extern int roundabout_left_down_y;     //左环岛左下拐点纵坐标
extern int roundabout_left_down_x ;     //左环岛左下拐点横坐标
extern int roundabout_left_up_y ;     //左环岛左上拐点纵坐标
extern int roundabout_left_up_x ;     //左环岛左上拐点横坐标
extern float right_boundary_slope ;     //右边线斜率
extern int lefty;//左环岛撕裂点
extern int state_continue_frame_count ;//保持某一个状态不跳转帧计数值，若大于某个值，则直接将状态置为初始状态。


/*-----------------------右-----------------------*/
extern u8  if_right_roundabout_recog ;  //if_right_roundabout_recog 默认为1，当开启了“只做一次环岛”时，会在环岛识别并处理完后置0）

/*------以入环次数为单位刷新的变量-----*/
/*----------按环岛处理流程排序---------*/
extern u8  right_roundabout_flag ;  //右环岛总标志位
extern int RIGHT_Roundabout_State_step;//传参用标志位
//入环之前识别环岛
extern bool right_roundabout_discerning ; //用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
extern int right_roundabout_discern_flag_count ; //右环岛入环之前环岛识别帧计数条件
extern bool right_roundabout_only_up_point_flag ; //右环岛只有上拐点判断入环标志，出环才重置
extern int right_roundabout_only_up_point_count; //右环岛只有上拐点判断入环帧计数条件，出环才重置
extern int right_roundabout_state1_repairline_count ; //右环岛第一阶段补线帧计数，用于辅助判断第一阶段的结束
extern bool right_roundabout_state1_repairline_to_end ; //右环岛第一阶段补线即将结束标志
//入环处理
extern int right_roundabout_state2_right_repairline_count ; //右环岛第一至第二过渡阶段右边界补线帧计数条件：为了下一阶段更好的过渡，在下一阶段的前几帧仍然补右边线
extern bool right_roundabout_in_right_repair_line ; //右环岛进环时右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
extern int right_roundabout_in_right_repair_line_count; //右环岛进环时右边界补线计数条件（每有一帧右边界底部丢线需要补线，则+1）
extern bool right_roundabout_in_left_repair_line ; //右环岛进环时左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
extern bool right_roundabout_in_change_angle ; //强打角标志（入环后期）
extern int right_roundabout_to_in_count ; //右环岛进环结束的计数条件（当左边界底部不再丢线时，结合此条件(>0)，判断成功进入环岛内部）
//环内处理
extern bool right_roundabout_in_flag ; //右环岛成功进入环岛内部标志位
extern int right_roundabout_in_to_out_count ; //右环岛内部识别出环帧计数条件（判断出环的条件之一）
extern int left_break_point_y_to_out ;           //出环时左拐点，用于出环打角
//出环处理
extern bool right_roundabout_to_out_flag ; //右环岛出环处理部分标志位
extern int right_roundabout_to_out_flag_count ; //右环岛出环处理标志位计数条件
extern bool right_roundabout_out_right_repair_line ;    //右环岛出环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
extern bool right_roundabout_out_left_repair_line ;     //右环岛出环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
extern bool right_roundabout_out_flag ;          //右环岛成功出环标志//改了一下


/*--------以帧为单位刷新的变量--------*/
/*----用于入环第一阶段（识别环岛）----*/
extern bool  find_roundabout_right_down ; //右环岛下拐点识别标志
extern bool  find_roundabout_right_up ; //右环岛上拐点识别标志
extern bool find_roundabout_right_up_only ; //右环岛只找到上拐点标志
extern int roundabout_right_down_y ;     //右环岛右下拐点纵坐标
extern int roundabout_right_down_x ;     //右环岛右下拐点横坐标
extern int roundabout_right_up_y ;     //右环岛右上拐点纵坐标
extern int roundabout_right_up_x ;     //右环岛右上拐点横坐标
extern float left_boundary_slope ;     //左边线斜率
extern int righty;//右环岛撕裂点




/*--------------------直道元素--------------------*/
extern int straight_flag;
void detectStraightRoad();//判别直道函数
extern int  startline_flag_delay;//识别起跑线后的计时
/*--------------------↑赛道元素识别↑-----------------------*/


/*---------------------↓有效行有关↓------------------------*/
extern int useful_line_initial ;                             //初始有效行，即最终丢线行
extern int useful_line_further ;                             //最远丢线行，用于元素判定
extern int useful_line;                                             //获取有效行
extern int left_roundabout_useful_line ;                        //左环有效行
extern int right_roundabout_useful_line ;                        //右环有效行
extern int left_roundabout_useful_line ;                     //左环有效行
extern int right_roundabout_useful_line ;                     //右环有效行
extern int cross_useful_line ;                              //十字路口有效行

/*---------------------↑有效行有关↑------------------------*/
extern int maxRow ;
extern int maxLength ;
/*------------------↓获取赛道中线偏差↓---------------------*/
extern float middle_error;                                  //最新的当前赛道中线偏差
extern float middle_error_filter;                           //滤波后的当前赛道中线偏差
extern uint8 middle_error_last;
extern int error_else;
extern uint8 middle_error_2;
extern int error_all;
/*------------------↑获取赛道中线偏差↑---------------------*/

/*------------------↓路障↓---------------------*/
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
/*------------------↑路障↑---------------------*/
/*外部文件调用*/
void Image_Recognition();//图像识别主函数

/*只在image.c调用，需要声明才可以调用*/
void array_set_uniform(int array[], int value, int start, int end);//数组值统一设置函数

void Get_Binary_Image(void);//获得二值化图像数组
int otsuthreshold(uint8 *image);//大津法获得二值化阈值
int IterativeThSegment(uint8 * image);//全局阈值迭代法获得二值化阈值

int findchange(int startx, int direction, int row, int color_change, int fail_boundary, int left, int right);//逐行搜跳变（边界）函数
int findlose(int direction, int arrayfind[], int row);//判断丢线函数

int middleadjust(int middle_old, int row);//中线调整函数
void findboundary(int firstx, int downy, int upy);//搜边线（及确定中线）函数
int find_one_boundary(int now_row, int last_middle_point);//迭代搜边线子函数

int findfirstlose(int downy, int upy, int direction);//寻找第一次丢线行函数
int findfinallose(int firstlosey, int upy, int direction);//寻找最终丢线行函数
void findloseline(int firstlosedown, int firstloseup, int finalloseup);//确定丢线行函数
float cross_bw_judge(int left_down, int left_up, int right_down, int right_up);//计算图像黑点占比（用于十字路口检测）
void repair_line(int down_y, int down_x, int up_y, int up_x, int dir);//左右边界补线函数（主要用于十字路口补线）
void repair_middline(int downx, int downy, int upx, int upy);//中线连线修正函数
void re_midline();//根据左右边界重写中线函数

void Road_Refer_Generate(); //生成参考路径
void turn_recog();//弯道识别处理函数
void cross_recog();//十字识别处理函数
void left_roundabout_recog();//左环岛识别处理函数
void right_roundabout_recog();//右环岛识别处理函数

void left_roundabout_recog_by_FSM();                   //识别左环岛（状态机模式）
void right_roundabout_recog_by_FSM();                  //识别右环岛（状态机模式）
void CAM_Outside_Detect();//冲出赛道检测
void loseline_adjust();
u8 Dynamic_useful_line();//计算有效行函数
float Middle_Error();//计算赛道中线偏差
float Middle_Error_temp2();

void flag_send_get();

void find_startline();//起跑线
void find_brick();//寻找砖块
void repair_middline_2(int down_y, int up_y,int dir ,int num);

#endif /* IMG_H_ */
