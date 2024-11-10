#include "zf_common_headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       十字识别处理函数
// @param       void
// @return  void
// @note        识别十字或上半十字，补线，置相应标志位
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------

void left_turn_to_cross()//左转入十字识别与处理
{
    int down_point_y = 0, up_point_y = 0; //右下、上纵坐标
    int down_point_x = 0, up_point_x = 0; //右上、下横坐标

    bool find_down_point = false, find_up_point = false;//找到下、上拐点的标志

    //找下拐点，一般为右边界
    for (int righti = IMG_H - 4; righti > useful_line_further /*此值>=3,则righti>=4，防止数组越界*/; righti--)
    {
        if (boundary_right[righti - 2] - boundary_right[righti] >= 4 && boundary_right[righti - 3] - boundary_right[righti] >= 8 && boundary_right[righti - 4] - boundary_right[righti] >= 12 /*判断跳变范围（拐点上半部分）*/
            && (boundary_right[righti + 1] >= boundary_right[righti] && boundary_right[righti + 2] > boundary_right[righti] && boundary_right[righti + 3] > boundary_right[righti]) /*拐点下半部分趋势正确*/
            && Binary_Image[righti][middle_line[righti]] == IMG_WHITE && Binary_Image[righti - 1][middle_line[righti - 1]] == IMG_WHITE && Binary_Image[righti + 1][middle_line[righti + 1]] == IMG_WHITE /*拐点处为赛道*/)
        {
            //判断拐点周围白点个数
            int whitecount_right_point = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int g = -1; g < 2; g++)
                {
                    if (righti + k >= 0 && righti + k <= IMG_H - 1 && boundary_right[righti] + g >= 0 && boundary_right[righti] + g <= IMG_W - 1)
                    {
                        if (Binary_Image[righti + k][boundary_right[righti] + g] == IMG_WHITE)
                            whitecount_right_point++;
                    }
                }
            }
            if (whitecount_right_point >= 5)//白点数大于一定值
            {
                down_point_y = righti;
                down_point_x = boundary_right[righti];
                find_down_point = true; //找到下拐点了
                break;
            }
        }
    }
    //在找到下拐点的前提下，找上拐点，一般是左边界存在极大跳变
    if (find_down_point == true)
    {
        //从下拐点往上找左边界的跳变
        for (int lefti = down_point_y; lefti > useful_line_further; lefti--)
        {
            if (boundary_left[lefti] - boundary_left[lefti + 1] > 15 /*左边界存在极大跳变*/
                && (boundary_left[lefti] < down_point_x) /*上拐点横坐标比下拐点横坐标小*/
                && (boundary_left[lefti - 1] - boundary_left[lefti] > /*2*/0 /*&& boundary_left[lefti - 1] - boundary_left[lefti] < 8*/ && boundary_left[lefti - 2] - boundary_left[lefti] >= /*5*/3 && boundary_left[lefti - 3] - boundary_left[lefti] >= /*8*/5) /*拐点上部分检查，趋势足够*/
                && (boundary_left[lefti + 1] - boundary_left[lefti + 2] <= 3 && boundary_left[lefti + 2] - boundary_left[lefti + 3] <= 3)/*拐点下半部分检查*/
                && Binary_Image[lefti][middle_line[lefti]] == IMG_WHITE && Binary_Image[lefti - 1][middle_line[lefti - 1]] == IMG_WHITE && Binary_Image[lefti + 1][middle_line[lefti + 1]] == IMG_WHITE /*拐点处为赛道*/)
            {
                //看拐点上方从右到左是否存在连续黑转连续白
                int row = lefti - 2;
                for (int x = boundary_left[row] - 1; x > 5; x--)//先找到有跳变，起点为黑
                {
                    bool leftachieve = true;
                    bool rightachieve = true;
                    if (Binary_Image[row][x - 1] == IMG_WHITE)//x为跳变前的点（黑），x-1为跳变后的点（白）
                    {
                        for (int i = x - 1; i > x - 1 - 5; i--)//左边满足有连续5个白点
                        {
                            if (Binary_Image[row][i] != IMG_WHITE)
                            {
                                leftachieve = false;
                                break;
                            }
                        }
                        if (!leftachieve)
                        {
                            continue;
                        }
                        else
                        {
                            for (int i = x; i < x + 5; i++)//左边满足条件的情况下，判断右边是否有连续5个黑点
                            {
                                if (Binary_Image[row][i] != IMG_BLACK)
                                {
                                    rightachieve = false;
                                    break;
                                }
                            }
                            if (!rightachieve)
                            {
                                continue;
                            }
                            else
                            {
                                find_up_point = true; //找到上拐点了
                                up_point_y = lefti;
                                up_point_x = boundary_left[lefti];
                            }
                        }
                    }
                }
            }
        }
    }
    //上下拐点都找到，补右边线
    if (find_down_point && find_up_point)
    {
        left_turn_cross_flag = 1;
        repair_line(down_point_y, down_point_x, up_point_y, up_point_x, RIGHT_DIR);
        if (firstloseline_left - finalloseline_left >= 8 && finalloseline_left >= 10 && finalloseline_left <= IMG_H - 10)
            repair_line(IMG_H - 1, boundary_left[IMG_H - 1], up_point_y + 1, boundary_left[up_point_y + 1], LEFT_DIR);
        re_midline();

        //补线了，则取有效行
        cross_useful_line = up_point_y + 1; //有效行取到上拐点处
    }

}
void right_turn_to_cross()//右转入十字识别与处理
{
    int down_point_y = 0, up_point_y = 0; //右下、上纵坐标
    int down_point_x = 0, up_point_x = 0; //右上、下横坐标

    bool find_down_point = false, find_up_point = false;//找到下、上拐点的标志

    //找下拐点，一般为左边界
    for (int lefti = IMG_H - 4; lefti > useful_line_further /*此值>=3,则 lefti>=4，防止数组越界*/; lefti--)
    {
//        if (boundary_left[lefti] - boundary_left[lefti - 2] >= 4 && boundary_left[lefti] - boundary_left[lefti - 3] >= 8 && boundary_left[lefti] - boundary_left[lefti - 4] >= 12 /*判断跳变范围（拐点上半部分）*/
//            && (boundary_left[lefti + 1] <= boundary_left[lefti] && boundary_left[lefti + 2] < boundary_left[lefti] && boundary_left[lefti + 3] < boundary_left[lefti]) /*拐点下半部分趋势正确*/
//            && Binary_Image[lefti][middle_line[lefti]] == IMG_WHITE && Binary_Image[lefti - 1][middle_line[lefti - 1]] == IMG_WHITE && Binary_Image[lefti + 1][middle_line[lefti + 1]] == IMG_WHITE /*拐点处为赛道*/)
        if (boundary_left[lefti] - boundary_left[lefti - 2] >= 2 && boundary_left[lefti] - boundary_left[lefti - 3] >= 5 && boundary_left[lefti] - boundary_left[lefti - 4] >= 10 /*判断跳变范围（拐点上半部分）*/
                   && (boundary_left[lefti + 1] <= boundary_left[lefti] && boundary_left[lefti + 2] < boundary_left[lefti] && boundary_left[lefti + 3] < boundary_left[lefti]) /*拐点下半部分趋势正确*/
                   && Binary_Image[lefti][middle_line[lefti]] == IMG_WHITE && Binary_Image[lefti - 1][middle_line[lefti - 1]] == IMG_WHITE && Binary_Image[lefti + 1][middle_line[lefti + 1]] == IMG_WHITE /*拐点处为赛道*/)
        {
            //判断拐点周围白点个数
            int whitecount_right_point = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int g = -1; g < 2; g++)
                {
                    if (lefti + k >= 0 && lefti + k <= IMG_H - 1 && boundary_left[lefti] + g >= 0 && boundary_left[lefti] + g <= IMG_W - 1)
                    {
                        if (Binary_Image[lefti + k][boundary_left[lefti] + g] == IMG_WHITE)
                            whitecount_right_point++;
                    }
                }
            }
            if (whitecount_right_point >= 4)//白点数大于一定值
            {
                down_point_y = lefti;
                down_point_x = boundary_left[lefti];
                find_down_point = true; //找到下拐点了
                break;
            }
        }
    }
    //在找到下拐点的前提下，找上拐点，一般是右边界存在极大跳变
    if (find_down_point == true)
    {
        //从下拐点往上找右边界的跳变
        for (int righti = down_point_y; righti > useful_line_further; righti--)
        {
            if (boundary_right[righti + 1] - boundary_right[righti] > 10 /*右边界存在极大跳变*/
                && (boundary_right[righti] > down_point_x) /*上拐点横坐标比下拐点横坐标大*/
                && (boundary_right[righti] - boundary_right[righti - 1] > /*2*/0 /*&& boundary_right[righti] - boundary_right[righti - 1] < 8*/ && boundary_right[righti] - boundary_right[righti - 2] >= /*5*/3 && boundary_right[righti] - boundary_right[righti - 3] >= /*8*/5) /*拐点上部分检查，趋势足够*/
                && (boundary_right[righti + 2] - boundary_right[righti + 1] <= 3 /*&& boundary_right[righti + 3] - boundary_right[righti + 2] <= 3*/)/*拐点下半部分检查*/
                && Binary_Image[righti][middle_line[righti]] == IMG_WHITE && Binary_Image[righti - 1][middle_line[righti - 1]] == IMG_WHITE && Binary_Image[righti + 1][middle_line[righti + 1]] == IMG_WHITE /*拐点处为赛道*/)
            {
                //看拐点上方从左到右是否存在连续黑转连续白
                int row = righti - 2;
                for (int x = boundary_right[row] + 1; x < IMG_W - 5; x++)//先找到有跳变，起点为黑
                {
                    bool leftachieve = true;
                    bool rightachieve = true;
                    if (Binary_Image[row][x + 1] == IMG_WHITE)//x为跳变前的点（黑），x+1为跳变后的点（白）
                    {
                        for (int i = x + 1; i < x + 1 + 5; i++)//左边满足有连续5个白点
                        {
                            if (Binary_Image[row][i] != IMG_WHITE)
                            {
                                rightachieve = false;
                                break;
                            }
                        }
                        if (!rightachieve)
                        {
                            continue;
                        }
                        else
                        {
                            for (int i = x; i > x - 5; i--)//左边满足条件的情况下，判断右边是否有连续5个黑点
                            {
                                if (Binary_Image[row][i] != IMG_BLACK)
                                {
                                    leftachieve = false;
                                    break;
                                }
                            }
                            if (!leftachieve)
                            {
                                continue;
                            }
                            else
                            {
                                find_up_point = true; //找到上拐点了
                                up_point_y = righti;
                                up_point_x = boundary_right[righti];
                            }
                        }
                    }
                }
            }
        }
    }
    //上下拐点都找到，补右边线
    if (find_down_point && find_up_point)
    {
        right_turn_cross_flag = 1;
        repair_line(down_point_y, down_point_x, up_point_y, up_point_x, LEFT_DIR);
        if (firstloseline_right - finalloseline_right >= 8 && finalloseline_right >= 10 && finalloseline_right <= IMG_H - 10)//若右边存在大段丢线，也进行补线
            repair_line(IMG_H - 1, boundary_right[IMG_H - 1], up_point_y + 1, boundary_right[up_point_y + 1], RIGHT_DIR);
        re_midline();

        //补线了，则取有效行
        cross_useful_line = up_point_y + 1; //有效行取到上拐点处
    }
}
int cross_time=0;
int cross_time2=0;

void cross_recog()
{
//{if((cross_full_flag==1||cross_half_flag==1||left_turn_cross_flag == 1||right_turn_cross_flag == 1)&&cross_time==0)
//{cross_time++;
//cross_time2=1;}
// if(cross_time>0){cross_time++;}
// if((cross_full_flag==1||cross_half_flag==1||left_turn_cross_flag == 1||right_turn_cross_flag == 1)&&cross_time>100)
// {cross_time=0;}
    if (left_roundabout_flag == 0 && right_roundabout_flag == 0
            )/*条件互锁*/
    {
        //相关变量与标志位
        cross_half_flag = 0;
        cross_full_flag = 0;
        left_turn_cross_flag = 0;
        right_turn_cross_flag = 0;
        cross_after_turn_flag = 0;

        cross_useful_line = 0;

        int L_Down_Pointx = 0, L_Down_Pointy = 0; //左下拐点横纵坐标
        int L_Up_Pointx = 0, L_Up_Pointy = 0;//左上拐点横纵坐标
        int R_Down_Pointx = 0, R_Down_Pointy = 0; //右下拐点横纵坐标
        int R_Up_Pointx = 0, R_Up_Pointy = 0;//右上拐点横纵坐标


        _Bool Cross_R_Down_flag = false, Cross_R_Up_flag = false, Cross_L_Down_flag = false, Cross_L_Up_flag = false;//右下、右上、左下、左上标志位

        /***** 正常十字的判断与处理 ******/
        //寻找拐点
        //右：
        for (int i = (IMG_H - 1); i > useful_line_further; i--)//先找右下拐点并作标志位，注意限制找拐点上限，防止数组越界
        {
            if (boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] >= boundary_right[i - 1] /*原本是右边界横坐标越来越小，到右下拐点时才会增大*/
                && boundary_right[i - 2] - boundary_right[i] > 3 /*存在跳变*/)//找到右下拐点了
            {
                //判断拐点周围白点个数，确保周围为赛道
                int whitecount_right_down = 0;
                for (int k = -1; k < 2; k++)
                {
                    for (int g = -1; g < 2; g++)
                    {
                        if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)//防止数组越界
                        {
                            if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                                whitecount_right_down++;
                        }
                    }
                }
                if (whitecount_right_down >= 5)//九个点中有5个白点
                {
                    R_Down_Pointy = i;                      //记录右下拐点横纵坐标
                    R_Down_Pointx = boundary_right[i];
                    Cross_R_Down_flag = true;               //找到右下拐点了
                    break;
                }
            }
        }
        if (Cross_R_Down_flag)//如果找到了右下拐点，再往上找右上拐点（要以找到了右下拐点为前提）
        {
            for (int i = R_Down_Pointy; i >= useful_line_further; i--)  //找右上拐点并作标志位
            {
                if (boundary_right[i] - boundary_right[i - 1] > 5  /*上拐点横坐标突然变小*/
                    && ((boundary_right[i - 2] - boundary_right[i - 3] < 3) || (boundary_right[i - 1] - boundary_right[i - 2] < 3))/*限制上拐点上方点横坐标差距*/)
                {
                    //判断拐点周围白点个数，确保周围为赛道
                    int whitecount_right_up = 0;
                    for (int k = -1; k < 2; k++)
                    {
                        for (int g = -1; g < 2; g++)
                        {
                            if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)
                            {
                                if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                                    whitecount_right_up++;
                            }
                        }
                    }
                    if (whitecount_right_up >= 4 && boundary_right[i - 2] < boundary_right[R_Down_Pointy])//判断周围白点个数,下拐点横坐标要比上拐点横坐标大
                    {
                        R_Up_Pointy = i - 2;                   //记录右上拐点横纵坐标
                        R_Up_Pointx = boundary_right[i - 2];
                        Cross_R_Up_flag = true;                //找到右上拐点了
                        break;
                    }
                }
            }
        }
        //左：
        for (int i = (IMG_H - 1); i > useful_line_further; i--)//找左下拐点并作标志位
        {
            if (boundary_left[i - 1] < boundary_left[i] && boundary_left[i - 2] <= boundary_left[i - 1] /*横坐标突然减小*/
                && boundary_left[i] - boundary_left[i - 2] > 3 /*存在跳变*/)
            {
                //计算判断拐点周围白点个数
                int whitecount_left_down = 0;
                for (int k = -1; k < 2; k++)
                {
                    for (int g = -1; g < 2; g++)
                    {
                        if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_left[i] + g >= 0 && boundary_left[i] + g <= IMG_W - 1)
                        {
                            if (Binary_Image[i + k][boundary_left[i] + g] != IMG_BLACK)
                                whitecount_left_down++;
                        }
                    }
                }
                if (whitecount_left_down >= 5)//判断周围白点个数
                {
                    L_Down_Pointy = i;
                    L_Down_Pointx = boundary_left[i];
                    Cross_L_Down_flag = true;
                    break;
                }
            }
        }
        if (Cross_L_Down_flag)//如果找到了左下拐点，再往上找左上拐点
        {
            for (int i = L_Down_Pointy; i >= useful_line_further; i--)//找左上拐点并作标志位
            {
                if ((boundary_left[i - 1] - boundary_left[i]) > 5 && ((boundary_left[i - 2] - boundary_left[i - 1] < 3) || (boundary_left[i - 3] - boundary_left[i - 2] < 3)))
                {
                    int whitecount_left_up = 0;
                    for (int k = -1; k < 2; k++)
                    {
                        for (int g = -1; g < 2; g++)
                        {
                            if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_left[i] + g >= 0 && boundary_left[i] + g <= IMG_W - 1)
                            {
                                if (Binary_Image[i + k][boundary_left[i] + g] == IMG_WHITE)
                                    whitecount_left_up++;
                            }
                        }
                    }
                    if (whitecount_left_up >= 4 && boundary_left[i - 2] > boundary_left[L_Down_Pointy])//判断周围白点个数，下横坐标要比上坐标小
                    {
                        L_Up_Pointy = i - 2;
                        L_Up_Pointx = boundary_left[i - 2];
                        Cross_L_Up_flag = true;
                        break;
                    }
                }
            }
        }

        //识别全十字
        // 下拐点范围 （ useful_line_further ，IMG_H - 1] ,上拐点范围 [ useful_line_further - 2, up_right）
        if (Cross_R_Down_flag && Cross_R_Up_flag && Cross_L_Down_flag && Cross_L_Up_flag) //四个拐点都找到了
        {
            if (L_Down_Pointx < R_Up_Pointx && L_Up_Pointx < R_Down_Pointx)//横坐标交叉比较
            {
                if (L_Down_Pointy > R_Up_Pointy && R_Down_Pointy > L_Up_Pointy)//纵坐标交叉比较
                {
                    double judge;//获取黑色像素点占比
                    judge = cross_bw_judge(L_Down_Pointy, L_Up_Pointy, R_Down_Pointy, R_Up_Pointy);
                    if (judge < 0.15)
                    {
                        cross_full_flag = 1;//十字位置为1
                    }
                }
            }
        }
        //识别上半十字
        if (cross_full_flag == 0)//没有识别到全十字
        {
            //重置相关变量与标志位
            L_Up_Pointx = 0; L_Up_Pointy = 0;//左上拐点横纵坐标清零
            R_Up_Pointx = 0; R_Up_Pointy = 0;//右上拐点横纵坐标清零
            Cross_L_Up_flag = false; Cross_R_Up_flag = false; //左上右上拐点标志位重置

            if (loseleftflag == 1 && loserightflag == 1)  //左右同时发生丢线
            {
                if (firstloseline_left == (IMG_H - 1) && firstloseline_right == (IMG_H - 1))        //左右两边都从最底下开始丢线（此时finalloseline_left与finalloseline_right<49)
                {
                    if (finalloseline_left < IMG_H - 6 && finalloseline_right < IMG_H - 6)         //限定最终丢线行高度（有一定的丢线长度，同时防止下方数组越界）
                    {
                        //获取上拐点坐标
                        for (int i = finalloseline_left + 5; i >= useful_line_further; i--)         //找左上拐点（从最终丢线行下方5行开始遍历）
                        {
                            if ((boundary_left[i] == 0) && (boundary_left[i - 1] - boundary_left[i]) > 5 && (boundary_left[i - 2] - boundary_left[i]) > 5)//左上拐点横坐标突然增大
                            {
                                L_Up_Pointy = i - 2;
                                L_Up_Pointx = boundary_left[i - 2];
                                Cross_L_Up_flag = true;
                                break;
                            }
                        }
                        for (int i = finalloseline_right + 5; i >= useful_line_further; i--)        //再找右上拐点（从最终丢线行下方5行开始遍历）
                        {
                            if ((boundary_right[i] == IMG_W - 1) && (boundary_right[i] - boundary_right[i - 1]) > 5 && (boundary_right[i] - boundary_right[i - 2]) > 5)//找到右上拐点了（会突然减小）
                            {
                                R_Up_Pointy = i - 2;
                                R_Up_Pointx = boundary_right[i - 2];
                                Cross_R_Up_flag = true;
                                break;
                            }
                        }
                        //判断上半十字
                        if (Cross_L_Up_flag && Cross_R_Up_flag && (L_Up_Pointy - 8 <= R_Up_Pointy && R_Up_Pointy <= L_Up_Pointy + 8) && L_Up_Pointx < R_Up_Pointx)//找到左上右上拐点且纵坐标相差较小
                        {
                            //矩形白点占比
                            int x1, x2, y;                                                //矩形横纵坐标
                            int white_point = 0, black_point = 0, totalpoint = 0;           //矩形中黑白点个数
                            x1 = L_Up_Pointx; x2 = R_Up_Pointx;                 //以左右上拐点的横坐标作为矩形的两个横坐标
                            y = ((L_Up_Pointy <= R_Up_Pointy) ? L_Up_Pointy : R_Up_Pointy);   //取纵坐标偏上方的作为矩形纵坐标

                            for (int j = y; j < IMG_H - 1; j++)         //检测像素点
                            {
                                for (int i = x1; i < x2; i++)
                                {
                                    if (Binary_Image[j][i] == IMG_BLACK)//像素点为黑色
                                        black_point++;
                                    else                                                                //像素点为白色
                                        white_point++;
                                    totalpoint++;                                               //累计总像素点
                                }
                            }
                            float per = 0;
                            if (totalpoint != 0)
                                per = (float)black_point / totalpoint;//计算黑色像素点占比
                            else
                                per = 1;
                            if (per < 0.1)                                                  //黑色占的较少（矩形区域内大面积为赛道）
                            {
                                cross_half_flag = 1;     //上半十字标志位置1
                            }

                        }
                    }
                }
            }
        }

        //十字处理
        if (cross_full_flag == 1 && cross_half_flag == 0)
        {
            repair_line(L_Down_Pointy, L_Down_Pointx, L_Up_Pointy, L_Up_Pointx, LEFT_DIR);      //左边界
            repair_line(R_Down_Pointy, R_Down_Pointx, R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//右边界
            re_midline();

            //补线了，则取有效行
            cross_useful_line = (L_Up_Pointy < R_Up_Pointy ? L_Up_Pointy : R_Up_Pointy);//有效行取到上拐点中高的一个
        }
        //上半十字处理
        if (cross_half_flag == 1 && cross_full_flag == 0)
        {
            array_set_uniform(boundary_left, L_Up_Pointx, L_Up_Pointy + 1, IMG_H);       //用于调整左边线 把第 up_left + 1(左上拐点处)到左第一次丢线处（最下面一行）的左边界都设为拐点处横坐标（ps：firstlose_left = IMG_H -1, 加1后为IMG_H，而此函数处理的最后一个数组元素恰为参数值（IMG_H）-1)
            array_set_uniform(boundary_right, R_Up_Pointx, R_Up_Pointy + 1, IMG_H);      //用于调整右边线 把第 up_right + 1(右上拐点处)到右第一次丢线处（最下面一行）的右边界都设为拐点处横坐标

            int adjust;             //获取左右丢线最高行纵坐标  数字越小越高
            adjust = ((L_Up_Pointy <= R_Up_Pointy) ? L_Up_Pointy : R_Up_Pointy); //取值更小的

            for (int i = adjust; i <= (IMG_H - 1); i++)
            {
                middle_line[i] = (boundary_left[i] + boundary_right[i]) / 2;                //根据调整后的边线调整中线
            }

            //补线了，则取有效行
            cross_useful_line = adjust;//有效行取到调整点处
        }

        /***** 弯入十字的判断与处理 ******/
        //左弯入十字
        if (cross_full_flag == 0 && cross_half_flag == 0 && loseleftflag == 1)//无全字且无半十字，且左边丢线
        {
            left_turn_to_cross();//左入十字的判断与处理
        }
        //若出现了弯入十字，则在弯入十字结束后的几帧内，放宽十字的条件
        if((left_turn_cross_flag == 1)||cross_time>10)
        {
            left_cross_end_frame_flag = true;
            left_cross_end_frame_count = 0;
        }
        if(left_cross_end_frame_flag && left_turn_cross_flag == 0)
        {
            left_cross_end_frame_count++;
            if(left_cross_end_frame_count <= 10)
            {
                //放宽十字条件
                if(cross_full_flag == 0 && cross_half_flag == 0)//在搜不到全十字和上半十字的前提下
                {
                    //右：
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//先找右下拐点并作标志位，注意限制找拐点上限，防止数组越界
                    {
                        if (boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] >= boundary_right[i - 1] /*原本是右边界横坐标越来越小，到右下拐点时才会增大*/
                            && boundary_right[i - 2] - boundary_right[i] >= 3 /*存在跳变*/
                            && boundary_right[i + 1] > boundary_right[i] /*拐点下部分*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE  && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE )//找到右下拐点了
                        {
                            R_Down_Pointy = i;                      //记录右下拐点横纵坐标
                            R_Down_Pointx = boundary_right[i];
                            Cross_R_Down_flag = true;               //找到右下拐点了
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)  //找右上拐点并作标志位
                    {
                        if (boundary_right[i] - boundary_right[i - 1] >=5  /*上拐点横坐标突然变小*/
                            && ((boundary_right[i - 2] - boundary_right[i - 3] < 3) || (boundary_right[i - 1] - boundary_right[i - 2] < 3))
                            && Binary_Image[i - 2][middle_line[i - 2]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE/*限制上拐点上方点横坐标差距*/)
                        {
                            R_Up_Pointy = i - 3;                   //记录右上拐点横纵坐标
                            R_Up_Pointx = boundary_right[i - 2];
                            Cross_R_Up_flag = true;                //找到右上拐点了
                            break;
                        }
                    }
                    //左：
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//找左下拐点并作标志位
                    {
                        if (boundary_left[i - 1] < boundary_left[i] && boundary_left[i - 2] <= boundary_left[i - 1] /*横坐标突然减小*/
                            && boundary_left[i] - boundary_left[i - 2] > 3 /*存在跳变*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)
                        {

                            L_Down_Pointy = i;
                            L_Down_Pointx = boundary_left[i];
                            Cross_L_Down_flag = true;
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)//找左上拐点并作标志位
                    {
                        if ((boundary_left[i] - boundary_left[i + 1]) > 5 && ((boundary_left[i - 1] - boundary_left[i] < 3) || (boundary_left[i - 2] - boundary_left[i - 1] < 3))
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)
                        {
                            L_Up_Pointy = i - 1;
                            L_Up_Pointx = boundary_left[i - 1];
                            Cross_L_Up_flag = true;
                            break;
                        }
                    }
                    if (Cross_R_Down_flag && Cross_R_Up_flag)        //找得到右上下拐点
                    {
                        repair_line(R_Down_Pointy, R_Down_Pointx, R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//右边界
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_R_Up_flag)                        //找不到右下拐点，只找到上拐点
                    {
                        repair_line(IMG_H - 1, boundary_right[IMG_H - 1], R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//右边界
                        cross_after_turn_flag = 1;
                    }
                    if (Cross_L_Down_flag && Cross_L_Up_flag)       //找得到左上下拐点
                    {
                        repair_line(L_Down_Pointy, L_Down_Pointx, L_Up_Pointy, L_Up_Pointx, LEFT_DIR);      //左边界
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_L_Up_flag)                       //找不到左下怪点，只找到上拐点
                    {
                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], L_Up_Pointy, L_Up_Pointx, LEFT_DIR);
                        cross_after_turn_flag = 1;
                    }
                    re_midline();

                    //补线了，则取有效行
                    if(Cross_R_Up_flag && Cross_L_Up_flag)
                        cross_useful_line = (L_Up_Pointy > R_Up_Pointy ? L_Up_Pointy : R_Up_Pointy);//有效行取到上拐点中低的一个
                    else if(Cross_R_Up_flag)
                        cross_useful_line = R_Up_Pointy;
                    else if(Cross_L_Up_flag)
                        cross_useful_line = L_Up_Pointy;
                }
            }
            else
            {
                left_cross_end_frame_flag = false;
                left_cross_end_frame_count = 0;
            }
        }

        //右弯入十字
        if(cross_full_flag == 0 && cross_half_flag == 0 && loserightflag == 1)//无全字且无半十字，且右边丢线
        {
            right_turn_to_cross();//右入十字的判断与处理
        }
        //若出现了弯入十字，则在弯入十字结束后的几帧内，放宽十字的条件
        if((right_turn_cross_flag == 1)||cross_time>10)
        {
            right_cross_end_frame_flag = true;//出现过弯入十字，标志位置1
            right_cross_end_frame_count = 0;
        }
        if (right_cross_end_frame_flag && right_turn_cross_flag == 0)
        {
            right_cross_end_frame_count++;
            if(right_cross_end_frame_count <= 3)
            {
                //放宽十字条件
                if (cross_full_flag == 0 && cross_half_flag == 0)//在搜不到全十字和上半十字的前提下
                {
                    //右：
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//先找右下拐点并作标志位，注意限制找拐点上限，防止数组越界
                    {
                        if (boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] >= boundary_right[i - 1] /*原本是右边界横坐标越来越小，到右下拐点时才会增大*/
                            && boundary_right[i - 2] - boundary_right[i] > 3 /*存在跳变*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)//找到右下拐点了
                        {
                            R_Down_Pointy = i;                      //记录右下拐点横纵坐标
                            R_Down_Pointx = boundary_right[i];
                            Cross_R_Down_flag = true;               //找到右下拐点了
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)  //找右上拐点并作标志位
                    {
                        if (boundary_right[i] - boundary_right[i - 1] > 5  /*上拐点横坐标突然变小*/
                            && ((boundary_right[i - 2] - boundary_right[i - 3] < 3) || (boundary_right[i - 1] - boundary_right[i - 2] < 3))
                            && Binary_Image[i - 2][middle_line[i - 2]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE/*限制上拐点上方点横坐标差距*/)
                        {
                            R_Up_Pointy = i - 2;                   //记录右上拐点横纵坐标
                            R_Up_Pointx = boundary_right[i - 2];
                            Cross_R_Up_flag = true;                //找到右上拐点了
                            break;
                        }
                    }
                    //左：
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//找左下拐点并作标志位
                    {
                        if (boundary_left[i - 1] < boundary_left[i] && boundary_left[i - 2] <= boundary_left[i - 1] /*横坐标突然减小*/
                            && boundary_left[i] - boundary_left[i - 2] > 3 /*存在跳变*/
                            && boundary_left[i + 1] < boundary_left[i] /*拐点下部分*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)
                        {

                            L_Down_Pointy = i;
                            L_Down_Pointx = boundary_left[i];
                            Cross_L_Down_flag = true;
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)//找左上拐点并作标志位
                    {
                        if ((boundary_left[i] - boundary_left[i + 1]) > 5 && ((boundary_left[i - 1] - boundary_left[i] < 3) || (boundary_left[i - 2] - boundary_left[i - 1] < 3))
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)
                        {
                            L_Up_Pointy = i - 1;
                            L_Up_Pointx = boundary_left[i - 1];
                            Cross_L_Up_flag = true;
                            break;
                        }
                    }
                    if (Cross_R_Down_flag && Cross_R_Up_flag)        //找得到右上下拐点
                    {
                        repair_line(R_Down_Pointy, R_Down_Pointx, R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//右边界
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_R_Up_flag)                        //找不到右下拐点，只找到上拐点
                    {
                        repair_line(IMG_H - 1, boundary_right[IMG_H - 1], R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//右边界
                        cross_after_turn_flag = 1;
                    }
                    if (Cross_L_Down_flag && Cross_L_Up_flag)       //找得到左上下拐点
                    {
                        repair_line(L_Down_Pointy, L_Down_Pointx, L_Up_Pointy, L_Up_Pointx, LEFT_DIR);      //左边界
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_L_Up_flag)                       //找不到左下怪点，只找到上拐点
                    {
                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], L_Up_Pointy, L_Up_Pointx, LEFT_DIR);
                        cross_after_turn_flag = 1;
                    }
                    re_midline();

                    //补线了，则取有效行
                    if(Cross_R_Up_flag && Cross_L_Up_flag)
                        cross_useful_line = (L_Up_Pointy > R_Up_Pointy ? L_Up_Pointy : R_Up_Pointy);//有效行取到上拐点中低的一个
                    else if(Cross_R_Up_flag)
                        cross_useful_line = R_Up_Pointy;
                    else if(Cross_L_Up_flag)
                        cross_useful_line = L_Up_Pointy;
                }
            }
            else
            {
                right_cross_end_frame_flag = false;
                right_cross_end_frame_count = 0;
            }
        }
    }

}
