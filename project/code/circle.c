/*
 * circle.c
 *
 *  Created on: 2024��7��10��
 *      Author: 86139
 */

#ifndef CIRCLE_C_
#define CIRCLE_C_
#include "zf_common_headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       �󻷵�ʶ������(״̬��ģʽ)
// @param       void
// @return      void
// @note        ʶ���󻷵������ߣ�����Ӧ��־λ
//              ע�⣺������ʶ�����������ڷֱ���Ϊ120*50��ͼ�����ֱ��ʸı䣬��ע��Ҫ�������еĲ���������
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
#if  USE_ROUNDABOUT_FSM
void left_roundabout_recog_by_FSM()
{
    //-----------------------------------�󻷵�����START------------------------------------//

    //--------------------��ر������ã�ÿһ֡�������ã�-------------------//
    find_roundabout_left_down = false; //�󻷵��¹յ�ʶ���־
    find_roundabout_left_up = false; //�󻷵��Ϲյ�ʶ���־
    find_roundabout_left_up_only = false; //�󻷵�ֻ�ҵ��Ϲյ��־
    roundabout_left_down_y = 0;     //�󻷵����¹յ�������
    roundabout_left_down_x = 0;     //�󻷵����¹յ������
    roundabout_left_up_y = 0;     //�󻷵����Ϲյ�������
    roundabout_left_up_x = 0;     //�󻷵����Ϲյ������
    right_boundary_slope = 0;     //�����б��
    left_roundabout_useful_line = 0;//����Ч��

    if (cross_full_flag == 0 && cross_half_flag == 0 && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && cross_after_turn_flag == 0
        && right_roundabout_flag == 0   )//������������û��ʮ�֡��һ�����ʱ������󻷵��ж�
    {
        switch (Left_Roundabout_State)
        {
            //------------------��һ�׶Σ���ʶ�𻷵����뻷ǰ�ڲ��֣�ͨ��˫�յ�򵥹յ����ʶ�𲢲��ߣ�---------------//
            /****�˽׶�Ӧ�ð������л�������������ûȷ��Ϊ������ʱ�Ĳ��ߡ�ȷ��Ϊ������Ĳ��ߣ�ֱ����ת����һ���׶Σ�****/
            case State1_Roundabout_Distern_1st_Repariline:
                {
                   // if (left_roundabout_discerning&&if_left_roundabout_recog)
                    if (left_roundabout_discerning)
                    {//left_roundabout_discerning�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
                     //if_left_roundabout_recogĬ��Ϊ1���������ˡ�ֻ��һ�λ�����ʱ�����ڻ���ʶ�𲢴��������0�����Ҫ���������轫�����������û��ڴ������ע��ȥ��


                        //����������־��
                        if ((firstloseline_left != IMG_H - 1)||firstloseline_left>IMG_H-10)    //ͼ���������в�����
                        {
                            for (int i = IMG_H - 3; i > useful_line_further /*��ֵ>=3*/; i--)  //��߽߱�������ʶ��Ѱ�����¹յ㣩
                            {
                                if ( boundary_left[i] > 5 /*���л������ϸ�����*/
                                    && boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >= boundary_left[i + 2] /*�¹յ��·�����Ϊ����������*/
                                    && boundary_left[i] - boundary_left[i + 1] < 3 && boundary_left[i + 1] - boundary_left[i] < 3 /*����һ�б߽�Ĳ����3����*/
                                    && ((lost_left_flag[i - 1] == 1 && lost_left_flag[i - 2] == 1) || (lost_left_flag[i - 2] == 1 && lost_left_flag[i - 3] == 1) || (lost_left_flag[i] == 1 && lost_left_flag[i - 3] == 1) /*�¹յ��Ϸ������������ж���*/ )
                                    && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ�������Ϊ����*/)   //Ѱ���¹յ�
                                {
                                    find_roundabout_left_down = true;              //��߽��¹յ�ʶ����
                                    roundabout_left_down_y = i;                    //��¼�¹յ��Ӧ������
                                    roundabout_left_down_x = boundary_left[i];     //��¼�¹յ��Ӧ������
                                }
                                if (find_roundabout_left_down)                    //���ҵ����¹յ㣨ǰ�ᣩ�����ϲ����Ϲյ�
                                {
                                    for (int j = roundabout_left_down_y - 1; j >= useful_line_further; j--)
                                    {
                                        if (boundary_left[j] >= boundary_left[j - 1] && boundary_left[j] >=boundary_left[j - 2] /*�Ϲյ���ϲ���*/
                                            && boundary_left[j] >= boundary_left[j + 1] && boundary_left[j] >= boundary_left[j + 2] && boundary_left[j] >= boundary_left[j + 3] /*�Ϲյ���²���*/
                                            && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j - 2] >= 5 /*��ֹΪ�߽�*/
                                            && Binary_Image[j][boundary_left[j] + 2] == IMG_WHITE && Binary_Image[j - 1][boundary_left[j - 1] + 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*�յ����ڴ�Ϊ����*/
                                            )
                                        {
                                            find_roundabout_left_up = true;                //��߽��Ϲյ�ʶ����
                                            roundabout_left_up_y = j;                     //��¼�Ϲյ��Ӧ������
                                            roundabout_left_up_x = boundary_left[j];     //��¼�Ϲյ��Ӧ������
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        else if (firstloseline_left == IMG_H - 1 && finalloseline_left > IMG_H - 15) //ͼ�����½���һС�ζ���Ӱ��ʶ��Ҫ�ֶ����ԣ������ն���������Ѱ�ҹյ㣩
                        {
                            for (int i = finalloseline_left - 1; i > useful_line_further ; i--)       //��߽��ϡ��¹յ�ʶ�𣨴Ӷ��߽�������ʼʶ��
                            {
                                if (boundary_left[i] > 5 /*���л������ϸ�����*/
                                    && boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >= boundary_left[i + 2] /*�¹յ��·�����Ϊ����������*/
                                    && boundary_left[i] - boundary_left[i + 1] < 3 && boundary_left[i + 1] - boundary_left[i] < 3 /*����һ�б߽�Ĳ����3����*/
                                    && ((lost_left_flag[i - 1] == 1 && lost_left_flag[i - 2] == 1) || (lost_left_flag[i - 2] == 1 && lost_left_flag[i - 3] == 1) || (lost_left_flag[i] == 1 && lost_left_flag[i - 3] == 1) /*�¹յ��Ϸ���������2�ж���*/ )
                                    && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ�������Ϊ��������ɫ��*/)   //Ѱ���¹յ�
                                {
                                    find_roundabout_left_down = true;              //��߽��¹յ�ʶ����
                                    roundabout_left_down_y = i;                    //��¼�¹յ��Ӧ������
                                    roundabout_left_down_x = boundary_left[i];     //��¼�¹յ��Ӧ������
                                }
                                if (find_roundabout_left_down)                    //���ҵ����¹յ㣨ǰ�ᣩ�����ϲ����Ϲյ�
                                {
                                    for (int j = roundabout_left_down_y - 1; j >= useful_line_further; j--)
                                    {
                                        if (boundary_left[j] >= boundary_left[j - 1] && boundary_left[j] >= boundary_left[j - 2] /*�Ϲյ���ϲ���*/
                                            && boundary_left[j] >= boundary_left[j + 1] && boundary_left[j] >= boundary_left[j + 2] && boundary_left[j] >=boundary_left[j + 3] /*�Ϲյ���²���*/
                                            && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j - 2] >= 5 /*��ֹΪ�߽�*/
                                            && Binary_Image[j][boundary_left[j] + 2] == IMG_WHITE && Binary_Image[j - 1][boundary_left[j - 1] + 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*�յ����ڴ�Ϊ����*/
                                           )
                                        {
                                            find_roundabout_left_up = true;                //��߽��Ϲյ�ʶ����
                                            roundabout_left_up_y = j;                     //��¼�Ϲյ��Ӧ������
                                            roundabout_left_up_x = boundary_left[j];     //��¼�Ϲյ��Ӧ������
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }

                        //���ݹյ���Ƿ��ǻ��������ж�
                        if (left_roundabout_flag == 0) //δʶ�𵽻����Ž����ж�
                        {
                            /*������һ֡ͼ����ͬʱ�ҵ������յ㣨������������*/
                            if (find_roundabout_left_down && find_roundabout_left_up)
                            {
                                //û�����������������ʶ��֡����������1
                                left_roundabout_discern_flag_count++;

                                for (int i = roundabout_left_up_y; i < roundabout_left_down_y; i++)//�����ж����¹յ㣨������߻�ã�����ұ����Ƿ�����
                                {
                                        if(lost_right_flag[i]==1){
                                        left_roundabout_discern_flag_count = 0;
                                             break;}
                                    }
                                if (left_roundabout_discern_flag_count==0)//�ұ߶���
                                    break;  //�˳�switch��������֡����ʶ��

//                                //����һЩ����������������У���ʶ��֡����������0��
                                //������һЩ�������Ǻܺã����»���ʶ�𲻵�����ע�͵��ˣ�����ڷǻ����ĵط����л����ˣ���ҿ�����������������
//                                //1��
//                                for (int counti = roundabout_left_down_y; counti >= roundabout_left_up_y; counti--)
//                                {
                                //�Դ��¹յ㵽�Ϲյ��ÿһ�У�������߽絽�ұ߽��Ƿ���ںڵ㣬�����ڣ���ʶ��֡����������0�����˳���֡�Ļ���ʶ��
//                                    for (int countj = boundary_left[roundabout_left_up_y]; countj < boundary_right[roundabout_left_up_y]; countj++)
//                                    {
//                                        if (Binary_Image[counti][countj] == IMG_BLACK)
//                                        {
//                                            left_roundabout_discern_flag_count = 0;
//                                            break;
//                                        }
//                                    }
//                                    if (left_roundabout_discern_flag_count == 0)
//                                        break;  //�˳����ѭ��
//                                }
//                                if (left_roundabout_discern_flag_count == 0)
//                                    break;  //�˳�switch��������֡����ʶ��
//                                //2��
//                                if (!(boundary_right[roundabout_left_up_y] - boundary_left[roundabout_left_up_y] >= 5 && roundabout_left_down_y - roundabout_left_up_y >= 8 && loserightflag == 0))
//                                {// !() ���������������е��������������㣨�Ϲյ㴦�ұ߽������߽�һ��ֵ�������¹յ����������һ������/*����һ�߶��ߣ�һ��û�ж���*/������������֡����������0
//                                    left_roundabout_discern_flag_count = 0;
//                                    break;  //�˳�switch��������֡����ʶ��
//                                }

//                                //3:�Ϲյ�����Ӧ����ȫ��
//                                int B2W_change_pointx_temp = 0;//�ڰ������
//                                B2W_change_pointx_temp = findchange(roundabout_left_up_x - 1, LEFT_DIR, roundabout_left_down_y, IMG_WHITE, 0, 2, 1);//���Ϲյ�����Һڰ������
//                                if (roundabout_left_up_x - B2W_change_pointx_temp <= 5)//���Ϲյ���ߺܽ����кڰ�����㣨˵�������Ϲյ㣩
//                                {
//                                    left_roundabout_discern_flag_count = 0;
//                                    break;  //�˳�switch��������֡����ʶ��
//                                }
//                                //4:�ұ���б��
//                                int boundary_Rdown_to_Lup_count = 0;   //�ұ߽�������������������Ƶ��ۼƼ�������
//                                for (int i = roundabout_left_down_y; i >= roundabout_left_up_y; i--)     //�ұ߽߱�������ʶ�𣬼��ұ߽��д��������������������
//                                {
//                                    if (boundary_right[i] > boundary_right[i - 1])                  //��һ�еĺ��������һ�еĴ�
//                                    {
//                                        boundary_Rdown_to_Lup_count++;                              //��¼�ұ߽���������������Ƶ��ۼƼ���
//                                    }
//                                }
//                                //�����ұ��߹յ㴦�������ڵ�ֱ��б�ʣ�����һ������б�ʣ���ͼ���������죩
//                                right_boundary_slope = (float)(roundabout_left_down_y - roundabout_left_up_y) / (boundary_right[roundabout_left_up_y] - boundary_right[roundabout_left_down_y]);
//
//                                if (boundary_Rdown_to_Lup_count < 0.7 * (roundabout_left_down_y - roundabout_left_up_y) || right_boundary_slope >= 0 /*|| boundary_right[roundabout_left_up_y] <= IMG_MIDDLE - 20*/)
//                                {//����ұ߽������������������Ʋ����������ұ߽�б��Ϊ�Ǹ�ֵ�������Ϲյ㴦���ұ߽����ƫ��
//                                    left_roundabout_discern_flag_count = 0;
//                                    break;  //�˳�switch��������֡����ʶ��
//                                }
                            }
                            /*���޷���һ֡ͼ����ͬʱ�ҵ������յ㣬����ݡ�ֻ���Ϲյ㡱�ж��뻷*/
                            //��Ϊ�����׼ȷ�ʣ�������Ҫ��������ĳһ֡ʶ��һ�� �¹յ㣬�Խ��Ϲյ�֡������־ ��
                            else if (find_roundabout_left_down && !find_roundabout_left_up)//�ҵ��¹յ��û���Ϲյ�
                            {
                                //Ѱ���Ƿ���һ���� �����ҵ��Ϲյ� �����ƣ���ʱ�Ϲյ���������ɣ�����ֻ�����Ϲյ���°벿�֣�
                                for (int i = (roundabout_left_down_y < IMG_H - 4 ? roundabout_left_down_y : IMG_H - 4)/*��ֹ����Խ��*/; i >= useful_line_further; i--)//���¹յ�������
                                {
                                    //Ѱ���±�ʶ�㣬�ҵ��Ϳ�ʼ��¼�ҵ�����Ѿ����˼�֡
                                    if (boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >=boundary_left[i + 2] && boundary_left[i + 1] >= boundary_left[i + 3] /*�Ϲյ��·����������������*/
                                        && boundary_left[i] >= 5 && boundary_left[i - 1] >= 5 && boundary_left[i + 1] >= 5  /*��ֹΪ�߽�*/
                                        && boundary_left[i] - boundary_left[i + 3] >= 5 /*�Ϲյ���·������㹻*/
                                        && Binary_Image[i][boundary_left[i] + 2] == IMG_WHITE && Binary_Image[i- 1][boundary_left[i - 1] + 2] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ����ڴ�Ϊ����*/
                                        && Binary_Image[i][middle_line[i]] == IMG_WHITE
                                        )
                                    {
                                        left_roundabout_only_up_point_flag = true; //�Ϲյ�֡������־��
                                        left_roundabout_only_up_point_count = 0; //׼������
                                        break;
                                    }

                                }

                            }

                            /*ֻ���Ϲյ��ж��뻷���н��Ϸ�else if*/
                            if (left_roundabout_only_up_point_flag)//����ҵ��±�ʶ�������8֡��û���ҵ��ϱ�ʶ�㣬������
                            {
                                left_roundabout_only_up_point_count++;

                                if (left_roundabout_only_up_point_count >= 8)//8֡���ݾ�������ı�
                                {
                                    left_roundabout_only_up_point_flag = false;
                                    left_roundabout_only_up_point_count = 0;
                                }
                            }

                            if (!find_roundabout_left_up && left_roundabout_only_up_point_flag)//���û���ҵ��Ϲյ㣬���Ϲյ�֡������־Ϊtrue����ֹ����һ֡����ͬʱ�ҵ����¹յ㣬��ִ���·���䣩
                            {
                                //����һ��������ʼ���Ϲյ�(��ʱ�����¹յ㣬�����ҵ��Ϲյ㣬���жϻ���)
                                if (finalloseline_left <= IMG_H - 5)//���ն�����
                                {
                                    for (int i = finalloseline_left; i >= useful_line_further; i--)
                                    {
                                        if (boundary_left[i] >= boundary_left[i - 1] && boundary_left[i] >= boundary_left[i - 2] /*�Ϲյ���ϰ벿��������ȷ*/
                                            && boundary_left[i] - boundary_left[i - 1] <= 5 && boundary_left[i - 1] - boundary_left[i] <= 5 && boundary_left[i] - boundary_left[i - 2] <= 5 && boundary_left[i - 2] - boundary_left[i] <= 5 /*���ƹյ��Ϸ���ĺ������� */
                                            && boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] > boundary_left[i + 2] && boundary_left[i + 1] > boundary_left[i + 3] /*�Ϲյ���°벿��������ȷ*/
                                            && boundary_left[i] - boundary_left[i + 4] >= 7 /*�¹յ��°벿�������㹻*/
                                            && boundary_left[i] >= 2 && boundary_left[i - 1] >= 2 && boundary_left[i + 1] >= 2 && Binary_Image[i][boundary_left[i]] == IMG_WHITE/*��ֹΪ�߽�*/
                                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i]] == IMG_WHITE && Binary_Image[i - 2][middle_line[i]] == IMG_WHITE && Binary_Image[i - 3][middle_line[i]] == IMG_WHITE /*ȷ��Ϊ����*/
                                            &&Binary_Image[i-3][boundary_left[i] ] == IMG_WHITE//ȷ��Ϊ����
                                            )
                                        {
                                            roundabout_left_up_y = i;
                                            roundabout_left_up_x = boundary_left[i];

                                            //û�����������������ʶ��֡����������1
                                            left_roundabout_discern_flag_count++;

                                            for (int i = roundabout_left_up_y-5; i < roundabout_left_up_y+5; i++) {
                                               if(lost_right_flag[i]==1){
                                                   left_roundabout_discern_flag_count = 0;break;
                                               } }
                                          if (left_roundabout_discern_flag_count==0)//�ұ߶��߶�

                                                                       break;  //�˳�switch��������֡����ʶ��

                                            //����һЩ����������������У���ʶ��֡����������0,���ϱ���ͬ��
//                                            //1��
//                                            if (!(boundary_right[roundabout_left_up_y] - roundabout_left_up_x >= 5 && loserightflag == 0))
//                                            {// !() ���������������е��������������㣨�Ϲյ㴦�ұ߽������߽�һ��ֵ/*����һ�߶��ߣ�һ��û�ж���*/������������֡����������0
//                                                left_roundabout_discern_flag_count = 0;
//                                                continue; //����Ѱ���Ϲյ�
//                                            }

//                                            //2:
//                                            for (int counti = finalloseline_left; counti >= roundabout_left_up_y; counti--)
//                                            {
//                                                //�Դ����ն����е��Ϲյ��ÿһ�У�������߽絽�ұ߽��Ƿ���ںڵ㣬�����ڣ���ʶ��֡����������0�����˳���֡�Ļ���ʶ��
//                                                for (int countj = boundary_left[roundabout_left_up_y]; countj < boundary_right[roundabout_left_up_y]; countj++)
//                                                {
//                                                    if (Binary_Image[counti][countj] == IMG_BLACK)
//                                                    {
//                                                        left_roundabout_discern_flag_count = 0;
//                                                        break;
//                                                    }
//                                                }
//                                                if (left_roundabout_discern_flag_count == 0)
//                                                    break;  //�˳����ѭ��
//                                            }
//                                            if (left_roundabout_discern_flag_count == 0)
//                                                continue;  //����Ѱ���Ϲյ�
//                                            //3:�ұ���б��
//                                            int boundary_Rdown_to_Lup_count = 0;   //�ұ߽�������������������Ƶ��ۼƼ�������
//                                            for (int m = finalloseline_left; m >= roundabout_left_up_y; m--)     //�ұ߽߱�������ʶ�𣬼��ұ߽��д��������������������
//                                            {
//                                                if (boundary_right[m] > boundary_right[m - 1])                  //��һ�еĺ��������һ�еĴ�
//                                                {
//                                                    boundary_Rdown_to_Lup_count++;                              //��¼�ұ߽���������������Ƶ��ۼƼ���
//                                                }
//                                            }
//
//                                            if (boundary_Rdown_to_Lup_count < 0.85 * (finalloseline_left - roundabout_left_up_y) /*|| boundary_right[roundabout_left_up_y] <= IMG_MIDDLE - 20*/)
//                                            {//����ұ߽������������������Ʋ����������Ϲյ㴦���ұ߽����ƫ��
//                                                left_roundabout_discern_flag_count = 0;
//                                                continue;  //����Ѱ���Ϲյ�
//                                            }

                                            //�������н���������ִ�е��ˣ���֡��������>=2�����ݳ��ٵ���
                                            if (left_roundabout_discern_flag_count >= 2)
                                            {
                                                find_roundabout_left_up_only = true;//ֻ�ҵ��Ϲյ��־λ��1
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                            /*��Ҫ�Ļ��ٲ��䡰б�뻷��������*/


                            //�����������뻷����дһ��б�뻷��


                            //����֡������������һ��ֵ�󣬳ɹ�ʶ�𻷵�
                            if (left_roundabout_discern_flag_count >= ROUNDABOUT_DISCERN_COUNTS)
                            {
                                left_roundabout_flag = 1;
                            }
                            else if(left_roundabout_discern_flag_count != 0) //ʶ����ĳһ֡����֮��һֱû����ʶ�𵽣������۵�ĳһ֡��������
                            {
                                state_continue_frame_count++;
                                if(state_continue_frame_count >= 100)//֡���ɵ�
                                {
                                    state_continue_frame_count = 0;
                                    left_roundabout_discern_flag_count = 0;
                                    break;
                                }
                            }
                        }

                        //���ݲ�ͬ�Ĺյ�������в���
                        if (left_roundabout_flag == 1)//ʶ�𵽻���
                        {
                            left_roundabout_state1_repairline_count++; //��һ�׶β���֡��������+1

                            //1:�ҵ������յ㣬����
                            if (find_roundabout_left_down && find_roundabout_left_up)
                            {
                                repair_line(roundabout_left_down_y, roundabout_left_down_x, roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR);//���������¹յ������߽������������ߣ�

                                re_midline(); //����������������д����
                                LEFT_Roundabout_State_step=1;
                                //��������ˣ���ȡ��Ч��
                                left_roundabout_useful_line = roundabout_left_up_y;
                            }
                            //2:ֻ���Ϲյ㣬����
                            else if (find_roundabout_left_up_only)
                            {
                                repair_line(IMG_H - 1, boundary_left[IMG_H - 1], roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR); //������߽�ױ����Ϲյ㲹��

                                re_midline(); //����������������д����
                                LEFT_Roundabout_State_step=1;
                                //��������ˣ���ȡ��Ч��
                                left_roundabout_useful_line = roundabout_left_up_y;
                            }
                            //3��ֻ���±�־��ʱ����
                            else if (find_roundabout_left_down && !find_roundabout_left_up)
                            {
                                //�Խ��ɵ��������Ϲյ�
                                for (int j = roundabout_left_down_y - 5; j >= useful_line_further; j--)
                                {
                                    if (boundary_left[j] >= boundary_left[j - 1] /*�Ϲյ���ϲ���*/
                                        && boundary_left[j] >= boundary_left[j + 1] /*�Ϲյ���²���*/
                                        && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j + 2] >= 5 /*��ֹΪ�߽�*/
                                        && Binary_Image[j][boundary_left[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE/*�յ����ڴ�Ϊ����*/
                                        &&Binary_Image[j-3][boundary_left[j] ] == IMG_WHITE)
                                    {
                                        roundabout_left_up_y = j;                     //��¼�Ϲյ��Ӧ������
                                        roundabout_left_up_x = boundary_left[j];     //��¼�Ϲյ��Ӧ������

                                        repair_line(roundabout_left_down_y, roundabout_left_down_x, roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR);//���������¹յ������߽������������ߣ�

                                        re_midline(); //����������������д����
                                        LEFT_Roundabout_State_step=1;
                                        //��������ˣ���ȡ��Ч��
                                        left_roundabout_useful_line = roundabout_left_up_y;

                                        break;
                                    }
                                }
                            }
                            //4:ʶ�𵽻������Ҳ����·��㣬Ҳ����ֻ�ҵ��Ϸ���Ĳ���
                            else if (!find_roundabout_left_down && !find_roundabout_left_up_only)
                            {
                                for (int j = (finalloseline_left <= IMG_H - 4 ? finalloseline_left : IMG_H - 4 /*��ֹ����Խ��*/); j >= useful_line_further; j--)//�����ն���������Ѱ�ҹյ�
                                {
                                    if (boundary_left[j] >= boundary_left[j - 1] /*�Ϲյ���ϲ���*/
                                        && boundary_left[j] >= boundary_left[j + 1] /*�Ϲյ���²���*/
                                        && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j + 2] >= 5 /*��ֹΪ�߽�*/
                                        && Binary_Image[j][boundary_left[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*�յ����ڴ�Ϊ����*/
                                        &&Binary_Image[j-3][boundary_left[j] ] == IMG_WHITE)
                                    {
                                        roundabout_left_up_y = j;                     //��¼�Ϲյ��Ӧ������
                                        roundabout_left_up_x = boundary_left[j];     //��¼�Ϲյ��Ӧ������
                                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR); //������߽�ױ����Ϲյ㲹��

                                        re_midline(); //����������������д����
                                        LEFT_Roundabout_State_step=1;
                                        //��������ˣ���ȡ��Ч��
                                        left_roundabout_useful_line = roundabout_left_up_y;

                                        left_roundabout_state1_repairline_to_end = true; //������ˣ����ʾ��һ�׶εĲ��߼�������

                                        break;
                                    }
                                }
                            }
                        }

                        //������һ�׶ε��ڶ��׶ε��ж�
                        if (left_roundabout_state1_repairline_count >= ROUNDABOUT_STATE1_TO_IN_COUNTS && left_roundabout_state1_repairline_to_end)
                        {
                            for (int i = IMG_H - 1; i >= /*IMG_H - 25*/10; i--)
                            {
                                if (boundary_left[i] >= boundary_left[i - 1] && boundary_left[i - 1] >= boundary_left[i - 2] && boundary_left[i - 2] >= boundary_left[i - 3] && boundary_left[i - 3] >= boundary_left[i - 4] && boundary_left[i] > boundary_left[i - 4]  /*�������ڽ�ǿ�������������ƣ�˵�����뻷����Ͻ�*/
                                    && boundary_left[i] >= 2 && boundary_left[i - 1] >= 2 && boundary_left[i - 2] >= 2 /*��ֹΪ�߽�*/
                                    && ((firstloseline_left != IMG_H - 1 && firstloseline_left - finalloseline_left <= 10) || (firstloseline_left == IMG_H - 1 && finalloseline_left > /*45*/IMG_H - 15))/*��߽�ײ������ߣ����߽϶�*/)
                                {
                                    left_roundabout_discerning = false; //�뻷ǰ����ʶ��ʧЧ��֮���ٽ��е�һ�׶Σ����뻷ǰ����ʶ��׶Σ���
                                  Left_Roundabout_State = State3_Roundabout_To_In_3th_Repairline; //�ڴ˴�������һ��״̬������ת�������״̬���������ڶ���״̬�Ѿ���Ч�ˣ�
                                  //  Left_Roundabout_State = State2_Roundabout_To_In_2nd_Repairline; //�ڴ˴�������һ��״̬������
                                    left_roundabout_state2_left_repairline_count = 0; //Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ���ұ���
                                    state_continue_frame_count = 0;//״̬����֡�����������㣬Ϊ��һ�׶���׼��
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            //-----�ڶ��׶Σ�ʶ�𻷵��ɹ���Ҫ���뻷�����뻷���ڣ���Ӧ���յ����߽粹�ߣ�(�����Ѿ������˽׶���)------//
            case State2_Roundabout_To_In_2nd_Repairline:
                {LEFT_Roundabout_State_step=2;
                    if (left_roundabout_flag == 1 && left_roundabout_discerning == false/*����һ��5*/&& left_roundabout_in_flag == false && left_roundabout_to_out_flag == false/*����һ��*/ && left_roundabout_in_left_repair_line == true) //�뻷�����֣�����ʶ��̣����뻷���ڲ�������������
                    {
                        //��ߴ�����п�ʼ���ڶ��ߣ���Ҫ������߽磨left_roundabout_in_left_repair_line = 1��ʾ��߽��Դ��ڶ��ߣ���Ҫ���ߣ����뻷���ڲ��֣�
                        if (firstloseline_left == 49 /*����һ��5*//*&& left_roundabout_in_left_repair_line*/)
                        {
                            int upy = 0;                                                                                    //��ȡ��߽�յ�������
                            for (int i = finalloseline_left; i > 2; i--)
                            {
                                //��������if�������Ѱ����߽�յ㣨��ʱû���¹յ�ֻ���Ϲյ��ˣ�
                                if (boundary_left[i] >= boundary_left[i - 1] /*&& boundary_left[i] >= boundary_left[i - 2]*/)  //Ѱ�ҹյ㣨���ϲ��֣�--�յ�ĺ�����������µĶ���
                                {
                                    if (boundary_left[i] > boundary_left[i + 1] && boundary_left[i] > boundary_left[i + 2]) //ȷ�Ϲյ㣨���²��֣�
                                    {
                                        upy = i;                                                                                            //��¼�յ�������
                                        break;
                                    }
                                }
                            }
                            left_roundabout_in_left_repair_line_count++;                        //��߽粹�ߣ���������+1������߽綪���ڼ��ÿһ֡����һ���ߣ����������ɴ�ֱ����߲������ˣ�
                            repair_line(49, boundary_left[49], upy, boundary_left[upy], LEFT_DIR); //������߽�
                            re_midline(); //�������ұ�����д����

                            //��������ˣ���ȡ��Ч��
                            left_roundabout_useful_line = upy;
                        }

                        //����߽粻������ж����ˣ�ͬʱ��߽粹�߼�������>0(�ɵ�)��������߽粹��ʧЧ-֮���ٲ��ߣ���ʱ�ѵ��뻷���ڲ��֣�
                        if ((firstloseline_left != 49 || (firstloseline_left == 49 && finalloseline_left > /*45*/40/*����һ�£���߽絽�����ڶ��ߣ���*/)) && left_roundabout_in_left_repair_line_count > 0/*֡������������*/)
                        {
                            left_roundabout_in_left_repair_line = false;                                    //��߽粹��ʧЧ��������Ҫ����
                            Left_Roundabout_State = 2;                                                                               //�ڴ˴������ڶ���״̬������ת�������״̬������
                        }
                    }
                }
                break;
            //-----�����׶Σ�ʶ�𻷵��ɹ���Ҫ���뻷�����뻷���ڣ���߽粻�ٲ��ߣ������ұ߽粹�ߣ�------//
            case State3_Roundabout_To_In_3th_Repairline:
                {LEFT_Roundabout_State_step=3;

                if (left_roundabout_flag == 1 && !left_roundabout_discerning && !left_roundabout_in_flag && !left_roundabout_to_out_flag  && left_roundabout_in_right_repair_line)
                    {
                        //��ʼǰ��֡����߽粹��
                        if(left_roundabout_state2_left_repairline_count <= 5)
                        {
                            left_roundabout_state2_left_repairline_count++;

                            for (int j = IMG_H - 4; j >= useful_line_further; j--)//�����ն���������Ѱ�ҹյ�
                            {
                                if (boundary_left[j] >= boundary_left[j - 1] && boundary_left[j] >=boundary_left[j - 2]/*�Ϲյ���ϲ���*/
                                    && boundary_left[j] >= boundary_left[j + 1] && boundary_left[j] >= boundary_left[j + 2]/*�Ϲյ���²���*/
                                    && boundary_left[j] >= 5 && boundary_left[j - 1] >= 5 && boundary_left[j + 1] >= 5 && boundary_left[j + 2] >= 5 /*��ֹΪ�߽�*/
                                    && Binary_Image[j][boundary_left[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE /*�յ����ڴ�Ϊ����*/

                                )
                                {
                                    roundabout_left_up_y = j;                     //��¼�Ϲյ��Ӧ������
                                    roundabout_left_up_x = boundary_left[j];     //��¼�Ϲյ��Ӧ������

                                    repair_line(IMG_H - 1, boundary_left[IMG_H - 1], roundabout_left_up_y, roundabout_left_up_x, LEFT_DIR); //������߽�ױ����Ϲյ㲹��

                                    re_midline(); //����������������д����

                                    break;
                                }
                            }
                        }


                        if (firstloseline_right == IMG_H - 1 && finalloseline_right < IMG_H - 10)      //�ұ߽�ײ����ֶ���//�뻷����������ʼ�Լ�
                        {
                            left_roundabout_to_in_count++;    //׼���뻷
                        }
                          /*
                                                             ����ǿ���ʱ�ڵ���⣺
                                                             ���뻷���ڲ��ֽ����������뻷���ڲ��֣�����߽�ײ����ٶ��ߣ�ʱ
                     (1)�ұ߽������һ��ʼ���ܲ����ߣ���ʱִ����ͨ���ߡ�������󷽴��룩
                     (2)��֮��һ��������ұ߽�����ж��߽׶Ρ�������һ��ʼ���߽϶̣����ն�����>20����Ȼִ����ͨ���ߣ�ֱ�����ִ�ζ��ߣ����ն�����<20��
                                                                      ִ��ǿ��ǣ�֮��һֱǿ���ֱ������ж��߽���
                     (3)��֮������ж��߽��������׽��뻷���ڣ���ʱ�·����뿪ʼִ�У����ұ߲��ٲ��ߣ������ڲ���־λ��1��
                          */
                        //״̬ת�Ƶ��ж�
                       //ע�⣡�����·���������е���������������Լ��ֻ�����ұ߽翪ʼ���ߣ�ֱ���ұ߽綪�߽�����Ż������֮���Խ���ִ�еĴ������ǰ�棬��Ϊ����ǰʶ������в����ߣ��Ӷ����ұ߲��߱�־��0��
                             if ((((firstloseline_right != IMG_H - 1 && firstloseline_left - finalloseline_left <= 5&&firstloseline_left)|| (firstloseline_right == IMG_H - 1 && finalloseline_right >= IMG_H - 5) /*�ұ߳���С�ζ���Ҳ��Ϊ������*/)
                                 && left_roundabout_to_in_count > 0/*��������������������*/)
                                     ||time_in>30//ÿһ֡����һ�������ڸ�״̬Ϊ��ʱ�䣬��ֹ��״̬λ����������״̬λһֱΪ3�������Ѿ��뻷��Ҳ��ˢ�£�
                                     )
                             {//���ұ߽粻�ٶ��߻��߽϶̣����뻷������������Ҫ�������״̬��ת
                                 left_roundabout_in_right_repair_line = false;  //�ұ߽粹��ʧЧ
                                 left_roundabout_in_flag = true;                //�����ڲ����ߴ�����Ч�����뻷���ڲ���
                                 left_roundabout_in_change_angle = false;       //ǿ�������ȥ��
                                 Left_Roundabout_State = State4_Roundabout_In;  //�ڴ˴�����������״̬������ת����ĸ�״̬������
                                 time_in=0;
                                 break; //�˳�������
                             }

                        if (firstloseline_right == IMG_H - 1 && finalloseline_right < IMG_H - 10/*������Сһ��Ļ�����ǵ�ʱ������һ��*/) //�ұߴ�����¿�ʼ��һ��ζ��ߣ�����ǿ����뻷
                        {
                            left_roundabout_in_change_angle = true;                                     //ǿ��Ǳ�־��1
                        }



                        //��ͨ�ұ߽粹�ߣ���ʱ��ûǿ���
                        /*��߽粻���ߺ�һ��ʼ�ұ߽��ǲ����ߵģ�ִ�е�����ͨ���ߣ��Լ����ұ߽�����п�ʼ���ߣ������߽϶�ʱҲִ����ͨ����*/
                        if (!left_roundabout_in_change_angle)
                        {
                            //�����ѱ��ߣ����ڻ���������ұ߽��뻷���Ϸ�ֱ������߽�ͬʱ���ڣ���ʹ���ұ߽�ʶ���ǰ�ߣ��������Ϸ�ֱ������߽��޷�ʶ�𣬹������ѱ��ߣ�
                            for (int i = IMG_H - 2; i > useful_line_further; i--)
                            {
                                //���ұ߽�Ϊ��׼�������߽���ƫ�ƣ�������ȷ��������ʼ�㣩
                                if (boundary_right[i + 1] - 7 >= 0)
                                {
                                    middle_line[i] = boundary_right[i + 1] - 7;
                                }
                                //��ƫ�ƺ��������������
                                boundary_left[i] = findchange(middle_line[i], LEFT_DIR, i, IMG_BLACK, 0, 2, 1);
                                boundary_right[i] = findchange(middle_line[i], RIGHT_DIR, i, IMG_BLACK, IMG_W - 1, 1, 2);
                            }


                            int lefty = 0;                                   //��ȡ��߽���ѵ������꣨����ֱ����Բ������ķֲ棬��߽����ն������ж��ѵ㣬������㴦��߽������ͻ�䣩
                            bool find_left_break_point = false;              //�Ƿ��ܻ�ȡָ����ı�־

                            for (int i = IMG_H - 10; i > useful_line_further; i--)
                            {
//
                                if (boundary_left[i] > 10&& (boundary_left[i] - boundary_left[i + 1] > 10 || boundary_left[i] - boundary_left[i + 2] > 10)/*���������ͻ��*/
                                        && boundary_left[i] - boundary_left[i - 1] <= 4 && boundary_left[i - 1] - boundary_left[i] <= 4 /*���ƹյ����Ϸ��������Ĳ��*/
                                        && Binary_Image[i][boundary_left[i]] == IMG_WHITE /*�յ㴦Ϊ����*/
                                        &&i>18//���ƹյ���ͼ���е�λ�ã���˾���ʲôʱ��ʼת���뻷
                                )
                                {
                                    //�����ɫռ�ȣ���ֹ���У�
                                    int count_white = 0, count = 0;
                                    for (int j = boundary_left[i + 1]; j <= boundary_left[i]; j++)//���������������Ӧ����ȫ��
                                    {
                                        if (Binary_Image[i + 1][j] == IMG_WHITE)//�������ж�
                                        {
                                            count_white++;
                                        }
                                        count++;
                                    }
                                    if (count_white >= 0.8 * count)
                                    {
                                        lefty = i;                        //��ȡָ����������
                                        find_left_break_point = true;     //��ȡ����ָ����
                                        break;
                                    }
                                }
                            }
                            if (find_left_break_point)
                            {

                                repair_line(IMG_H -1, boundary_right[IMG_H - 1], lefty, boundary_left[lefty], RIGHT_DIR); //��ָ���㵽��׶��ұ߽������������ұ߽�

                                //��������ˣ���ȡ��Ч��
                                left_roundabout_useful_line = lefty;
                            }

                            re_midline();         //��д����
                        }
                        else     //ǿ��ǣ��ɿ��ϱ�ǿ��ŵ�����
                        {
                            //���������У����Ե��¶̾��붪��
                            loseline_adjust(LEFT_DIR, 8);
                            time_in++;
                            //ֱ����������ǿ��ǹ�ǿ����Ϊ�����ұ߽�
                            repair_line(IMG_H - 1, boundary_right[IMG_H - 1], finalloseline_left + 2, /*boundary_right[finalloseline_left + 2]*/20, RIGHT_DIR);
                            re_midline();
                            //��������ˣ���ȡ��Ч��
                            left_roundabout_useful_line = finalloseline_left + 1;
                        }
                    }
                }
                break;
            //-------------���Ľ׶Σ����뻷���ڲ��������ڲ������֣�-------------//
            case State4_Roundabout_In:
                {LEFT_Roundabout_State_step=4;

                    if (left_roundabout_flag == 1 && left_roundabout_in_flag)       //ʶ�𻷵���־λ�ͽ��뻷���ڲ���־λ��Ϊ1����ʼ���´���
                    {
                        left_roundabout_in_to_out_count++;                          //�󻷵��ڲ�ʶ�����֡��������+1

                        /*�ڲ�ת�䴦������ת��ͬ��һ������*/

                        //״̬ת�Ƶ��ж�
                        if (left_roundabout_in_to_out_count > ROUNDABOUT_IN_TO_OUT_COUNTS)
                        {
                            //���ұ߽��Ƿ���ڹյ�
                            bool find_right_break_point = false;
                            right_break_point_y_to_out = 0; //��¼�ұ߽�յ�������
                            for (int i = (IMG_H - 5); i > useful_line_further /*����>=����ֹ����Խ��=*/; i--)//���ҹյ㲢����־λ
                            {
                                if (boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i] < boundary_right[i + 3] && boundary_right[i + 1] - boundary_right[i] <= 5 /*�յ��·���������������*/
                                        &&i>15//���ƹյ�λ�ã���˾���ʲôʱ�����
                                        && boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] > boundary_right[i] /*�յ��Ϸ�*/
                                    && (boundary_right[i - 1] - boundary_right[i] >= 10 || boundary_right[i - 2] - boundary_right[i] >= 10 || boundary_right[i - 3] - boundary_right[i] >= 10)/*�յ��Ϸ����ٴ���һ��������ͻ�䣬ע��·���Ӱ�죡��*/
                                    && ((boundary_right[i - 1] == IMG_W - 1 && boundary_right[i - 2] == IMG_W - 1)||
                                            (boundary_right[i - 2] == IMG_W - 1 && boundary_right[i - 3] == IMG_W - 1) ||
                                            (boundary_right[i - 3] == IMG_W - 1 && boundary_right[i - 4] == IMG_W - 1)||
                                            (boundary_right[i - 4] == IMG_W - 1 && boundary_right[i - 5] == IMG_W - 1)||
                                            (boundary_right[i - 6] == IMG_W - 1 && boundary_right[i - 7] == IMG_W - 1))/*�յ��Ϸ����ٴ����������ж���*/
                                    && Binary_Image[i][boundary_right[i]]== IMG_WHITE && Binary_Image[i + 1][boundary_right[i + 1]] == IMG_WHITE && Binary_Image[i - 1][boundary_right[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ㴦Ϊ����*/)
                                {
                                    find_right_break_point = true;
                                    right_break_point_y_to_out = i;
                                    break;
                                }
                            }
                            if (find_right_break_point == true)//�ҵ��ҹյ㣬�������г���
                            {
                                if (firstloseline_right > 15&& firstloseline_left==IMG_H - 1 && firstloseline_right - finalloseline_right >= 5)
                                {
                                    //��ת����һ��״̬ǰ���߹���
                                    repair_line(right_break_point_y_to_out, boundary_right[right_break_point_y_to_out], finalloseline_left + 1, boundary_left[finalloseline_left + 1], RIGHT_DIR);
                                    re_midline();
                                    //��������ˣ���ȡ��Ч��
                                    left_roundabout_useful_line = finalloseline_left + 1;

                                    left_roundabout_in_flag = false;        //ʹ���ڻ����ڲ���־��0���������ڲ����ߴ���ʧЧ��
                                    left_roundabout_to_out_flag = true;     //������־λ��Ч��������Ľ׶γ�������
                                    Left_Roundabout_State = State5_Roundabout_To_Out_Repairline; //�ڴ˴��������ĸ�״̬������ת������״̬������
                                    state_continue_frame_count = 0;         //״̬����֡�����������㣬Ϊ��һ�׶���׼��
                                }
                            }
                            else if (firstloseline_right == IMG_H - 1 && finalloseline_right < /*30*/IMG_H - 15 && left_roundabout_in_to_out_count > ROUNDABOUT_IN_TO_OUT_COUNTS + 3) //û���ҵ��յ㣬�ұߴ�ͼ������п�ʼ���ֽϳ��Ķ��ߣ����󻷵�����֡������������(Ĭ��>5)�����ж�Ϊ����·��ͼ�񣬿�ʼ������>5�����복���йأ�������Ҫ������
                            {
                                //��ת����һ��״̬ǰ���߹���
                                repair_line(IMG_H - 1, boundary_right[IMG_H - 1], finalloseline_left + 1, boundary_right[finalloseline_left + 1], RIGHT_DIR); //��ͼ����߽����ն����ж�Ӧ���ұ߽�ĵ���������ұ߽�ĵ����ӣ��������ұ߽�
                                re_midline();
                                //��������ˣ���ȡ��Ч��
                                left_roundabout_useful_line = finalloseline_left + 1;

                                left_roundabout_in_flag = false;                                     //ʹ���ڻ����ڲ���־��0���������ڲ����ߴ���ʧЧ��
                                left_roundabout_to_out_flag = true;                                  //������־λ��Ч��������Ľ׶γ�������
                                Left_Roundabout_State = State5_Roundabout_To_Out_Repairline;         //�ڴ˴��������ĸ�״̬������ת������״̬������
                                state_continue_frame_count = 0;  //״̬����֡�����������㣬Ϊ��һ�׶���׼��
                            }
//

                        }
                    }
                }
                break;
            //---------------����׶Σ�ʶ���˳���ͼ�񣬳�������----------------//
            case State5_Roundabout_To_Out_Repairline:
                {   LEFT_Roundabout_State_step=5;
                    if (left_roundabout_flag == 1 && left_roundabout_to_out_flag)
                    {
                        left_roundabout_out_left_repair_line = false;//��߽粹�ߣ�ÿ֡��ˢ�£�����һ֡ͼ���н�������߽粹�ߣ�������Ϊtrue

                        //�������ұ߽粹�߱�־��ֻ�����ұ߽��Ҳ����յ㣨���ٶ��ߣ�������߽翪ʼ���ߺ�Ž�����Ϊfalse

                        //����׶ε�һ�����ұ߽�����������ǰ�ڲ��֣����� �����ҹյ�����ұ߽��ζ��߶��ұ߽��������
                        if (left_roundabout_out_right_repair_line)
                        {
                            //�Դ������ζ��ߵ�����Ĵ���ȡ�ϳ����ߣ�
                            if (firstloseline_left == IMG_H - 1)              //�����ױ߶���
                                loseline_adjust(LEFT_DIR, 10);
                            if (firstloseline_right == IMG_H - 1)             //�ұ���ױ߶���
                                loseline_adjust(RIGHT_DIR, 10);

                            //���ұ߽粻�ٶ��ߣ����߼��̣����ٲ��ұ��ߣ�          ������һ�׶ε�����������������������������
                            if (
                            (((((firstloseline_right != IMG_H - 1 && firstloseline_right - finalloseline_right <= 5) || (firstloseline_right == IMG_H - 1 && finalloseline_right >= IMG_H - 5)) && firstloseline_right - finalloseline_right <= 5)
                                    ||(firstloseline_right==IMG_H - 1&&firstloseline_left<IMG_H-10))&&state_continue_frame_count>10)
                                  ||state_continue_frame_count>30
                            )
                            {
                                left_roundabout_out_right_repair_line = false;
                                state_continue_frame_count=0;
                            }

                            //������Ҫ���ұ��ߣ����������޹յ㣨��ʱ�������״̬4�ˣ��ʹյ㲻����£�
                            if (left_roundabout_out_right_repair_line)//����
                            {   state_continue_frame_count++;

                                //���ұ߽��Ƿ���ڹյ�
                                bool find_right_break_point = false;
                                right_break_point_y_to_out = 0; //��¼�ұ߽�յ�������

                                for (int i = (IMG_H - 5); i > useful_line_further/*����Ϊ>=��������Խ��*/; i--)//���ҹյ㲢����־λ
                                {
                                    //�ȵ�4�׶ε���΢����һ��
                                    if (boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i + 1] - boundary_right[i] <= 5 /*�յ��·���������������*/
                                        && boundary_right[i - 1] > boundary_right[i] /*�յ��Ϸ�*/
                                        && (boundary_right[i - 1] - boundary_right[i] >= 15 || boundary_right[i - 2] - boundary_right[i] >= 15 || boundary_right[i - 3] - boundary_right[i] >= 15)/*�յ��Ϸ����ٴ���һ��������ͻ�䣬ע��·���Ӱ�죡��*/
                                        && ((boundary_right[i - 1] == IMG_W - 1 && boundary_right[i - 2] == IMG_W - 1)
                                        || (boundary_right[i - 2] == IMG_W - 1 && boundary_right[i - 3] == IMG_W - 1)
                                        || (boundary_right[i - 3] == IMG_W - 1 && boundary_right[i - 4] == IMG_W - 1)
                                        ||(boundary_right[i - 4] == IMG_W - 1 && boundary_right[i - 5] == IMG_W - 1)
                                        ||(boundary_right[i - 6] == IMG_W - 1 && boundary_right[i - 7] == IMG_W - 1))/*�յ��Ϸ����ٴ����������ж���*/
                                        && Binary_Image[i][boundary_right[i]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ㴦Ϊ����*/)
                                    {
                                        find_right_break_point = true;
                                        right_break_point_y_to_out = i;
                                        break;
                                    }
                                }
                                if (find_right_break_point && (firstloseline_right != IMG_H - 1 && finalloseline_right != -1 && firstloseline_right - finalloseline_right >= 5))//�ҵ��ҹյ㣬�������г���
                                {
                                    repair_line(right_break_point_y_to_out, boundary_right[right_break_point_y_to_out], finalloseline_left + 1, boundary_left[finalloseline_left + 1]+1, RIGHT_DIR);
                                    re_midline();
                                    //��������ˣ���ȡ��Ч��
                                    left_roundabout_useful_line = finalloseline_left + 1;

                                    break;//������
                                }
                                else if ((firstloseline_right == IMG_H - 1 && finalloseline_right < IMG_H - 5) || (firstloseline_right >= IMG_H - 10 && finalloseline_right < IMG_H - 5) || (firstloseline_right - finalloseline_right >= 8))//���ұ߽���ڴ�ζ��ߣ�Ҳ����
                                {
                                    repair_line(IMG_H - 1, boundary_right[IMG_H - 1], finalloseline_left + 1, /*boundary_right[finalloseline_left + 1]*/10, RIGHT_DIR); //��ͼ����߽����ն����ж�Ӧ���ұ߽�ĵ���������ұ߽�ĵ����ӣ��������ұ߽�
                                    re_midline();

                                    //��������ˣ���ȡ��Ч��
                                    left_roundabout_useful_line = finalloseline_left + 1;
                                    break;//������
                                }
                            }
                        }
                        if (!left_roundabout_out_left_repair_line){  left_roundabout_to_out_flag_count++; }
                        //����׶� �ڶ�����ת����������뿪�󻷵����򣬽�����߽��������������ڲ��֣�
                        if (!left_roundabout_out_left_repair_line /*δ������߽�����*/
                            && ((firstloseline_right != IMG_H - 1 && firstloseline_right - finalloseline_right<10)|| (firstloseline_right == IMG_H - 1 && finalloseline_right >= IMG_H - 5))/*�ұ߶��ߺܶ�*/)
                        {

                            /*�ж��Ƿ����*/

                            //ͳ�Ƶײ���߽���������������ƣ�������߽�б�ʣ�
                            int boundary_left_count = 0;
                            int count_total = 0;

                            for (int i = IMG_H - 20; i <= IMG_H - 2; i++)
                            {
                                if (boundary_left[i] < boundary_left[i - 1]) //��һ�еĺ��������һ�е�С
                                {
                                    boundary_left_count++;
                                }
                                count_total++;
                            }
                            if (((boundary_left_count >= 0.7 * count_total) /*�����㹻*/
                                && firstloseline_left != IMG_H - 1 && firstloseline_left <= IMG_H - 15 /*��߽�ײ���β�����*/
                                && left_roundabout_to_out_flag_count >= 40/*����֡����������Ҫ����һ��ֵ*/)
                                || left_roundabout_to_out_flag_count >= 50/*ͨ��֡������֡������ĳһ���ϴ��ֵʱ���ж�Ϊ����*/)//�ж�Ϊ����
                            {
                                left_roundabout_out_flag = true; //������־��1
                                left_roundabout_to_out_flag = false;
                                Left_Roundabout_State = State6_Roundabout_Reset; //��ת����һ�׶ν��б�������
                                break;
                            }
                            else //��δ�������������߽粹�ߴ���
                            {
                                left_roundabout_useful_line = useful_line_further;//ȡ���������Ч��
                                for (int i = 1; i <= IMG_H - 1; i++)
                                {
                                    if (Road_Width[i] > 0) //·�����0��������
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



            //---------------�����׶Σ�������ر������־λ----------------//
            case State6_Roundabout_Reset:
                {
                    //���ñ�־λ������
                    //if (left_roundabout_out_flag)//�������ò�һ�����ɳ������µģ�Ҳ���������ڳ���֡������һ��ֵ����ע�ʹ�����
                    {
                        Left_Roundabout_State = State1_Roundabout_Distern_1st_Repariline;//�ڴ˴�����������״̬������ת���һ��״̬������
                        LEFT_Roundabout_State_step=0;
                        left_roundabout_flag = 0; //�󻷵��ܱ�־λ

                        //�뻷֮ǰʶ�𻷵�
                        left_roundabout_discerning = true;//�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
                        left_roundabout_discern_flag_count = 0;//�󻷵��뻷֮ǰ����ʶ��֡��������
                        left_roundabout_only_up_point_flag = false; //�󻷵�ֻ���Ϲյ��ж��뻷��־������������
                        left_roundabout_only_up_point_count = 0; //�󻷵�ֻ���Ϲյ��ж��뻷֡��������������������
                        left_roundabout_state1_repairline_count = 0; //�󻷵���һ�׶β���֡���������ڸ����жϵ�һ�׶εĽ���
                        left_roundabout_state1_repairline_to_end = false; //�󻷵���һ�׶β��߼���������־
                        //�뻷����
                        left_roundabout_state2_left_repairline_count = 0; //�󻷵���һ���ڶ����ɽ׶���߽粹��֡����������Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ�������
                        left_roundabout_in_left_repair_line = true;//�󻷵�����ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                        left_roundabout_in_left_repair_line_count = 0; //�󻷵�����ʱ��߽粹�߼���������ÿ��һ֡��߽�ײ�������Ҫ���ߣ���+1��
                        left_roundabout_in_right_repair_line = true;  //�󻷵�����ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                        left_roundabout_in_change_angle = false;   //ǿ��Ǳ�־���뻷���ڣ�
                        left_roundabout_to_in_count = 0;  //�󻷵����������ļ������������ұ߽�ײ����ٶ���ʱ����ϴ�����(>0)���жϳɹ����뻷���ڲ���
                        //���ڴ���
                        left_roundabout_in_flag = false;  //�󻷵��ɹ����뻷���ڲ���־λ
                        left_roundabout_in_to_out_count = 0; //�󻷵��ڲ�ʶ�����֡�����������жϳ���������֮һ��
                        right_break_point_y_to_out = 0;     //����ʱ�ҹյ㣬���ڳ������
                        //��������
                        left_roundabout_to_out_flag = false;  //�󻷵����������ֱ�־λ
                        left_roundabout_to_out_flag_count = 0; //�󻷵����������־λ��������
                        left_roundabout_out_left_repair_line = false; //�󻷵�����ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                        left_roundabout_out_right_repair_line = true; //�󻷵�����ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                        left_roundabout_out_flag = false;   //�󻷵������ɹ���־

                        state_continue_frame_count = 0;  //״̬����֡��������
//#if RIGHT_ROUNDABOUT_ONLY_ONE
//                if_right_roundabout_recog                                 = 0;                 //ֻ��һ�λ���(ע�͵���ֻ��һ�λ�����
//#endif
                    }
                }
                break;

            default:
                Left_Roundabout_State = State1_Roundabout_Distern_1st_Repariline;
                break;
        }
    }
    //-----------------------------------�󻷵�����END-----------------------------------//
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// @brief       �һ���ʶ������(״̬��ģʽ)
// @param       void
// @return  void
// @note        ʶ���һ��������ߣ�����Ӧ��־λ
//                  ע�⣺������ʶ�����������ڷֱ���Ϊ120*50��ͼ�����ֱ��ʸı䣬��ע��Ҫ�������еĲ���������
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
#if USE_ROUNDABOUT_FSM
void right_roundabout_recog_by_FSM()
{
    //-----------------------------------�һ�������START------------------------------------//

    //--------------------��ر������ã�ÿһ֡�������ã�-------------------//
    find_roundabout_right_down = false;                  //�һ����¹յ�ʶ���־
    find_roundabout_right_up = false;                    //�һ����Ϲյ�ʶ���־
    find_roundabout_right_up_only = false;               //�һ���ֻ�ҵ��Ϲյ��־
    roundabout_right_down_y = 0;                         //�һ������¹յ�������
    roundabout_right_down_x = 0;                         //�һ������¹յ������
    roundabout_right_up_y = 0;                           //�һ������Ϲյ�������
    roundabout_right_up_x = 0;                           //�һ������Ϲյ������
    left_boundary_slope = 0;                             //��߽�б��

    right_roundabout_useful_line = 0;                    //�һ�����Ч��

    if (cross_full_flag == 0 && cross_half_flag == 0 && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && cross_after_turn_flag == 0 && left_roundabout_flag == 0  ) //������������û��ʮ�֡��󻷵��������ʱ������һ����ж�
    {
        switch (Right_Roundabout_State)
        {
            //------------------��һ�׶Σ���ʶ�𻷵����뻷ǰ�ڲ��֣�ͨ��˫�յ�򵥹յ����ʶ�𲢲��ߣ�---------------//
            /****�˽׶�Ӧ�ð������л�������������ûȷ��Ϊ������ʱ�Ĳ��ߡ�ȷ��Ϊ������Ĳ��ߣ�ֱ����ת����һ���׶Σ�****/
            case 0 /*State1_Roundabout_Distern_1st_Repariline*/:
            {
           //     if (right_roundabout_discerning&&if_right_roundabout_recog)
                if (right_roundabout_discerning)
                { //right_roundabout_discerning�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
                    //Ĭ��Ϊ1���������ˡ�ֻ��һ�λ�����ʱ�����ڻ���ʶ�𲢴��������0�����Ҫ���������轫�����������û��ڴ������ע��ȥ��

                    //����������־��
                    if (firstloseline_right != IMG_H - 1)     //ͼ���ұ�����в�����
                    {
                        for (int i = IMG_H - 3; i > useful_line_further /*��ֵ>=3*/; i--)                                                //�ұ߽߱�������ʶ��Ѱ�����¹յ㣩
                        {
                            if (boundary_right[i] < /*114*/IMG_W - 5/*���л������ϸ�����*/
                                && boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] /*�¹յ��·�����Ϊ����������*/
                                && boundary_right[i + 1] - boundary_right[i] < 3 && boundary_right[i] - boundary_right[i + 1] < 3 /*����һ�б߽�Ĳ����3����*/
                                && ((lost_right_flag[i - 1] == 1 && lost_right_flag[i - 2] == 1) || (lost_right_flag[i - 2] == 1 && lost_right_flag[i - 3] == 1) || (lost_right_flag[i - 3] == 1 && lost_right_flag[i - 1] == 1))/*�¹յ��Ϸ���������һ�ж���*/
                                && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ�������Ϊ����*/)   //Ѱ���¹յ�
                            {
                                find_roundabout_right_down = true;              //�ұ߽��¹յ�ʶ����
                                roundabout_right_down_y = i;                    //��¼�¹յ��Ӧ������
                                roundabout_right_down_x = boundary_right[i];    //��¼�¹յ��Ӧ������
                            }
                            if (find_roundabout_right_down)                     //���ҵ����¹յ㣨ǰ�ᣩ�����ϲ����Ϲյ㣨�Ϲյ�ĺ�����������µĶ�С��
                            {
                                for (int j = roundabout_right_down_y - 1; j >= useful_line_further; j--)
                                {
                                    /*���л������ϸ�����*/
                                    if (boundary_right[j] <= boundary_right[j - 1] && boundary_right[j] <= boundary_right[j - 2] /*�Ϲյ���ϲ���*/
                                        && boundary_right[j] <= boundary_right[j + 1] && boundary_right[j] <=boundary_right[j + 2] && boundary_right[j] <= boundary_right[j + 3]  /*�Ϲյ���²���*/
                                        && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j - 2] <= IMG_W - 5 /*��ֹΪ�߽�*/
                                        && (Binary_Image[j][boundary_right[j] - 2] == IMG_WHITE && Binary_Image[j - 1][boundary_right[j - 1] - 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*�յ����ڴ�Ϊ����*/)
                                    {
                                        find_roundabout_right_up = true;                //�ұ߽��Ϲյ�ʶ����
                                        roundabout_right_up_y = j;                   //��¼�Ϲյ��Ӧ������
                                        roundabout_right_up_x = boundary_right[j];   //��¼�Ϲյ��Ӧ������
                                        break;
                                    }
                                }
                            }

                        }
                    }
                    else if (firstloseline_right == IMG_H - 1 && finalloseline_right > IMG_H - 15)     //��ͼ�����½���һС�ζ���Ӱ��ʶ��Ҫ�ֶ����ԣ������ն���������Ѱ�ҹյ㣩
                    {
                        for (int i = finalloseline_right - 1; i > useful_line_further; i--)             //�ұ߽��ϡ��¹յ�ʶ�𣨴Ӷ��߽�������ʼʶ��
                        {
                            if (boundary_right[i] < /*114*/IMG_W - 5/*���л������ϸ�����*/
                            && boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] /*�¹յ��·�����Ϊ����������*/
                            && boundary_right[i + 1] - boundary_right[i] < 3 && boundary_right[i] - boundary_right[i + 1] < 3 /*����һ�б߽�Ĳ����3����*/
                            && ((lost_right_flag[i - 1] == 1 && lost_right_flag[i - 2] == 1) || (lost_right_flag[i - 2] == 1 && lost_right_flag[i - 3] == 1) || (lost_right_flag[i - 3] == 1 && lost_right_flag[i - 1] == 1)) /*�¹յ��Ϸ���������һ�ж���*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ�������Ϊ����*/)   //Ѱ���¹յ�
                            {
                                find_roundabout_right_down = true;              //�ұ߽��¹յ�ʶ����
                                roundabout_right_down_y = i;                    //��¼�¹յ��Ӧ������
                                roundabout_right_down_x = boundary_right[i];    //��¼�¹յ��Ӧ������
                            }
                            if (find_roundabout_right_down)                     //���ҵ����¹յ㣨ǰ�ᣩ�����ϲ����Ϲյ㣨�Ϲյ�ĺ�����������µĶ�С��
                            {
                                for (int j = roundabout_right_down_y - 1; j > useful_line_further; j--)
                                {
                                    /*���л������ϸ�����*/
                                    if (boundary_right[j] <= boundary_right[j - 1] && boundary_right[j] <= boundary_right[j - 2] /*�Ϲյ���ϲ���*/
                                        && boundary_right[j] <= boundary_right[j + 1] && boundary_right[j] <= boundary_right[j + 2] && boundary_right[j] <= boundary_right[j + 3]  /*�Ϲյ���²���*/
                                        && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j - 2] <= IMG_W - 5 /*��ֹΪ�߽�*/
                                        && (Binary_Image[j][boundary_right[j] - 2] == IMG_WHITE && Binary_Image[j - 1][boundary_right[j - 1] - 2] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*�յ����ڴ�Ϊ����*/)
                                    {
                                        find_roundabout_right_up = true;                //�ұ߽��Ϲյ�ʶ����
                                        roundabout_right_up_y = j;                   //��¼�Ϲյ��Ӧ������
                                        roundabout_right_up_x = boundary_right[j];   //��¼�Ϲյ��Ӧ������
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    //���ݹյ���Ƿ��ǻ��������ж�
                    if (right_roundabout_flag == 0) //δʶ�𵽻����Ž����ж�
                    {
                        /*������һ֡ͼ����ͬʱ�ҵ������յ㣨������������*/
                        if (find_roundabout_right_down && find_roundabout_right_up)
                        {
                            //û�����������������ʶ��֡����������1
                            right_roundabout_discern_flag_count++;
                            for (int i = roundabout_right_up_y; i < roundabout_right_down_y; i++) {

                          if(lost_left_flag[i]==1){right_roundabout_discern_flag_count = 0;  break;}

                        }
                  if (right_roundabout_discern_flag_count==0)
                    break;  //�˳�switch��������֡����ʶ��

//
////                            //����һЩ����������������У���ʶ��֡����������0���������пɿ���һ������
////                            //1��
//                            for (int counti = roundabout_right_down_y; counti >= roundabout_right_up_y; counti--)
//                            {
//                                //�Դ��¹յ㵽�Ϲյ��ÿһ�У�������߽絽�ұ߽��Ƿ���ںڵ㣬�����ڣ���ʶ��֡����������0�����˳���֡�Ļ���ʶ��
//                                for (int countj = boundary_left[roundabout_right_up_y]; countj < boundary_right[roundabout_right_up_y]; countj++)
//                                {
//                                    if (Binary_Image[counti][countj] == IMG_BLACK)
//                                    {
//                                        right_roundabout_discern_flag_count = 0;
//                                        break;
//                                    }
//                                }
//                                if (right_roundabout_discern_flag_count == 0)
//                                    break;  //�˳����ѭ��
//                            }
//                            if (right_roundabout_discern_flag_count == 0)
//                                break;  //�˳�switch��������֡����ʶ��
//                            //2��
//                            if (!(boundary_right[roundabout_right_up_y] - boundary_left[roundabout_right_up_y] >= 5 && roundabout_right_down_y - roundabout_right_up_y >= 8 && loseleftflag == 0))
//                            // !() ���������������е��������������㣨�Ϲյ㴦�ұ߽������߽�һ��ֵ�������¹յ����������һ������/*����һ�߶��ߣ�һ��û�ж���*/������������֡����������0
//                            {
//                                right_roundabout_discern_flag_count = 0;
//                                break;  //�˳�switch��������֡����ʶ��
//                            }
//                            //3����߽�б��
//                            int boundary_Ldown_to_Rup_count = 0;     //��߽����������������������ۼƼ�������
//                            for (int i = roundabout_right_down_y; i >= roundabout_right_up_y; i--)                                                    //��߽߱�������ʶ�𣬼���߽��д��������������������
//                            {
//                                if (boundary_left[i] < boundary_left[i - 1])                 //��һ�еĺ��������һ�е�С
//                                {
//                                    boundary_Ldown_to_Rup_count++;                           //��¼��߽���������������Ƶ��ۼƼ���
//                                }
//                            }
//                            //��������߹յ㴦�������ڵ�ֱ��б�ʣ���Ϊ�һ���������һ������б�ʣ���ͼ���������죩
//                            left_boundary_slope = (float)(roundabout_right_down_y - roundabout_right_up_y) / (boundary_left[roundabout_right_up_y] - boundary_left[roundabout_right_down_y]);
//
//                            if (boundary_Ldown_to_Rup_count < 0.7 * (roundabout_right_down_y - roundabout_right_up_y) || left_boundary_slope <= 0 /*|| boundary_left[roundabout_right_up_y] >= IMG_MIDDLE + 20*/)
//                            { //�����߽������������������Ʋ�����������߽�б��Ϊ����ֵ�������Ϲյ㴦����߽����ƫ��
//                                right_roundabout_discern_flag_count = 0; //��֡����������0
//                                break;  //�˳�switch��������֡����ʶ��
//                            }

                        }
                        /*���޷���һ֡ͼ����ͬʱ�ҵ������յ㣬����ݡ�ֻ���Ϲյ㡱�ж��뻷*/
                        //��Ϊ�����׼ȷ�ʣ�������Ҫ��������ĳһ֡ʶ��һ���¹յ㣬�Խ� �Ϲյ�֡������־ ��
                        else if (find_roundabout_right_down && !find_roundabout_right_up)//�ҵ��¹յ��û���Ϲյ�
                        {
                            //Ѱ���Ƿ���һ���� �����ҵ��Ϲյ� �����ƣ���ʱ�Ϲյ���������ɣ�����ֻ�����Ϲյ���°벿�֣�����bug�����¶����ǡ�
                            for (int i = (roundabout_right_down_y < IMG_H - 4 ? roundabout_right_down_y : IMG_H - 4)/*��ֹ����Խ��*/; i >= useful_line_further; i--)//���¹յ�������
                            {
                                //Ѱ���±�ʶ�㣬�ҵ��Ϳ�ʼ��¼�ҵ�����Ѿ����˼�֡
                                if (boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i + 1] < boundary_right[i + 3] /*�¹յ��·����������������*/
                                        && boundary_right[i] <= IMG_W - 5 && boundary_right[i - 1] <= IMG_W - 5 && boundary_right[i + 1] <= IMG_W - 5 /*��ֹΪ�߽�*/
                                        && (boundary_right[i + 3] - boundary_right[i] >= 5
                                         && (Binary_Image[i][boundary_right[i] - 2] == IMG_WHITE && Binary_Image[i - 1][boundary_right[i - 1] - 2] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE) /*�յ����ڴ�Ϊ����*/

                                        ) /*�Ϲյ���·������㹻*/
                                        )
                                {
                                    right_roundabout_only_up_point_flag = true; //�Ϲյ�֡������־��
                                    right_roundabout_only_up_point_count = 0;   //׼������
                                    break;
                                }
                            }
                        }


                        /*ֻ���Ϲյ��ж��뻷���н��Ϸ�else if*/
                        if (right_roundabout_only_up_point_flag)//����ҵ��±�ʶ�������8֡��û���ҵ��ϱ�ʶ�㣬������
                        {
                            right_roundabout_only_up_point_count++;

                            if (right_roundabout_only_up_point_count >= 8)//8֡���ݾ�������ı�
                            {
                                right_roundabout_only_up_point_flag = false;
                                right_roundabout_only_up_point_count = 0;
                            }
                        }

                        if (!find_roundabout_right_up && right_roundabout_only_up_point_flag)//���û���ҵ��Ϲյ㣬���Ϲյ�֡������־Ϊtrue����ֹ����һ֡����ͬʱ�ҵ����¹յ㣬��ִ���·���䣩
                        {
                            //����һ��������ʼ���Ϲյ�
                            if (finalloseline_right <= IMG_H - 5)//���ն�����
                            {
                                for (int i = finalloseline_right; i >= useful_line_further; i--)
                                {
                                    if (boundary_right[i] <= boundary_right[i - 1] && boundary_right[i] < boundary_right[i - 2]/*�Ϲյ���ϰ벿��������ȷ*/
                                        && boundary_right[i] - boundary_right[i - 1] <= 5 && boundary_right[i - 1] - boundary_right[i] <= 5  && boundary_right[i] -  boundary_right[i - 2] <= 5 && boundary_right[i - 2] - boundary_right[i] <= 5 /*���ƹյ��Ϸ���ĺ������� */
                                        && boundary_right[i] <= boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2] && boundary_right[i] < boundary_right[i + 3] /*�Ϲյ���°벿��������ȷ*/
                                        && boundary_right[i + 4] - boundary_right[i] >= 4 /*�¹յ��°벿�������㹻*/
                                        && boundary_right[i] <= IMG_W - 2 && boundary_right[i + 1] <= IMG_W - 2 && boundary_right[i - 1] <= IMG_W - 2 && Binary_Image[i][boundary_right[i]] == IMG_WHITE /*��ֹΪ�߽�*/
                                        && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i]] == IMG_WHITE && Binary_Image[i - 2][middle_line[i]] == IMG_WHITE && Binary_Image[i - 3][middle_line[i]] == IMG_WHITE /*ȷ��Ϊ����*/)
                                    {
                                        roundabout_right_up_y = i;
                                        roundabout_right_up_x = boundary_right[i];

                                        //û�����������������ʶ��֡����������1
                                        right_roundabout_discern_flag_count++;
                                        for (int i = roundabout_right_up_y-5; i < roundabout_right_up_y+5; i++) {
                                          if(lost_left_flag[i]==1){right_roundabout_discern_flag_count = 0; break;}//�ж�������Ƿ���
                                                                                                              }
                                        if (right_roundabout_discern_flag_count == 0)
                                                    break;
                                        //����һЩ����������ϸ��������������У���֡����������0��
//                                        //1��
//                                        if (!(roundabout_right_up_x - boundary_left[roundabout_right_up_y] >= 5  /*&& loseleftflag == 0 */))
//                                        { //�����㣨�Ϲյ㴦�ұ߽������߽�һ��ֵ /*����һ�߶��ߣ�һ��û�ж���*/�����������򽫻���ʶ��֡����������0
//                                            right_roundabout_discern_flag_count = 0;
//                                            continue; //����Ѱ���Ϲյ�
//                                        }
//                                        //2��
//                                        for (int counti = finalloseline_right; counti >= roundabout_right_up_y; counti--)
//                                        {
//                                            //�Դ����ն����е��Ϲյ��ÿһ�У�������߽絽�ұ߽��Ƿ���ںڵ㣬�����ڣ���ʶ��֡����������0
//                                            for (int countj = boundary_left[roundabout_right_up_y]; countj < roundabout_right_up_x; countj++)
//                                            {
//                                                if (Binary_Image[counti][countj] == IMG_BLACK)
//                                                {
//                                                    right_roundabout_discern_flag_count = 0;
//                                                    break;
//                                                }
//                                            }
//                                            if (right_roundabout_discern_flag_count == 0)
//                                                break;  //�˳����ѭ��
//                                        }
//                                        if (right_roundabout_discern_flag_count == 0)
//                                            continue;  //����Ѱ���Ϲյ�
//
//                                        //3����߽�б��
//                                        int boundary_Ldown_to_Rup_count = 0;     //��߽����������������������ۼƼ�������
//                                        for (int m = finalloseline_right; m >= roundabout_right_up_y; m--)  //��߽߱�������ʶ�𣬼���߽��д��������������������
//                                        {
//                                            if (boundary_left[m] < boundary_left[m - 1])                    //��һ�еĺ��������һ�е�С
//                                            {
//                                                boundary_Ldown_to_Rup_count++;                              //��¼��߽���������������Ƶ��ۼƼ���
//                                            }
//                                        }
//                                        if (boundary_Ldown_to_Rup_count < 0.85 * (finalloseline_right - roundabout_right_up_y) /*|| boundary_left[roundabout_right_up_y] >= IMG_MIDDLE + 20*/)
//                                        { //�����߽������������������Ʋ����������Ϲյ㴦����߽����ƫ��
//                                            right_roundabout_discern_flag_count = 0; //��֡����������0
//                                            continue;  //����Ѱ���Ϲյ�
//                                        }

                                        //�������н���������ִ�е��ˣ���֡��������>=1
                                        if (right_roundabout_discern_flag_count >= 1)
                                        {
                                            find_roundabout_right_up_only = true;//ֻ�ҵ��Ϲյ��־λ��1
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        /*��Ҫ�Ļ��ٲ��䡰б�뻷��������*/

                        //����֡������������һ��ֵ�󣬳ɹ�ʶ�𻷵�
                        if(right_roundabout_discern_flag_count >= ROUNDABOUT_DISCERN_COUNTS)
                        {
                            right_roundabout_flag = 1;
                        }

                    }

                    //���ݲ�ͬ�Ĺյ�������в���
                    if (right_roundabout_flag == 1)//�һ�����־Ϊ1������ʱ�뻷ǰ����ʶ���־��Ϊ1�����Ի�������¹յ�����������
                    {
                        right_roundabout_state1_repairline_count++; //��һ�׶β���֡��������+1
                        //1:ʶ�𵽻��������ҵ������յ㣬����
                        if (find_roundabout_right_down && find_roundabout_right_up)
                        {
                            repair_line(roundabout_right_down_y, roundabout_right_down_x, roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR);//���������¹յ���ұ��߽������������ߣ�
                            RIGHT_Roundabout_State_step=1;
                            re_midline(); //����������������д����
                            //��������ˣ���ȡ��Ч��
                            right_roundabout_useful_line = roundabout_right_up_y;
                        }
                        //2:ʶ�𵽻�������ֻ���Ϲյ㣬����
                        else if (find_roundabout_right_up_only)
                        {
                            repair_line(IMG_H - 1, boundary_right[IMG_H - 1], roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR); //�����ұ߽�ױ����Ϲյ㲹��

                            re_midline(); //����������������д����
                            RIGHT_Roundabout_State_step=1;
                            //��������ˣ���ȡ��Ч��
                            right_roundabout_useful_line = roundabout_right_up_y;
                        }
                        //3:ʶ�𵽻�����ֻ���±�־��ʱ����
                        else if (find_roundabout_right_down && !find_roundabout_right_up)
                        {
                            //�Խ��ɵ��������Ϲյ�
                            for (int j = roundabout_right_down_y - 5; j >= useful_line_further; j--)
                            {
                                if (boundary_right[j] <= boundary_right[j - 1]  /*�Ϲյ���ϲ���*/
                                    && boundary_right[j] <= boundary_right[j + 1] /*�Ϲյ���²���*/
                                    && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j + 2] <= IMG_W - 5 /*��ֹΪ�߽�*/
                                    && (Binary_Image[j][boundary_right[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*�յ����ڴ�Ϊ����*/)
                                {
                                    roundabout_right_up_y = j;                   //��¼�Ϲյ��Ӧ������
                                    roundabout_right_up_x = boundary_right[j];   //��¼�Ϲյ��Ӧ������

                                    repair_line(roundabout_right_down_y, roundabout_right_down_x, roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR);//���������¹յ���ұ��߽������������ߣ�

                                    re_midline(); //����������������д����
                                    RIGHT_Roundabout_State_step=1;
                                    //��������ˣ���ȡ��Ч��
                                    right_roundabout_useful_line = roundabout_right_up_y;
                                    break;
                                }

                            }
                        }
                        //4:ʶ�𵽻������Ҳ����·��㣬Ҳ����ֻ�ҵ��Ϸ���Ĳ���
                        else if (!find_roundabout_right_down && !find_roundabout_right_up_only)
                        {
                            for (int j = (finalloseline_right <= IMG_H - 4 ? finalloseline_right : IMG_H - 4 /*��ֹ����Խ��*/); j > useful_line_further; j--)//�����ն���������Ѱ�ҹյ�
                            {
                                if (boundary_right[j] <= boundary_right[j - 1]  /*�Ϲյ���ϲ���*/
                                    && boundary_right[j] <= boundary_right[j + 1] /*�Ϲյ���²���*/
                                    && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j + 2] <= IMG_W - 5 /*��ֹΪ�߽�*/
                                    && (Binary_Image[j][boundary_right[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*�յ����ڴ�Ϊ����*/)
                                {
                                    roundabout_right_up_y = j;                   //��¼�Ϲյ��Ӧ������
                                    roundabout_right_up_x = boundary_right[j];   //��¼�Ϲյ��Ӧ������

                                    repair_line(IMG_H - 1, boundary_right[IMG_H - 1], roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR); //�����ұ߽�ױ����Ϲյ㲹��

                                    re_midline(); //����������������д����
                                    RIGHT_Roundabout_State_step=1;
                                    //��������ˣ���ȡ��Ч��
                                    right_roundabout_useful_line = roundabout_right_up_y;

                                    right_roundabout_state1_repairline_to_end = true;   //������ˣ����ʾ��һ�׶εĲ��߼�������
                                    break;
                                }
                            }
                        }
                    }
                    //������һ�׶ε��ڶ��׶ε��ж�
                    if (right_roundabout_state1_repairline_count >= ROUNDABOUT_STATE1_TO_IN_COUNTS && right_roundabout_state1_repairline_to_end)
                    {
                        for (int i = IMG_H - 1; i >= /*IMG_H - 25*/10; i--)
                        {
                            if (boundary_right[i] <= boundary_right[i - 1] && boundary_right[i - 1] <= boundary_right[i - 2] && boundary_right[i - 2] <= boundary_right[i - 3] && boundary_right[i - 3] <= boundary_right[i - 4] && boundary_right[i] < boundary_right[i - 4] /*�������ڽ�ǿ�������������ƣ�˵�����뻷����Ͻ�*/
                                && boundary_right[i] <= IMG_W - 2 && boundary_right[i - 1] <= IMG_W - 2 && boundary_right[i - 2] <= IMG_W - 2 /*��ֹΪ�߽�*/
                                && ((firstloseline_right != IMG_H - 1 && firstloseline_right - finalloseline_right <= 5 ) || (firstloseline_right == IMG_H - 1 && finalloseline_right > /*45*/IMG_H - 10)) /*�ұ߽�ײ������ߣ����߽϶�*/)
                            {
                                right_roundabout_discerning = false;    //�뻷ǰ����ʶ��ʧЧ��֮���ٽ��е�һ�׶Σ����뻷ǰ����ʶ��׶Σ���
                                Right_Roundabout_State = 2 /*State3_Roundabout_To_In_3th_Repairline*/;            //�ڴ˴�������һ��״̬������ת��ڶ���״̬������
                                right_roundabout_state2_right_repairline_count = 0; //Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ���ұ���
                                break;
                            }
                        }
                    }

                }
            }
            break;
            //-----�ڶ��׶Σ�ʶ�𻷵��ɹ���Ҫ���뻷�����뻷���ڣ���Ӧ���յ����߽粹�ߣ�(�����Ѿ������˽׶���)------//
            case 1 /*State2_Roundabout_To_In_2nd_Repairline*/:
            {RIGHT_Roundabout_State_step=2;

                if (right_roundabout_flag == 1 && !right_roundabout_discerning && !right_roundabout_in_flag && !right_roundabout_to_out_flag && right_roundabout_in_right_repair_line) //�뻷�����֣�����ʶ��̣����뻷���ڲ�������������
                {
                    //�ұߴ�����п�ʼ���ڶ��ߣ���Ҫ�����ұ߽磨right_roundabout_in_right_repair_line = 1��ʾ�ұ߽��Դ��ڶ��ߣ���Ҫ���ߣ����뻷���ڲ��֣�
                    if (firstloseline_right == 49 /*&& right_roundabout_in_right_repair_line*/)
                    {
                        int upy = 0;                                                                                    //��ȡ�ұ߽�յ�������
                        for (int i = finalloseline_right; i > 2; i--)
                        {
                            //��������if�������Ѱ���ұ߽�յ㣨��ʱû���¹յ�ֻ���Ϲյ��ˣ�
                            if (boundary_right[i] <= boundary_right[i - 1])                     //Ѱ�ҹյ㣨���ϲ��֣�--�յ�ĺ�����������µĶ�С
                            {
                                if (boundary_right[i] < boundary_right[i + 1] && boundary_right[i] < boundary_right[i + 2]) //ȷ�Ϲյ㣨���²��֣�
                                {
                                    upy = i;                                                                                            //��¼�յ�������
                                    break;
                                }
                            }
                        }
                        right_roundabout_in_right_repair_line_count++;                      //�ұ߽粹�ߣ���������+1�����ұ߽綪���ڼ��ÿһ֡����һ���ߣ����������ɴ�ֱ���ұ߲������ˣ�
                        repair_line(49, boundary_right[49], upy, boundary_right[upy], RIGHT_DIR); //�����ұ߽�
                        re_midline(); //�������������д����

                        //��������ˣ���ȡ��Ч��
                        right_roundabout_useful_line = upy;
                    }

                    //���ұ߽粻������ж����ˣ�ͬʱ�ұ߽粹�߼�������>0�������ұ߽粹��ʧЧ-֮���ٲ��ߣ���ʱ�ѵ��뻷���ڲ��֣�
                    if ((firstloseline_right != 49 || (firstloseline_right == 49 && finalloseline_right > /*45*/40/*����һ��3���ұ߽絽������ȡ�����ߣ���*/)) && right_roundabout_in_right_repair_line_count > 0)
                    {
                        right_roundabout_in_right_repair_line = false;                                  //�ұ߽粹��ʧЧ��������Ҫ����
                        Right_Roundabout_State = 2;//�ڴ˴������ڶ���״̬������ת�������״̬������
                    }
                }
            }
            break;
            //-----�����׶Σ�ʶ�𻷵��ɹ���Ҫ���뻷�����뻷���ڣ���߽粻�ٲ��ߣ������ұ߽粹�ߣ�------//
            case 2 /*State3_Roundabout_To_In_3th_Repairline*/:
            {RIGHT_Roundabout_State_step=3;
                if (right_roundabout_flag == 1 && !right_roundabout_discerning && !right_roundabout_in_flag && !right_roundabout_to_out_flag && right_roundabout_in_left_repair_line)
                {


                    //��ʼǰ��֡���ұ߽粹��
                    if (right_roundabout_state2_right_repairline_count <= 2)
                    {
                        right_roundabout_state2_right_repairline_count++;
                        for (int j =  IMG_H - 4; j >= useful_line_further; j--)//����Ѱ�ҹյ�
                        {
                            if (boundary_right[j] <= boundary_right[j - 1] && boundary_right[j] < boundary_right[j - 2] /*�Ϲյ���ϲ���*/
                                && boundary_right[j] <= boundary_right[j + 1] && boundary_right[j] < boundary_right[j + 2]/*�Ϲյ���²���*/
                                && boundary_right[j] <= IMG_W - 5 && boundary_right[j - 1] <= IMG_W - 5 && boundary_right[j + 1] <= IMG_W - 5 && boundary_right[j + 2] <= IMG_W - 5 /*��ֹΪ�߽�*/
                                && (Binary_Image[j][boundary_right[j]] == IMG_WHITE && Binary_Image[j][middle_line[j]] == IMG_WHITE) /*�յ����ڴ�Ϊ����*/)
                            {
                                roundabout_right_up_y = j;                   //��¼�Ϲյ��Ӧ������
                                roundabout_right_up_x = boundary_right[j];   //��¼�Ϲյ��Ӧ������

                                repair_line(IMG_H - 1, boundary_right[IMG_H - 1], roundabout_right_up_y, roundabout_right_up_x, RIGHT_DIR); //�����ұ߽�ױ����Ϲյ㲹��

                                re_midline(); //����������������д����

                                break;
                            }
                        }
                    }
                    if (firstloseline_left == IMG_H - 1 && finalloseline_left < IMG_H - 10)        //��߽�ײ����ֶ���//����һ��3
                {
                    right_roundabout_to_in_count++;
                }

                    /*
                      ����ǿ���ʱ�ڵ���⣺
                      ���뻷���ڲ��ֽ����������뻷���ڲ��֣����ұ߽�ײ����ٶ��ߣ�ʱ
                                      (1)��߽������һ��ʼ���ܲ����ߣ���ʱִ����ͨ���ߡ�������󷽴��룩
                                      (2)��֮��һ���������߽�����ж��߽׶Ρ�������һ��ʼ���߽϶̣����ն�����>20����Ȼִ����ͨ���ߣ�ֱ�����ִ�ζ��ߣ����ն�����<20��ִ��ǿ��ǣ�֮��һֱǿ���ֱ������ж��߽���
                                      (3)��֮������ж��߽��������׽��뻷���ڣ���ʱ�·����뿪ʼִ�У�����߲��ٲ��ߣ������ڲ���־λ��1��
                    */

                    //ע�⣡�����·���������е���������������Լ��ֻ������߽翪ʼ���ߣ�ֱ����߽綪�߽�����Ż������֮���Խ���ִ�еĴ������ǰ�棬��Ϊ����ǰʶ������в����ߣ��Ӷ�����߲��߱�־��0��
                    if ((((firstloseline_left != IMG_H - 1 && firstloseline_left - finalloseline_left <= 5&&firstloseline_right) || (firstloseline_left == IMG_H - 1 && finalloseline_left >= IMG_H - 5)/*��߳���С�ζ���Ҳ��Ϊ������*/)
                         && right_roundabout_to_in_count > 0)||time_in>30)
                    { //����߽粻�ٶ��߻��߽϶̣����뻷������������Ҫ�������״̬��ת
                        right_roundabout_in_left_repair_line = false;       //��߽粹��ʧЧ
                        right_roundabout_in_flag = true;                    //�����ڲ����ߴ�����Ч�����뻷���ڲ���
                        right_roundabout_in_change_angle = false;           //ǿ�������ȥ��
                        Right_Roundabout_State = 3 /*State4_Roundabout_In*/;                         //�ڴ˴�����������״̬������ת����ĸ�״̬������
                        state_continue_frame_count = 0;//״̬����֡�����������㣬Ϊ��һ�׶���׼��
                        time_in=0;
                        break;                                              //�˳�����case������ִ���·�����
                    }


                    if (firstloseline_left == IMG_H - 1 && finalloseline_left <= IMG_H - 10 /*20*/ /*������Сһ��Ļ�����ǵ�ʱ������һ��*/) //��ߴ�����¿�ʼ��һ��ζ��ߣ���ʼǿ���
                    {
                        right_roundabout_in_change_angle = true;                                    //ǿ��Ǳ�־��1
                    }

                    //��ͨ����
                    /*
                        �ұ߽粻���ߺ�һ��ʼ��߽��ǲ����ߵģ�ִ�е�����ͨ���ߣ��Լ�����߽�����п�ʼ���ߣ������߽϶�ʱҲִ����ͨ����
                    */

//
                    if (!right_roundabout_in_change_angle)
                    {
                        //�����ѱ��ߣ����ڻ����������߽��뻷���Ϸ�ֱ�����ұ߽�ͬʱ���ڣ���ʹ����߽�ʶ���ǰ�ߣ��������Ϸ�ֱ�����ұ߽��޷�ʶ�𣬹������ѱ��ߣ�
                        for (int i = IMG_H - 2; i > useful_line_further; i--)
                        {
                            //����߽�Ϊ��׼�������߽���ƫ�ƣ������¶���������ʼ�㣩
                            if (boundary_left[i + 1] + 7 <= IMG_W - 1)
                            {
                                middle_line[i] = boundary_left[i + 1] + 7;
                            }
                            //��ƫ�ƺ��������������
                            boundary_left[i] = findchange(middle_line[i], LEFT_DIR, i, IMG_BLACK, 0, 2, 1);
                            boundary_right[i] = findchange(middle_line[i], RIGHT_DIR, i, IMG_BLACK, IMG_W - 1, 1, 2);
                        }

                        int righty = 0;                           //��ȡ�ұ߽���ѵ������꣨����ֱ����Բ������ķֲ棬�ұ߽����ն������ж��ѵ㣬������㴦�ұ߽������ͻ�䣩
                        bool find_right_break_point = false;      //�Ƿ��ܻ�ȡָ����ı�־

                        for (int i = IMG_H - 10; i > useful_line_further; i--)
                        {

                                if (boundary_right[i] < IMG_W - 10&& (boundary_right[i + 1] - boundary_right[i] > 15 || boundary_right[i + 2] - boundary_right[i] > 15 )/*���ѵ㴦ͻ�䣨������ͻȻ��С��*/
                              && boundary_right[i] - boundary_right[i - 1] <= 4 /*���ƹյ����Ϸ��������Ĳ��*/
                              && Binary_Image[i][boundary_right[i]] == IMG_WHITE /*�յ㴦Ϊ����*/
                              &&i>15//���ƹյ㵽���ľ���
                                                  )
                            {
                                //�����ɫռ�ȣ���ֹ���У�
                                int count_white = 0, count = 0;
                                for (int j = boundary_right[i]; j <= boundary_right[i + 1]; j++)//���������������Ӧ����ȫ��
                                {
                                    if (Binary_Image[i + 1][j] == IMG_WHITE)//�������ж�
                                    {
                                        count_white++;
                                    }
                                    count++;
                                }
                                if (count_white >= 0.8 * count)
                                {
                                    righty = i;                                   //��ȡָ����������
                                    find_right_break_point = true;
                                   //��ȡ����ָ����
                                    break;
                                }
                            }
                        }
                        if (find_right_break_point)
                        {
                     repair_line(IMG_H - 1, boundary_left[IMG_H - 1], righty, boundary_right[righty], LEFT_DIR); //��ָ���㵽��׶�����������������߽�(����ʵ���޸ĵĲ�����ʱ��������ȫ�ֱ�����

                            right_roundabout_useful_line = righty;//��������ˣ���ȡ��Ч��
                        }
                        //}
                        re_midline();                                                                               //��д����
                    }
                    else    //ǿ���
                    {
                        //���������У����Ե��¶̾��붪��
                        loseline_adjust(RIGHT_DIR, 8);
                        time_in++;
                        //����Сһ��Ļ�������������ǿ���
                        //repair_middline(middle_line[IMG_H - 1], IMG_H - 1, boundary_right_temp[finalloseline_right + 1], (finalloseline_right + 1));//���ұ߽����ն��ߴ�����׶��е�������Ϊ����
                        //ֱ����������ǿ��ǹ�ǿ����Ϊ������߽�
                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], finalloseline_right + 2, /*boundary_left_temp[finalloseline_right + 2]*/IMG_W - 20, LEFT_DIR);

                        re_midline();

                        //��������ˣ���ȡ��Ч��
                        right_roundabout_useful_line = finalloseline_right + 1;

                    }

                }
            }
            break;
            //-------------���Ľ׶Σ����뻷���ڲ��������ڲ������֣�-------------//
            case 3 /*State4_Roundabout_In*/:
            {RIGHT_Roundabout_State_step=4;
                if (right_roundabout_flag == 1 && right_roundabout_in_flag)       //ʶ�𻷵���־λ�ͽ��뻷���ڲ���־λ��Ϊ1����ʼ���´���
                {
                    right_roundabout_in_to_out_count++;                                                           //�һ����ڲ�ʶ�����֡��������+1

                    /*�ڲ�ת�䴦������ת��ͬ��һ������*/

                    if (right_roundabout_in_to_out_count > ROUNDABOUT_IN_TO_OUT_COUNTS)
                    {
                        //����߽��Ƿ���ڹյ�
                        bool find_left_break_point = false;
                        left_break_point_y_to_out = 0; //��¼��߽�յ�������
                        for (int i = IMG_H - 5; i > useful_line_further /*����>=����ֹ����Խ��=*/; i--)//���ҹյ㲢����־λ
                        {
                            if (boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] >= boundary_left[i + 2] && boundary_left[i] >=boundary_left[i + 3] && boundary_left[i] - boundary_left[i + 1] <= 10 /*�յ��·���������������*/
                              &&i>25//���ƹյ���ͼ���е�λ�ã���ʲôʱ��ʼ����
                                    && boundary_left[i - 1]<= boundary_left[i] && boundary_left[i - 2] < boundary_left[i] /*�յ��Ϸ�*/
                                && (boundary_left[i] - boundary_left[i - 1] >= 5|| boundary_left[i] - boundary_left[i - 2] >= 5 || boundary_left[i] - boundary_left[i - 3] >= 5 /*�յ��Ϸ����ٴ���һ��������ͻ��·���Ӱ�죡��*/)
                              //  && ((boundary_left[i - 1] == 0 && boundary_left[i - 2] == 0) || (boundary_left[i - 2] == 0 && boundary_left[i - 3] == 0) || (boundary_left[i - 3] == 0 && boundary_left[i - 4] == 0)|| (boundary_left[i - 4] == 0 && boundary_left[i - 5] == 0)|| (boundary_left[i - 5] == 0 && boundary_left[i - 6] == 0)|| (boundary_left[i - 6] == 0 && boundary_left[i - 7] == 0))/*�յ��Ϸ����ٴ����������ж���*/
                                && Binary_Image[i][boundary_left[i]] == IMG_WHITE && Binary_Image[i + 1][boundary_left[i + 1]] == IMG_WHITE && Binary_Image[i - 1][boundary_left[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ㴦Ϊ����*/)
                            {
                                find_left_break_point = true;
                                left_break_point_y_to_out = i;
                                break;
                            }

                        }
                        if (find_left_break_point == true)//�ҵ���յ㣬�������г���
                        {
//                            if (firstloseline_left >15 && finalloseline_right==IMG_H - 1 && firstloseline_left - finalloseline_left >= 5)
//                            {
                                //��ת����һ��״̬ǰ���߹���
                                repair_line(left_break_point_y_to_out, boundary_left[left_break_point_y_to_out], finalloseline_right + 1, boundary_right[finalloseline_right + 1], LEFT_DIR);
                                re_midline();
                                //��������ˣ���ȡ��Ч��
                                right_roundabout_useful_line = finalloseline_right + 1;

                                right_roundabout_in_flag = false; //ʹ���ڻ����ڲ���־��0���������ڲ����ߴ���ʧЧ��
                                right_roundabout_to_out_flag = true; //������־λ��Ч��������Ľ׶γ�������
                                Right_Roundabout_State = 4 /*State5_Roundabout_To_Out_Repairline*/; //�ڴ˴��������ĸ�״̬������ת������״̬������
                                state_continue_frame_count = 0;         //״̬����֡�����������㣬Ϊ��һ�׶���׼��

                          //  }
                        }
                        else if (firstloseline_left==IMG_H-1 && finalloseline_left> /*30*/IMG_H - 25 &&firstloseline_left-finalloseline_left>10&&firstloseline_right==IMG_H-1&& right_roundabout_in_to_out_count> ROUNDABOUT_IN_TO_OUT_COUNTS + 3) //��ߴ�ͼ������п�ʼ���ֽϳ��Ķ��ߣ����һ�������֡������������(Ĭ��>5)�����ж�Ϊ����·��ͼ�񣬿�ʼ������>5�����복���йأ�������Ҫ������
                                //û�ҵ��յ�
                            {

//
                                //��ת����һ��״̬ǰ���߹���
                                repair_line(IMG_H - 1, boundary_left[IMG_H - 1], finalloseline_right + 1, boundary_left[finalloseline_right + 1] , LEFT_DIR); //��ͼ���ұ߽����ն����ж�Ӧ����߽�ĵ����������߽�ĵ����ӣ���������߽�
                                re_midline();

                                //��������ˣ���ȡ��Ч��
                                right_roundabout_useful_line = finalloseline_right + 1;

                                right_roundabout_in_flag = false;                                                    //ʹ���ڻ����ڲ���־��0���������ڲ����ߴ���ʧЧ��
                                right_roundabout_to_out_flag = true;     //����һ��                                                  //������־λ��Ч��������Ľ׶γ�������

                                Right_Roundabout_State = 4 /*State5_Roundabout_To_Out_Repairline*/;
                                state_continue_frame_count = 0;         //״̬����֡�����������㣬Ϊ��һ�׶���׼��
                            }

                    }
                }
            }
            break;
            //---------------����׶Σ�ʶ���˳���ͼ�񣬳�������----------------//
            case 4 /*State5_Roundabout_To_Out_Repairline*/:
            {RIGHT_Roundabout_State_step=5;
                if (right_roundabout_flag == 1 && right_roundabout_to_out_flag)
                {

                    right_roundabout_out_right_repair_line = false;  //�ұ߽粹�ߣ�ÿ֡��ˢ�£�����һ֡ͼ���н������ұ߽粹�ߣ�������Ϊ1

                    //��������߽粹�߱�־��ֻ������߽��Ҳ����յ㣨���ڶ��ߣ������ұ߽翪ʼ���ߺ�Ž�����Ϊ0

                    //����׶ε�һ������߽�����������ǰ�ڲ��֣����� ������յ������߽��ζ��߶���߽��������
                    if (right_roundabout_out_left_repair_line )
                    {
                        //Ϊ�Դ������ζ��ߵ�����Ĵ���ȡ�ϳ����ߣ�
                        if (firstloseline_right == IMG_H - 1) //�ұ���ױ߶���
                            loseline_adjust(RIGHT_DIR, 10);
                        if (firstloseline_left == IMG_H - 1)  //�����ױ߶���
                            loseline_adjust(LEFT_DIR, 10);
                        state_continue_frame_count++;

                        if (
                               ( ((((firstloseline_left != IMG_H - 1 && firstloseline_left - finalloseline_left <= 5) || (firstloseline_left == IMG_H - 1 && finalloseline_left >= IMG_H - 5)) && firstloseline_left - finalloseline_left <= 5)//���һ����߽粻�ٶ��ߣ����߼��̣����ٲ������
                                || ((firstloseline_left == IMG_H - 1 && finalloseline_left >=IMG_H - 10) )
                                    )&&state_continue_frame_count>15)
                                        ||state_continue_frame_count>30
                                )
                        {
                            right_roundabout_out_left_repair_line = false;
                            state_continue_frame_count=0;


                        }
                        //������Ҫ������ߣ����������޹յ㣨��ʱ�������״̬4�ˣ���˹յ㲻����£�
                        if (right_roundabout_out_left_repair_line)
                        {
                            //����߽��Ƿ���ڹյ�
                            bool find_left_break_point = false;
                            left_break_point_y_to_out = 0;

                            for (int i = (IMG_H - 5); i > useful_line_further/*����Ϊ>=��������Խ��*/; i--)//���ҹյ㲢����־λ
                            {
                                //�ȵ�4�׶ε���΢����һ��
                                if (boundary_left[i] >= boundary_left[i + 1] && boundary_left[i] > boundary_left[i + 2] && boundary_left[i] - boundary_left[i + 1] <= 5 /*�յ��·���������������*/
                                && boundary_left[i - 1] < boundary_left[i]  /*�յ��Ϸ�*/
                                && (boundary_left[i] - boundary_left[i - 1] >= 15 || boundary_left[i] - boundary_left[i - 2] >= 15 || boundary_left[i] - boundary_left[i - 3] >= 15 /*�յ��Ϸ����ٴ���һ��������ͻ��·���Ӱ�죡��*/)
                                && ((boundary_left[i - 1] == 0 && boundary_left[i - 2] == 0) || (boundary_left[i - 2] == 0 && boundary_left[i - 3] == 0) || (boundary_left[i - 3] == 0 && boundary_left[i - 4] == 0)|| (boundary_left[i - 4] == 0 && boundary_left[i - 5] == 0)|| (boundary_left[i - 5] == 0 && boundary_left[i - 6] == 0)|| (boundary_left[i - 6] == 0 && boundary_left[i - 7] == 0))/*�յ��Ϸ����ٴ����������ж���*/
                                && Binary_Image[i][boundary_left[i]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE /*�յ㴦Ϊ����*/
                                )
                                {
                                    find_left_break_point = true;
                                    left_break_point_y_to_out = i;
                                    break;
                                }

                            }
                            if (find_left_break_point && (firstloseline_left != IMG_H - 1 && finalloseline_left != -1 && firstloseline_left - finalloseline_left >= 5))//�ҵ���յ㣬�������г���
                            {
                                repair_line(left_break_point_y_to_out, boundary_left[left_break_point_y_to_out], finalloseline_right + 1, boundary_right[finalloseline_right + 1]+1, LEFT_DIR);
                                re_midline();
                                //��������ˣ���ȡ��Ч��
                                right_roundabout_useful_line = finalloseline_right + 1;
                                break;
                            }
                            else if ((firstloseline_left == IMG_H - 1 && finalloseline_left< IMG_H - 5 ) || (firstloseline_left >= IMG_H - 10 && finalloseline_left< IMG_H - 5) || (firstloseline_left - finalloseline_left >= 8) )//����߽���ڴ�ζ��ߣ�Ҳ����
                            {
                                repair_line(IMG_H - 1, boundary_left[IMG_H - 1], finalloseline_right + 1,  IMG_W - 10, LEFT_DIR); //��ͼ���ұ߽����ն����ж�Ӧ����߽�ĵ����������߽�ĵ����ӣ���������߽�
                                re_midline();

                                //��������ˣ���ȡ��Ч��
                                right_roundabout_useful_line = finalloseline_right + 1;
                                break;
                            }
                        }

                    }

                    if (!right_roundabout_out_right_repair_line){       right_roundabout_to_out_flag_count++;}
//                    //����׶� �ڶ�����ת����������뿪�һ������򣬽����ұ߽��������������ڲ��֣�
                    if (!right_roundabout_out_right_repair_line /*&& firstloseline_right == IMG_H - 1 */
                        && (((firstloseline_left != IMG_H - 1 /*&& firstloseline_left - finalloseline_right <= 5 */)|| (firstloseline_left == IMG_H - 1 && finalloseline_left >= IMG_H - 10))
                                ||(finalloseline_left<IMG_H - 15&&firstloseline_right<IMG_H - 20)
                        ))//�ұ߶��ߣ���߶��ߺܶ�
                    {
                        right_roundabout_to_out_flag_count++;   //����֡��������+1

                        /*�ж��Ƿ����*/

                        //ͳ�Ƶײ��ұ߽���������������ƣ������ұ߽�б�ʣ�
                        int boundary_right_count = 0;
                        int count_total = 0;

                        for (int i = IMG_H - 20; i <= IMG_H - 2; i++)
                        {
                            if (boundary_right[i] > boundary_right[i - 1])                  //��һ�еĺ��������һ�еĴ�
                            {
                                boundary_right_count++;                                    //��¼��߽���������������Ƶ��ۼƼ���
                            }
                            count_total++;
                        }
                        if (((boundary_right_count >= 0.7 * count_total) /*�����㹻*/
                            && firstloseline_right != IMG_H - 1 && firstloseline_right <= IMG_H - 20 /*�ұ߽�ײ���β�����*/
                            && right_roundabout_to_out_flag_count >= 40 /*����֡�������������һ��ֵ*/)
                            || right_roundabout_to_out_flag_count >= 50/*ͨ��֡������֡������ĳһ���ϴ��ֵʱ���ж�Ϊ����*/) //�ж�Ϊ����
                        {
                            right_roundabout_to_out_flag_count=0;
                            right_roundabout_out_flag = true;           //������־��1
                            right_roundabout_to_out_flag = false;
                            Right_Roundabout_State = 5 /*State6_Roundabout_Reset*/;                 //��������һ�׶ν��б�������
                                break;
                        }
                        else //��δ������������ұ߽粹�ߴ���
                        {
                            right_roundabout_useful_line = useful_line_further;  //ȡ���������Ч��
                            for (int i = right_roundabout_useful_line; i <= IMG_H - 1; i++)
                            {
                                if (Road_Width[i] > 0) //·�����0��������
                                {
                                    if (boundary_left[i] + Road_Width[i] <= IMG_W - 1)
                                        boundary_right[i] = boundary_left[i] + Road_Width[i];
                                    else
                                        boundary_right[i] = IMG_W - 1;
                                }

                                ////����ʱ����ƫ�ң����� ֱ���������� ������
                                //int length_temp = IMG_MIDDLE - Road_Refer_Left[i];
                                //if (length_temp > 0)//����ƫ��������0��������
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
                //���ñ�־λ������
                //if (right_roundabout_out_flag)//�������ò�һ�����ɳ������µģ�Ҳ���������ڳ���֡������һ��ֵ����ע�ʹ�����
                {
                    Right_Roundabout_State = 0 /*State1_Roundabout_Distern_1st_Repariline*/;//�ڴ˴����������״̬������ת���һ��״̬������
                    RIGHT_Roundabout_State_step=0;
                    right_roundabout_flag = 0;   //�һ����ܱ�־λ

                    //�뻷֮ǰʶ�𻷵�
                    right_roundabout_discerning = true; //�����뻷֮ǰ�Ļ���ʶ�𣨿���û�л�����һ���ɹ�ʶ�𵽻���������0��
                    right_roundabout_discern_flag_count = 0; //�һ����뻷֮ǰ����ʶ��֡��������
                    right_roundabout_only_up_point_flag = false; //�һ���ֻ���Ϲյ��ж��뻷��־������������
                    right_roundabout_only_up_point_count = 0; //�һ���ֻ���Ϲյ��ж��뻷֡��������������������
                    right_roundabout_state1_repairline_count = 0; //�һ�����һ�׶β���֡���������ڸ����жϵ�һ�׶εĽ���
                    right_roundabout_state1_repairline_to_end = false; //�һ�����һ�׶β��߼���������־
                    //�뻷����
                    right_roundabout_state2_right_repairline_count = 0; //�һ�����һ���ڶ����ɽ׶��ұ߽粹��֡����������Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ���ұ���
                    right_roundabout_in_right_repair_line = true; //�һ�������ʱ�ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                    right_roundabout_in_right_repair_line_count = 0; //�һ�������ʱ�ұ߽粹�߼���������ÿ��һ֡�ұ߽�ײ�������Ҫ���ߣ���+1��
                    right_roundabout_in_left_repair_line = true; //�һ�������ʱ��߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                    right_roundabout_in_change_angle = false; //ǿ��Ǳ�־�����뻷������߽�ײ����ٶ��ߣ�ǿ��Ǳ�־��1��
                    right_roundabout_to_in_count = 0; //�һ������������ļ�������������߽�ײ����ٶ���ʱ����ϴ�����(>0)���жϳɹ����뻷���ڲ���
                    //���ڴ���
                    right_roundabout_in_flag = false; //�һ����ɹ����뻷���ڲ���־λ
                    right_roundabout_in_to_out_count = 0; //�һ����ڲ�ʶ�����֡�����������жϳ���������֮һ��
                    left_break_point_y_to_out = 0;           //����ʱ��յ㣬���ڳ������
                    //��������
                    right_roundabout_to_out_flag = false; //�һ������������ֱ�־λ
                    right_roundabout_to_out_flag_count = 0; //�һ������������־λ��������
                    right_roundabout_out_right_repair_line = false;    //�һ�������ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                    right_roundabout_out_left_repair_line = true;     //�һ�������ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
                    right_roundabout_out_flag = false;          //�һ���������־//����һ��


//#if RIGHT_ROUNDABOUT_ONLY_ONE
//                        if_right_roundabout_recog                                 = 0;                 //ֻ��һ�λ���(ע�͵���ֻ��һ�λ�����
//#endif
                }
            }
            break;
            default:
                Right_Roundabout_State = 0 /*State1_Roundabout_Distern_1st_Repariline*/;
                break;
        }
    }

    //-----------------------------------�һ�������END-------------------------------------//
}
#endif


#endif /* CIRCLE_C_ */
