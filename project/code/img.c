

#include "zf_common_headfile.h"
/*---------------------↓二值化变量↓------------------------*/
uint8 img_thread = 0;                                                                               //二值化阈值
uint8 Binary_Image[MT9V03X_H][MT9V03X_W];                               //二值化后的数组
/*---------------------↑二值化变量↑------------------------*/

/*-------------------↓图像搜线预处理↓----------------------*/

/*------------存放线（横坐标）的数组变量-----------*/
int boundary_left[IMG_H] = { 0 };                 //左边界横坐标
int boundary_right[IMG_H] = { 0 };                //右边界横坐标
int middle_line[IMG_H] = { 0 };                   //中线横坐标（每个数组元素存储某一行的中线横坐标）

int Road_Refer_Left[IMG_H] = { 0 };               //参考路径左边界横坐标
int Road_Refer_Right[IMG_H] = { 0 };              //参考路径右边界横坐标
int Road_Width[IMG_H] = { 0 };                    //参考路径路宽
/*--------------------搜线变量--------------------*/
int firstloseline_left = 0;                     //左边第一次丢线行
int firstloseline_right = 0;                    //右边第一次丢线行

int finalloseline_right = 0;                    //右边最终丢线行
int finalloseline_left = 0;                     //左边最终丢线行

int finalloseline = 0;                          //最终有效行

int loserightflag = 0;                          //判断右边是否丢线 1是有丢线
int loseleftflag = 0;                           //判断左边是否丢线 1是有丢线

int lost_right_flag[IMG_H] = { 0 };             //记录右边丢线行，丢线为1，否则为0
int lost_left_flag[IMG_H] = { 0 };                //记录左边丢线行，丢线为1，否则为0

/*-------------------↑图像搜线预处理↑----------------------*/

/*--------------------↓赛道元素识别↓-----------------------*/
/*-------------------（考虑用结构体？）--------------------*/
/*----------标志位-----------*/
uint8 flag_send=0;
/*--------------------弯道元素--------------------*/
/*----------标志位-----------*/
#define TURN_PROCESS_WAY            1           //1为平移补线法，0为近似直线打角法
u8 left_turn_flag = 0;                                              //左转标志位
u8 right_turn_flag = 0;                                             //右转标志位

/*--------------------十字元素--------------------*/
/*----------标志位-----------*/
u8 cross_full_flag = 0;                                             //全十字标志位         1为识别到十字
u8 cross_half_flag = 0;                                             //上半十字标志位 1为识别为上半十字
int left_turn_cross_flag = 0;           //识别到左弯入十字路口的标志位
int right_turn_cross_flag = 0;          //识别到左弯入十字路口的标志位
int cross_after_turn_flag = 0;          //斜入十字后的补线标志（此时斜入十字标志由1转0的后几帧，若补线则标志为1）
bool left_cross_end_frame_flag = false;//若出现了弯入十字，则在弯入十字结束后，开始帧计数的标志（以放宽十字条件）
int left_cross_end_frame_count = 0; //弯入十字结束帧计数值

bool right_cross_end_frame_flag = false;//若出现了弯入十字，则在弯入十字结束后，开始帧计数的标志（以放宽十字条件）
int right_cross_end_frame_count = 0; //弯入十字结束帧计数值

/*--------------------环岛元素--------------------*/
#if USE_ROUNDABOUT_FSM
Roundabout_FSM  Left_Roundabout_State;//左环岛状态机状态枚举变量
Roundabout_FSM  Right_Roundabout_State;//右环岛状态机状态枚举变量
#endif
int Roundabout_size=0;//圆环大小，初始为0,1为小，2为大
int time_in=0;//圆环状态持续时间，用于控制圆环状态的更换

/*-----------------------左-----------------------*/
#define LEFT_ROUNDABOUT_ONLY_ONE                    1  //决定是否只做一次左环岛，与if_left_roundabout_recog标志配合，若只做一次环岛则将此宏定义置1，则才执行完一次环岛程序后将if_left_roundabout_recog 置0，不再执行环岛程序
u8  if_left_roundabout_recog = 1;  //if_left_roundabout_recog默认为1，当开启了“只做一次环岛”时，会在环岛识别并处理完后置0）
int LEFT_Roundabout_State_step=0;
/*------以入环次数为单位刷新的变量-----*/
/*----------按环岛处理流程排序---------*/
u8  left_roundabout_flag = 0;   //左环岛总标志位
int LEFR_Roundabout_State_step=0;//左环岛标志位，传输用
//入环之前识别环岛
bool left_roundabout_discerning = true;//用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
int left_roundabout_discern_flag_count = 0;//左环岛入环之前环岛识别帧计数条件
bool left_roundabout_only_up_point_flag = false; //左环岛只有上拐点判断入环标志，出环才重置
int left_roundabout_only_up_point_count = 0; //左环岛只有上拐点判断入环帧计数条件，出环才重置
int left_roundabout_state1_repairline_count = 0; //左环岛第一阶段补线帧计数，用于辅助判断第一阶段的结束
bool left_roundabout_state1_repairline_to_end = false; //左环岛第一阶段补线即将结束标志
//入环处理
int left_roundabout_state2_left_repairline_count = 0; //左环岛第一至第二过渡阶段左边界补线帧计数条件：为了下一阶段更好的过渡，在下一阶段的前几帧仍然补左边线
bool left_roundabout_in_left_repair_line = true;//左环岛进环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
int left_roundabout_in_left_repair_line_count = 0; //左环岛进环时左边界补线计数条件（每有一帧左边界底部丢线需要补线，则+1）
bool left_roundabout_in_right_repair_line = true;  //左环岛进环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
bool left_roundabout_in_change_angle = false;   //强打角标志（入环后期）
int left_roundabout_to_in_count = 0;  //左环岛进环结束的计数条件（当右边界底部不再丢线时，结合此条件(>0)，判断成功进入环岛内部）
//环内处理
bool left_roundabout_in_flag = false;  //左环岛成功进入环岛内部标志位
int left_roundabout_in_to_out_count = 0; //左环岛内部识别出环帧计数条件（判断出环的条件之一）
int right_break_point_y_to_out = 0;     //出环时右拐点，用于出环打角
//出环处理
bool left_roundabout_to_out_flag = false;  //左环岛出环处理部分标志位
int left_roundabout_to_out_flag_count = 0; //左环岛出环处理标志位计数变量
bool left_roundabout_out_left_repair_line = false; //左环岛出环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
bool left_roundabout_out_right_repair_line = true; //左环岛出环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
bool left_roundabout_out_flag = false;   //左环岛出环成功标志

/*--------以帧为单位刷新的变量--------*/
/*----用于入环第一阶段（识别环岛）----*/
bool find_roundabout_left_down = false; //左环岛下拐点识别标志
bool find_roundabout_left_up = false; //左环岛上拐点识别标志
bool find_roundabout_left_up_only = false; //左环岛只找到上拐点标志
int roundabout_left_down_y = 0;     //左环岛左下拐点纵坐标
int roundabout_left_down_x = 0;     //左环岛左下拐点横坐标
int roundabout_left_up_y = 0;     //左环岛左上拐点纵坐标
int roundabout_left_up_x = 0;     //左环岛左上拐点横坐标
float right_boundary_slope = 0;     //右边线斜率
int lefty=0;//左环岛撕裂点
int state_continue_frame_count = 0;//保持某一个状态不跳转帧计数值，若大于某个值，则直接将状态置为初始状态。

/*-----------------------右-----------------------*/
#define RIGHT_ROUNDABOUT_ONLY_ONE                    1  //决定是否只做一次右环岛，与if_right_roundabout_recog标志配合，若只做一次环岛则将此宏定义置1，则才执行完一次环岛程序后将if_right_roundabout_recog 置0，不再执行环岛程序
u8  if_right_roundabout_recog = 1;  //if_right_roundabout_recog 默认为1，当开启了“只做一次环岛”时，会在环岛识别并处理完后置0）

/*------以入环次数为单位刷新的变量-----*/
/*----------按环岛处理流程排序---------*/
u8  right_roundabout_flag = 0;  //右环岛总标志位
int RIGHT_Roundabout_State_step=0;//传参用标志位
//入环之前识别环岛
bool right_roundabout_discerning = true; //用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
int right_roundabout_discern_flag_count = 0; //右环岛入环之前环岛识别帧计数条件
bool right_roundabout_only_up_point_flag = false; //右环岛只有上拐点判断入环标志，出环才重置
int right_roundabout_only_up_point_count = 0; //右环岛只有上拐点判断入环帧计数条件，出环才重置
int right_roundabout_state1_repairline_count = 0; //右环岛第一阶段补线帧计数，用于辅助判断第一阶段的结束
bool right_roundabout_state1_repairline_to_end = false; //右环岛第一阶段补线即将结束标志
//入环处理
int right_roundabout_state2_right_repairline_count = 0; //右环岛第一至第二过渡阶段右边界补线帧计数条件：为了下一阶段更好的过渡，在下一阶段的前几帧仍然补右边线
bool right_roundabout_in_right_repair_line = true; //右环岛进环时右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
int right_roundabout_in_right_repair_line_count = 0; //右环岛进环时右边界补线计数条件（每有一帧右边界底部丢线需要补线，则+1）
bool right_roundabout_in_left_repair_line = true; //右环岛进环时左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
bool right_roundabout_in_change_angle = false; //强打角标志（入环后期）
int right_roundabout_to_in_count = 0; //右环岛进环结束的计数条件（当左边界底部不再丢线时，结合此条件(>0)，判断成功进入环岛内部）
//环内处理
bool right_roundabout_in_flag = false; //右环岛成功进入环岛内部标志位
int right_roundabout_in_to_out_count = 0; //右环岛内部识别出环帧计数条件（判断出环的条件之一）
int left_break_point_y_to_out = 0;           //出环时左拐点，用于出环打角
//出环处理
bool right_roundabout_to_out_flag = false; //右环岛出环处理部分标志位
int right_roundabout_to_out_flag_count = 0; //右环岛出环处理标志位计数条件
bool right_roundabout_out_right_repair_line = false;    //右环岛出环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
bool right_roundabout_out_left_repair_line = true;     //右环岛出环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
bool right_roundabout_out_flag = false;          //右环岛成功出环标志//改了一下


/*--------以帧为单位刷新的变量--------*/
/*----用于入环第一阶段（识别环岛）----*/
bool  find_roundabout_right_down = false; //右环岛下拐点识别标志
bool  find_roundabout_right_up = false; //右环岛上拐点识别标志
bool find_roundabout_right_up_only = false; //右环岛只找到上拐点标志
int roundabout_right_down_y = 0;     //右环岛右下拐点纵坐标
int roundabout_right_down_x = 0;     //右环岛右下拐点横坐标
int roundabout_right_up_y = 0;     //右环岛右上拐点纵坐标
int roundabout_right_up_x = 0;     //右环岛右上拐点横坐标
float left_boundary_slope = 0;     //左边线斜率
int righty=0;//右环岛撕裂点


/*--------------------↑赛道元素识别↑-----------------------*/


/*---------------------↓有效行有关↓------------------------*/
int useful_line_initial = 0;                             //初始有效行，即最终丢线行
int useful_line_further = 0;                             //最远丢线行，用于元素判定
int useful_line = 0;                                     //获取有效行
int left_roundabout_useful_line = 0;                     //左环有效行
int right_roundabout_useful_line = 0;                     //右环有效行
int cross_useful_line = 0;                              //十字路口有效行



/*---------------------↑有效行有关↑------------------------*/

/*------------------↓获取赛道中线偏差↓---------------------*/
float middle_error = 0;                                  //最新的当前赛道中线偏差
float middle_error_filter = 0;                          //滤波后的当前赛道中线偏差
uint8 middle_error_2=0;
uint8 middle_error_last=0;
int error_else=0;
int error_all=0;
void get_error(){error_all=(0.7*middle_error+0.5*(middle_error_2-200));}
/*------------------↑获取赛道中线偏差↑---------------------*/

//-------------------------------------------------------------------------------------------------------------------
// @brief       图像识别主函数
// @param       void
// @return  void
// @note        在此函数中实现了获取二值化图像，搜线，赛道元素识别，计算赛道偏差等
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void Image_Recognition()
{
    Get_Binary_Image();     //获取二值化图像，包括：通过大津法获取动态阈值、使用得到的动态阈值将图像二值化。
    //对图像进行初级处理
    findboundary(IMG_MIDDLE - 1, IMG_H - 1, 0); //搜边线
    findloseline(IMG_H - 1, USEFUL_FOR_LOSELINE, USEFUL_FOR_LOSELINE);              //搜丢线

    Road_Refer_Generate(); //生成参考路径

    cross_recog();//识别十字

#if USE_ROUNDABOUT_FSM//状态机（各环节一个接一个，只有前一个状态位结束才会触发下一状态位开始）
    left_roundabout_recog_by_FSM();     //识别左环岛
    right_roundabout_recog_by_FSM();    //识别右环岛
#else//非状态机，现已删除（各状态位相互独立）
    left_roundabout_recog();          //识别左环岛
    right_roundabout_recog();         //识别右环岛
#endif
    turn_recog();                       //识别弯道（优先级比十字、环岛等要低）
    useful_line = Dynamic_useful_line();//计算有效行
//    find_brick();//识别路障

    middle_error=Middle_Error()+error_else;//赛道偏差
    middle_error_last=middle_error+60;//无符号的赛道偏差，传输用
    get_error();//总偏差获取，上位机用
    detectStraightRoad();//直道判别
    flag_send_get();//获取各元素状态位，传输用
    find_startline();//识别起跑线
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       使用自动阈值法（大律法）得到二值化阈值
// @param       image 采集到的图像
// @return      int 二值化阈值
// Sample usage:    otsuthreshold(mt9v03x_image[0]);
//-------------------------------------------------------------------------------------------------------------------
int otsuthreshold(uint8 *image)
{
    int hist[256] = { 0 };
    uint8* data = image;
    int thresh_value = 0;
    float p1k = 0;
    float pi_value[256] = { 0 };
    float mk = 0;
    float mg = 0;
    float xitaB[256] = { 0 };
    int area;
    float compare_value = 0;


    for(int i=0;i<MT9V03X_H;i++)
    {
        for (int j = 0; j < MT9V03X_W; j++)
        {
            hist[(int)data[i * MT9V03X_W + j]]++;  //计算图像中每种灰度级像素的个数ni，hist[i]为灰度值为i的像素点的个数
        }
    }
    area = MT9V03X_H*MT9V03X_W; //图像的总像素N

    for (int i = 0; i < 256; i++)
    {
        pi_value[i] = (float)hist[i] / area;//统计图像中每种灰度值i出现的概率pi（所有的pi_value加起来应该是1）
        mg = mg + i * pi_value[i];//整幅图像的平均灰度
    }
    for (int i = 0; i < 256; i++)
    {
        p1k = p1k + pi_value[i];
        if (p1k != 0)
        {
            mk = mk + i * pi_value[i];
            float fenzi, fenmu;
            fenzi = (mg*p1k - mk)*(mg*p1k - mk);
            fenmu = p1k * (1 - p1k);
            xitaB[i] = (float)fenzi / fenmu; //类间方差
            if (xitaB[i] > compare_value)
            {
                compare_value = xitaB[i];
                thresh_value = i;
            }
        }
    }
    return thresh_value;
}
int otsuthreshold_update(uint8 *image)//大律法二值化（优化版）
{
    int hist[256] = { 0 };
    uint8* data = image;
    int thresh_value = 0;
    float p1k = 0;
    float pi_value[256] = { 0 };
    float mk = 0;
    float mg = 0;
    float xitaB[256] = { 0 };
    int area;
    float compare_value = 0;

    /*分析图像的大小为1/4原图（每4个点取一次）*/
    for(int i=0;i< MT9V03X_H/4;i++)
    {
        for (int j = 0; j < MT9V03X_W/4; j++)
        {
            hist[(int)data[4 * i * MT9V03X_W + 4*j]]++;  //计算图像中每种灰度级像素的个数ni，hist[i]为灰度值为i的像素点的个数
        }
    }
    area = (MT9V03X_H / 4) * (MT9V03X_W / 4); //图像的总像素N
    for (int i = 0; i < 256; i++)
    {
        pi_value[i] = (float)hist[i] / area;//统计图像中每种灰度值i出现的概率pi（所有的pi_value加起来应该是1）
        mg = mg + i * pi_value[i];//整幅图像的平均灰度
    }
    for (int i = 0; i < 256; i++)//0 256(10 80 )
    {
        p1k = p1k + pi_value[i];
        if (p1k != 0)
        {
            mk = mk + i * pi_value[i];
            float fenzi, fenmu;
            fenzi = (mg*p1k - mk)*(mg*p1k - mk);
            fenmu = p1k * (1 - p1k);
            xitaB[i] = (float)fenzi / fenmu; //类间方差
            if (xitaB[i] > compare_value)
            {
                compare_value = xitaB[i];
                thresh_value = i;
            }
        }
    }
    return thresh_value;
}
int otsuthreshold_integer(uint8 *image)
{
    int hist[256] = { 0 };
    uint8* data = image;
    int area;
    int thresh_value = 0;
    uint32_t p1k = 0;
    uint32_t pi_value[256] = { 0 };
    uint32_t mk = 0;
    uint32_t mg = 0;
    uint32_t xitaB[256] = { 0 };

    uint32_t compare_value = 0;


    for(int i=0;i<MT9V03X_H;i++)
    {
        for (int j = 0; j < MT9V03X_W; j++)
        {
            hist[(int)data[i * MT9V03X_W + j]]++;  //计算图像中每种灰度级像素的个数ni，hist[i]为灰度值为i的像素点的个数
        }
    }
    area = MT9V03X_H*MT9V03X_W; //图像的总像素N

    for (int i = 0; i < 256; i++)
    {
        pi_value[i] = 1000 * hist[i] / area;//统计图像中每种灰度值i出现的概率pi（所有的pi_value加起来应该是1）,每一个pi都乘了1000
        mg = mg + i * pi_value[i];//整幅图像的平均灰度（mg也乘了1000）
    }

    for (int i = 0; i < 256; i++)
    {
        p1k = p1k + pi_value[i];   //plk也乘了1000
        if (p1k != 0)
        {
            mk = mk + i * pi_value[i];//mk也乘了1000
            uint64_t fenzi, fenmu;
            fenzi = (mg*p1k / 1000  - mk)*(mg*p1k / 1000 - mk);  // (1000*mg*plk - 1000*mk)^2 = 1000 ^ 2 *(mg*plk - mk)^2
            fenmu = p1k * (1000 - p1k);    //1000*plk * (1000 - 1000*plk) =  1000 * 1000 * plk * (1 - plk) = 1000^2 * plk * (1 - plk)
            xitaB[i] = 1000 *fenzi / fenmu; //类间方差 (乘了1000)
            if (xitaB[i] > compare_value)
            {
                compare_value = xitaB[i];
                thresh_value = i;
            }
        }
    }

    return thresh_value;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       使用全局阈值迭代法得到二值化阈值
// @param       image 采集到的图像
// @return      int 二值化阈值
// Sample usage:    img_thread = IterativeThSegment(mt9v03x_image[0]);
//-------------------------------------------------------------------------------------------------------------------
int IterativeThSegment(uint8 * image)
{

    uint8 * data = image;
    int Binaryzation_Value = 0;
    int T0=0,T1=0,G1=0,G2=0,G1_Count=0,G2_Count=0;

    T0=125; //初始阈值
    for (int i = 5; i < IMG_H - 5; i+=2)
    {
        for (int j = 0; j < IMG_W; j+=2)
        {
                if(data[i * IMG_W + j]>T0)
                {
                    G1+=data[i * IMG_W + j];//如果比初始阈值大，归入G1分组
                    G1_Count++;
                }
                else
                {
                    G2+=data[i * IMG_W + j];
                    G2_Count++;
                }
        }
    }
    T1=(G1/G1_Count+G2/G2_Count)/2; //取两个分组的灰度均值的平均值
    while((T1-T0) > 1 || (T0 - T1) > 1)
    {
        T0=T1; //以计算出来的分度值替代初始阈值，重新计算
        G1=0,G2=0,G1_Count=0,G2_Count=0;
        for (int i = 5; i < IMG_H - 5; i+=2)
        {
            for (int j = 0; j < IMG_W; j+=2)
            {
                    if(data[i * IMG_W + j]>T0)
                    {
                        G1+=data[i * IMG_W + j];//如果比初始阈值大，归入G1分组
                        G1_Count++;
                    }
                    else
                    {
                        G2+=data[i * IMG_W + j];
                        G2_Count++;
                    }
            }
        }
        T1=(G1/G1_Count+G2/G2_Count)/2;
    }
//    //限幅
//  if(T1<60)
//  {
//      Binaryzation_Value=60;
//  }
//  else if(T1>110)
//  {
//      Binaryzation_Value=110;
//  }
//  else
//  {
//      Binaryzation_Value=T1;
//  }

    Binaryzation_Value=T1;

    return Binaryzation_Value;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       获取二值化图像 函数
// @param       void
// @return  void
// Sample usage:    Get_Binary_Image();
//-------------------------------------------------------------------------------------------------------------------
void Get_Binary_Image(void)
{
    //img_thread = otsuthreshold_integer(mt9v03x_image[0]);//尝试用整型值算大津法，效果较差，且所需时间更多

    img_thread = 1.00*otsuthreshold(mt9v03x_image[0]);//大津法：确定二值化阈值，得到的阈值就是img_thread

    //img_thread = otsuthreshold_update(mt9v03x_image[0]);//改善的大津法：确定二值化阈值，得到的阈值就是img_thread

    //img_thread = IterativeThSegment(mt9v03x_image[0]);//全局阈值迭代法：确定二值化阈值，得到的阈值就是img_thread

    /*二值化阈值限幅，之后有需要再加*/
//  if(img_thread>THREAD_MAX)
//  {
//      img_thread = THREAD_MAX;
//  }
//  else if(img_thread<THREAD_MIN)
//  {
//      img_thread=THREAD_MIN  ;
//  }

    for(int i=0;i<MT9V03X_H;i++)
    {
        for(int j=0;j<MT9V03X_W;j++)
        {
            //mt9v03x_image[i][j]>=img_thread?(Binary_Image[i][j]=IMG_WHITE):(Binary_Image[i][j]=IMG_BLACK);
            //大于阈值的设为白色（255），小于阈值的设为黑色（0）
            if(mt9v03x_image[i][j] >= img_thread)
            {
                Binary_Image[i][j] = IMG_WHITE;
            }
            else
            {
                Binary_Image[i][j] = IMG_BLACK;
            }
        }
    }

}


//-------------------------------------------------------------------------------------------------------------------
// @brief       数组值统一设置函数
// @param       array                       要处理的数组
// @param       value                       每个数组元素要赋的值
// @param       start                       起始点
// @param       end                         终点（end>start）
// @return  void
// @note        思路：在选定范围内遍历数组，将相应的值设为要赋的值
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void array_set_uniform(int array[], int value, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        array[i] = value;
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       最小二乘法求解斜率
// @param       direction           方向LEFT_DIR / RIGHT_DIR
// @param       downy               起始纵坐标
// @param       upy                 终止纵坐标
// @return      float               斜率
// @note        对于没有FPU的mm32，可能费时较久，谨慎使用
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
float leastSquareLinearFit(int direction, int downy, int upy)
{
    float k;
    int i, count;
    int num = downy - upy - 1;//求解总行数
    float sum_x2 = 0.0f;
    float sum_y = 0.0f;
    float sum_x = 0.0f;
    float sum_xy = 0.0f;
    count = 0;
    if (direction == LEFT_DIR)
    {
        for (i = upy + 1; i < downy; i++)
        {
            sum_x2 += boundary_left[i] * boundary_left[i];
            sum_y += i;
            sum_x += boundary_left[i];
            sum_xy += boundary_left[i] * i;
            if (boundary_left[i] == boundary_left[downy])
            {
                count++;
            }
        }
    }

    else
    {
        for (i = upy + 1; i < downy; i++)
        {
            sum_x2 += boundary_right[i] * boundary_right[i];
            sum_y += i;
            sum_x += boundary_right[i];
            sum_xy += boundary_right[i] * i;
            if (boundary_right[i] == boundary_right[downy])
            {
                count++;
            }
        }
    }
    if (count >= 0.95 * num)//接近垂直
    {
        k = 10;          //???
    }
    else
    {
        k = (num * sum_xy - sum_x * sum_y) / (num * sum_x2 - sum_x * sum_x);
    }

    return k;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       逐行搜跳变（边界）函数
// @param   startx                  搜线的起始横坐标
// @param       direction               RIGHT_DIR / LEFT_DIR 搜线的方向————RIGHT_DIR为往右边，LEFT_DIR为往左边
// @param       row                         要在哪一行搜跳变
// @param   color_change        IMG_BLACK / IMG_WHITE，黑到白的跳变（IMG_WHITE）还是白到黑的跳变（IMG_BLACK）
// @param       fail_boundary       当找不到符合的边界时把边界设定的值
// @param       left                        跳变左边需要有几个同颜色点
// @param       right                       跳变右边需要有几个同颜色点
// @return  int                         搜到跳变列的横坐标
// @note        left、right是用来决定搜到白白黑黑还是白黑还是白黑黑等，才算是跳变
//                  fail_boundary的一个应用例子：找边界时，如果没有符合条件的跳变点，把该值设为119，则该行的边界就为119
//                  思路：从起始点开始，往选定的方向搜索跳变点，返回搜到边线的横坐标
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
int findchange(int startx, int direction, int row, int color_change, int fail_boundary, int left, int right)
{
    int j, i;
    bool leftachieve = 1;   //判断左边是否达到连续点的条件
    bool rightachieve = 1;  //判断右边是否达到连续点的条件
    if (direction == RIGHT_DIR)//往右边搜
    {
        for (j = startx; j < IMG_W - right - 1; j++) //先找到有跳变
        {
            leftachieve = 1;
            rightachieve = 1;
            if (Binary_Image[row][j + 1] == color_change)//j为跳变前的点，j+1为跳变后的点
            {
                for (i = j + 1; i < j + 1 + right; i++)//右边满足有连续right个跳变后的颜色的点
                {
                    if (Binary_Image[row][i] != color_change)
                    {
                        rightachieve = 0;//不满足则退出
                        break;
                    }
                }
                if (!rightachieve)
                {
                    continue;
                }
                else
                {
                    for (i = j; i > j - left; i--)//右边满足条件的情况下，判断左边是否有连续left个和color_change颜色相反的点
                    {
                        if (Binary_Image[row][i] != (IMG_WHITE - color_change))  //color_change为黑，则IMG_WHITE - color_change = 255 为白，color_change 为白，则IMG_WHITE - color_change = 0 为黑
                        {
                            leftachieve = 0;
                            break;
                        }
                    }
                }
                if (!leftachieve)
                {
                    continue;
                }
                else
                {
                    return j;//如果两个条件都符合，返还找到的边界点
                }
            }
        }
        return fail_boundary;
    }
    else//左边，思路和右边一样
    {
        for (j = startx; j > left; j--)
        {
            leftachieve = 1;
            rightachieve = 1;
            if (Binary_Image[row][j - 1] == color_change)//j为跳变前的点，j-1为跳变后的点
            {
                for (i = j - 1; i > j - 1 - left; i--)
                {
                    if (Binary_Image[row][i] != color_change)
                    {
                        leftachieve = 0;
                        break;
                    }
                }
                if (!leftachieve)
                {
                    continue;
                }
                else
                {
                    for (i = j; i < j + right; i++)
                    {
                        if (Binary_Image[row][i] != (IMG_WHITE - color_change))
                        {
                            rightachieve = 0;
                            break;
                        }
                    }
                    if (!rightachieve)
                    {
                        continue;
                    }
                    else
                    {
                        return j;
                    }
                }
            }
        }
        return fail_boundary;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       单行判断丢线函数
// @param       direction               RIGHT_DIR / LEFT_DIR  判断的方向————RIGHT_DIR为往右边，LEFT_DIR为往左边
// @param       arrayfind               需要找丢线情况的数组（数组元素为每行的边界横坐标）
// @param       row                         要在第几行寻找丢线情况
// @return  int                         1为丢线，0为不丢线
// @note        什么是丢线————即赛道边界为图像的边界（一般是没法直接搜到跳变，故将图像边界作为赛道边界）
//                  思路：若某行搜到边界的横坐标为图像的边界，则返回1
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
int findlose(int direction, int arrayfind[], int row)
{
    if (direction == RIGHT_DIR)
    {
        if (arrayfind[row] == IMG_W - 1 && Binary_Image[row][middle_line[row]] == IMG_WHITE)  //右边线，注意中线为赛道（否则对于中线为黑点处也会丢线）        //数组起始为0，最大值为IMG_W-1
        {
            return 1;
        }
    }
    else
    {
        if (arrayfind[row] == 0 && Binary_Image[row][middle_line[row]] == IMG_WHITE)          //左边线，注意中线为赛道
        {
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       中线调整函数
// @param       middle_old          原来的赛道中点
// @param       row                         要在第几行调整
// @return  int                         调整后的中点横坐标
// @note
// Sample usage：
//                  middle_line[i - 1] = middleadjust(IMG_MIDDLE, i - 1)
//                  一般用于 搜边线函数中确定某行赛道中点时，计算出来的中点为黑色，且图像中点也为黑色 时的情况
//-------------------------------------------------------------------------------------------------------------------
int middleadjust(int middle_old, int row)
{
    int adjustedleft = 0;//左边界点
    int adjustedright = 0;//右边界点
    int left_distance = 0;//左边调整的距离
    int right_distance = 0;//右边调整的距离

    //从middle_old开始往两边搜连续两个或三个白色点（即赛道）
    adjustedright = findchange(middle_old, RIGHT_DIR, row, IMG_WHITE, (IMG_W - 1), 1, 2);//找右边可调整点（找黑到白跳变点，即赛道）
    adjustedleft = findchange(middle_old, LEFT_DIR, row, IMG_WHITE, 0, 2, 1);//找左边可调整点（找黑到白跳变点）

    if (adjustedright == (IMG_W - 1) && adjustedleft == 0)//左右两边都没有找到可以调整的点（该行视野中没有赛道），返回原值
    {
        return middle_old;
    }

    //计算左右两边分别经过多少距离后能搜到赛道
    left_distance = middle_old - adjustedleft;
    right_distance = adjustedright - middle_old;

    //取其中距离较小的那个赛道边界作为调整后的中点
    if (left_distance <= right_distance)
    {
        return adjustedleft;
    }
    else
    {
        return adjustedright;
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       迭代搜边线子函数（含中线调整，寻找丢线情况，未使用）
// @param       now_row                 本行行数
// @param       last_middle_point       上一行中点，也即本行搜线起始点
// @param       upy                     搜线的最终行，辅助调整中线，防止越界
// @return      int                     本行中点
// @note
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
int find_one_boundary(int now_row, int last_middle_point)
{
    //调整中线，即本行搜线起始点，使本行搜线起始点非黑
    if (Binary_Image[now_row][last_middle_point] == IMG_BLACK)   //当以上一行的中点作为本行搜线起始点而为黑色（即不是赛道）时，把本行起始点设为图像中点（即IMG_MIDDLE）
    {
        if (Binary_Image[now_row][IMG_MIDDLE] == IMG_BLACK)      //图像中点也为黑色，执行调整中点的函数
        {
            last_middle_point = middleadjust(IMG_MIDDLE, now_row);
        }
        else
        {
            last_middle_point = IMG_MIDDLE; //图像中点不为黑色，将起始点设为图像中点
        }

    }//搜线起始点不为黑色时，直接将上一行的中点作为本行的起始点，不需调整

    //搜边线（last_middle_point为搜线起始点）
    boundary_left[now_row] = findchange(last_middle_point, LEFT_DIR, now_row, IMG_BLACK, 0, 2, 1);           //搜左边线
    boundary_right[now_row] = findchange(last_middle_point, RIGHT_DIR, now_row, IMG_BLACK, (IMG_W - 1), 1, 2); //搜右边线

     //提取该行的中点，为下一行的搜线提供起始点
    middle_line[now_row] = (boundary_left[now_row] + boundary_right[now_row]) / 2;

    //寻找丢线情况（若该行的边界为图像边界，则丢线标志为1）
   lost_left_flag[now_row] = findlose(LEFT_DIR, boundary_left, now_row);        //寻找左边丢线情况
lost_right_flag[now_row] = findlose(RIGHT_DIR, boundary_right, now_row);     //寻找右边丢线情况

    return middle_line[now_row];
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       原搜边线（及确定中线）函数
// @param       firstx                  起始点x坐标
// @param       downy                       起始点y坐标（图像偏下方，数值较大）
// @param       upy                         结束点y坐标（图像偏上方，数值较小）
// @param       iffindlose          是否找丢线
// @param       ifadjust                是否调整中线
// @return  void
// @note        在自己想要的范围寻找边线
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void findboundary(int firstx, int downy, int upy)
{
    array_set_uniform(boundary_left, 0, 0, IMG_H);//清空左边界数组
    array_set_uniform(boundary_right, 0, 0, IMG_H);//清空右边界数组
    array_set_uniform(middle_line,0,0,IMG_H);//清空中线横坐标数组

    array_set_uniform(lost_right_flag, 0, 0, IMG_H);
    array_set_uniform(lost_left_flag, 0, 0, IMG_H);

    middle_line[downy] = firstx;//规定起始行的横坐标（只有起始行的起始横坐标是规定为firstx的，其余行的起始横坐标为下一行的中线横坐标

    int i;
    for (i = downy; i >= upy; i--)
    {
        boundary_left[i]  = findchange(middle_line[i], LEFT_DIR , i, IMG_BLACK, 0, 1, 1);                         //搜左边线（这里的第一个参数仅仅表示搜线起始点而已，并不是该行中线横坐标）
        boundary_right[i] = findchange(middle_line[i], RIGHT_DIR, i, IMG_BLACK, (IMG_W - 1), 1, 1);               //搜右边线


        lost_left_flag[i] = findlose(LEFT_DIR, boundary_left, i);  //若第i行的边界为图像边界，则丢线标志为1        //寻找左边丢线情况
        lost_right_flag[i] = findlose(RIGHT_DIR, boundary_right, i);                        //寻找右边丢线情况


        middle_line[i] = (boundary_left[i] + boundary_right[i]) / 2;        //更新该行的中点，作为i-1行的起始点

        if (i != upy)//确定（调整）中线横坐标数组
        {
            if (Binary_Image[i - 1][middle_line[i]] == IMG_BLACK)                  //当以i行中点作为i-1行的搜线起始点而为黑色（即不是赛道）时，把起始点设为图像中点（即下行IMG_MIDDLE）
            {
                if (Binary_Image[i - 1][IMG_MIDDLE] == IMG_BLACK)         //图像中点也为黑色，执行调整中点的函数
                {
                    middle_line[i - 1] = middleadjust(IMG_MIDDLE, i - 1);
                }
                else
                {
                    middle_line[i - 1] = IMG_MIDDLE; //图像中点不为黑色，将赛道中点设为图像中点
                }

            }
            else                                   //搜线起始点不为黑色时，直接将i行的中点作为i-1行的起始点
            {
                middle_line[i - 1] = middle_line[i];
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       寻找第一次丢线行函数
// @param       downy                   起始点y坐标（图像偏下方，数值较大）
// @param       upy                     结束点y坐标（图像偏上方，数值较小）
// @param       direction               RIGHT_DIR / LEFT_DIR 方向
// @return      int                     找到的第一次丢线行的纵坐标（从图像下方开始寻找的首次丢线的行数）-- 若没有丢线则返回-1
// @note        思路：在一定范围内寻找lost_right_flag或者lost_left_flag数组中第一次出现1对应的索引值
//              第一丢线行是丢线的
// Sample usage：firstloseline_left = findfirstlose(firstlosedown, firstloseup, LEFT_DIR);
//-------------------------------------------------------------------------------------------------------------------
int findfirstlose(int downy, int upy, int direction)
{
    int i;
    if (direction == RIGHT_DIR)//右边
    {
        for (i = downy; i >= upy; i--)
        {
            if (lost_right_flag[i] == 1 && lost_right_flag[i - 1] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//从图像下方往上找，找到丢线标志连续两行为1，且中线处为白色
            {
                return i;
            }
        }
    }
    else
    {
        for (i = downy; i >= upy; i--)
        {
            if (lost_left_flag[i] == 1 && lost_left_flag[i - 1] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//从图像下方往上找，找到丢线标志连续两行为1，且中线处为白色
            {
                return i;
            }
        }
    }
    return -1;//没有丢线，此时 第一丢线行 为负数，慎防数组越界！！！

}
//-------------------------------------------------------------------------------------------------------------------
// @brief       寻找最终丢线行函数
// @param       firstlosey          起始点y坐标（图像偏下方，数值较大），为已经找到的第一次丢线行
// @param       upy                         结束点y坐标（图像偏上方，数值较小）
// @param       direction               RIGHT_DIR / LEFT DIR 方向
// @return      int                         找到的左边或者右边连续最后一次丢线行的纵坐标
// @note        思路                      从第一次丢线开始往往上找连续丢线行
//              最终丢线行是丢线的
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
int findfinallose(int firstlosey, int upy, int direction)
{
    int i;
    if (direction == RIGHT_DIR)
    {
        i = firstlosey;
        while (lost_right_flag[i] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//往上搜丢线（且要保证丢线行中点在跑道上）
        {
            i--;
            if (i < upy)//最终丢线行不能超过上限值
            {
                i++;
                break;
            }
            if (lost_right_flag[i] == 0 && lost_right_flag[i - 1] == 1 && lost_right_flag[i - 2] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)
            {
                i--;
            }//改了一下4，还没验证！！！忽略掉一点误差，提前判断若出现下一行不丢线，但是其上方又有连续两行丢线，则i--，跳过这一行
        }
        return i + 1;//改了一下4，确保最终丢线行所在行是丢线的
    }
    else
    {
        i = firstlosey;
        while (lost_left_flag[i] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//往上搜丢线（且要保证丢线行中点在跑道上）
        {
            i--;
            if (i < upy)
            {
                i++;
                break;
            }
            if (lost_left_flag[i] == 0 && lost_left_flag[i - 1] == 1 && lost_left_flag[i - 2] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)
            {
                i--;
            }//改了一下4，还没验证！！！忽略掉一点误差，提前判断若出现下一行不丢线，但是其上方又有连续两行丢线，则i--，跳过这一行
        }
        return i + 1;//改了一下4，确保最终丢线行所在行是丢线的
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       最终丢线行调整函数
// @param       finalloseline_init      原最终丢线行
// @param       direction               RIGHT_DIR / LEFT DIR 方向
// @param       useful_length           有效长度，上方丢线段大于此才调整
// @return      int                     调整后的最终丢线行
// @note        思路                  若原最终丢线行上仍有大段丢线，将最终丢线行上拉
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
int finalloseline_adjust(int finalloseline_init, int direction, int useful_length)

{int adjust_temp = finalloseline_init;
if (direction == RIGHT_DIR)//右边
{
    for (int j = finalloseline_init - 1; j >= useful_length + USEFUL_FOR_LOSELINE; j--)
    {
        if (lost_right_flag[j] == 1)
        {
            int k = j;                     //记录起始行数
            while (lost_right_flag[j] == 1) //往上搜丢线
            {
                j--;
                if (j <= USEFUL_FOR_LOSELINE)
                {
                    j = USEFUL_FOR_LOSELINE;
                    break;
                }
            }
            if ((k - j) >= useful_length)//若存在大段丢线，最终丢线行上提
            {
                adjust_temp = j;
                break;
            }
        }
    }
}
else //左边
{
    for (int j = finalloseline_init - 1; j >= useful_length + USEFUL_FOR_LOSELINE; j--)
    {
        if (lost_left_flag[j] == 1)
        {
            int k = j;                    //记录起始行数
            while (lost_left_flag[j] == 1) //往上搜丢线
            {
                j--;
                if (j <= USEFUL_FOR_LOSELINE)
                {
                    j = USEFUL_FOR_LOSELINE;
                    break;
                }
            }
            if ((k - j) >= useful_length)//若存在大段丢线，有效行上提
            {
                adjust_temp = j;
                break;
            }
        }
    }
}
//判断最终丢线行的中点是不是还在跑道上，如果在就确定此行为有效行，如果不在，则继续判断下面一行是否满足条件
while (Binary_Image[adjust_temp][middle_line[adjust_temp]] == IMG_BLACK || Binary_Image[adjust_temp + 1][middle_line[adjust_temp + 1]] == IMG_BLACK)
{
    adjust_temp++;
    if (adjust_temp >= finalloseline_init)
    {
        adjust_temp = finalloseline_init;
        break;
    }
}

//若不需要调整，返回原来值(需要调整，则调整值一定小于原值)
return (adjust_temp <= finalloseline_init ? adjust_temp : finalloseline_init);
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       丢线行调整函数
// @param       direction               RIGHT_DIR / LEFT DIR 方向
// @param       useful_length           有效长度，上方丢线段大于此才调整
// @note        若原最终丢线行上仍有大段丢线（或丢线行数比下方的要多），将第一丢线行和最终丢线行均上拉，即使两段丢线成为一段丢线
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void loseline_adjust(int direction, int useful_length)
{
    if (direction == RIGHT_DIR)
    {
        int lose_right_length_1 = 0, lose_right_length_2 = 0;             //分别获取第一段、第二段（如果有的话）丢线行的长度
        int lose_right_first_2 = 0, lose_right_final_2 = 0;               //分别获取第二段丢线行（如果有的话）的起点行与最终行纵坐标
        lose_right_length_1 = firstloseline_right - finalloseline_right;    //获取第一段丢线行的长度

        lose_right_first_2 = findfirstlose(finalloseline_right - 1, useful_line_further, RIGHT_DIR);//finalloseline_right - 1必不丢线，但还是从这一行遍历----好读一点
        if (lose_right_first_2 != -1)//找到第一丢线行了（finalloseline_right - 1 ,useful_line_further]
        {
            lose_right_final_2 = findfinallose(lose_right_first_2 - 1, useful_line_further, RIGHT_DIR);//在新找到的第一丢线行往上找//lose_right_first_2 - 1必丢线
            //最终丢线行范围 [lose_right_first_2 - 1,useful_line_further]//如果lose_right_first_2就是 useful_line_further ，最终得到最终丢线行也是 useful_line_further

            lose_right_length_2 = lose_right_first_2 - lose_right_final_2;    //获取第二段丢线长度

            if (lose_right_length_2 > lose_right_length_1 || lose_right_length_2 > useful_length)    //第二段丢线比第一段长或大于一定值
            {
                firstloseline_right = lose_right_first_2;                   //将第二段丢线识别为第一段，丢弃较短的第一段丢线
                finalloseline_right = lose_right_final_2;
            }
        }   //以上为对存在两段丢线的情况的处理（使之成为“只有一段丢线”）
    }
    else
    {
        int lose_left_length_1 = 0, lose_left_length_2 = 0;             //分别获取第一段、第二段（如果有的话）丢线行的长度
        int lose_left_first_2 = 0, lose_left_final_2 = 0;               //分别获取第二段丢线行（如果有的话）的起点行与最终行纵坐标

        lose_left_length_1 = firstloseline_left - finalloseline_left;    //获取第一段丢线行的长度

        lose_left_first_2 = findfirstlose(finalloseline_left - 1, useful_line_further, LEFT_DIR);//finalloseline_right - 1必不丢线，但还是从这一行遍历----好读一点

        if (lose_left_first_2 != -1)//找到第一丢线行了（finalloseline_left - 1 ,useful_line_further]
        {
            lose_left_final_2 = findfinallose(lose_left_first_2 - 1, useful_line_further, LEFT_DIR);//在新找到的第一丢线行往上找//lose_left_first_2 - 1必丢线
            //最终丢线行范围 [lose_left_first_2 - 1,useful_line_further]//如果lose_left_first_2就是 useful_line_further ，最终得到最终丢线行也是 useful_line_further

            lose_left_length_2 = lose_left_first_2 - lose_left_final_2;            //获取第二段丢线长度

            if (lose_left_length_2 > lose_left_length_1 || lose_left_length_2 > useful_length)       //第二段丢线比第一段长或大于一定值
            {
                firstloseline_left = lose_left_first_2;                   //将第二段丢线识别为第一段，丢弃较短的第一段丢线
                finalloseline_left = lose_left_final_2;
            }
        }//以上为对存在两段丢线的情况的处理（使之成为“只有一段丢线”）
    }

}

//-------------------------------------------------------------------------------------------------------------------
// @brief       确定丢线行函数
// @param       firstlosedown       找第一次丢线时寻找范围的下限
// @param       firstloseup         找第一次丢线时寻找范围的上限
// @param       finalloseup         找左和右最终丢线行时寻找范围的上限
// @return  void
// @note        最终得到了左右两边的第一次丢线行，以及图像的最终丢线行，其中是否丢线的标志以及丢线的行数作为全局变量在进行赛道元素检测时也要用到
//              若找不到第一次丢线行，则其值为-1，且最终丢线行赋为-1，此时丢线行标志为0（认为整个边界不丢线）
//              在找得到第一次丢线行的基础上，再往上找最终丢线行，此时丢线行标志为1
// Sample usage：findloseline(49,9,9);
//-------------------------------------------------------------------------------------------------------------------
void findloseline(int firstlosedown, int firstloseup, int finalloseup)
{
    //重置变量与标志
    firstloseline_left = 0;
    firstloseline_right = 0;
    loserightflag = 0;

    finalloseline_right = 0;
    finalloseline_left = 0;
    loserightflag = 0;

    finalloseline = 0;
    useful_line_initial = 0;

    /******左边*******/
    firstloseline_left = findfirstlose(firstlosedown, firstloseup, LEFT_DIR); //在给定寻找范围内找右边的第一次丢线行

    if (firstloseline_left == (-1))//左边没有丢线
    {
        loseleftflag = 0;//左丢线标志置0
        finalloseline_left = -1;//改了一下4
    }
    else //第一次丢线行找到了才找最终丢线行
    {
        loseleftflag = 1;
        finalloseline_left = findfinallose(firstloseline_left, finalloseup, LEFT_DIR);//最终丢线行是第一次丢线行的基础上往上找的，故是在图像上方的

        //左最终丢线行调整（判断是否上方仍存在大段丢线）
        if (finalloseline_left > 25)//偏低
        {
            loseline_adjust(LEFT_DIR, 10);
            //finalloseline_left = finalloseline_adjust(finalloseline_left, LEFT_DIR, 10);
        }
    }

    /******右边*******/
    firstloseline_right = findfirstlose(firstlosedown, firstloseup, RIGHT_DIR);//在给定寻找范围内找左边的第一次丢线行

    if (firstloseline_right == -1)//右边没有丢线
    {
        loserightflag = 0;//右丢线标志置0
        finalloseline_right = -1;//改了一下4
    }
    else //第一次丢线行找到了才找最终丢线行
    {
        loserightflag = 1;
        finalloseline_right = findfinallose(firstloseline_right, finalloseup, RIGHT_DIR);

        //右最终丢线行调整（判断是否上方仍存在大段丢线）
        if (finalloseline_right > 25)//偏低
        {
            loseline_adjust(RIGHT_DIR, 10);
            //finalloseline_right = finalloseline_adjust(finalloseline_right, RIGHT_DIR, 10);
        }
    }



    /*******确定最终丢线行*******/
    if (finalloseline_right >= finalloseline_left) //两条图像上方分界线中，选一条偏下方（值较大）的作为最终丢线（若某一侧不丢线，值为-1，小于有丢线那一方，故也是取那方有丢线的）
    {
        if ((finalloseline_right >= 45 && firstloseline_left - finalloseline_left >= 5) || (firstloseline_left - finalloseline_left >= 15))//本来是选右边，但若右边丢线行太低，且左边存在大段丢线，则取左边（防止底部丢线导致不识别左右转）
            finalloseline = finalloseline_left;
        else
            finalloseline = finalloseline_right;

    }
    else
    {
        if ((finalloseline_left >= 45 && firstloseline_right - finalloseline_right >= 5) || (firstloseline_left - finalloseline_left >= 15))//本来是选左边，但若左边丢线行太低，且右边存在大段丢线，则取右边（防止底部丢线导致不识别左右转）
            finalloseline = finalloseline_right;
        else
            finalloseline = finalloseline_left;
    }


    if (loseleftflag == 1 && (firstloseline_left < finalloseline))//如果左边第一丢线行高于最终丢线行，左边认为不丢线，用意是？
    {
        loseleftflag = 0;
    }
    if (loserightflag == 1 && firstloseline_right < finalloseline)//如果右边第一丢线行高于最终丢线行，右边认为不丢线，用意是？
    {
        loserightflag = 0;
    }


    useful_line_further = USEFUL_FOR_LOSELINE;
    //确定最远有效行，用于元素判断的最远
    for (int i = IMG_H - 1; i >= USEFUL_FOR_LOSELINE; i--)
    {
        if (Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_BLACK && Binary_Image[i - 2][middle_line[i - 2]] == IMG_BLACK)//出现连续中线两行为黑，有效中线限制于此
        {
            useful_line_further = i;//找最远的有效中线
            break;
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
// @brief       计算图像黑点占比（用于十字路口检测）
// @param       left_down               左下拐点纵坐标
// @param       left_up                 左上拐点纵坐标
// @param       right_down          右下拐点纵坐标
// @param       right_up                右下拐点纵坐标
// @return  float                       图像黑点占比
// @note
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
float cross_bw_judge(int left_down, int left_up, int right_down, int right_up)
{
    int white_piont = 0, black_point = 0, totalpoint = 0;//累计黑点、白点、总像素点
    int x = 0, y = 0, xmax = 0, ymax = 0;//矩形左横坐标，矩形上纵坐标，矩形右横坐标，矩形下横坐标

    y = ((left_up >= right_up) ? right_up : left_up);//将纵坐标小(偏上方)的上拐点赋给y

    ymax = ((left_down >= right_down) ? left_down : right_down);//将纵坐标大(偏下方)的下拐点赋给ymax

    x = ((boundary_left[left_up] >= boundary_left[left_down])? boundary_left[left_down] : boundary_left[left_up]);//将横坐标小的左拐点赋给x

    xmax = ((boundary_right[right_up] >= boundary_right[right_down]) ? boundary_right[right_up]: boundary_right[right_down]);//将横坐标大的右拐点赋给xmax


    for (int i = x; i < xmax; i++)//检测像素点
    {
        for (int j = y; j < ymax; j++)
        {
            if (Binary_Image[j][i] == IMG_BLACK)//像素点为黑色
                black_point++;
            if (Binary_Image[j][i] == IMG_WHITE)//像素点为白色
                white_piont++;
            totalpoint++;//累计总像素点
        }
    }
    float per = 0;
    if (totalpoint != 0)
        per = (float)black_point / totalpoint;//计算黑色像素点占比
    else
        per = 1;

    return per;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       计算图像近车端矩形黑像素占比（用于路障识别）
// @param       x1  矩阵的0.5倍宽
// @param       y1矩阵的高
// @note
// return       per（0-1）
//-------------------------------------------------------------------------------------------------------------------
float cross_judge(int x1, int y1)//x1为矩形0.5倍的宽，y1为矩形的高
{
    int white_piont = 0, black_point = 0, totalpoint = 0;//累计黑点、白点、总像素点
    int x = 0, y = 0, xmax = 0, ymax = 0;//矩形左横坐标，矩形上纵坐标，矩形右横坐标，矩形下横坐标

    y=IMG_H-1-y1;
    ymax=IMG_H-1;
    x=IMG_W/2-x1;
    xmax=IMG_W/2+x1;

    for (int i = x; i < xmax; i++)//检测像素点
    {
        for (int j = y; j < ymax; j++)
        {
            if (Binary_Image[j][i] == IMG_BLACK)//像素点为黑色
                black_point++;
            if (Binary_Image[j][i] == IMG_WHITE)//像素点为白色
                white_piont++;
            totalpoint++;//累计总像素点
        }
    }
    float per = 0;
    if (totalpoint != 0)
        per = (float)black_point / totalpoint;//计算黑色像素点占比
    else
        per = 1;

    return per;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       左右边界补线函数（主要用于十字路口补线）
// @param       down_y                  下拐点纵坐标
// @param       down_x                  下拐点横坐标
// @param       up_y                        上拐点纵坐标
// @param       up_x                        上拐点横坐标
// @param       dir                     RIGHT_DIR / LEFT_DIR    方向
// @return  void
// @note        将上下拐点间的边线写为一条直线
// Sample usage：repair_line(down_left, boundary_left[down_left], up_left, boundary_left[up_left], LEFT_DIR);
//-------------------------------------------------------------------------------------------------------------------
void repair_line(int down_y, int down_x, int up_y, int up_x, int dir)
{
    // x = ky + b    如 boundry_left[y] = k * y + b

    float k, b;

    if (up_y - down_y != 0)
    {
        k = (float)(up_x - down_x) / (float)(up_y - down_y);
        b = (float)up_x - k * (float)up_y;
        if (dir == LEFT_DIR)
        {
                for (int i = up_y; i <= down_y; i++)
                        boundary_left[i] = (int)(k * i + b);  //根据x = ky + b 更新每行的左边界横坐标
        }
        if (dir == RIGHT_DIR)
        {
                for (int i = up_y; i <= down_y; i++)
                        boundary_right[i] = (int)(k * i + b); //根据x = ky + b 更新每行的右边界横坐标
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       中线连线修正函数
// @param       downx                   下拐点横坐标
// @param       downy                   下拐点纵坐标
// @param       upx                     上拐点横坐标
// @param       upy                     上拐点纵坐标
// @return  void
// @note
// Sample usage：repair_middline(middle_line[imgheight - 1], (imgheight - 1), boundary_left[finalloseline_left + 1], (finalloseline_left + 1));
//-------------------------------------------------------------------------------------------------------------------
void repair_middline(int downx, int downy, int upx, int upy)
{
    //x = ky + b
    float k, b;
    if (upy - downy != 0)
    {
        k = (float)(upx - downx) / (float)(upy - downy);
        b = (float)upx - k * (float)upy;
        for (int i = upy; i <= downy; i++)
            middle_line[i] = (int)(k * i + b);
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       中线偏移函数
// @param       downy                   下拐点纵坐标
// @param       upy                     上拐点纵坐标
// @param       num                     偏移坐标数
// @return  void
// @note
// Sample usage：repair_middline(middle_line[imgheight - 1], (imgheight - 1), boundary_left[finalloseline_left + 1], (finalloseline_left + 1));
//-------------------------------------------------------------------------------------------------------------------
void repair_middline_2(int down_y, int up_y,int dir ,int num)
{
    if (up_y - down_y != 0){
        for (int i = up_y; i <= down_y; i++){

        if (dir == LEFT_DIR)
        {
           for (int i = up_y; i <= down_y; i++)
               middle_line[i] = middle_line[i]-num;
        }
        if (dir == RIGHT_DIR)
        {
           for (int i = up_y; i <= down_y; i++)
               middle_line[i] = middle_line[i]+num;
        }
    }}}
//-------------------------------------------------------------------------------------------------------------------
// @brief       根据左右边界重写中线函数
// @param       void
// @return  void
// @note
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void re_midline()
{
    for(int i = 0; i < IMG_H; i++)
        middle_line[i] = (boundary_left[i] + boundary_right[i])/2;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       参考路径生成函数（计算路宽）
// @param       void
// @return      void
// @note        在调用搜线函数后再调用此函数
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void Road_Refer_Generate()
{
    if (cross_full_flag == 0 && cross_half_flag == 0 && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && cross_after_turn_flag == 0
        && left_roundabout_flag == 0 && right_roundabout_flag == 0 )//特殊元素不更新
    {
        int i, count;
        float leftk, rightk;            //斜率
        for (i = IMG_H - 1; i >= 0; i--)
        {
            Road_Refer_Left[i] = boundary_left[i];
            Road_Refer_Right[i] = boundary_right[i];
            Road_Width[i] = boundary_right[i] - boundary_left[i];
        }

//        leftk = (float)0.95;//leastSquareLinearFit(LEFT_DIR,44,48);
//        rightk = (float)(-0.95);//leastSquareLinearFit(RIGHT_DIR,44,48);
        leftk = 0.95;
              rightk = 0.95;


        count = 1;
        for (i = IMG_H - 2; i >= 0; i--)
        {
            if (boundary_left[IMG_H - 1] + leftk * count < 0 || boundary_left[IMG_H - 1] + leftk * count > 119 || boundary_right[IMG_H - 1] + rightk * count < 0 || boundary_right[IMG_H - 1] + rightk * count > 119)
            {
                break;
            }
            Road_Refer_Left[i] = (int)(boundary_left[IMG_H - 1] + leftk * count);
            Road_Refer_Right[i] = (int)(boundary_right[IMG_H - 1] + rightk * count);
            Road_Width[i] = Road_Refer_Right[i] - Road_Refer_Left[i];
            count++;
            if (Road_Width[i] <= 0)
            {
                break;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       弯道识别处理函数
// @param       void
// @return  void
// @note        识别弯道，重写中线，置相应标志位
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
void turn_recog()
{
    right_turn_flag = 0;                                                                                                    //右转弯标志位清零
    left_turn_flag = 0;                                                                                                     //左转弯标志位清零

    if (cross_full_flag == 0 && cross_half_flag == 0 \
        && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && left_cross_end_frame_flag == false && right_cross_end_frame_flag == false \
        && (left_roundabout_flag == 0 || (left_roundabout_flag == 1 && left_roundabout_in_flag == 1)) \
        && (right_roundabout_flag == 0 || (right_roundabout_flag == 1 && right_roundabout_in_flag)) \


        )
        //不是全十字、上半十字和左右环岛的前提下，做以下弯道处理。如果处于三岔内部而没有补线，也进行转弯处理
    {
        if (loserightflag == 1 /*&& loseleftflag == 0*/)        //右边有丢线（右第一丢线行不为-1（<=49），且要比最终丢线行低）      右转弯判定                                                                                      //右边有丢线      开启右转弯判定
        {
            //改了一下4
            if (firstloseline_right == IMG_H - 1)      //右边最低行丢线(最终丢线行<49)，判断是否还有第二段更长的丢线
            {
                loseline_adjust(RIGHT_DIR, 8);  //丢线行调整
            }
            if (finalloseline_right < (IMG_H - 5) && finalloseline_right >= useful_line_further && firstloseline_right - finalloseline_right >= 8/*10*//*6*/)
            {   /* 最终丢线行限定在45-5之间，丢线行长度>=10 */

                int leftcount = 0;            //左边界延伸趋势计数

                for (int i = IMG_H - 1; i > IMG_H - 30; i--) //左边界右上延伸趋势
                {
                    if (boundary_left[i - 1] > boundary_left[i])
                        leftcount++;                                  //左边界弯曲程度条件计数
                }

                if (leftcount > 15/*10*/)//改了一下4
                {
                    if (Binary_Image[finalloseline_right][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_right - 1][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_right - 2][IMG_MIDDLE] == IMG_BLACK)
                    {
                        right_turn_flag = 1;                          //识别到了右转弯（标志位置1）
                    }
                }

            }

        }
        if (loseleftflag == 1 /*&& loserightflag == 1*/)         //左边有丢线 （左第一丢线行不为-1（<=49），且要比最终丢线行低 ）    左转弯判定                                                                                     //左边有丢线      左转弯判定
        {


            if (firstloseline_left == IMG_H - 1)      //左边第一丢线行==49(最终丢线行<49)，判断是否还有第二段更长的丢线
            {
                loseline_adjust(LEFT_DIR, 8);   //丢线行调整
            }
            if (finalloseline_left < (IMG_H - 5) && finalloseline_left >= USEFUL_FOR_LOSELINE /*改了一下4*/ && firstloseline_left - finalloseline_left >= /*10*/8)
            {   /* 丢线行限定在45-5之间，丢线行长度>=10 */

                int rightcot = 0;             //右边界计数

                //左转，数右边界左上延伸趋势
                for (int i = IMG_H - 1; i > IMG_H - 30; i--)
                {
                    if (boundary_right[i - 1] < boundary_right[i])
                        rightcot++;                                  //右边界弯曲程度条件计数
                }
                if (rightcot > 15)
                {
                    if (Binary_Image[finalloseline_left][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_left - 1][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_left - 2][IMG_MIDDLE] == IMG_BLACK)
                    {
                        left_turn_flag = 1;                          //识别到了左转弯（标志位置1）
                    }
                }
            }
        }


        //-------------------------------------右转弯处理-------------------------------//
        if (right_turn_flag == 1 && left_turn_flag == 0)
        {
#if TURN_PROCESS_WAY
            // 第一代渣渣转弯处理方法
            int temp = 0, temp1 = 0;//存储最下行中线与左边线横坐标差值，重写中线用
            temp = middle_line[(IMG_H - 1)] - boundary_left[(IMG_H - 1)];
            for (int i = IMG_H - 2; i >= finalloseline_right; i--)/*改了一下4，从倒数第二行计数到右最终丢线行*/
            {
                temp1 = boundary_left[i] + temp;//相当于以最下行为标准，重新确定上面各行的中点位置（这样每一行中点与左边线横坐标值都一样，除了中点已经越过图像右边界的情况）
                if (temp1 < IMG_W)
                    middle_line[i] = temp1;
                else    //中点超过了图像右边界，限制在最右处
                    middle_line[i] = IMG_W - 1;
            }
#else //近似直线打角，效果一般
            int count = 0;
            float rightk = (float)(IMG_W - 1 - middle_line[firstloseline_right]) / (firstloseline_right - finalloseline);
            for (int i = firstloseline_right; i >= finalloseline; i--)
            {
                if ((middle_line[firstloseline_right] + rightk * count) <= IMG_W - 1)
                {
                    middle_line[i] = (int)(middle_line[firstloseline_right] + rightk * count);
                    count++;
                }
                else
                {
                    middle_line[i] = IMG_W - 1;
                }
            }
#endif
        }
        //-------------------------------------左转弯处理-------------------------------//
        if (left_turn_flag == 1 && right_turn_flag == 0)
        {
#if TURN_PROCESS_WAY
            //第一代渣渣转弯处理方法
            int temp = 0, temp1 = 0;//存储最下行中线与右边线横坐标差值，重写中线用
            temp = boundary_right[(IMG_H - 1)] - middle_line[(IMG_H - 1)];
            for (int i = IMG_H - 2; i >= finalloseline_left; i--)/*改了一下4，从倒数第二行计数到左最终丢线行*/
            {
                temp1 = boundary_right[i] - temp;
                if (temp1 > 0)
                    middle_line[i] = temp1;
                else
                    middle_line[i] = 0;
            }
#else //近似直线打角，效果一般
            int count = 0;
            float leftk = (float)middle_line[firstloseline_left] / (firstloseline_left - finalloseline);
            for (int i = firstloseline_left; i >= finalloseline; i--)
            {
                if ((middle_line[firstloseline_left] - count * leftk) >= 0)
                {
                    middle_line[i] = (int)(middle_line[firstloseline_left] - count * leftk);
                    count++;
                }
                else
                    middle_line[i] = 0;
            }
#endif
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
// @brief       计算有效行函数
// @param       void
// @return      void
// @note
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
u8 Dynamic_useful_line()/*改了一下4*/
{
    u8 useful_line_temp = 0; //获取每一帧有效行前先复位，此为有效行临时变量

    //右转弯有效行
    if (right_turn_flag == 1 && left_turn_flag == 0) //右转弯标志位1 ， 左转弯标志位0
        useful_line_temp = finalloseline_right;           //有效行只到右边最终丢线行——范围[USEFUL_FOR_LOSELINE(9)，45）

    //左转弯有效行
    if (left_turn_flag == 1 && right_turn_flag == 0)
        useful_line_temp = finalloseline_left;           //有效行只到左边最终丢线行——范围[USEFUL_FOR_LOSELINE(9)，45）

    //十字有效行
    if (cross_useful_line != 0)
        useful_line_temp = cross_useful_line;

    //左环岛有效行START
    if (left_roundabout_useful_line >= useful_line_further && left_roundabout_useful_line < IMG_H - 1)
    {
        useful_line_temp = left_roundabout_useful_line;
    }
    //左环岛有效行END

    //右环岛有效行START
    if (right_roundabout_useful_line >= useful_line_further && right_roundabout_useful_line < IMG_H - 1)
    {
        useful_line_temp = right_roundabout_useful_line;
    }
    //右环岛有效行END


    if (useful_line_temp == 0)
    {
        //一般情况下有效行的处理START
        bool middle_line_mutation = false;//中线突变
        for (int i = IMG_H - 1; i >= useful_line_further; i--)
        {
            int judge1 = middle_line[i - 1] - middle_line[i];   //获取差值
            int judge2 = middle_line[i - 2] - middle_line[i];   //获取差值
            if ((judge1 > 10 || judge1 < -10) || (judge2 > 10 || judge2 < -10))//变化量在(-10,10)之外，则说明找到了中线突变点
            {
                //获取到的有效行 为 横坐标差值不超过最大限定偏差的点（从最下行到有效行 为 有效，这些行中中点横坐标差值不超过最大限定偏差(10)，再往上就无效了）
                useful_line_temp = i;
                middle_line_mutation = true;  //获取到了指定点，退出循环
                break;
            }
        }
        if (middle_line_mutation == false)//若没有获取到指定点
        {
            useful_line_temp = useful_line_further;//若从最低行往上找不到上述点，则直接取有效行 为 useful_line_further
        }
        //一般情况下有效行的处理END

        //有效行误识别到图像最低行，改有效行到图像中间
        if (useful_line_temp == (IMG_H - 1))
            useful_line_temp = IMG_H / 2;
    }

    return useful_line_temp;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       计算赛道中线偏差
// @param       void
// @return      float   返回赛道中线偏差
// @note        由于操作系统时序安排问题，在进行图像处理的过程中程序会不断地被优先级更高的控制打断
//              所以尽量采用临时变量，防止变量还在计算中就被传递到其他控制中，造成问题！
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------

float Middle_Error()
{
    int i;

    float middle_error_temp = 0;


    /*赛道偏差计算方式*/
    /*环岛*/
    if(right_roundabout_flag||left_roundabout_flag )
    {
        for (i = (IMG_H - 1); i >= useful_line; i--)
        {
            middle_error_temp += (IMG_MIDDLE - middle_line[i]);  //摄像头并不能处于绝对中线，需要人为定中线60
        }
        middle_error_temp = middle_error_temp / (IMG_H  - useful_line); //每一行的误差加起来再平均
    }
    else
    {

        /************误差分段权值处理**************/
        if (useful_line < (IMG_H - 1) && useful_line >= useful_line_further)
        {

            int line_temp = IMG_H - (int)((IMG_H - useful_line) / 2);
            float middle_error_temp1 = 0, middle_error_temp2 = 0;
            //先计算下部分赛道误差
            for (i = (IMG_H - 1); i >= line_temp; i--)
            {
                middle_error_temp1 += (IMG_MIDDLE - middle_line[i]);  //摄像头并不能处于绝对中线，需要人为定中线60
            }
            middle_error_temp1 = middle_error_temp1 / (IMG_H - line_temp);
            //先计算上部分赛道误差
            for (i = line_temp - 1; i >= useful_line; i--)
            {
                middle_error_temp2 += (IMG_MIDDLE - middle_line[i]);  //摄像头并不能处于绝对中线，需要人为定中线60
            }
            middle_error_temp2 = middle_error_temp2 / (line_temp - useful_line);
            //下部分权值为0.7，上部分权值为0.5
           middle_error_temp = (float)0.7 * middle_error_temp1/*下部分，即近端*/ + (float)0.5* middle_error_temp2/*上部分，即*/;


        }
    }



    /**************特殊赛道（环岛）偏差乘系数*************/
    /****************左******************/
    switch (Left_Roundabout_State)
    {
    case State3_Roundabout_To_In_3th_Repairline://状态三：入环右边界补线
    {
        if (!left_roundabout_in_change_angle)
            middle_error_temp = middle_error_temp * (float)1.8;//0.6;//普通补线
        else
            middle_error_temp = middle_error_temp * (float)1.6/*1.1*/;//强打角

    }
    break;
    case State4_Roundabout_In://状态四：内部处理
    {
        middle_error_temp = middle_error_temp * (float)1.0;
    }
    break;
    case State5_Roundabout_To_Out_Repairline:
    {
        //出环打角
        if (left_roundabout_out_right_repair_line)//当修正右边线时（出环打角）
        {
            middle_error_temp = middle_error_temp * (float)1.7;
            if(middle_error_temp<35){middle_error_temp=35;}
        }
        else if (left_roundabout_out_left_repair_line)//当修正左边线（即将结束的阶段）
        {
            middle_error_temp = middle_error_temp * (float)1.0;
        }
    }
    break;
    default:
        break;

    }
    /****************右******************/
    switch(Right_Roundabout_State)
    {
        case State3_Roundabout_To_In_3th_Repairline://状态三：入环右边界补线
            {
                if (!right_roundabout_in_change_angle)
                    middle_error_temp = middle_error_temp * (float)1.8/*1.5*//*0.6*/;//普通补线
                else
                    middle_error_temp = middle_error_temp * (float)1.6/*1.0*/;//强打角
            }
            break;
        case State4_Roundabout_In://状态四：内部处理
            {
                middle_error_temp = middle_error_temp * (float)/*0.8*/1.0;
            }
            break;
        case State5_Roundabout_To_Out_Repairline:
            {
                //出环打角
                if (right_roundabout_out_left_repair_line)//修正左边界（出环打角）
                {
                    middle_error_temp = middle_error_temp * (float)1.7;
                    if(middle_error_temp<-35){middle_error_temp=-35;}


                }
                else if(right_roundabout_out_right_repair_line)//修正右边界（即将结束的阶段）
                {
                    middle_error_temp = middle_error_temp * (float)1.0;
                }
            }
            break;
        default:
            break;

    }
//    if(flag_send==0||flag_send==8){middle_error_temp=middle_error_temp*0.44;}
    if(flag_send==0){middle_error_temp=middle_error_temp*0.8;}
    if(flag_send==8){middle_error_temp=middle_error_temp*0.5;}

//  if(right_turn_flag){if(middle_error_temp>15){middle_error_temp=15;}}
//  if(left_turn_flag){if(middle_error_temp<-15){middle_error_temp=-15;}}

    /***************偏差突变限幅*****************/

    /*******************偏差限幅*****************/
    if (middle_error_temp > 50)
        middle_error_temp = 50;
    if (middle_error_temp < -50)
        middle_error_temp = -50;

    return middle_error_temp;
}


//-------------------------------------------------------------------------------------------------------------------
        // @brief       起跑线函数
        // @param       void
        // @return      void
        // @note
        // Sample usage：
        //-------------------------------------------------------------------------------------------------------------------
        int startpoint_count_line = 0;//计算符合要求的行数(每一帧重置一次)
        int startline_second_discern_count = 0;
        int  startline_flag=0;
        int  startline_flag_delay=0;


        void find_startline()
              {if((flag_send==8||flag_send==0||brick_time_end>0)){

              int continuation_left;
              int continuation_right;

                  for (int i =IMG_H-10 ; i < IMG_H-1; i++) {
                      if(boundary_left[i]>=boundary_left[i+1]||boundary_left[i]>=boundary_left[i+2])
                      {
                          if(boundary_left[i]-boundary_left[i+1]<=3){continuation_left=1;}
                          else{     continuation_left=0;
                                       break;}
                      } }
                  for (int i =IMG_H-10 ; i < IMG_H-1; i++) {
                      if(boundary_right[i]<=boundary_right[i+1]||boundary_right[i]<=boundary_right[i+2])
                      {
                          if(boundary_right[i+1]-boundary_right[i]<=3){continuation_right=1;}
                          else{     continuation_right=0;break;}

                      }
                            }
                            if (firstloseline_left<10&&firstloseline_right<10

                                    &&continuation_right==1
                                    &&continuation_left==1
                                    ) {
                              //开始搜索斑马线
                      int in_ku_change_NUM = 0;//用于存储有多少行有这个现象
                      for (int i = IMG_H - 5; i > 20; i--)
                      {
                          int in_ku_change = 0;//用于存储每一行黑白跳变沿的数目

                          for (int j = 10; j < (IMG_W-10); j++)
                          {
                              if (Binary_Image[i][j] == IMG_WHITE && Binary_Image[i][j + 1] ==IMG_BLACK)
                              {
                                  in_ku_change++;

                              }
                          }
                          if (in_ku_change >= 5)

                          {
                              in_ku_change_NUM++;
                          }

                      }
                      if (in_ku_change_NUM >= 4)
                      {
                          startline_flag = 1;
                          startline_flag_delay=1;
                      }

              }}}
        //-------------------------------------------------------------------------------------------------------------------
                // @brief       标志位获取
                // @param       void
                // @return      void
                // @note
                // Sample usage：
                //-------------------------------------------------------------------------------------------------------------------
      void flag_send_get()
        {        //环岛1-5
      if( straight_flag ==1){flag_send=8;}//直道

      else if(RIGHT_Roundabout_State_step>0)
          {flag_send=RIGHT_Roundabout_State_step;}
          else if(LEFT_Roundabout_State_step>0)
          {flag_send=LEFT_Roundabout_State_step;}

        else if(left_turn_flag==1){flag_send=9;}//左转
        else if(right_turn_flag==1){flag_send=10;}//右转
        else if(cross_full_flag==1||cross_half_flag==1||left_turn_cross_flag == 1||right_turn_cross_flag == 1)
            {flag_send=11;}//十字，仅用于开始的识别
        else if(brick_right_flag==1&&judge_2<1){flag_send=6;}//右路障
        else if(brick_left_flag==1&&judge_2<1){flag_send=7;}//左路障
        else if(brick_time_end>0){flag_send=0;}
//        else if(brick_right_flag==1||brick_end_left==1){flag_send=6;}//右路障
//        else if(brick_left_flag==1||brick_end_right==1){flag_send=7;}//左路障
        else if(startline_flag==1){flag_send=12;}//起跑线

        else{flag_send=0;}
        }

//-------------------------------------------------------------------------------------------------------------------
// @brief       直线判别函数
// @param
// @return
// @note
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
      int straight_flag = 0;
      // 计算中线数组的方差和作为中线偏差
      int calculateMiddleLineVarianceSum() {
          double sum = 0.0;//用于存储方差的总和
          double mean = 0.0;//用于存储计算出的平均值
          for (int i = 0; i < useful_line; i++){
              mean += middle_line[i];
          }
          mean /= useful_line;

          for (int i = 0; i < useful_line; i++) {
              sum += (middle_line[i] - mean) * (middle_line[i] - mean);
          }
          return sum;
      }

      // 直道判别函数
    void detectStraightRoad() {
          // 计算中线数组的方差和作为中线偏差
          int middleLineVarianceSum = calculateMiddleLineVarianceSum();
          int continuation_left=0;
          int continuation_right=0;
    for (int i = 5; i < IMG_H-10; i++) {//左边线单调连续
        if(boundary_left[i]>=boundary_left[i+1]||boundary_left[i]>=boundary_left[i+2])
        {
            if(boundary_left[i]-boundary_left[i+1]<=2){continuation_left=1;}
            else{     continuation_left=0;
             break;}
        }}

    for (int i = 5; i < IMG_H-10; i++) {//有边线单调连续
        if(boundary_right[i]<=boundary_right[i+1]||boundary_right[i]<=boundary_right[i+2])
        {
            if(boundary_right[i+1]-boundary_right[i]<=1){continuation_right=1;}
            else{     continuation_right=0;break;}

        }
          }
          // 根据方差和判断是否为直道
          if (middleLineVarianceSum <2000&&(firstloseline_left<30&&firstloseline_right<30)//近端不丢线
              // ||(finalloseline_left>35||finalloseline_right>35))
                  && cross_full_flag==0&&cross_half_flag==0&&left_turn_cross_flag == 0&&right_turn_cross_flag == 0//
                  && left_roundabout_flag == 0//非环岛
                  && right_roundabout_flag == 0//非环岛
                  &&right_turn_flag == 0//非右转
                  &&left_turn_flag == 0//非左转
                  &&continuation_right==1//非右连续
                  &&continuation_left==1//非左连续
                  &&brick_right_flag==0//右路障
                  &&brick_left_flag==0//左路障
                  ) {
              straight_flag = 1; // 是直道
          } else {
              straight_flag = 0; //不是直道
          }
      }
//-------------------------------------------------------------------------------------------------------------------
// @brief      路障识别函数
// @param
// @return
// @note
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
int brick_down_x;//下角点横坐标
int brick_down_y;//下角点纵坐标
int brick_up_x;//上角点横坐标
int brick_up_y;//上角点纵坐标
int brick_down_left_flag;//左路障下角点标志位
int brick_up_left_flag;//左路障上角点标志物
int brick_left_flag;//左路障标志位
int brick_down_right_flag;//右路障下角点标志位
int brick_up_right_flag;//右路障上角点标志位
int brick_right_flag;//右路障标志位
int brick_time=0;//路障时间
int brick_end_left=0;//左路障结束标志位
int brick_end_right=0;//右路障结束标志位
int brick_time_end=0;//路障结束阶段时间
int judge_2=0;//获取近车端矩形黑色像素点占比

 void find_brick()
 {
        brick_down_x=0;
        brick_down_y=0;
        brick_up_x=0;
        brick_up_y=0;
        judge_2=cross_judge(20,10)*10;//范围为0-10,0为全白，10为全黑

        if (
        ( left_turn_cross_flag == 0
        && right_turn_cross_flag == 0
        && left_cross_end_frame_flag == false
        && right_cross_end_frame_flag == false
        &&cross_full_flag==0
        &&cross_half_flag==0
        && left_roundabout_flag == 0
        && right_roundabout_flag == 0
        &&right_turn_flag == 0
        &&left_turn_flag == 0)
        ||(brick_time!=0||brick_time_end!=0)

        ) {

     //找左路障角点
            for (int i = (IMG_H-1); i >= 1; i--)
                {
                   if ((boundary_left[i] - boundary_left[i + 1] > 6 || boundary_left[i] - boundary_left[i + 2] > 6)/*横坐标存在突变*/
                   && boundary_left[i-1] - boundary_left[i] <= 4 && boundary_left[i-2 ] - boundary_left[i] <= 4 /*限制拐点与上方点横坐标的差距*/
                   )//找下角点
                   {

                       //判断拐点周围白点个数
                           int whitecount_right_point = 0;
                           for (int k = -1; k < 2; k++)
                           {
                               for (int k = -1; k < 2; k++)
                                           {
                                               for (int g = -1; g < 2; g++)
                                               {
                                                   if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_left[i] + g >= 0 && boundary_left[i] + g <= IMG_W - 1)//防止数组越界
                                                   {
                                                       if (Binary_Image[i + k][boundary_left[i] + g] == IMG_WHITE)
                                                           whitecount_right_point++;
                                                   }
                                               }
                                           }
                           }
                           if (whitecount_right_point >= 4)//白点数大于一定值
                           {
                               brick_down_x=boundary_left[i];
                                  brick_down_y=i;
                                  brick_down_left_flag=1;
                                  break;
                           }
                     }}
  if(   brick_down_left_flag==1){  for (int i = (IMG_H-1); i >= 1; i--)
    {
     if (   (boundary_left[i] - boundary_left[i -1] >= 1|| boundary_left[i] - boundary_left[i - 2] >= 1)/*横坐标存在突变*/
    && boundary_left[i] - boundary_left[i + 1] <= 4 && boundary_left[i +1] - boundary_left[i+2] <= 4 /*限制拐点与下方点横坐标的差距*/
  )//找上角点
    {
         //判断拐点周围白点个数
              int whitecount_right_point = 0;
              for (int k = -1; k < 2; k++)
              {
                  for (int k = -1; k < 2; k++)
                              {
                                  for (int g = -1; g < 2; g++)
                                  {
                                      if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_left[i] + g >= 0 && boundary_left[i] + g <= IMG_W - 1)//防止数组越界
                                      {
                                          if (Binary_Image[i + k][boundary_left[i] + g] == IMG_WHITE)
                                              whitecount_right_point++;
                                      }
                                  }
                              }
              }
              if (whitecount_right_point >= 4)//白点数大于一定值
              {
                  brick_up_x=boundary_left[i];
                  brick_up_y=i;
                  brick_up_left_flag=1;
                  break;
              }
    }
    }}




     //找右路障角点
     for (int i = (IMG_H-1); i >= 1; i--)
     {
         if ((boundary_right[i+1] - boundary_right[i] >5 || boundary_right[i+2] - boundary_right[i ] > 5)/*横坐标存在突变*/
             && boundary_right[i] - boundary_right[i-1] <= 4 && boundary_right[i-1] - boundary_right[i-2] <= 4 /*限制拐点与上方点横坐标的差距*/
         )//找下角点
         {
             //判断拐点周围白点个数
                 int whitecount_right_point = 0;
                 for (int k = -1; k < 2; k++)
                 {
                     for (int k = -1; k < 2; k++)
                                 {
                                     for (int g = -1; g < 2; g++)
                                     {
                                         if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)//防止数组越界
                                         {
                                             if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                                                 whitecount_right_point++;
                                         }
                                     }
                                 }
                 }
                 if (whitecount_right_point >= 4)//白点数大于一定值
                 {
                     brick_down_x = boundary_right[i];
                              brick_down_y=i;
                              brick_down_right_flag =1;
                     break;
                 }

         }}
  if(   brick_down_right_flag ==1){
     for (int i = (IMG_H-1); i >= 1; i--)
     {
            if (  (boundary_right[i-1] - boundary_right[i] >=1 || boundary_right[i-2] - boundary_right[i] >=1)/*横坐标存在突变*/
             && boundary_right[i+1] - boundary_right[i] <= 4 && boundary_right[i +2] - boundary_right[i+1] <= 4 /*限制拐点与下方点横坐标的差距*/
)//找上角点
         {
            //判断拐点周围白点个数
            int whitecount_right_point = 0;
            for (int k = -1; k < 2; k++)
            {
             for (int k = -1; k < 2; k++)
             {
                 for (int g = -1; g < 2; g++)
                 {
                     if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)//防止数组越界
                     {
                         if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                             whitecount_right_point++;
                     }
                 }
             }
            }
            if (whitecount_right_point >= 4)//白点数大于一定值
            {
             brick_up_x = boundary_right[i];
                 brick_up_y = i;
                 brick_up_right_flag=1;
             break;
            }

         }
     }}
     int continuation_left=0;
     int continuation_right=0;
     //边线单调连续性
for (int i = brick_up_y; i < brick_down_y; i++) {
if(boundary_left[i]>=boundary_left[i+1]||boundary_left[i]>=boundary_left[i+2])
{
   if(boundary_left[i]-boundary_left[i+1]<=3){continuation_left=1;}
   else{     continuation_left=0;  break;}

}
     }
for (int i = brick_up_y; i < brick_down_y; i++) {
if(boundary_right[i]<=boundary_right[i+1]||boundary_right[i]<=boundary_right[i+2])
{
   if(boundary_right[i+1]-boundary_right[i]<=3){continuation_right=1;}
   else{     continuation_right=0;break;}
}
}
//以下为对左路障的识别
if(brick_end_left==0&&continuation_right==1&&brick_up_left_flag&&brick_down_left_flag&&brick_down_y-brick_up_y<30
   &&brick_down_y-brick_up_y>5&&boundary_right[brick_down_y]-brick_down_x>2)
    //上下拐点都找到，右边线具有连续性，上下角点的纵坐标差小于30且大于5，与下角点相同纵坐标的右边线点的横坐标比下角点的横坐标差大于2
{
    for(int i=brick_up_y;i<=brick_down_y-1;i++)
    {  if(boundary_left[i]>=boundary_left[i+1]&&boundary_left[i]-boundary_left[i+1]<2&&boundary_right[i]-boundary_left[i]<=60//确保左边线的单调性，路宽小于60
        &&lost_left_flag[brick_up_y-1]==0&&lost_left_flag[brick_up_y-2]==0&&lost_left_flag[brick_down_y+1]==0&&lost_left_flag[brick_down_y+2]==0//路障的上下角点间不丢线
        )
    {
           double judge;//获取黑色像素点占比
     judge = cross_bw_judge(brick_down_y, brick_up_y, brick_down_y, brick_up_y);
     if (judge < 0.3)
     {
         brick_time=0;
         brick_left_flag = 1;//左路障识别成功
    }
    }
    }
}
  //以下为识别右路障
     if(brick_end_right==0&&continuation_left==1&&brick_up_right_flag&&brick_down_right_flag&&brick_down_y-brick_up_y<30&&brick_down_y-brick_up_y>5&&brick_down_x-boundary_left[brick_down_y]>2){
         for(int i=brick_up_y;i<=brick_down_y-1;i++)
         {
           if(boundary_right[i]<=boundary_right[i+1]&&boundary_right[i+1]-boundary_right[i]<2&&boundary_right[i]-boundary_left[i]<=60
           &&lost_right_flag[brick_up_y-1]==0&&lost_right_flag[brick_up_y-2]==0&&lost_right_flag[brick_down_y+1]==0&&lost_right_flag[brick_down_y+2]==0
           )
        {
               double judge;//获取黑色像素点占比
         judge = cross_bw_judge(brick_down_y, brick_up_y, brick_down_y, brick_up_y);
         if (judge < 0.3)
         {
             brick_right_flag = 1;//右路障识别成功
             brick_time=0;
         } }}}


     //左路障的控制应对（适用于气垫船，其他车型自行设计控制方式）
  if(brick_left_flag==1){error_else=-15;brick_time++;//通过直接在赛道偏差的基础上加error_else以实现赛道中线偏移，此时会偏右走
  if(judge_2>5){brick_end_left=1;}
  }
     if((brick_time>5&&brick_left_flag==1)||brick_end_left==1){//初识别路障时的计时，气垫船此时右漂5帧的时间
    error_else=0;
    brick_down_left_flag=0;
    brick_up_left_flag=0;
    brick_down_right_flag=0;
    brick_up_right_flag=0;
    brick_left_flag=0;
     brick_right_flag=0;
     brick_time=0;
     brick_end_left=1;}
     if(brick_end_left==1){brick_time_end++;if(judge_2>1&&brick_time_end<10){error_else=45;}else{error_else=0;}}//以judge_2判断是否严重出界，改变偏差以使车头转向
     if(brick_time_end>20){brick_end_left=0;brick_time_end=0; }//参数置零

     //右路障
     if(brick_right_flag==1){error_else=15;brick_time++;//通过直接在赛道偏差的基础上加error_else以实现赛道中线偏移，此时会偏左走
     if(judge_2>5){brick_end_right=1;}
     }
          if((brick_time>5&&brick_right_flag==1)||brick_end_right==1){//初识别路障时的计时，气垫船此时右漂5帧的时间
          error_else=0;
          brick_down_left_flag=0;
         brick_up_left_flag=0;
         brick_down_right_flag=0;
         brick_up_right_flag=0;
         brick_left_flag=0;
         brick_right_flag=0;
          brick_time=0;
          brick_end_right=1;
          }
          if(brick_end_right==1){brick_time_end++;if(judge_2>1&&brick_time_end<10){error_else=-45;}else{error_else=0;}}//以judge_2判断是否严重出界，改变偏差以使车头转向
          if(brick_time_end>20){brick_end_right=0;brick_time_end=0;}//参数置零

        }}
