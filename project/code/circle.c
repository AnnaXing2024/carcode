/*
 * circle.c
 *
 *  Created on: 2024年7月10日
 *      Author: 86139
 */

#ifndef CIRCLE_C_
#define CIRCLE_C_
#include "zf_common_headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       左环岛识别处理函数(状态机模式)
// @param       void
// @return      void
// @note        识别左环岛，补线，置相应标志位
//              注意：本环岛识别处理函数适用于分辨率为120*50的图像，若分辨率改变，请注意要调整其中的参数！！！
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
#if  USE_ROUNDABOUT_FSM
void left_roundabout_recog_by_FSM()
{
    //-----------------------------------左环岛处理START------------------------------------//

    //--------------------相关变量重置（每一帧都会重置）-------------------//
    find_roundabout_left_down = false; //左环岛下拐点识别标志
    find_roundabout_left_up = false; //左环岛上拐点识别标志
    find_roundabout_left_up_only = false; //左环岛只找到上拐点标志
    roundabout_left_down_y = 0;     //左环岛左下拐点纵坐标
    roundabout_left_down_x = 0;     //左环岛左下拐点横坐标
    roundabout_left_up_y = 0;     //左环岛左上拐点纵坐标
    roundabout_left_up_x = 0;     //左环岛左上拐点横坐标
    right_boundary_slope = 0;     //左边线斜率
    left_roundabout_useful_line = 0;//左环有效行

    if (cross_full_flag == 0 && cross_half_flag == 0 && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && cross_after_turn_flag == 0
        && right_roundabout_flag == 0   )//条件互锁，在没有十字、右环岛的时候进行左环岛判断
    {
        switch (Left_Roundabout_State)
        {
            //------------------第一阶段，先识别环岛（入环前期部分，通过双拐点或单拐点进行识别并补线）---------------//
            /****此阶段应该包括，有环岛特征（但还没确定为环岛）时的补线、确定为环岛后的补线（直到跳转到下一个阶段）****/
            case State1_Roundabout_Distern_1st_Repariline:
                {
                   // if (left_roundabout_discerning&&if_left_roundabout_recog)
                    if (left_roundabout_discerning)
                    {//left_roundabout_discerning用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
                     //if_left_roundabout_recog默认为1，当开启了“只做一次环岛”时，会在环岛识别并处理完后置0，如果要开启，还需将环岛最后的重置环节代码相关注释去掉


                        //搜索环岛标志点
                        if ((firstloseline_left != IMG_H - 1)||firstloseline_left>IMG_H-10)    //图像左边最低行不丢线
                        {
                            for (int i = IMG_H - 3; i > useful_line_further /*此值>=3*/; i--)  //左边边界条件的识别（寻找上下拐点）
                            {
                                if ( boundary_left[i] > 5 /*误判环岛，严格条件*/
                                    && boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >= boundary_left[i + 2] /*下拐点下方趋势为往左下延伸*/
                                    && boundary_left[i] - boundary_left[i + 1] < 3 && boundary_left[i + 1] - boundary_left[i] < 3 /*与下一行边界的差距在3以内*/
                                    && ((lost_left_flag[i - 1] == 1 && lost_left_flag[i - 2] == 1) || (lost_left_flag[i - 2] == 1 && lost_left_flag[i - 3] == 1) || (lost_left_flag[i] == 1 && lost_left_flag[i - 3] == 1) /*下拐点上方存在至少两行丢线*/ )
                                    && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点所在行为赛道*/)   //寻找下拐点
                                {
                                    find_roundabout_left_down = true;              //左边界下拐点识别到了
                                    roundabout_left_down_y = i;                    //记录下拐点对应纵坐标
                                    roundabout_left_down_x = boundary_left[i];     //记录下拐点对应横坐标
                                }
                                if (find_roundabout_left_down)                    //若找到了下拐点（前提），往上查找上拐点
                                {
                                    for (int j = roundabout_left_down_y - 1; j >= useful_line_further; j--)
                                    {
                                        if (boundary_left[j] >= boundary_left[j - 1] && boundary_left[j] >=boundary_left[j - 2] /*上拐点的上部分*/
                                            && boundary_left[j] >= boundary_left[j + 1] && boundary_left[j] >= boundary_left[j + 2] && boundary_left[j] >= boundary_left[j + 3] /*上拐点的下部分*/
                                            && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j - 2] >= 5 /*防止为边界*/
                                            && Binary_Image[j][boundary_left[j] + 2] == IMG_WHITE && Binary_Image[j - 1][boundary_left[j - 1] + 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*拐点所在处为赛道*/
                                            )
                                        {
                                            find_roundabout_left_up = true;                //左边界上拐点识别到了
                                            roundabout_left_up_y = j;                     //记录上拐点对应纵坐标
                                            roundabout_left_up_x = boundary_left[j];     //记录上拐点对应横坐标
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        else if (firstloseline_left == IMG_H - 1 && finalloseline_left > IMG_H - 15) //图像左下角有一小段丢线影响识别，要手动忽略（从最终丢线行往上寻找拐点）
                        {
                            for (int i = finalloseline_left - 1; i > useful_line_further ; i--)       //左边界上、下拐点识别（从丢线结束处开始识别）
                            {
                                if (boundary_left[i] > 5 /*误判环岛，严格条件*/
                                    && boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >= boundary_left[i + 2] /*下拐点下方趋势为往左下延伸*/
                                    && boundary_left[i] - boundary_left[i + 1] < 3 && boundary_left[i + 1] - boundary_left[i] < 3 /*与下一行边界的差距在3以内*/
                                    && ((lost_left_flag[i - 1] == 1 && lost_left_flag[i - 2] == 1) || (lost_left_flag[i - 2] == 1 && lost_left_flag[i - 3] == 1) || (lost_left_flag[i] == 1 && lost_left_flag[i - 3] == 1) /*下拐点上方存在至少2行丢线*/ )
                                    && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点所在行为赛道（白色）*/)   //寻找下拐点
                                {
                                    find_roundabout_left_down = true;              //左边界下拐点识别到了
                                    roundabout_left_down_y = i;                    //记录下拐点对应纵坐标
                                    roundabout_left_down_x = boundary_left[i];     //记录下拐点对应横坐标
                                }
                                if (find_roundabout_left_down)                    //若找到了下拐点（前提），往上查找上拐点
                                {
                                    for (int j = roundabout_left_down_y - 1; j >= useful_line_further; j--)
                                    {
                                        if (boundary_left[j] >= boundary_left[j - 1] && boundary_left[j] >= boundary_left[j - 2] /*上拐点的上部分*/
                                            && boundary_left[j] >= boundary_left[j + 1] && boundary_left[j] >= boundary_left[j + 2] && boundary_left[j] >=boundary_left[j + 3] /*上拐点的下部分*/
                                            && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j - 2] >= 5 /*防止为边界*/
                                            && Binary_Image[j][boundary_left[j] + 2] == IMG_WHITE && Binary_Image[j - 1][boundary_left[j - 1] + 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*拐点所在处为赛道*/
                                           )
                                        {
                                            find_roundabout_left_up = true;                //左边界上拐点识别到了
                                            roundabout_left_up_y = j;                     //记录上拐点对应纵坐标
                                            roundabout_left_up_x = boundary_left[j];     //记录上拐点对应横坐标
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }

                        //根据拐点对是否是环岛进行判断
                        if (left_roundabout_flag == 0) //未识别到环岛才进行判断
                        {
                            /*若能在一帧图像中同时找到两个拐点（最理想的情况）*/
                            if (find_roundabout_left_down && find_roundabout_left_up)
                            {
                                //没有以下误判情况，则识别帧计数条件加1
                                left_roundabout_discern_flag_count++;

                                for (int i = roundabout_left_up_y; i < roundabout_left_down_y; i++)//用于判断上下拐点（右左边线获得）间的右边线是否丢线了
                                {
                                        if(lost_right_flag[i]==1){
                                        left_roundabout_discern_flag_count = 0;
                                             break;}
                                    }
                                if (left_roundabout_discern_flag_count==0)//右边丢线
                                    break;  //退出switch，结束本帧环岛识别

//                                //处理一些误判情况（出现误判，则将识别帧计数条件置0）
                                //（其中一些条件不是很好，导致环岛识别不到，故注释掉了，如果在非环岛的地方误判环岛了，大家可以试试以下条件）
//                                //1：
//                                for (int counti = roundabout_left_down_y; counti >= roundabout_left_up_y; counti--)
//                                {
                                //对从下拐点到上拐点的每一行，看从左边界到右边界是否存在黑点，若存在，则将识别帧计数条件置0，并退出本帧的环岛识别
//                                    for (int countj = boundary_left[roundabout_left_up_y]; countj < boundary_right[roundabout_left_up_y]; countj++)
//                                    {
//                                        if (Binary_Image[counti][countj] == IMG_BLACK)
//                                        {
//                                            left_roundabout_discern_flag_count = 0;
//                                            break;
//                                        }
//                                    }
//                                    if (left_roundabout_discern_flag_count == 0)
//                                        break;  //退出外层循环
//                                }
//                                if (left_roundabout_discern_flag_count == 0)
//                                    break;  //退出switch，结束本帧环岛识别
//                                //2：
//                                if (!(boundary_right[roundabout_left_up_y] - boundary_left[roundabout_left_up_y] >= 5 && roundabout_left_down_y - roundabout_left_up_y >= 8 && loserightflag == 0))
//                                {// !() ：若不满足括号中的条件，即不满足（上拐点处右边界大于左边界一定值，且上下拐点的纵坐标有一定距离/*，且一边丢线，一边没有丢线*/）的条件，则将帧计数条件置0
//                                    left_roundabout_discern_flag_count = 0;
//                                    break;  //退出switch，结束本帧环岛识别
//                                }

//                                //3:上拐点的左边应几乎全黑
//                                int B2W_change_pointx_temp = 0;//黑白跳变点
//                                B2W_change_pointx_temp = findchange(roundabout_left_up_x - 1, LEFT_DIR, roundabout_left_down_y, IMG_WHITE, 0, 2, 1);//从上拐点左边找黑白跳变点
//                                if (roundabout_left_up_x - B2W_change_pointx_temp <= 5)//若上拐点左边很近即有黑白跳变点（说明不是上拐点）
//                                {
//                                    left_roundabout_discern_flag_count = 0;
//                                    break;  //退出switch，结束本帧环岛识别
//                                }
//                                //4:右边线斜率
//                                int boundary_Rdown_to_Lup_count = 0;   //右边界满足往左上延伸的趋势的累计计数条件
//                                for (int i = roundabout_left_down_y; i >= roundabout_left_up_y; i--)     //右边边界条件的识别，即右边界有从右下向左上延伸的趋势
//                                {
//                                    if (boundary_right[i] > boundary_right[i - 1])                  //下一行的横坐标比上一行的大
//                                    {
//                                        boundary_Rdown_to_Lup_count++;                              //记录右边界往左上延伸的趋势的累计计数
//                                    }
//                                }
//                                //计算右边线拐点处连线所在的直线斜率（这是一个负的斜率，往图像左上延伸）
//                                right_boundary_slope = (float)(roundabout_left_down_y - roundabout_left_up_y) / (boundary_right[roundabout_left_up_y] - boundary_right[roundabout_left_down_y]);
//
//                                if (boundary_Rdown_to_Lup_count < 0.7 * (roundabout_left_down_y - roundabout_left_up_y) || right_boundary_slope >= 0 /*|| boundary_right[roundabout_left_up_y] <= IMG_MIDDLE - 20*/)
//                                {//如果右边界右下往左上延伸趋势不够，或者右边界斜率为非负值，或者上拐点处的右边界过于偏左
//                                    left_roundabout_discern_flag_count = 0;
//                                    break;  //退出switch，结束本帧环岛识别
//                                }
                            }
                            /*若无法在一帧图像中同时找到两个拐点，则根据“只有上拐点”判断入环*/
                            //但为了提高准确率，还是需要至少能在某一帧识别到一下 下拐点，以将上拐点帧计数标志 打开
                            else if (find_roundabout_left_down && !find_roundabout_left_up)//找到下拐点而没有上拐点
                            {
                                //寻找是否有一定的 可以找到上拐点 的趋势（此时上拐点的条件很松，甚至只考虑上拐点的下半部分）
                                for (int i = (roundabout_left_down_y < IMG_H - 4 ? roundabout_left_down_y : IMG_H - 4)/*防止数组越界*/; i >= useful_line_further; i--)//从下拐点往上找
                                {
                                    //寻找下标识点，找到就开始记录找到点后已经过了几帧
                                    if (boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >=boundary_left[i + 2] && boundary_left[i + 1] >= boundary_left[i + 3] /*上拐点下方有向下延伸的趋势*/
                                        && boundary_left[i] >= 5 && boundary_left[i - 1] >= 5 && boundary_left[i + 1] >= 5  /*防止为边界*/
                                        && boundary_left[i] - boundary_left[i + 3] >= 5 /*上拐点的下方弧度足够*/
                                        && Binary_Image[i][boundary_left[i] + 2] == IMG_WHITE && Binary_Image[i- 1][boundary_left[i - 1] + 2] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点所在处为赛道*/
                                        && Binary_Image[i][middle_line[i]] == IMG_WHITE
                                        )
                                    {
                                        left_roundabout_only_up_point_flag = true; //上拐点帧计数标志打开
                                        left_roundabout_only_up_point_count = 0; //准备计数
                                        break;
                                    }

                                }

                            }

                            /*只有上拐点判断入环，承接上方else if*/
                            if (left_roundabout_only_up_point_flag)//如果找到下标识点后连续8帧都没有找到上标识点，则清零
                            {
                                left_roundabout_only_up_point_count++;

                                if (left_roundabout_only_up_point_count >= 8)//8帧根据具体情况改变
                                {
                                    left_roundabout_only_up_point_flag = false;
                                    left_roundabout_only_up_point_count = 0;
                                }
                            }

                            if (!find_roundabout_left_up && left_roundabout_only_up_point_flag)//如果没有找到上拐点，且上拐点帧计数标志为true（防止在下一帧又能同时找到上下拐点，则不执行下方语句）
                            {
                                //满足一定条件开始找上拐点(此时不管下拐点，若能找到上拐点，即判断环岛)
                                if (finalloseline_left <= IMG_H - 5)//最终丢线行
                                {
                                    for (int i = finalloseline_left; i >= useful_line_further; i--)
                                    {
                                        if (boundary_left[i] >= boundary_left[i - 1] && boundary_left[i] >= boundary_left[i - 2] /*上拐点的上半部分趋势正确*/
                                            && boundary_left[i] - boundary_left[i - 1] <= 5 && boundary_left[i - 1] - boundary_left[i] <= 5 && boundary_left[i] - boundary_left[i - 2] <= 5 && boundary_left[i - 2] - boundary_left[i] <= 5 /*限制拐点上方点的横坐标间距 */
                                            && boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] > boundary_left[i + 2] && boundary_left[i + 1] > boundary_left[i + 3] /*上拐点的下半部分趋势正确*/
                                            && boundary_left[i] - boundary_left[i + 4] >= 7 /*下拐点下半部分趋势足够*/
                                            && boundary_left[i] >= 2 && boundary_left[i - 1] >= 2 && boundary_left[i + 1] >= 2 && Binary_Image[i][boundary_left[i]] == IMG_WHITE/*防止为边界*/
                                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i]] == IMG_WHITE && Binary_Image[i - 2][middle_line[i]] == IMG_WHITE && Binary_Image[i - 3][middle_line[i]] == IMG_WHITE /*确保为赛道*/
                                            &&Binary_Image[i-3][boundary_left[i] ] == IMG_WHITE//确保为赛道
                                            )
                                        {
                                            roundabout_left_up_y = i;
                                            roundabout_left_up_x = boundary_left[i];

                                            //没有以下误判情况，则识别帧计数条件加1
                                            left_roundabout_discern_flag_count++;

                                            for (int i = roundabout_left_up_y-5; i < roundabout_left_up_y+5; i++) {
                                               if(lost_right_flag[i]==1){
                                                   left_roundabout_discern_flag_count = 0;break;
                                               } }
                                          if (left_roundabout_discern_flag_count==0)//右边丢线段

                                                                       break;  //退出switch，结束本帧环岛识别

                                            //处理一些误判情况（出现误判，则将识别帧计数条件置0,与上边相同）
//                                            //1：
//                                            if (!(boundary_right[roundabout_left_up_y] - roundabout_left_up_x >= 5 && loserightflag == 0))
//                                            {// !() ：若不满足括号中的条件，即不满足（上拐点处右边界大于左边界一定值/*，且一边丢线，一边没有丢线*/）的条件，则将帧计数条件置0
//                                                left_roundabout_discern_flag_count = 0;
//                                                continue; //继续寻找上拐点
//                                            }

//                                            //2:
//                                            for (int counti = finalloseline_left; counti >= roundabout_left_up_y; counti--)
//                                            {
//                                                //对从最终丢线行到上拐点的每一行，看从左边界到右边界是否存在黑点，若存在，则将识别帧计数条件置0，并退出本帧的环岛识别
//                                                for (int countj = boundary_left[roundabout_left_up_y]; countj < boundary_right[roundabout_left_up_y]; countj++)
//                                                {
//                                                    if (Binary_Image[counti][countj] == IMG_BLACK)
//                                                    {
//                                                        left_roundabout_discern_flag_count = 0;
//                                                        break;
//                                                    }
//                                                }
//                                                if (left_roundabout_discern_flag_count == 0)
//                                                    break;  //退出外层循环
//                                            }
//                                            if (left_roundabout_discern_flag_count == 0)
//                                                continue;  //继续寻找上拐点
//                                            //3:右边线斜率
//                                            int boundary_Rdown_to_Lup_count = 0;   //右边界满足往左上延伸的趋势的累计计数条件
//                                            for (int m = finalloseline_left; m >= roundabout_left_up_y; m--)     //右边边界条件的识别，即右边界有从右下向左上延伸的趋势
//                                            {
//                                                if (boundary_right[m] > boundary_right[m - 1])                  //下一行的横坐标比上一行的大
//                                                {
//                                                    boundary_Rdown_to_Lup_count++;                              //记录右边界往左上延伸的趋势的累计计数
//                                                }
//                                            }
//
//                                            if (boundary_Rdown_to_Lup_count < 0.85 * (finalloseline_left - roundabout_left_up_y) /*|| boundary_right[roundabout_left_up_y] <= IMG_MIDDLE - 20*/)
//                                            {//如果右边界右下往左上延伸趋势不够，或者上拐点处的右边界过于偏左
//                                                left_roundabout_discern_flag_count = 0;
//                                                continue;  //继续寻找上拐点
//                                            }

                                            //处理误判结束，若能执行到此，则帧计数条件>=2，根据车速调节
                                            if (left_roundabout_discern_flag_count >= 2)
                                            {
                                                find_roundabout_left_up_only = true;//只找到上拐点标志位置1
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                            /*需要的话再补充“斜入环岛函数”*/


                            //建议在能正入环岛后写一下斜入环岛


                            //环岛帧计数条件到达一定值后，成功识别环岛
                            if (left_roundabout_discern_flag_count >= ROUNDABOUT_DISCERN_COUNTS)
                            {
                                left_roundabout_flag = 1;
                            }
                            else if(left_roundabout_discern_flag_count != 0) //识别到了某一帧，但之后一直没有再识别到，当积累到某一帧，则清零
                            {
                                state_continue_frame_count++;
                                if(state_continue_frame_count >= 100)//帧数可调
                                {
                                    state_continue_frame_count = 0;
                                    left_roundabout_discern_flag_count = 0;
                                    break;
                                }
                            }
                        }

                        //根据不同的拐点情况进行补线
                        if (left_roundabout_flag == 1)//识别到环岛
                        {
                            left_roundabout_state1_repairline_count++; //第一阶段补线帧计数条件+1

                            //1:找到两个拐点，补线
                            if (find_roundabout_left_down && find_roundabout_left_up)
                            {
                                repair_line(roundabout_left_down_y, roundabout_left_down_x, roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR);//根据左上下拐点对左边线进行修正（补线）

                                re_midline(); //根据左右两边线重写中线
                                LEFT_Roundabout_State_step=1;
                                //如果补线了，则取有效行
                                left_roundabout_useful_line = roundabout_left_up_y;
                            }
                            //2:只有上拐点，补线
                            else if (find_roundabout_left_up_only)
                            {
                                repair_line(IMG_H - 1, boundary_left[IMG_H - 1], roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR); //根据左边界底边与上拐点补线

                                re_midline(); //根据左右两边线重写中线
                                LEFT_Roundabout_State_step=1;
                                //如果补线了，则取有效行
                                left_roundabout_useful_line = roundabout_left_up_y;
                            }
                            //3：只有下标志点时补线
                            else if (find_roundabout_left_down && !find_roundabout_left_up)
                            {
                                //以较松的条件找上拐点
                                for (int j = roundabout_left_down_y - 5; j >= useful_line_further; j--)
                                {
                                    if (boundary_left[j] >= boundary_left[j - 1] /*上拐点的上部分*/
                                        && boundary_left[j] >= boundary_left[j + 1] /*上拐点的下部分*/
                                        && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j + 2] >= 5 /*防止为边界*/
                                        && Binary_Image[j][boundary_left[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE/*拐点所在处为赛道*/
                                        &&Binary_Image[j-3][boundary_left[j] ] == IMG_WHITE)
                                    {
                                        roundabout_left_up_y = j;                     //记录上拐点对应纵坐标
                                        roundabout_left_up_x = boundary_left[j];     //记录上拐点对应横坐标

                                        repair_line(roundabout_left_down_y, roundabout_left_down_x, roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR);//根据左上下拐点对左边线进行修正（补线）

                                        re_midline(); //根据左右两边线重写中线
                                        LEFT_Roundabout_State_step=1;
                                        //如果补线了，则取有效行
                                        left_roundabout_useful_line = roundabout_left_up_y;

                                        break;
                                    }
                                }
                            }
                            //4:识别到环岛，找不到下方点，也不能只找到上方点的补线
                            else if (!find_roundabout_left_down && !find_roundabout_left_up_only)
                            {
                                for (int j = (finalloseline_left <= IMG_H - 4 ? finalloseline_left : IMG_H - 4 /*防止数组越界*/); j >= useful_line_further; j--)//从最终丢线行往上寻找拐点
                                {
                                    if (boundary_left[j] >= boundary_left[j - 1] /*上拐点的上部分*/
                                        && boundary_left[j] >= boundary_left[j + 1] /*上拐点的下部分*/
                                        && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j + 2] >= 5 /*防止为边界*/
                                        && Binary_Image[j][boundary_left[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*拐点所在处为赛道*/
                                        &&Binary_Image[j-3][boundary_left[j] ] == IMG_WHITE)
                                    {
                                        roundabout_left_up_y = j;                     //记录上拐点对应纵坐标
                                        roundabout_left_up_x = boundary_left[j];     //记录上拐点对应横坐标
                                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR); //根据左边界底边与上拐点补线

                                        re_midline(); //根据左右两边线重写中线
                                        LEFT_Roundabout_State_step=1;
                                        //如果补线了，则取有效行
                                        left_roundabout_useful_line = roundabout_left_up_y;

                                        left_roundabout_state1_repairline_to_end = true; //当进入此，则表示第一阶段的补线即将结束

                                        break;
                                    }
                                }
                            }
                        }

                        //结束第一阶段到第二阶段的判断
                        if (left_roundabout_state1_repairline_count >= ROUNDABOUT_STATE1_TO_IN_COUNTS && left_roundabout_state1_repairline_to_end)
                        {
                            for (int i = IMG_H - 1; i >= /*IMG_H - 25*/10; i--)
                            {
                                if (boundary_left[i] >= boundary_left[i - 1] && boundary_left[i - 1] >= boundary_left[i - 2] && boundary_left[i - 2] >= boundary_left[i - 3] && boundary_left[i - 3] >= boundary_left[i - 4] && boundary_left[i] > boundary_left[i - 4]  /*环岛存在较强的左上延伸趋势，说明离入环弯道较近*/
                                    && boundary_left[i] >= 2 && boundary_left[i - 1] >= 2 && boundary_left[i - 2] >= 2 /*防止为边界*/
                                    && ((firstloseline_left != IMG_H - 1 && firstloseline_left - finalloseline_left <= 10) || (firstloseline_left == IMG_H - 1 && finalloseline_left > /*45*/IMG_H - 15))/*左边界底部不丢线，或丢线较短*/)
                                {
                                    left_roundabout_discerning = false; //入环前环岛识别失效（之后不再进行第一阶段（即入环前环岛识别阶段））
                                  Left_Roundabout_State = State3_Roundabout_To_In_3th_Repairline; //在此处结束第一个状态！！！转入第三个状态！！！（第二个状态已经无效了）
                                  //  Left_Roundabout_State = State2_Roundabout_To_In_2nd_Repairline; //在此处结束第一个状态！！！
                                    left_roundabout_state2_left_repairline_count = 0; //为了下一阶段更好的过渡，在下一阶段的前几帧仍然补右边线
                                    state_continue_frame_count = 0;//状态保持帧计数条件清零，为下一阶段做准备
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            //-----第二阶段，识别环岛成功后，要进入环岛（入环中期，对应单拐点的左边界补线）(现在已经跳过此阶段了)------//
            case State2_Roundabout_To_In_2nd_Repairline:
                {LEFT_Roundabout_State_step=2;
                    if (left_roundabout_flag == 1 && left_roundabout_discerning == false/*改了一下5*/&& left_roundabout_in_flag == false && left_roundabout_to_out_flag == false/*改了一下*/ && left_roundabout_in_left_repair_line == true) //入环处理部分（环岛识别√，进入环岛内部×，出环×）
                    {
                        //左边从最低行开始存在丢线，需要修正左边界（left_roundabout_in_left_repair_line = 1表示左边界仍存在丢线，需要补线）（入环中期部分）
                        if (firstloseline_left == 49 /*改了一下5*//*&& left_roundabout_in_left_repair_line*/)
                        {
                            int upy = 0;                                                                                    //获取左边界拐点纵坐标
                            for (int i = finalloseline_left; i > 2; i--)
                            {
                                //以下两个if语句用于寻找左边界拐点（此时没有下拐点只有上拐点了）
                                if (boundary_left[i] >= boundary_left[i - 1] /*&& boundary_left[i] >= boundary_left[i - 2]*/)  //寻找拐点（的上部分）--拐点的横坐标比其上下的都大
                                {
                                    if (boundary_left[i] > boundary_left[i + 1] && boundary_left[i] > boundary_left[i + 2]) //确认拐点（的下部分）
                                    {
                                        upy = i;                                                                                            //记录拐点纵坐标
                                        break;
                                    }
                                }
                            }
                            left_roundabout_in_left_repair_line_count++;                        //左边界补线，计数条件+1（在左边界丢线期间的每一帧都补一次线，连续补若干次直到左边不丢线了）
                            repair_line(49, boundary_left[49], upy, boundary_left[upy], LEFT_DIR); //修正左边界
                            re_midline(); //根据左右边线重写中线

                            //如果补线了，则取有效行
                            left_roundabout_useful_line = upy;
                        }

                        //当左边界不从最低行丢线了，同时左边界补线计数条件>0(可调)，则让左边界补线失效-之后不再补线（此时已到入环后期部分）
                        if ((firstloseline_left != 49 || (firstloseline_left == 49 && finalloseline_left > /*45*/40/*改了一下，左边界到很晚都在丢线！！*/)) && left_roundabout_in_left_repair_line_count > 0/*帧数可利用起来*/)
                        {
                            left_roundabout_in_left_repair_line = false;                                    //左边界补线失效，不再需要补线
                            Left_Roundabout_State = 2;                                                                               //在此处结束第二个状态！！！转入第三个状态！！！
                        }
                    }
                }
                break;
            //-----第三阶段，识别环岛成功后，要进入环岛（入环后期，左边界不再补线，开启右边界补线）------//
            case State3_Roundabout_To_In_3th_Repairline:
                {LEFT_Roundabout_State_step=3;

                if (left_roundabout_flag == 1 && !left_roundabout_discerning && !left_roundabout_in_flag && !left_roundabout_to_out_flag  && left_roundabout_in_right_repair_line)
                    {
                        //初始前几帧，左边界补线
                        if(left_roundabout_state2_left_repairline_count <= 5)
                        {
                            left_roundabout_state2_left_repairline_count++;

                            for (int j = IMG_H - 4; j >= useful_line_further; j--)//从最终丢线行往上寻找拐点
                            {
                                if (boundary_left[j] >= boundary_left[j - 1] && boundary_left[j] >=boundary_left[j - 2]/*上拐点的上部分*/
                                    && boundary_left[j] >= boundary_left[j + 1] && boundary_left[j] >= boundary_left[j + 2]/*上拐点的下部分*/
                                    && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j + 2] >= 5 /*防止为边界*/
                                    && Binary_Image[j][boundary_left[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*拐点所在处为赛道*/

                                )
                                {
                                    roundabout_left_up_y = j;                     //记录上拐点对应纵坐标
                                    roundabout_left_up_x = boundary_left[j];     //记录上拐点对应横坐标

                                    repair_line(IMG_H - 1, boundary_left[IMG_H - 1], roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR); //根据左边界底边与上拐点补线

                                    re_midline(); //根据左右两边线重写中线

                                    break;
                                }
                            }
                        }


                        if (firstloseline_right == IMG_H - 1 && finalloseline_right < IMG_H - 10)      //右边界底部出现丢线//入环计数条件开始自加
                        {
                            left_roundabout_to_in_count++;    //准备入环
                        }
                          /*
                                                             关于强打角时期的理解：
                                                             在入环中期部分结束，进入入环后期部分（即左边界底部不再丢线）时
                     (1)右边界最低行一开始可能不丢线（此时执行普通补线——见后后方代码）
                     (2)但之后一定会进入右边界最低行丢线阶段————一开始丢线较短（最终丢线行>20）仍然执行普通补线，直到出现大段丢线（最终丢线行<20）
                                                                      执行强打角，之后一直强打角直到最低行丢线结束
                     (3)再之后最低行丢线结束，彻底进入环岛内（此时下方代码开始执行，即右边不再补线，环岛内部标志位置1）
                          */
                        //状态转移的判断
                       //注意！！！下方这个代码中的两个条件互相制约，只有在右边界开始丢线，直到右边界丢线结束后才会成立（之所以将后执行的代码放在前面，是为了提前识别到最低行不丢线，从而将右边补线标志置0）
                             if ((((firstloseline_right != IMG_H - 1 && firstloseline_left - finalloseline_left <= 5&&firstloseline_left)|| (firstloseline_right == IMG_H - 1 && finalloseline_right >= IMG_H - 5) /*右边出现小段丢线也视为不丢线*/)
                                 && left_roundabout_to_in_count > 0/*计数条件可以利用起来*/)
                                     ||time_in>30//每一帧都加一，限制在该状态为的时间，防止卡状态位（即环岛的状态位一直为3，就算已经入环了也不刷新）
                                     )
                             {//当右边界不再丢线或丢线较短，且入环计数条件满足要求，则进行状态跳转
                                 left_roundabout_in_right_repair_line = false;  //右边界补线失效
                                 left_roundabout_in_flag = true;                //环岛内部中线处理生效（进入环岛内部）
                                 left_roundabout_in_change_angle = false;       //强打角条件去掉
                                 Left_Roundabout_State = State4_Roundabout_In;  //在此处结束第三个状态！！！转入第四个状态！！！
                                 time_in=0;
                                 break; //退出！！！
                             }

                        if (firstloseline_right == IMG_H - 1 && finalloseline_right < IMG_H - 10/*对于稍小一点的环，打角的时机得早一点*/) //右边从最底下开始有一大段丢线，开启强打角入环
                        {
                            left_roundabout_in_change_angle = true;                                     //强打角标志置1
                        }



                        //普通右边界补线，此时还没强打角
                        /*左边界不丢线后，一开始右边界是不丢线的，执行的是普通补线；以及在右边界最低行开始丢线，但丢线较短时也执行普通补线*/
                        if (!left_roundabout_in_change_angle)
                        {
                            //重新搜边线（由于环岛弯道的右边界与环岛上方直道的左边界同时存在，会使得右边界识别成前者，而环岛上方直道的左边界无法识别，故重新搜边线）
                            for (int i = IMG_H - 2; i > useful_line_further; i--)
                            {
                                //以右边界为基准，对中线进行偏移（即重新确定搜线起始点）
                                if (boundary_right[i + 1] - 7 >= 0)
                                {
                                    middle_line[i] = boundary_right[i + 1] - 7;
                                }
                                //以偏移后的中线重新搜线
                                boundary_left[i] = findchange(middle_line[i], LEFT_DIR, i, IMG_BLACK, 0, 2, 1);
                                boundary_right[i] = findchange(middle_line[i], RIGHT_DIR, i, IMG_BLACK, IMG_W - 1, 1, 2);
                            }


                            int lefty = 0;                                   //获取左边界断裂点纵坐标（由于直道与圆环弯道的分叉，左边界最终丢线行有断裂点，即交叉点处左边界横坐标突变）
                            bool find_left_break_point = false;              //是否能获取指定点的标志

                            for (int i = IMG_H - 10; i > useful_line_further; i--)
                            {
//
                                if (boundary_left[i] > 10&& (boundary_left[i] - boundary_left[i + 1] > 10 || boundary_left[i] - boundary_left[i + 2] > 10)/*横坐标存在突变*/
                                        && boundary_left[i] - boundary_left[i - 1] <= 4 && boundary_left[i - 1] - boundary_left[i] <= 4 /*限制拐点与上方点横坐标的差距*/
                                        && Binary_Image[i][boundary_left[i]] == IMG_WHITE /*拐点处为赛道*/
                                        &&i>18//限制拐点在图像中的位置，借此决定什么时候开始转弯入环
                                )
                                {
                                    //计算白色占比（防止误判）
                                    int count_white = 0, count = 0;
                                    for (int j = boundary_left[i + 1]; j <= boundary_left[i]; j++)//跳变的两点所在行应几乎全白
                                    {
                                        if (Binary_Image[i + 1][j] == IMG_WHITE)//从左到右判断
                                        {
                                            count_white++;
                                        }
                                        count++;
                                    }
                                    if (count_white >= 0.8 * count)
                                    {
                                        lefty = i;                        //获取指定点纵坐标
                                        find_left_break_point = true;     //获取到了指定点
                                        break;
                                    }
                                }
                            }
                            if (find_left_break_point)
                            {

                                repair_line(IMG_H -1, boundary_right[IMG_H - 1], lefty, boundary_left[lefty], RIGHT_DIR); //从指定点到最底端右边界连线以修正右边界

                                //如果补线了，则取有效行
                                left_roundabout_useful_line = lefty;
                            }

                            re_midline();         //重写中线
                        }
                        else     //强打角，可看上边强打脚的条件
                        {
                            //调整丢线行，忽略底下短距离丢线
                            loseline_adjust(LEFT_DIR, 8);
                            time_in++;
                            //直接修正中线强打角过强，改为修正右边界
                            repair_line(IMG_H - 1, boundary_right[IMG_H - 1], finalloseline_left + 2, /*boundary_right[finalloseline_left + 2]*/20, RIGHT_DIR);
                            re_midline();
                            //如果补线了，则取有效行
                            left_roundabout_useful_line = finalloseline_left + 1;
                        }
                    }
                }
                break;
            //-------------第四阶段，进入环岛内部（环岛内部处理部分）-------------//
            case State4_Roundabout_In:
                {LEFT_Roundabout_State_step=4;

                    if (left_roundabout_flag == 1 && left_roundabout_in_flag)       //识别环岛标志位和进入环岛内部标志位都为1，开始以下处理
                    {
                        left_roundabout_in_to_out_count++;                          //左环岛内部识别出环帧计数条件+1

                        /*内部转弯处理——与转弯同用一个函数*/

                        //状态转移的判断
                        if (left_roundabout_in_to_out_count > ROUNDABOUT_IN_TO_OUT_COUNTS)
                        {
                            //找右边界是否存在拐点
                            bool find_right_break_point = false;
                            right_break_point_y_to_out = 0; //记录右边界拐点纵坐标
                            for (int i = (IMG_H - 5); i > useful_line_further /*不能>=，防止数组越界=*/; i--)//先找拐点并作标志位
                            {
                                if (boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i] < boundary_right[i + 3] && boundary_right[i + 1] - boundary_right[i] <= 5 /*拐点下方沿右下延伸趋势*/
                                        &&i>15//限制拐点位置，借此决定什么时候出环
                                        && boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] > boundary_right[i] /*拐点上方*/
                                    && (boundary_right[i - 1] - boundary_right[i] >= 10 || boundary_right[i - 2] - boundary_right[i] >= 10 || boundary_right[i - 3] - boundary_right[i] >= 10)/*拐点上方至少存在一处横坐标突变，注意路肩的影响！！*/
                                    && ((boundary_right[i - 1] == IMG_W - 1 && boundary_right[i - 2] == IMG_W - 1)||
                                            (boundary_right[i - 2] == IMG_W - 1 && boundary_right[i - 3] == IMG_W - 1) ||
                                            (boundary_right[i - 3] == IMG_W - 1 && boundary_right[i - 4] == IMG_W - 1)||
                                            (boundary_right[i - 4] == IMG_W - 1 && boundary_right[i - 5] == IMG_W - 1)||
                                            (boundary_right[i - 6] == IMG_W - 1 && boundary_right[i - 7] == IMG_W - 1))/*拐点上方至少存在连续两行丢线*/
                                    && Binary_Image[i][boundary_right[i]]== IMG_WHITE && Binary_Image[i + 1][boundary_right[i + 1]] == IMG_WHITE && Binary_Image[i - 1][boundary_right[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点处为赛道*/)
                                {
                                    find_right_break_point = true;
                                    right_break_point_y_to_out = i;
                                    break;
                                }
                            }
                            if (find_right_break_point == true)//找到右拐点，看丢线行长度
                            {
                                if (firstloseline_right > 15&& firstloseline_left==IMG_H - 1 && firstloseline_right - finalloseline_right >= 5)
                                {
                                    //在转到下一个状态前补线过渡
                                    repair_line(right_break_point_y_to_out, boundary_right[right_break_point_y_to_out], finalloseline_left + 1, boundary_left[finalloseline_left + 1], RIGHT_DIR);
                                    re_midline();
                                    //如果补线了，则取有效行
                                    left_roundabout_useful_line = finalloseline_left + 1;

                                    left_roundabout_in_flag = false;        //使处于环岛内部标志置0（即环岛内部补线处理失效）
                                    left_roundabout_to_out_flag = true;     //出环标志位生效，进入第四阶段出环处理
                                    Left_Roundabout_State = State5_Roundabout_To_Out_Repairline; //在此处结束第四个状态！！！转入第五个状态！！！
                                    state_continue_frame_count = 0;         //状态保持帧计数条件清零，为下一阶段做准备
                                }
                            }
                            else if (firstloseline_right == IMG_H - 1 && finalloseline_right < /*30*/IMG_H - 15 && left_roundabout_in_to_out_count > ROUNDABOUT_IN_TO_OUT_COUNTS + 3) //没有找到拐点，右边从图像最低行开始出现较长的丢线，且左环岛出环帧计数条件满足(默认>5)，则判定为出环路口图像，开始出环（>5可能与车速有关，可能需要调整）
                            {
                                //在转到下一个状态前补线过渡
                                repair_line(IMG_H - 1, boundary_right[IMG_H - 1], finalloseline_left + 1, boundary_right[finalloseline_left + 1], RIGHT_DIR); //将图像左边界最终丢线行对应的右边界的点与最底行右边界的点连接，以修正右边界
                                re_midline();
                                //如果补线了，则取有效行
                                left_roundabout_useful_line = finalloseline_left + 1;

                                left_roundabout_in_flag = false;                                     //使处于环岛内部标志置0（即环岛内部补线处理失效）
                                left_roundabout_to_out_flag = true;                                  //出环标志位生效，进入第四阶段出环处理
                                Left_Roundabout_State = State5_Roundabout_To_Out_Repairline;         //在此处结束第四个状态！！！转入第五个状态！！！
                                state_continue_frame_count = 0;  //状态保持帧计数条件清零，为下一阶段做准备
                            }
//

                        }
                    }
                }
                break;
            //---------------第五阶段，识别到了出环图像，出环处理----------------//
            case State5_Roundabout_To_Out_Repairline:
                {   LEFT_Roundabout_State_step=5;
                    if (left_roundabout_flag == 1 && left_roundabout_to_out_flag)
                    {
                        left_roundabout_out_left_repair_line = false;//左边界补线，每帧都刷新，当这一帧图像中进行了左边界补线，则将其置为true

                        //而对于右边界补线标志，只有在右边界找不到拐点（或不再丢线）或者左边界开始补线后才将其置为false

                        //第五阶段第一步，右边界修正（出环前期部分）—— 根据右拐点或者右边界大段丢线对右边界进行修正
                        if (left_roundabout_out_right_repair_line)
                        {
                            //对存在两段丢线的情况的处理（取较长丢线）
                            if (firstloseline_left == IMG_H - 1)              //左边最底边丢线
                                loseline_adjust(LEFT_DIR, 10);
                            if (firstloseline_right == IMG_H - 1)             //右边最底边丢线
                                loseline_adjust(RIGHT_DIR, 10);

                            //当右边界不再丢线，或丢线极短，则不再补右边线，          进入下一阶段的条件！！！！！！！！！！！！
                            if (
                            (((((firstloseline_right != IMG_H - 1 && firstloseline_right - finalloseline_right <= 5) || (firstloseline_right == IMG_H - 1 && finalloseline_right >= IMG_H - 5)) && firstloseline_right - finalloseline_right <= 5)
                                    ||(firstloseline_right==IMG_H - 1&&firstloseline_left<IMG_H-10))&&state_continue_frame_count>10)
                                  ||state_continue_frame_count>30
                            )
                            {
                                left_roundabout_out_right_repair_line = false;
                                state_continue_frame_count=0;
                            }

                            //若仍需要补右边线，则先找有无拐点（此时不会进入状态4了，故拐点不会更新）
                            if (left_roundabout_out_right_repair_line)//补线
                            {   state_continue_frame_count++;

                                //找右边界是否存在拐点
                                bool find_right_break_point = false;
                                right_break_point_y_to_out = 0; //记录右边界拐点纵坐标

                                for (int i = (IMG_H - 5); i > useful_line_further/*不能为>=，防数组越界*/; i--)//先找拐点并作标志位
                                {
                                    //比第4阶段的稍微松了一点
                                    if (boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i + 1] - boundary_right[i] <= 5 /*拐点下方沿右下延伸趋势*/
                                        && boundary_right[i - 1] > boundary_right[i] /*拐点上方*/
                                        && (boundary_right[i - 1] - boundary_right[i] >= 15 || boundary_right[i - 2] - boundary_right[i] >= 15 || boundary_right[i - 3] - boundary_right[i] >= 15)/*拐点上方至少存在一处横坐标突变，注意路肩的影响！！*/
                                        && ((boundary_right[i - 1] == IMG_W - 1 && boundary_right[i - 2] == IMG_W - 1)
                                        || (boundary_right[i - 2] == IMG_W - 1 && boundary_right[i - 3] == IMG_W - 1)
                                        || (boundary_right[i - 3] == IMG_W - 1 && boundary_right[i - 4] == IMG_W - 1)
                                        ||(boundary_right[i - 4] == IMG_W - 1 && boundary_right[i - 5] == IMG_W - 1)
                                        ||(boundary_right[i - 6] == IMG_W - 1 && boundary_right[i - 7] == IMG_W - 1))/*拐点上方至少存在连续两行丢线*/
                                        && Binary_Image[i][boundary_right[i]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点处为赛道*/)
                                    {
                                        find_right_break_point = true;
                                        right_break_point_y_to_out = i;
                                        break;
                                    }
                                }
                                if (find_right_break_point && (firstloseline_right != IMG_H - 1 && finalloseline_right != -1 && firstloseline_right - finalloseline_right >= 5))//找到右拐点，看丢线行长度
                                {
                                    repair_line(right_break_point_y_to_out, boundary_right[right_break_point_y_to_out], finalloseline_left + 1, boundary_left[finalloseline_left + 1]+1, RIGHT_DIR);
                                    re_midline();
                                    //如果补线了，则取有效行
                                    left_roundabout_useful_line = finalloseline_left + 1;

                                    break;//跳出！
                                }
                                else if ((firstloseline_right == IMG_H - 1 && finalloseline_right < IMG_H - 5) || (firstloseline_right >= IMG_H - 10 && finalloseline_right < IMG_H - 5) || (firstloseline_right - finalloseline_right >= 8))//若右边界存在大段丢线，也补线
                                {
                                    repair_line(IMG_H - 1, boundary_right[IMG_H - 1], finalloseline_left + 1, /*boundary_right[finalloseline_left + 1]*/10, RIGHT_DIR); //将图像左边界最终丢线行对应的右边界的点与最底行右边界的点连接，以修正右边界
                                    re_midline();

                                    //如果补线了，则取有效行
                                    left_roundabout_useful_line = finalloseline_left + 1;
                                    break;//跳出！
                                }
                            }
                        }
                        if (!left_roundabout_out_left_repair_line){  left_roundabout_to_out_flag_count++; }
                        //第五阶段 第二步，转弯结束即将离开左环岛区域，进行左边界修正（出环后期部分）
                        if (!left_roundabout_out_left_repair_line /*未进行左边界修正*/
                            && ((firstloseline_right != IMG_H - 1 && firstloseline_right - finalloseline_right<10)|| (firstloseline_right == IMG_H - 1 && finalloseline_right >= IMG_H - 5))/*右边丢线很短*/)
                        {

                            /*判断是否出环*/

                            //统计底部左边界向右上延伸的趋势（或用左边界斜率）
                            int boundary_left_count = 0;
                            int count_total = 0;

                            for (int i = IMG_H - 20; i <= IMG_H - 2; i++)
                            {
                                if (boundary_left[i] < boundary_left[i - 1]) //下一行的横坐标比上一行的小
                                {
                                    boundary_left_count++;
                                }
                                count_total++;
                            }
                            if (((boundary_left_count >= 0.7 * count_total) /*趋势足够*/
                                && firstloseline_left != IMG_H - 1 && firstloseline_left <= IMG_H - 15 /*左边界底部大段不丢线*/
                                && left_roundabout_to_out_flag_count >= 40/*出环帧计数条件需要大于一定值*/)
                                || left_roundabout_to_out_flag_count >= 50/*通过帧数，当帧数大于某一个较大的值时，判断为出环*/)//判断为出环
                            {
                                left_roundabout_out_flag = true; //出环标志置1
                                left_roundabout_to_out_flag = false;
                                Left_Roundabout_State = State6_Roundabout_Reset; //跳转到下一阶段进行变量重置
                                break;
                            }
                            else //还未出环，则进行左边界补线处理
                            {
                                left_roundabout_useful_line = useful_line_further;//取补线最高有效行
                                for (int i = 1; i <= IMG_H - 1; i++)
                                {
                                    if (Road_Width[i] > 0) //路宽大于0才有意义
                                    {
                                        if (boundary_right[i] - Road_Width[i] >= 0)
                                            boundary_left[i] = boundary_right[i] - Road_Width[i];
                                        else
                                            boundary_left[i] = 0;
                                    }
                                }

                                re_midline();

                                left_roundabout_out_left_repair_line = true;
                                left_roundabout_out_right_repair_line = false;
                            }
                        }

                    }
                }
                break;



            //---------------第六阶段，重置相关变量与标志位----------------//
            case State6_Roundabout_Reset:
                {
                    //重置标志位及变量
                    //if (left_roundabout_out_flag)//由于重置不一定是由出环导致的，也可能是由于持续帧数到达一定值，故注释此条件
                    {
                        Left_Roundabout_State = State1_Roundabout_Distern_1st_Repariline;//在此处结束第六个状态！！！转入第一个状态！！！
                        LEFT_Roundabout_State_step=0;
                        left_roundabout_flag = 0; //左环岛总标志位

                        //入环之前识别环岛
                        left_roundabout_discerning = true;//用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
                        left_roundabout_discern_flag_count = 0;//左环岛入环之前环岛识别帧计数条件
                        left_roundabout_only_up_point_flag = false; //左环岛只有上拐点判断入环标志，出环才重置
                        left_roundabout_only_up_point_count = 0; //左环岛只有上拐点判断入环帧计数条件，出环才重置
                        left_roundabout_state1_repairline_count = 0; //左环岛第一阶段补线帧计数，用于辅助判断第一阶段的结束
                        left_roundabout_state1_repairline_to_end = false; //左环岛第一阶段补线即将结束标志
                        //入环处理
                        left_roundabout_state2_left_repairline_count = 0; //左环岛第一至第二过渡阶段左边界补线帧计数条件：为了下一阶段更好的过渡，在下一阶段的前几帧仍然补左边线
                        left_roundabout_in_left_repair_line = true;//左环岛进环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
                        left_roundabout_in_left_repair_line_count = 0; //左环岛进环时左边界补线计数条件（每有一帧左边界底部丢线需要补线，则+1）
                        left_roundabout_in_right_repair_line = true;  //左环岛进环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
                        left_roundabout_in_change_angle = false;   //强打角标志（入环后期）
                        left_roundabout_to_in_count = 0;  //左环岛进环结束的计数条件（当右边界底部不再丢线时，结合此条件(>0)，判断成功进入环岛内部）
                        //环内处理
                        left_roundabout_in_flag = false;  //左环岛成功进入环岛内部标志位
                        left_roundabout_in_to_out_count = 0; //左环岛内部识别出环帧计数条件（判断出环的条件之一）
                        right_break_point_y_to_out = 0;     //出环时右拐点，用于出环打角
                        //出环处理
                        left_roundabout_to_out_flag = false;  //左环岛出环处理部分标志位
                        left_roundabout_to_out_flag_count = 0; //左环岛出环处理标志位计数变量
                        left_roundabout_out_left_repair_line = false; //左环岛出环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
                        left_roundabout_out_right_repair_line = true; //左环岛出环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
                        left_roundabout_out_flag = false;   //左环岛出环成功标志

                        state_continue_frame_count = 0;  //状态保持帧计数条件
//#if RIGHT_ROUNDABOUT_ONLY_ONE
//                if_right_roundabout_recog                                 = 0;                 //只做一次环岛(注释掉则不只做一次环岛）
//#endif
                    }
                }
                break;

            default:
                Left_Roundabout_State = State1_Roundabout_Distern_1st_Repariline;
                break;
        }
    }
    //-----------------------------------左环岛处理END-----------------------------------//
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// @brief       右环岛识别处理函数(状态机模式)
// @param       void
// @return  void
// @note        识别右环岛，补线，置相应标志位
//                  注意：本环岛识别处理函数适用于分辨率为120*50的图像，若分辨率改变，请注意要调整其中的参数！！！
// Sample usage：
//-------------------------------------------------------------------------------------------------------------------
#if USE_ROUNDABOUT_FSM
void right_roundabout_recog_by_FSM()
{
    //-----------------------------------右环岛处理START------------------------------------//

    //--------------------相关变量重置（每一帧都会重置）-------------------//
    find_roundabout_right_down = false;                  //右环岛下拐点识别标志
    find_roundabout_right_up = false;                    //右环岛上拐点识别标志
    find_roundabout_right_up_only = false;               //右环岛只找到上拐点标志
    roundabout_right_down_y = 0;                         //右环岛右下拐点纵坐标
    roundabout_right_down_x = 0;                         //右环岛右下拐点横坐标
    roundabout_right_up_y = 0;                           //右环岛右上拐点纵坐标
    roundabout_right_up_x = 0;                           //右环岛右上拐点横坐标
    left_boundary_slope = 0;                             //左边界斜率

    right_roundabout_useful_line = 0;                    //右环岛有效行

    if (cross_full_flag == 0 && cross_half_flag == 0 && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && cross_after_turn_flag == 0 && left_roundabout_flag == 0  ) //条件互锁，在没有十字、左环岛和三岔的时候进行右环岛判断
    {
        switch (Right_Roundabout_State)
        {
            //------------------第一阶段，先识别环岛（入环前期部分，通过双拐点或单拐点进行识别并补线）---------------//
            /****此阶段应该包括，有环岛特征（但还没确定为环岛）时的补线、确定为环岛后的补线（直到跳转到下一个阶段）****/
            case 0 /*State1_Roundabout_Distern_1st_Repariline*/:
            {
           //     if (right_roundabout_discerning&&if_right_roundabout_recog)
                if (right_roundabout_discerning)
                { //right_roundabout_discerning用于入环之前的环岛识别（只要其为1，则会进行环岛识别、以及识别到环岛但是还没有进入第二阶段的补线，相当于第一次补线标志，与状态1等效）
                    //默认为1，当开启了“只做一次环岛”时，会在环岛识别并处理完后置0，如果要开启，还需将环岛最后的重置环节代码相关注释去掉

                    //搜索环岛标志点
                    if (firstloseline_right != IMG_H - 1)     //图像右边最低行不丢线
                    {
                        for (int i = IMG_H - 3; i > useful_line_further /*此值>=3*/; i--)                                                //右边边界条件的识别（寻找上下拐点）
                        {
                            if (boundary_right[i] < /*114*/IMG_W - 5/*误判环岛，严格条件*/
                                && boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] /*下拐点下方趋势为往右下延伸*/
                                && boundary_right[i + 1] - boundary_right[i] < 3 && boundary_right[i] - boundary_right[i + 1] < 3 /*与下一行边界的差距在3以内*/
                                && ((lost_right_flag[i - 1] == 1 && lost_right_flag[i - 2] == 1) || (lost_right_flag[i - 2] == 1 && lost_right_flag[i - 3] == 1) || (lost_right_flag[i - 3] == 1 && lost_right_flag[i - 1] == 1))/*下拐点上方存在至少一行丢线*/
                                && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点所在行为赛道*/)   //寻找下拐点
                            {
                                find_roundabout_right_down = true;              //右边界下拐点识别到了
                                roundabout_right_down_y = i;                    //记录下拐点对应纵坐标
                                roundabout_right_down_x = boundary_right[i];    //记录下拐点对应横坐标
                            }
                            if (find_roundabout_right_down)                     //若找到了下拐点（前提），往上查找上拐点（上拐点的横坐标比其上下的都小）
                            {
                                for (int j = roundabout_right_down_y - 1; j >= useful_line_further; j--)
                                {
                                    /*误判环岛，严格条件*/
                                    if (boundary_right[j] <= boundary_right[j - 1] && boundary_right[j] <= boundary_right[j - 2] /*上拐点的上部分*/
                                        && boundary_right[j] <= boundary_right[j + 1] && boundary_right[j] <=boundary_right[j + 2] && boundary_right[j] <= boundary_right[j + 3]  /*上拐点的下部分*/
                                        && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j - 2] <= IMG_W - 5 /*防止为边界*/
                                        && (Binary_Image[j][boundary_right[j] - 2] == IMG_WHITE && Binary_Image[j - 1][boundary_right[j - 1] - 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*拐点所在处为赛道*/)
                                    {
                                        find_roundabout_right_up = true;                //右边界上拐点识别到了
                                        roundabout_right_up_y = j;                   //记录上拐点对应纵坐标
                                        roundabout_right_up_x = boundary_right[j];   //记录上拐点对应横坐标
                                        break;
                                    }
                                }
                            }

                        }
                    }
                    else if (firstloseline_right == IMG_H - 1 && finalloseline_right > IMG_H - 15)     //若图像右下角有一小段丢线影响识别，要手动忽略（从最终丢线行往上寻找拐点）
                    {
                        for (int i = finalloseline_right - 1; i > useful_line_further; i--)             //右边界上、下拐点识别（从丢线结束处开始识别）
                        {
                            if (boundary_right[i] < /*114*/IMG_W - 5/*误判环岛，严格条件*/
                            && boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] /*下拐点下方趋势为往右下延伸*/
                            && boundary_right[i + 1] - boundary_right[i] < 3 && boundary_right[i] - boundary_right[i + 1] < 3 /*与下一行边界的差距在3以内*/
                            && ((lost_right_flag[i - 1] == 1 && lost_right_flag[i - 2] == 1) || (lost_right_flag[i - 2] == 1 && lost_right_flag[i - 3] == 1) || (lost_right_flag[i - 3] == 1 && lost_right_flag[i - 1] == 1)) /*下拐点上方存在至少一行丢线*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点所在行为赛道*/)   //寻找下拐点
                            {
                                find_roundabout_right_down = true;              //右边界下拐点识别到了
                                roundabout_right_down_y = i;                    //记录下拐点对应纵坐标
                                roundabout_right_down_x = boundary_right[i];    //记录下拐点对应横坐标
                            }
                            if (find_roundabout_right_down)                     //若找到了下拐点（前提），往上查找上拐点（上拐点的横坐标比其上下的都小）
                            {
                                for (int j = roundabout_right_down_y - 1; j > useful_line_further; j--)
                                {
                                    /*误判环岛，严格条件*/
                                    if (boundary_right[j] <= boundary_right[j - 1] && boundary_right[j] <= boundary_right[j - 2] /*上拐点的上部分*/
                                        && boundary_right[j] <= boundary_right[j + 1] && boundary_right[j] <= boundary_right[j + 2] && boundary_right[j] <= boundary_right[j + 3]  /*上拐点的下部分*/
                                        && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j - 2] <= IMG_W - 5 /*防止为边界*/
                                        && (Binary_Image[j][boundary_right[j] - 2] == IMG_WHITE && Binary_Image[j - 1][boundary_right[j - 1] - 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*拐点所在处为赛道*/)
                                    {
                                        find_roundabout_right_up = true;                //右边界上拐点识别到了
                                        roundabout_right_up_y = j;                   //记录上拐点对应纵坐标
                                        roundabout_right_up_x = boundary_right[j];   //记录上拐点对应横坐标
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    //根据拐点对是否是环岛进行判断
                    if (right_roundabout_flag == 0) //未识别到环岛才进行判断
                    {
                        /*若能在一帧图像中同时找到两个拐点（最理想的情况）*/
                        if (find_roundabout_right_down && find_roundabout_right_up)
                        {
                            //没有以下误判情况，则识别帧计数条件加1
                            right_roundabout_discern_flag_count++;
                            for (int i = roundabout_right_up_y; i < roundabout_right_down_y; i++) {

                          if(lost_left_flag[i]==1){right_roundabout_discern_flag_count = 0;  break;}

                        }
                  if (right_roundabout_discern_flag_count==0)
                    break;  //退出switch，结束本帧环岛识别

//
////                            //处理一些误判情况（出现误判，则将识别帧计数条件置0）如有误判可考虑一下条件
////                            //1：
//                            for (int counti = roundabout_right_down_y; counti >= roundabout_right_up_y; counti--)
//                            {
//                                //对从下拐点到上拐点的每一行，看从左边界到右边界是否存在黑点，若存在，则将识别帧计数条件置0，并退出本帧的环岛识别
//                                for (int countj = boundary_left[roundabout_right_up_y]; countj < boundary_right[roundabout_right_up_y]; countj++)
//                                {
//                                    if (Binary_Image[counti][countj] == IMG_BLACK)
//                                    {
//                                        right_roundabout_discern_flag_count = 0;
//                                        break;
//                                    }
//                                }
//                                if (right_roundabout_discern_flag_count == 0)
//                                    break;  //退出外层循环
//                            }
//                            if (right_roundabout_discern_flag_count == 0)
//                                break;  //退出switch，结束本帧环岛识别
//                            //2：
//                            if (!(boundary_right[roundabout_right_up_y] - boundary_left[roundabout_right_up_y] >= 5 && roundabout_right_down_y - roundabout_right_up_y >= 8 && loseleftflag == 0))
//                            // !() ：若不满足括号中的条件，即不满足（上拐点处右边界大于左边界一定值，且上下拐点的纵坐标有一定距离/*，且一边丢线，一边没有丢线*/）的条件，则将帧计数条件置0
//                            {
//                                right_roundabout_discern_flag_count = 0;
//                                break;  //退出switch，结束本帧环岛识别
//                            }
//                            //3：左边界斜率
//                            int boundary_Ldown_to_Rup_count = 0;     //左边界满足从左下往右上延伸的累计计数条件
//                            for (int i = roundabout_right_down_y; i >= roundabout_right_up_y; i--)                                                    //左边边界条件的识别，即左边界有从左下向右上延伸的趋势
//                            {
//                                if (boundary_left[i] < boundary_left[i - 1])                 //下一行的横坐标比上一行的小
//                                {
//                                    boundary_Ldown_to_Rup_count++;                           //记录左边界往右上延伸的趋势的累计计数
//                                }
//                            }
//                            //计算左边线拐点处连线所在的直线斜率（若为右环岛，这是一个正的斜率，往图像右上延伸）
//                            left_boundary_slope = (float)(roundabout_right_down_y - roundabout_right_up_y) / (boundary_left[roundabout_right_up_y] - boundary_left[roundabout_right_down_y]);
//
//                            if (boundary_Ldown_to_Rup_count < 0.7 * (roundabout_right_down_y - roundabout_right_up_y) || left_boundary_slope <= 0 /*|| boundary_left[roundabout_right_up_y] >= IMG_MIDDLE + 20*/)
//                            { //如果左边界右下往左上延伸趋势不够，或者左边界斜率为非正值，或者上拐点处的左边界过于偏右
//                                right_roundabout_discern_flag_count = 0; //将帧计数条件置0
//                                break;  //退出switch，结束本帧环岛识别
//                            }

                        }
                        /*若无法在一帧图像中同时找到两个拐点，则根据“只有上拐点”判断入环*/
                        //但为了提高准确率，还是需要至少能在某一帧识别到一下下拐点，以将 上拐点帧计数标志 打开
                        else if (find_roundabout_right_down && !find_roundabout_right_up)//找到下拐点而没有上拐点
                        {
                            //寻找是否有一定的 可以找到上拐点 的趋势（此时上拐点的条件很松，甚至只考虑上拐点的下半部分），有bug得上下都考虑。
                            for (int i = (roundabout_right_down_y < IMG_H - 4 ? roundabout_right_down_y : IMG_H - 4)/*防止数组越界*/; i >= useful_line_further; i--)//从下拐点往上找
                            {
                                //寻找下标识点，找到就开始记录找到点后已经过了几帧
                                if (boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i + 1] < boundary_right[i + 3] /*下拐点下方有向下延伸的趋势*/
                                        && boundary_right[i] <= IMG_W - 5 && boundary_right[i - 1] <= IMG_W - 5 && boundary_right[i + 1] <= IMG_W - 5 /*防止为边界*/
                                        && (boundary_right[i + 3] - boundary_right[i] >= 5
                                         && (Binary_Image[i][boundary_right[i] - 2] == IMG_WHITE && Binary_Image[i - 1][boundary_right[i - 1] - 2] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE) /*拐点所在处为赛道*/

                                        ) /*上拐点的下方弧度足够*/
                                        )
                                {
                                    right_roundabout_only_up_point_flag = true; //上拐点帧计数标志打开
                                    right_roundabout_only_up_point_count = 0;   //准备计数
                                    break;
                                }
                            }
                        }


                        /*只有上拐点判断入环，承接上方else if*/
                        if (right_roundabout_only_up_point_flag)//如果找到下标识点后连续8帧都没有找到上标识点，则清零
                        {
                            right_roundabout_only_up_point_count++;

                            if (right_roundabout_only_up_point_count >= 8)//8帧根据具体情况改变
                            {
                                right_roundabout_only_up_point_flag = false;
                                right_roundabout_only_up_point_count = 0;
                            }
                        }

                        if (!find_roundabout_right_up && right_roundabout_only_up_point_flag)//如果没有找到上拐点，且上拐点帧计数标志为true（防止在下一帧又能同时找到上下拐点，则不执行下方语句）
                        {
                            //满足一定条件开始找上拐点
                            if (finalloseline_right <= IMG_H - 5)//最终丢线行
                            {
                                for (int i = finalloseline_right; i >= useful_line_further; i--)
                                {
                                    if (boundary_right[i] <= boundary_right[i - 1] && boundary_right[i] < boundary_right[i - 2]/*上拐点的上半部分趋势正确*/
                                        && boundary_right[i] - boundary_right[i - 1] <= 5 && boundary_right[i - 1] - boundary_right[i] <= 5  && boundary_right[i] -  boundary_right[i - 2] <= 5 && boundary_right[i - 2] - boundary_right[i] <= 5 /*限制拐点上方点的横坐标间距 */
                                        && boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i] < boundary_right[i + 3] /*上拐点的下半部分趋势正确*/
                                        && boundary_right[i + 4] - boundary_right[i] >= 4 /*下拐点下半部分趋势足够*/
                                        && boundary_right[i] <= IMG_W - 2 && boundary_right[i + 1] <= IMG_W - 2 && boundary_right[i - 1] <= IMG_W - 2 && Binary_Image[i][boundary_right[i]] == IMG_WHITE /*防止为边界*/
                                        && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i]] == IMG_WHITE && Binary_Image[i - 2][middle_line[i]] == IMG_WHITE && Binary_Image[i - 3][middle_line[i]] == IMG_WHITE /*确保为赛道*/)
                                    {
                                        roundabout_right_up_y = i;
                                        roundabout_right_up_x = boundary_right[i];

                                        //没有以下误判情况，则识别帧计数条件加1
                                        right_roundabout_discern_flag_count++;
                                        for (int i = roundabout_right_up_y-5; i < roundabout_right_up_y+5; i++) {
                                          if(lost_left_flag[i]==1){right_roundabout_discern_flag_count = 0; break;}//判断左边线是否丢线
                                                                                                              }
                                        if (right_roundabout_discern_flag_count == 0)
                                                    break;
                                        //处理一些误判情况，严格条件（出现误判，则将帧计数条件置0）
//                                        //1：
//                                        if (!(roundabout_right_up_x - boundary_left[roundabout_right_up_y] >= 5  /*&& loseleftflag == 0 */))
//                                        { //不满足（上拐点处右边界大于左边界一定值 /*，且一边丢线，一边没有丢线*/）的条件，则将环岛识别帧计数条件置0
//                                            right_roundabout_discern_flag_count = 0;
//                                            continue; //继续寻找上拐点
//                                        }
//                                        //2：
//                                        for (int counti = finalloseline_right; counti >= roundabout_right_up_y; counti--)
//                                        {
//                                            //对从最终丢线行到上拐点的每一行，看从左边界到右边界是否存在黑点，若存在，则将识别帧计数条件置0
//                                            for (int countj = boundary_left[roundabout_right_up_y]; countj < roundabout_right_up_x; countj++)
//                                            {
//                                                if (Binary_Image[counti][countj] == IMG_BLACK)
//                                                {
//                                                    right_roundabout_discern_flag_count = 0;
//                                                    break;
//                                                }
//                                            }
//                                            if (right_roundabout_discern_flag_count == 0)
//                                                break;  //退出外层循环
//                                        }
//                                        if (right_roundabout_discern_flag_count == 0)
//                                            continue;  //继续寻找上拐点
//
//                                        //3：左边界斜率
//                                        int boundary_Ldown_to_Rup_count = 0;     //左边界满足从左下往右上延伸的累计计数条件
//                                        for (int m = finalloseline_right; m >= roundabout_right_up_y; m--)  //左边边界条件的识别，即左边界有从左下向右上延伸的趋势
//                                        {
//                                            if (boundary_left[m] < boundary_left[m - 1])                    //下一行的横坐标比上一行的小
//                                            {
//                                                boundary_Ldown_to_Rup_count++;                              //记录左边界往右上延伸的趋势的累计计数
//                                            }
//                                        }
//                                        if (boundary_Ldown_to_Rup_count < 0.85 * (finalloseline_right - roundabout_right_up_y) /*|| boundary_left[roundabout_right_up_y] >= IMG_MIDDLE + 20*/)
//                                        { //如果左边界右下往左上延伸趋势不够，或者上拐点处的左边界过于偏右
//                                            right_roundabout_discern_flag_count = 0; //将帧计数条件置0
//                                            continue;  //继续寻找上拐点
//                                        }

                                        //处理误判结束，若能执行到此，则帧计数条件>=1
                                        if (right_roundabout_discern_flag_count >= 1)
                                        {
                                            find_roundabout_right_up_only = true;//只找到上拐点标志位置1
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        /*需要的话再补充“斜入环岛函数”*/

                        //环岛帧计数条件到达一定值后，成功识别环岛
                        if(right_roundabout_discern_flag_count >= ROUNDABOUT_DISCERN_COUNTS)
                        {
                            right_roundabout_flag = 1;
                        }

                    }

                    //根据不同的拐点情况进行补线
                    if (right_roundabout_flag == 1)//右环岛标志为1，而此时入环前环岛识别标志仍为1，故仍会进行上下拐点搜索及补线
                    {
                        right_roundabout_state1_repairline_count++; //第一阶段补线帧计数条件+1
                        //1:识别到环岛，且找到两个拐点，补线
                        if (find_roundabout_right_down && find_roundabout_right_up)
                        {
                            repair_line(roundabout_right_down_y, roundabout_right_down_x, roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR);//根据右上下拐点对右边线进行修正（补线）
                            RIGHT_Roundabout_State_step=1;
                            re_midline(); //根据左右两边线重写中线
                            //如果补线了，则取有效行
                            right_roundabout_useful_line = roundabout_right_up_y;
                        }
                        //2:识别到环岛，且只有上拐点，补线
                        else if (find_roundabout_right_up_only)
                        {
                            repair_line(IMG_H - 1, boundary_right[IMG_H - 1], roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR); //根据右边界底边与上拐点补线

                            re_midline(); //根据左右两边线重写中线
                            RIGHT_Roundabout_State_step=1;
                            //如果补线了，则取有效行
                            right_roundabout_useful_line = roundabout_right_up_y;
                        }
                        //3:识别到环岛，只有下标志点时补线
                        else if (find_roundabout_right_down && !find_roundabout_right_up)
                        {
                            //以较松的条件找上拐点
                            for (int j = roundabout_right_down_y - 5; j >= useful_line_further; j--)
                            {
                                if (boundary_right[j] <= boundary_right[j - 1]  /*上拐点的上部分*/
                                    && boundary_right[j] <= boundary_right[j + 1] /*上拐点的下部分*/
                                    && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j + 2] <= IMG_W - 5 /*防止为边界*/
                                    && (Binary_Image[j][boundary_right[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*拐点所在处为赛道*/)
                                {
                                    roundabout_right_up_y = j;                   //记录上拐点对应纵坐标
                                    roundabout_right_up_x = boundary_right[j];   //记录上拐点对应横坐标

                                    repair_line(roundabout_right_down_y, roundabout_right_down_x, roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR);//根据右上下拐点对右边线进行修正（补线）

                                    re_midline(); //根据左右两边线重写中线
                                    RIGHT_Roundabout_State_step=1;
                                    //如果补线了，则取有效行
                                    right_roundabout_useful_line = roundabout_right_up_y;
                                    break;
                                }

                            }
                        }
                        //4:识别到环岛，找不到下方点，也不能只找到上方点的补线
                        else if (!find_roundabout_right_down && !find_roundabout_right_up_only)
                        {
                            for (int j = (finalloseline_right <= IMG_H - 4 ? finalloseline_right : IMG_H - 4 /*防止数组越界*/); j > useful_line_further; j--)//从最终丢线行往上寻找拐点
                            {
                                if (boundary_right[j] <= boundary_right[j - 1]  /*上拐点的上部分*/
                                    && boundary_right[j] <= boundary_right[j + 1] /*上拐点的下部分*/
                                    && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j + 2] <= IMG_W - 5 /*防止为边界*/
                                    && (Binary_Image[j][boundary_right[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*拐点所在处为赛道*/)
                                {
                                    roundabout_right_up_y = j;                   //记录上拐点对应纵坐标
                                    roundabout_right_up_x = boundary_right[j];   //记录上拐点对应横坐标

                                    repair_line(IMG_H - 1, boundary_right[IMG_H - 1], roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR); //根据右边界底边与上拐点补线

                                    re_midline(); //根据左右两边线重写中线
                                    RIGHT_Roundabout_State_step=1;
                                    //如果补线了，则取有效行
                                    right_roundabout_useful_line = roundabout_right_up_y;

                                    right_roundabout_state1_repairline_to_end = true;   //当进入此，则表示第一阶段的补线即将结束
                                    break;
                                }
                            }
                        }
                    }
                    //结束第一阶段到第二阶段的判断
                    if (right_roundabout_state1_repairline_count >= ROUNDABOUT_STATE1_TO_IN_COUNTS && right_roundabout_state1_repairline_to_end)
                    {
                        for (int i = IMG_H - 1; i >= /*IMG_H - 25*/10; i--)
                        {
                            if (boundary_right[i] <= boundary_right[i - 1] && boundary_right[i - 1] <= boundary_right[i - 2] && boundary_right[i - 2] <= boundary_right[i - 3] && boundary_right[i - 3] <= boundary_right[i - 4] && boundary_right[i] < boundary_right[i - 4] /*环岛存在较强的右上延伸趋势，说明离入环弯道较近*/
                                && boundary_right[i] <= IMG_W - 2 && boundary_right[i - 1] <= IMG_W - 2 && boundary_right[i - 2] <= IMG_W - 2 /*防止为边界*/
                                && ((firstloseline_right != IMG_H - 1 && firstloseline_right - finalloseline_right <= 5 ) || (firstloseline_right == IMG_H - 1 && finalloseline_right > /*45*/IMG_H - 10)) /*右边界底部不丢线，或丢线较短*/)
                            {
                                right_roundabout_discerning = false;    //入环前环岛识别失效（之后不再进行第一阶段（即入环前环岛识别阶段））
                                Right_Roundabout_State = 2 /*State3_Roundabout_To_In_3th_Repairline*/;            //在此处结束第一个状态！！！转入第二个状态！！！
                                right_roundabout_state2_right_repairline_count = 0; //为了下一阶段更好的过渡，在下一阶段的前几帧仍然补右边线
                                break;
                            }
                        }
                    }

                }
            }
            break;
            //-----第二阶段，识别环岛成功后，要进入环岛（入环中期，对应单拐点的左边界补线）(现在已经跳过此阶段了)------//
            case 1 /*State2_Roundabout_To_In_2nd_Repairline*/:
            {RIGHT_Roundabout_State_step=2;

                if (right_roundabout_flag == 1 && !right_roundabout_discerning && !right_roundabout_in_flag && !right_roundabout_to_out_flag && right_roundabout_in_right_repair_line) //入环处理部分（环岛识别√，进入环岛内部×，出环×）
                {
                    //右边从最低行开始存在丢线，需要修正右边界（right_roundabout_in_right_repair_line = 1表示右边界仍存在丢线，需要补线）（入环中期部分）
                    if (firstloseline_right == 49 /*&& right_roundabout_in_right_repair_line*/)
                    {
                        int upy = 0;                                                                                    //获取右边界拐点纵坐标
                        for (int i = finalloseline_right; i > 2; i--)
                        {
                            //以下两个if语句用于寻找右边界拐点（此时没有下拐点只有上拐点了）
                            if (boundary_right[i] <= boundary_right[i - 1])                     //寻找拐点（的上部分）--拐点的横坐标比其上下的都小
                            {
                                if (boundary_right[i] < boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2]) //确认拐点（的下部分）
                                {
                                    upy = i;                                                                                            //记录拐点纵坐标
                                    break;
                                }
                            }
                        }
                        right_roundabout_in_right_repair_line_count++;                      //右边界补线，计数条件+1（在右边界丢线期间的每一帧都补一次线，连续补若干次直到右边不丢线了）
                        repair_line(49, boundary_right[49], upy, boundary_right[upy], RIGHT_DIR); //修正右边界
                        re_midline(); //根据右左边线重写中线

                        //如果补线了，则取有效行
                        right_roundabout_useful_line = upy;
                    }

                    //当右边界不从最低行丢线了，同时右边界补线计数条件>0，则让右边界补线失效-之后不再补线（此时已到入环后期部分）
                    if ((firstloseline_right != 49 || (firstloseline_right == 49 && finalloseline_right > /*45*/40/*改了一下3，右边界到很晚都不取消补线！！*/)) && right_roundabout_in_right_repair_line_count > 0)
                    {
                        right_roundabout_in_right_repair_line = false;                                  //右边界补线失效，不再需要补线
                        Right_Roundabout_State = 2;//在此处结束第二个状态！！！转入第三个状态！！！
                    }
                }
            }
            break;
            //-----第三阶段，识别环岛成功后，要进入环岛（入环后期，左边界不再补线，开启右边界补线）------//
            case 2 /*State3_Roundabout_To_In_3th_Repairline*/:
            {RIGHT_Roundabout_State_step=3;
                if (right_roundabout_flag == 1 && !right_roundabout_discerning && !right_roundabout_in_flag && !right_roundabout_to_out_flag && right_roundabout_in_left_repair_line)
                {


                    //初始前几帧，右边界补线
                    if (right_roundabout_state2_right_repairline_count <= 2)
                    {
                        right_roundabout_state2_right_repairline_count++;
                        for (int j =  IMG_H - 4; j >= useful_line_further; j--)//往上寻找拐点
                        {
                            if (boundary_right[j] <= boundary_right[j - 1] && boundary_right[j] < boundary_right[j - 2] /*上拐点的上部分*/
                                && boundary_right[j] <= boundary_right[j + 1] && boundary_right[j] < boundary_right[j + 2]/*上拐点的下部分*/
                                && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j + 2] <= IMG_W - 5 /*防止为边界*/
                                && (Binary_Image[j][boundary_right[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*拐点所在处为赛道*/)
                            {
                                roundabout_right_up_y = j;                   //记录上拐点对应纵坐标
                                roundabout_right_up_x = boundary_right[j];   //记录上拐点对应横坐标

                                repair_line(IMG_H - 1, boundary_right[IMG_H - 1], roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR); //根据右边界底边与上拐点补线

                                re_midline(); //根据左右两边线重写中线

                                break;
                            }
                        }
                    }
                    if (firstloseline_left == IMG_H - 1 && finalloseline_left < IMG_H - 10)        //左边界底部出现丢线//改了一下3
                {
                    right_roundabout_to_in_count++;
                }

                    /*
                      关于强打角时期的理解：
                      在入环中期部分结束，进入入环后期部分（即右边界底部不再丢线）时
                                      (1)左边界最低行一开始可能不丢线（此时执行普通补线——见后后方代码）
                                      (2)但之后一定会进入左边界最低行丢线阶段————一开始丢线较短（最终丢线行>20）仍然执行普通补线，直到出现大段丢线（最终丢线行<20）执行强打角，之后一直强打角直到最低行丢线结束
                                      (3)再之后最低行丢线结束，彻底进入环岛内（此时下方代码开始执行，即左边不再补线，环岛内部标志位置1）
                    */

                    //注意！！！下方这个代码中的两个条件互相制约，只有在左边界开始丢线，直到左边界丢线结束后才会成立（之所以将后执行的代码放在前面，是为了提前识别到最低行不丢线，从而将左边补线标志置0）
                    if ((((firstloseline_left != IMG_H - 1 && firstloseline_left - finalloseline_left <= 5&&firstloseline_right) || (firstloseline_left == IMG_H - 1 && finalloseline_left >= IMG_H - 5)/*左边出现小段丢线也视为不丢线*/)
                         && right_roundabout_to_in_count > 0)||time_in>30)
                    { //当左边界不再丢线或丢线较短，且入环计数条件满足要求，则进行状态跳转
                        right_roundabout_in_left_repair_line = false;       //左边界补线失效
                        right_roundabout_in_flag = true;                    //环岛内部中线处理生效（进入环岛内部）
                        right_roundabout_in_change_angle = false;           //强打角条件去掉
                        Right_Roundabout_State = 3 /*State4_Roundabout_In*/;                         //在此处结束第三个状态！！！转入第四个状态！！！
                        state_continue_frame_count = 0;//状态保持帧计数条件清零，为下一阶段做准备
                        time_in=0;
                        break;                                              //退出此轮case，不再执行下方程序
                    }


                    if (firstloseline_left == IMG_H - 1 && finalloseline_left <= IMG_H - 10 /*20*/ /*对于稍小一点的环，打角的时机得早一点*/) //左边从最底下开始有一大段丢线，开始强打角
                    {
                        right_roundabout_in_change_angle = true;                                    //强打角标志置1
                    }

                    //普通补线
                    /*
                        右边界不丢线后，一开始左边界是不丢线的，执行的是普通补线；以及在左边界最低行开始丢线，但丢线较短时也执行普通补线
                    */

//
                    if (!right_roundabout_in_change_angle)
                    {
                        //重新搜边线（由于环岛弯道的左边界与环岛上方直道的右边界同时存在，会使得左边界识别成前者，而环岛上方直道的右边界无法识别，故重新搜边线）
                        for (int i = IMG_H - 2; i > useful_line_further; i--)
                        {
                            //以左边界为基准，对中线进行偏移（即重新定义搜线起始点）
                            if (boundary_left[i + 1] + 7 <= IMG_W - 1)
                            {
                                middle_line[i] = boundary_left[i + 1] + 7;
                            }
                            //以偏移后的中线重新搜线
                            boundary_left[i] = findchange(middle_line[i], LEFT_DIR, i, IMG_BLACK, 0, 2, 1);
                            boundary_right[i] = findchange(middle_line[i], RIGHT_DIR, i, IMG_BLACK, IMG_W - 1, 1, 2);
                        }

                        int righty = 0;                           //获取右边界断裂点纵坐标（由于直道与圆环弯道的分叉，右边界最终丢线行有断裂点，即交叉点处右边界横坐标突变）
                        bool find_right_break_point = false;      //是否能获取指定点的标志

                        for (int i = IMG_H - 10; i > useful_line_further; i--)
                        {

                                if (boundary_right[i] < IMG_W - 10&& (boundary_right[i + 1] - boundary_right[i] > 15 || boundary_right[i + 2] - boundary_right[i] > 15 )/*断裂点处突变（横坐标突然减小）*/
                              && boundary_right[i] - boundary_right[i - 1] <= 4 /*限制拐点与上方点横坐标的差距*/
                              && Binary_Image[i][boundary_right[i]] == IMG_WHITE /*拐点处为赛道*/
                              &&i>15//限制拐点到车的距离
                                                  )
                            {
                                //计算白色占比（防止误判）
                                int count_white = 0, count = 0;
                                for (int j = boundary_right[i]; j <= boundary_right[i + 1]; j++)//跳变的两点所在行应几乎全白
                                {
                                    if (Binary_Image[i + 1][j] == IMG_WHITE)//从左到右判断
                                    {
                                        count_white++;
                                    }
                                    count++;
                                }
                                if (count_white >= 0.8 * count)
                                {
                                    righty = i;                                   //获取指定点纵坐标
                                    find_right_break_point = true;
                                   //获取到了指定点
                                    break;
                                }
                            }
                        }
                        if (find_right_break_point)
                        {
                     repair_line(IMG_H - 1, boundary_left[IMG_H - 1], righty, boundary_right[righty], LEFT_DIR); //从指定点到最底端中线连线以修正左边界(补线实际修改的不是临时变量而是全局变量）

                            right_roundabout_useful_line = righty;//如果补线了，则取有效行
                        }
                        //}
                        re_midline();                                                                               //重写中线
                    }
                    else    //强打角
                    {
                        //调整丢线行，忽略底下短距离丢线
                        loseline_adjust(RIGHT_DIR, 8);
                        time_in++;
                        //对于小一点的环，修正中线来强打角
                        //repair_middline(middle_line[IMG_H - 1], IMG_H - 1, boundary_right_temp[finalloseline_right + 1], (finalloseline_right + 1));//将右边界最终丢线处与最底端中点连接作为中线
                        //直接修正中线强打角过强，改为修正左边界
                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], finalloseline_right + 2, /*boundary_left_temp[finalloseline_right + 2]*/IMG_W - 20, LEFT_DIR);

                        re_midline();

                        //如果补线了，则取有效行
                        right_roundabout_useful_line = finalloseline_right + 1;

                    }

                }
            }
            break;
            //-------------第四阶段，进入环岛内部（环岛内部处理部分）-------------//
            case 3 /*State4_Roundabout_In*/:
            {RIGHT_Roundabout_State_step=4;
                if (right_roundabout_flag == 1 && right_roundabout_in_flag)       //识别环岛标志位和进入环岛内部标志位都为1，开始以下处理
                {
                    right_roundabout_in_to_out_count++;                                                           //右环岛内部识别出环帧计数条件+1

                    /*内部转弯处理——与转弯同用一个函数*/

                    if (right_roundabout_in_to_out_count > ROUNDABOUT_IN_TO_OUT_COUNTS)
                    {
                        //找左边界是否存在拐点
                        bool find_left_break_point = false;
                        left_break_point_y_to_out = 0; //记录左边界拐点纵坐标
                        for (int i = IMG_H - 5; i > useful_line_further /*不能>=，防止数组越界=*/; i--)//先找拐点并作标志位
                        {
                            if (boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >= boundary_left[i + 2] && boundary_left[i] >=boundary_left[i + 3] && boundary_left[i] - boundary_left[i + 1] <= 10 /*拐点下方沿左下延伸趋势*/
                              &&i>25//限制拐点在图像中的位置，即什么时候开始出环
                                    && boundary_left[i - 1]<= boundary_left[i] && boundary_left[i - 2] < boundary_left[i] /*拐点上方*/
                                && (boundary_left[i] - boundary_left[i - 1] >= 5|| boundary_left[i] - boundary_left[i - 2] >= 5 || boundary_left[i] - boundary_left[i - 3] >= 5 /*拐点上方至少存在一处横坐标突变路肩的影响！！*/)
                              //  && ((boundary_left[i - 1] == 0 && boundary_left[i - 2] == 0) || (boundary_left[i - 2] == 0 && boundary_left[i - 3] == 0) || (boundary_left[i - 3] == 0 && boundary_left[i - 4] == 0)|| (boundary_left[i - 4] == 0 && boundary_left[i - 5] == 0)|| (boundary_left[i - 5] == 0 && boundary_left[i - 6] == 0)|| (boundary_left[i - 6] == 0 && boundary_left[i - 7] == 0))/*拐点上方至少存在连续两行丢线*/
                                && Binary_Image[i][boundary_left[i]] == IMG_WHITE && Binary_Image[i + 1][boundary_left[i + 1]] == IMG_WHITE && Binary_Image[i - 1][boundary_left[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点处为赛道*/)
                            {
                                find_left_break_point = true;
                                left_break_point_y_to_out = i;
                                break;
                            }

                        }
                        if (find_left_break_point == true)//找到左拐点，看丢线行长度
                        {
//                            if (firstloseline_left >15 && finalloseline_right==IMG_H - 1 && firstloseline_left - finalloseline_left >= 5)
//                            {
                                //在转到下一个状态前补线过渡
                                repair_line(left_break_point_y_to_out, boundary_left[left_break_point_y_to_out], finalloseline_right + 1, boundary_right[finalloseline_right + 1], LEFT_DIR);
                                re_midline();
                                //如果补线了，则取有效行
                                right_roundabout_useful_line = finalloseline_right + 1;

                                right_roundabout_in_flag = false; //使处于环岛内部标志置0（即环岛内部补线处理失效）
                                right_roundabout_to_out_flag = true; //出环标志位生效，进入第四阶段出环处理
                                Right_Roundabout_State = 4 /*State5_Roundabout_To_Out_Repairline*/; //在此处结束第四个状态！！！转入第五个状态！！！
                                state_continue_frame_count = 0;         //状态保持帧计数条件清零，为下一阶段做准备

                          //  }
                        }
                        else if (firstloseline_left==IMG_H-1 && finalloseline_left> /*30*/IMG_H - 25 &&firstloseline_left-finalloseline_left>10&&firstloseline_right==IMG_H-1&& right_roundabout_in_to_out_count> ROUNDABOUT_IN_TO_OUT_COUNTS + 3) //左边从图像最低行开始出现较长的丢线，且右环岛出环帧计数条件满足(默认>5)，则判定为出环路口图像，开始出环（>5可能与车速有关，可能需要调整）
                                //没找到拐点
                            {

//
                                //在转到下一个状态前补线过渡
                                repair_line(IMG_H - 1, boundary_left[IMG_H - 1], finalloseline_right + 1, boundary_left[finalloseline_right + 1] , LEFT_DIR); //将图像右边界最终丢线行对应的左边界的点与最底行左边界的点连接，以修正左边界
                                re_midline();

                                //如果补线了，则取有效行
                                right_roundabout_useful_line = finalloseline_right + 1;

                                right_roundabout_in_flag = false;                                                    //使处于环岛内部标志置0（即环岛内部补线处理失效）
                                right_roundabout_to_out_flag = true;     //改了一下                                                  //出环标志位生效，进入第四阶段出环处理

                                Right_Roundabout_State = 4 /*State5_Roundabout_To_Out_Repairline*/;
                                state_continue_frame_count = 0;         //状态保持帧计数条件清零，为下一阶段做准备
                            }

                    }
                }
            }
            break;
            //---------------第五阶段，识别到了出环图像，出环处理----------------//
            case 4 /*State5_Roundabout_To_Out_Repairline*/:
            {RIGHT_Roundabout_State_step=5;
                if (right_roundabout_flag == 1 && right_roundabout_to_out_flag)
                {

                    right_roundabout_out_right_repair_line = false;  //右边界补线，每帧都刷新，当这一帧图像中进行了右边界补线，则将其置为1

                    //而对于左边界补线标志，只有在左边界找不到拐点（或不在丢线）或者右边界开始补线后才将其置为0

                    //第五阶段第一步，左边界修正（出环前期部分）—— 根据左拐点或者左边界大段丢线对左边界进行修正
                    if (right_roundabout_out_left_repair_line )
                    {
                        //为对存在两段丢线的情况的处理（取较长丢线）
                        if (firstloseline_right == IMG_H - 1) //右边最底边丢线
                            loseline_adjust(RIGHT_DIR, 10);
                        if (firstloseline_left == IMG_H - 1)  //左边最底边丢线
                            loseline_adjust(LEFT_DIR, 10);
                        state_continue_frame_count++;

                        if (
                               ( ((((firstloseline_left != IMG_H - 1 && firstloseline_left - finalloseline_left <= 5) || (firstloseline_left == IMG_H - 1 && finalloseline_left >= IMG_H - 5)) && firstloseline_left - finalloseline_left <= 5)//情况一当左边界不再丢线，或丢线极短，则不再补左边线
                                || ((firstloseline_left == IMG_H - 1 && finalloseline_left >=IMG_H - 10) )
                                    )&&state_continue_frame_count>15)
                                        ||state_continue_frame_count>30
                                )
                        {
                            right_roundabout_out_left_repair_line = false;
                            state_continue_frame_count=0;


                        }
                        //若仍需要补左边线，则先找有无拐点（此时不会进入状态4了，因此拐点不会更新）
                        if (right_roundabout_out_left_repair_line)
                        {
                            //找左边界是否存在拐点
                            bool find_left_break_point = false;
                            left_break_point_y_to_out = 0;

                            for (int i = (IMG_H - 5); i > useful_line_further/*不能为>=，防数组越界*/; i--)//先找拐点并作标志位
                            {
                                //比第4阶段的稍微松了一点
                                if (boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] > boundary_left[i + 2] && boundary_left[i] - boundary_left[i + 1] <= 5 /*拐点下方沿左下延伸趋势*/
                                && boundary_left[i - 1] < boundary_left[i]  /*拐点上方*/
                                && (boundary_left[i] - boundary_left[i - 1] >= 15 || boundary_left[i] - boundary_left[i - 2] >= 15 || boundary_left[i] - boundary_left[i - 3] >= 15 /*拐点上方至少存在一处横坐标突变路肩的影响！！*/)
                                && ((boundary_left[i - 1] == 0 && boundary_left[i - 2] == 0) || (boundary_left[i - 2] == 0 && boundary_left[i - 3] == 0) || (boundary_left[i - 3] == 0 && boundary_left[i - 4] == 0)|| (boundary_left[i - 4] == 0 && boundary_left[i - 5] == 0)|| (boundary_left[i - 5] == 0 && boundary_left[i - 6] == 0)|| (boundary_left[i - 6] == 0 && boundary_left[i - 7] == 0))/*拐点上方至少存在连续两行丢线*/
                                && Binary_Image[i][boundary_left[i]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*拐点处为赛道*/
                                )
                                {
                                    find_left_break_point = true;
                                    left_break_point_y_to_out = i;
                                    break;
                                }

                            }
                            if (find_left_break_point && (firstloseline_left != IMG_H - 1 && finalloseline_left != -1 && firstloseline_left - finalloseline_left >= 5))//找到左拐点，看丢线行长度
                            {
                                repair_line(left_break_point_y_to_out, boundary_left[left_break_point_y_to_out], finalloseline_right + 1, boundary_right[finalloseline_right + 1]+1, LEFT_DIR);
                                re_midline();
                                //如果补线了，则取有效行
                                right_roundabout_useful_line = finalloseline_right + 1;
                                break;
                            }
                            else if ((firstloseline_left == IMG_H - 1 && finalloseline_left< IMG_H - 5 ) || (firstloseline_left >= IMG_H - 10 && finalloseline_left< IMG_H - 5) || (firstloseline_left - finalloseline_left >= 8) )//若左边界存在大段丢线，也补线
                            {
                                repair_line(IMG_H - 1, boundary_left[IMG_H - 1], finalloseline_right + 1,  IMG_W - 10, LEFT_DIR); //将图像右边界最终丢线行对应的左边界的点与最底行左边界的点连接，以修正左边界
                                re_midline();

                                //如果补线了，则取有效行
                                right_roundabout_useful_line = finalloseline_right + 1;
                                break;
                            }
                        }

                    }

                    if (!right_roundabout_out_right_repair_line){       right_roundabout_to_out_flag_count++;}
//                    //第五阶段 第二步，转弯结束即将离开右环岛区域，进行右边界修正（出环后期部分）
                    if (!right_roundabout_out_right_repair_line /*&& firstloseline_right == IMG_H - 1 */
                        && (((firstloseline_left != IMG_H - 1 /*&& firstloseline_left - finalloseline_right <= 5 */)|| (firstloseline_left == IMG_H - 1 && finalloseline_left >= IMG_H - 10))
                                ||(finalloseline_left<IMG_H - 15&&firstloseline_right<IMG_H - 20)
                        ))//右边丢线，左边丢线很短
                    {
                        right_roundabout_to_out_flag_count++;   //出环帧计数条件+1

                        /*判断是否出环*/

                        //统计底部右边界向左上延伸的趋势（或用右边界斜率）
                        int boundary_right_count = 0;
                        int count_total = 0;

                        for (int i = IMG_H - 20; i <= IMG_H - 2; i++)
                        {
                            if (boundary_right[i] > boundary_right[i - 1])                  //下一行的横坐标比上一行的大
                            {
                                boundary_right_count++;                                    //记录左边界往右上延伸的趋势的累计计数
                            }
                            count_total++;
                        }
                        if (((boundary_right_count >= 0.7 * count_total) /*趋势足够*/
                            && firstloseline_right != IMG_H - 1 && firstloseline_right <= IMG_H - 20 /*右边界底部大段不丢线*/
                            && right_roundabout_to_out_flag_count >= 40 /*出环帧计数条件需大于一定值*/)
                            || right_roundabout_to_out_flag_count >= 50/*通过帧数，当帧数大于某一个较大的值时，判断为出环*/) //判断为出环
                        {
                            right_roundabout_to_out_flag_count=0;
                            right_roundabout_out_flag = true;           //出环标志置1
                            right_roundabout_to_out_flag = false;
                            Right_Roundabout_State = 5 /*State6_Roundabout_Reset*/;                 //调整到下一阶段进行变量重置
                                break;
                        }
                        else //还未出环，则进行右边界补线处理
                        {
                            right_roundabout_useful_line = useful_line_further;  //取补线最高有效行
                            for (int i = right_roundabout_useful_line; i <= IMG_H - 1; i++)
                            {
                                if (Road_Width[i] > 0) //路宽大于0才有意义
                                {
                                    if (boundary_left[i] + Road_Width[i] <= IMG_W - 1)
                                        boundary_right[i] = boundary_left[i] + Road_Width[i];
                                    else
                                        boundary_right[i] = IMG_W - 1;
                                }

                                ////出环时经常偏右，采用 直接修正中线 来补线
                                //int length_temp = IMG_MIDDLE - Road_Refer_Left[i];
                                //if (length_temp > 0)//中线偏移量大于0才有意义
                                //{
                                //    if (boundary_left[i] + length_temp <= IMG_MIDDLE - 20)
                                //        middle_line[i] = IMG_MIDDLE - 20;
                                //    else if (boundary_left[i] + length_temp >= IMG_MIDDLE + 20)
                                //        middle_line[i] = IMG_MIDDLE + 20;
                                //    else
                                //        middle_line[i] = boundary_left[i] + length_temp;
                                //}
                            }
                            re_midline();
                            right_roundabout_out_right_repair_line = true;
                            right_roundabout_out_left_repair_line = false;
                        }
                    }
            }}
            break;
            case 5 /*State6_Roundabout_Reset*/:
            {RIGHT_Roundabout_State_step=0;
                //重置标志位及变量
                //if (right_roundabout_out_flag)//由于重置不一定是由出环导致的，也可能是由于持续帧数到达一定值，故注释此条件
                {
                    Right_Roundabout_State = 0 /*State1_Roundabout_Distern_1st_Repariline*/;//在此处结束第五个状态！！！转入第一个状态！！！
                    RIGHT_Roundabout_State_step=0;
                    right_roundabout_flag = 0;   //右环岛总标志位

                    //入环之前识别环岛
                    right_roundabout_discerning = true; //用于入环之前的环岛识别（看有没有环岛，一旦成功识别到环岛，则置0）
                    right_roundabout_discern_flag_count = 0; //右环岛入环之前环岛识别帧计数条件
                    right_roundabout_only_up_point_flag = false; //右环岛只有上拐点判断入环标志，出环才重置
                    right_roundabout_only_up_point_count = 0; //右环岛只有上拐点判断入环帧计数条件，出环才重置
                    right_roundabout_state1_repairline_count = 0; //右环岛第一阶段补线帧计数，用于辅助判断第一阶段的结束
                    right_roundabout_state1_repairline_to_end = false; //右环岛第一阶段补线即将结束标志
                    //入环处理
                    right_roundabout_state2_right_repairline_count = 0; //右环岛第一至第二过渡阶段右边界补线帧计数条件：为了下一阶段更好的过渡，在下一阶段的前几帧仍然补右边线
                    right_roundabout_in_right_repair_line = true; //右环岛进环时右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
                    right_roundabout_in_right_repair_line_count = 0; //右环岛进环时右边界补线计数条件（每有一帧右边界底部丢线需要补线，则+1）
                    right_roundabout_in_left_repair_line = true; //右环岛进环时左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
                    right_roundabout_in_change_angle = false; //强打角标志（当入环后期左边界底部不再丢线，强打角标志置1）
                    right_roundabout_to_in_count = 0; //右环岛进环结束的计数条件（当左边界底部不再丢线时，结合此条件(>0)，判断成功进入环岛内部）
                    //环内处理
                    right_roundabout_in_flag = false; //右环岛成功进入环岛内部标志位
                    right_roundabout_in_to_out_count = 0; //右环岛内部识别出环帧计数条件（判断出环的条件之一）
                    left_break_point_y_to_out = 0;           //出环时左拐点，用于出环打角
                    //出环处理
                    right_roundabout_to_out_flag = false; //右环岛出环处理部分标志位
                    right_roundabout_to_out_flag_count = 0; //右环岛出环处理标志位计数条件
                    right_roundabout_out_right_repair_line = false;    //右环岛出环时候的右边界补线处理（=1表示右边界底部仍存在丢线，需要补线）
                    right_roundabout_out_left_repair_line = true;     //右环岛出环时候的左边界补线处理（=1表示左边界底部仍存在丢线，需要补线）
                    right_roundabout_out_flag = false;          //右环岛出环标志//改了一下


//#if RIGHT_ROUNDABOUT_ONLY_ONE
//                        if_right_roundabout_recog                                 = 0;                 //只做一次环岛(注释掉则不只做一次环岛）
//#endif
                }
            }
            break;
            default:
                Right_Roundabout_State = 0 /*State1_Roundabout_Distern_1st_Repariline*/;
                break;
        }
    }

    //-----------------------------------右环岛处理END-------------------------------------//
}
#endif


#endif /* CIRCLE_C_ */
