#include "zf_common_headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       ʮ��ʶ������
// @param       void
// @return  void
// @note        ʶ��ʮ�ֻ��ϰ�ʮ�֣����ߣ�����Ӧ��־λ
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------

void left_turn_to_cross()//��ת��ʮ��ʶ���봦��
{
    int down_point_y = 0, up_point_y = 0; //���¡���������
    int down_point_x = 0, up_point_x = 0; //���ϡ��º�����

    bool find_down_point = false, find_up_point = false;//�ҵ��¡��Ϲյ�ı�־

    //���¹յ㣬һ��Ϊ�ұ߽�
    for (int righti = IMG_H - 4; righti > useful_line_further /*��ֵ>=3,��righti>=4����ֹ����Խ��*/; righti--)
    {
        if (boundary_right[righti - 2] - boundary_right[righti] >= 4 && boundary_right[righti - 3] - boundary_right[righti] >= 8 && boundary_right[righti - 4] - boundary_right[righti] >= 12 /*�ж����䷶Χ���յ��ϰ벿�֣�*/
            && (boundary_right[righti + 1] >= boundary_right[righti] && boundary_right[righti + 2] > boundary_right[righti] && boundary_right[righti + 3] > boundary_right[righti]) /*�յ��°벿��������ȷ*/
            && Binary_Image[righti][middle_line[righti]] == IMG_WHITE && Binary_Image[righti - 1][middle_line[righti - 1]] == IMG_WHITE && Binary_Image[righti + 1][middle_line[righti + 1]] == IMG_WHITE /*�յ㴦Ϊ����*/)
        {
            //�жϹյ���Χ�׵����
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
            if (whitecount_right_point >= 5)//�׵�������һ��ֵ
            {
                down_point_y = righti;
                down_point_x = boundary_right[righti];
                find_down_point = true; //�ҵ��¹յ���
                break;
            }
        }
    }
    //���ҵ��¹յ��ǰ���£����Ϲյ㣬һ������߽���ڼ�������
    if (find_down_point == true)
    {
        //���¹յ���������߽������
        for (int lefti = down_point_y; lefti > useful_line_further; lefti--)
        {
            if (boundary_left[lefti] - boundary_left[lefti + 1] > 15 /*��߽���ڼ�������*/
                && (boundary_left[lefti] < down_point_x) /*�Ϲյ��������¹յ������С*/
                && (boundary_left[lefti - 1] - boundary_left[lefti] > /*2*/0 /*&& boundary_left[lefti - 1] - boundary_left[lefti] < 8*/ && boundary_left[lefti - 2] - boundary_left[lefti] >= /*5*/3 && boundary_left[lefti - 3] - boundary_left[lefti] >= /*8*/5) /*�յ��ϲ��ּ�飬�����㹻*/
                && (boundary_left[lefti + 1] - boundary_left[lefti + 2] <= 3 && boundary_left[lefti + 2] - boundary_left[lefti + 3] <= 3)/*�յ��°벿�ּ��*/
                && Binary_Image[lefti][middle_line[lefti]] == IMG_WHITE && Binary_Image[lefti - 1][middle_line[lefti - 1]] == IMG_WHITE && Binary_Image[lefti + 1][middle_line[lefti + 1]] == IMG_WHITE /*�յ㴦Ϊ����*/)
            {
                //���յ��Ϸ����ҵ����Ƿ����������ת������
                int row = lefti - 2;
                for (int x = boundary_left[row] - 1; x > 5; x--)//���ҵ������䣬���Ϊ��
                {
                    bool leftachieve = true;
                    bool rightachieve = true;
                    if (Binary_Image[row][x - 1] == IMG_WHITE)//xΪ����ǰ�ĵ㣨�ڣ���x-1Ϊ�����ĵ㣨�ף�
                    {
                        for (int i = x - 1; i > x - 1 - 5; i--)//�������������5���׵�
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
                            for (int i = x; i < x + 5; i++)//�����������������£��ж��ұ��Ƿ�������5���ڵ�
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
                                find_up_point = true; //�ҵ��Ϲյ���
                                up_point_y = lefti;
                                up_point_x = boundary_left[lefti];
                            }
                        }
                    }
                }
            }
        }
    }
    //���¹յ㶼�ҵ������ұ���
    if (find_down_point && find_up_point)
    {
        left_turn_cross_flag = 1;
        repair_line(down_point_y, down_point_x, up_point_y, up_point_x, RIGHT_DIR);
        if (firstloseline_left - finalloseline_left >= 8 && finalloseline_left >= 10 && finalloseline_left <= IMG_H - 10)
            repair_line(IMG_H - 1, boundary_left[IMG_H - 1], up_point_y + 1, boundary_left[up_point_y + 1], LEFT_DIR);
        re_midline();

        //�����ˣ���ȡ��Ч��
        cross_useful_line = up_point_y + 1; //��Ч��ȡ���Ϲյ㴦
    }

}
void right_turn_to_cross()//��ת��ʮ��ʶ���봦��
{
    int down_point_y = 0, up_point_y = 0; //���¡���������
    int down_point_x = 0, up_point_x = 0; //���ϡ��º�����

    bool find_down_point = false, find_up_point = false;//�ҵ��¡��Ϲյ�ı�־

    //���¹յ㣬һ��Ϊ��߽�
    for (int lefti = IMG_H - 4; lefti > useful_line_further /*��ֵ>=3,�� lefti>=4����ֹ����Խ��*/; lefti--)
    {
//        if (boundary_left[lefti] - boundary_left[lefti - 2] >= 4 && boundary_left[lefti] - boundary_left[lefti - 3] >= 8 && boundary_left[lefti] - boundary_left[lefti - 4] >= 12 /*�ж����䷶Χ���յ��ϰ벿�֣�*/
//            && (boundary_left[lefti + 1] <= boundary_left[lefti] && boundary_left[lefti + 2] < boundary_left[lefti] && boundary_left[lefti + 3] < boundary_left[lefti]) /*�յ��°벿��������ȷ*/
//            && Binary_Image[lefti][middle_line[lefti]] == IMG_WHITE && Binary_Image[lefti - 1][middle_line[lefti - 1]] == IMG_WHITE && Binary_Image[lefti + 1][middle_line[lefti + 1]] == IMG_WHITE /*�յ㴦Ϊ����*/)
        if (boundary_left[lefti] - boundary_left[lefti - 2] >= 2 && boundary_left[lefti] - boundary_left[lefti - 3] >= 5 && boundary_left[lefti] - boundary_left[lefti - 4] >= 10 /*�ж����䷶Χ���յ��ϰ벿�֣�*/
                   && (boundary_left[lefti + 1] <= boundary_left[lefti] && boundary_left[lefti + 2] < boundary_left[lefti] && boundary_left[lefti + 3] < boundary_left[lefti]) /*�յ��°벿��������ȷ*/
                   && Binary_Image[lefti][middle_line[lefti]] == IMG_WHITE && Binary_Image[lefti - 1][middle_line[lefti - 1]] == IMG_WHITE && Binary_Image[lefti + 1][middle_line[lefti + 1]] == IMG_WHITE /*�յ㴦Ϊ����*/)
        {
            //�жϹյ���Χ�׵����
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
            if (whitecount_right_point >= 4)//�׵�������һ��ֵ
            {
                down_point_y = lefti;
                down_point_x = boundary_left[lefti];
                find_down_point = true; //�ҵ��¹յ���
                break;
            }
        }
    }
    //���ҵ��¹յ��ǰ���£����Ϲյ㣬һ�����ұ߽���ڼ�������
    if (find_down_point == true)
    {
        //���¹յ��������ұ߽������
        for (int righti = down_point_y; righti > useful_line_further; righti--)
        {
            if (boundary_right[righti + 1] - boundary_right[righti] > 10 /*�ұ߽���ڼ�������*/
                && (boundary_right[righti] > down_point_x) /*�Ϲյ��������¹յ�������*/
                && (boundary_right[righti] - boundary_right[righti - 1] > /*2*/0 /*&& boundary_right[righti] - boundary_right[righti - 1] < 8*/ && boundary_right[righti] - boundary_right[righti - 2] >= /*5*/3 && boundary_right[righti] - boundary_right[righti - 3] >= /*8*/5) /*�յ��ϲ��ּ�飬�����㹻*/
                && (boundary_right[righti + 2] - boundary_right[righti + 1] <= 3 /*&& boundary_right[righti + 3] - boundary_right[righti + 2] <= 3*/)/*�յ��°벿�ּ��*/
                && Binary_Image[righti][middle_line[righti]] == IMG_WHITE && Binary_Image[righti - 1][middle_line[righti - 1]] == IMG_WHITE && Binary_Image[righti + 1][middle_line[righti + 1]] == IMG_WHITE /*�յ㴦Ϊ����*/)
            {
                //���յ��Ϸ��������Ƿ����������ת������
                int row = righti - 2;
                for (int x = boundary_right[row] + 1; x < IMG_W - 5; x++)//���ҵ������䣬���Ϊ��
                {
                    bool leftachieve = true;
                    bool rightachieve = true;
                    if (Binary_Image[row][x + 1] == IMG_WHITE)//xΪ����ǰ�ĵ㣨�ڣ���x+1Ϊ�����ĵ㣨�ף�
                    {
                        for (int i = x + 1; i < x + 1 + 5; i++)//�������������5���׵�
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
                            for (int i = x; i > x - 5; i--)//�����������������£��ж��ұ��Ƿ�������5���ڵ�
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
                                find_up_point = true; //�ҵ��Ϲյ���
                                up_point_y = righti;
                                up_point_x = boundary_right[righti];
                            }
                        }
                    }
                }
            }
        }
    }
    //���¹յ㶼�ҵ������ұ���
    if (find_down_point && find_up_point)
    {
        right_turn_cross_flag = 1;
        repair_line(down_point_y, down_point_x, up_point_y, up_point_x, LEFT_DIR);
        if (firstloseline_right - finalloseline_right >= 8 && finalloseline_right >= 10 && finalloseline_right <= IMG_H - 10)//���ұߴ��ڴ�ζ��ߣ�Ҳ���в���
            repair_line(IMG_H - 1, boundary_right[IMG_H - 1], up_point_y + 1, boundary_right[up_point_y + 1], RIGHT_DIR);
        re_midline();

        //�����ˣ���ȡ��Ч��
        cross_useful_line = up_point_y + 1; //��Ч��ȡ���Ϲյ㴦
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
            )/*��������*/
    {
        //��ر������־λ
        cross_half_flag = 0;
        cross_full_flag = 0;
        left_turn_cross_flag = 0;
        right_turn_cross_flag = 0;
        cross_after_turn_flag = 0;

        cross_useful_line = 0;

        int L_Down_Pointx = 0, L_Down_Pointy = 0; //���¹յ��������
        int L_Up_Pointx = 0, L_Up_Pointy = 0;//���Ϲյ��������
        int R_Down_Pointx = 0, R_Down_Pointy = 0; //���¹յ��������
        int R_Up_Pointx = 0, R_Up_Pointy = 0;//���Ϲյ��������


        _Bool Cross_R_Down_flag = false, Cross_R_Up_flag = false, Cross_L_Down_flag = false, Cross_L_Up_flag = false;//���¡����ϡ����¡����ϱ�־λ

        /***** ����ʮ�ֵ��ж��봦�� ******/
        //Ѱ�ҹյ�
        //�ң�
        for (int i = (IMG_H - 1); i > useful_line_further; i--)//�������¹յ㲢����־λ��ע�������ҹյ����ޣ���ֹ����Խ��
        {
            if (boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] >= boundary_right[i - 1] /*ԭ�����ұ߽������Խ��ԽС�������¹յ�ʱ�Ż�����*/
                && boundary_right[i - 2] - boundary_right[i] > 3 /*��������*/)//�ҵ����¹յ���
            {
                //�жϹյ���Χ�׵������ȷ����ΧΪ����
                int whitecount_right_down = 0;
                for (int k = -1; k < 2; k++)
                {
                    for (int g = -1; g < 2; g++)
                    {
                        if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)//��ֹ����Խ��
                        {
                            if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                                whitecount_right_down++;
                        }
                    }
                }
                if (whitecount_right_down >= 5)//�Ÿ�������5���׵�
                {
                    R_Down_Pointy = i;                      //��¼���¹յ��������
                    R_Down_Pointx = boundary_right[i];
                    Cross_R_Down_flag = true;               //�ҵ����¹յ���
                    break;
                }
            }
        }
        if (Cross_R_Down_flag)//����ҵ������¹յ㣬�����������Ϲյ㣨Ҫ���ҵ������¹յ�Ϊǰ�ᣩ
        {
            for (int i = R_Down_Pointy; i >= useful_line_further; i--)  //�����Ϲյ㲢����־λ
            {
                if (boundary_right[i] - boundary_right[i - 1] > 5  /*�Ϲյ������ͻȻ��С*/
                    && ((boundary_right[i - 2] - boundary_right[i - 3] < 3) || (boundary_right[i - 1] - boundary_right[i - 2] < 3))/*�����Ϲյ��Ϸ����������*/)
                {
                    //�жϹյ���Χ�׵������ȷ����ΧΪ����
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
                    if (whitecount_right_up >= 4 && boundary_right[i - 2] < boundary_right[R_Down_Pointy])//�ж���Χ�׵����,�¹յ������Ҫ���Ϲյ�������
                    {
                        R_Up_Pointy = i - 2;                   //��¼���Ϲյ��������
                        R_Up_Pointx = boundary_right[i - 2];
                        Cross_R_Up_flag = true;                //�ҵ����Ϲյ���
                        break;
                    }
                }
            }
        }
        //��
        for (int i = (IMG_H - 1); i > useful_line_further; i--)//�����¹յ㲢����־λ
        {
            if (boundary_left[i - 1] < boundary_left[i] && boundary_left[i - 2] <= boundary_left[i - 1] /*������ͻȻ��С*/
                && boundary_left[i] - boundary_left[i - 2] > 3 /*��������*/)
            {
                //�����жϹյ���Χ�׵����
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
                if (whitecount_left_down >= 5)//�ж���Χ�׵����
                {
                    L_Down_Pointy = i;
                    L_Down_Pointx = boundary_left[i];
                    Cross_L_Down_flag = true;
                    break;
                }
            }
        }
        if (Cross_L_Down_flag)//����ҵ������¹յ㣬�����������Ϲյ�
        {
            for (int i = L_Down_Pointy; i >= useful_line_further; i--)//�����Ϲյ㲢����־λ
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
                    if (whitecount_left_up >= 4 && boundary_left[i - 2] > boundary_left[L_Down_Pointy])//�ж���Χ�׵�������º�����Ҫ��������С
                    {
                        L_Up_Pointy = i - 2;
                        L_Up_Pointx = boundary_left[i - 2];
                        Cross_L_Up_flag = true;
                        break;
                    }
                }
            }
        }

        //ʶ��ȫʮ��
        // �¹յ㷶Χ �� useful_line_further ��IMG_H - 1] ,�Ϲյ㷶Χ [ useful_line_further - 2, up_right��
        if (Cross_R_Down_flag && Cross_R_Up_flag && Cross_L_Down_flag && Cross_L_Up_flag) //�ĸ��յ㶼�ҵ���
        {
            if (L_Down_Pointx < R_Up_Pointx && L_Up_Pointx < R_Down_Pointx)//�����꽻��Ƚ�
            {
                if (L_Down_Pointy > R_Up_Pointy && R_Down_Pointy > L_Up_Pointy)//�����꽻��Ƚ�
                {
                    double judge;//��ȡ��ɫ���ص�ռ��
                    judge = cross_bw_judge(L_Down_Pointy, L_Up_Pointy, R_Down_Pointy, R_Up_Pointy);
                    if (judge < 0.15)
                    {
                        cross_full_flag = 1;//ʮ��λ��Ϊ1
                    }
                }
            }
        }
        //ʶ���ϰ�ʮ��
        if (cross_full_flag == 0)//û��ʶ��ȫʮ��
        {
            //������ر������־λ
            L_Up_Pointx = 0; L_Up_Pointy = 0;//���Ϲյ������������
            R_Up_Pointx = 0; R_Up_Pointy = 0;//���Ϲյ������������
            Cross_L_Up_flag = false; Cross_R_Up_flag = false; //�������Ϲյ��־λ����

            if (loseleftflag == 1 && loserightflag == 1)  //����ͬʱ��������
            {
                if (firstloseline_left == (IMG_H - 1) && firstloseline_right == (IMG_H - 1))        //�������߶�������¿�ʼ���ߣ���ʱfinalloseline_left��finalloseline_right<49)
                {
                    if (finalloseline_left < IMG_H - 6 && finalloseline_right < IMG_H - 6)         //�޶����ն����и߶ȣ���һ���Ķ��߳��ȣ�ͬʱ��ֹ�·�����Խ�磩
                    {
                        //��ȡ�Ϲյ�����
                        for (int i = finalloseline_left + 5; i >= useful_line_further; i--)         //�����Ϲյ㣨�����ն������·�5�п�ʼ������
                        {
                            if ((boundary_left[i] == 0) && (boundary_left[i - 1] - boundary_left[i]) > 5 && (boundary_left[i - 2] - boundary_left[i]) > 5)//���Ϲյ������ͻȻ����
                            {
                                L_Up_Pointy = i - 2;
                                L_Up_Pointx = boundary_left[i - 2];
                                Cross_L_Up_flag = true;
                                break;
                            }
                        }
                        for (int i = finalloseline_right + 5; i >= useful_line_further; i--)        //�������Ϲյ㣨�����ն������·�5�п�ʼ������
                        {
                            if ((boundary_right[i] == IMG_W - 1) && (boundary_right[i] - boundary_right[i - 1]) > 5 && (boundary_right[i] - boundary_right[i - 2]) > 5)//�ҵ����Ϲյ��ˣ���ͻȻ��С��
                            {
                                R_Up_Pointy = i - 2;
                                R_Up_Pointx = boundary_right[i - 2];
                                Cross_R_Up_flag = true;
                                break;
                            }
                        }
                        //�ж��ϰ�ʮ��
                        if (Cross_L_Up_flag && Cross_R_Up_flag && (L_Up_Pointy - 8 <= R_Up_Pointy && R_Up_Pointy <= L_Up_Pointy + 8) && L_Up_Pointx < R_Up_Pointx)//�ҵ��������Ϲյ�������������С
                        {
                            //���ΰ׵�ռ��
                            int x1, x2, y;                                                //���κ�������
                            int white_point = 0, black_point = 0, totalpoint = 0;           //�����кڰ׵����
                            x1 = L_Up_Pointx; x2 = R_Up_Pointx;                 //�������Ϲյ�ĺ�������Ϊ���ε�����������
                            y = ((L_Up_Pointy <= R_Up_Pointy) ? L_Up_Pointy : R_Up_Pointy);   //ȡ������ƫ�Ϸ�����Ϊ����������

                            for (int j = y; j < IMG_H - 1; j++)         //������ص�
                            {
                                for (int i = x1; i < x2; i++)
                                {
                                    if (Binary_Image[j][i] == IMG_BLACK)//���ص�Ϊ��ɫ
                                        black_point++;
                                    else                                                                //���ص�Ϊ��ɫ
                                        white_point++;
                                    totalpoint++;                                               //�ۼ������ص�
                                }
                            }
                            float per = 0;
                            if (totalpoint != 0)
                                per = (float)black_point / totalpoint;//�����ɫ���ص�ռ��
                            else
                                per = 1;
                            if (per < 0.1)                                                  //��ɫռ�Ľ��٣����������ڴ����Ϊ������
                            {
                                cross_half_flag = 1;     //�ϰ�ʮ�ֱ�־λ��1
                            }

                        }
                    }
                }
            }
        }

        //ʮ�ִ���
        if (cross_full_flag == 1 && cross_half_flag == 0)
        {
            repair_line(L_Down_Pointy, L_Down_Pointx, L_Up_Pointy, L_Up_Pointx, LEFT_DIR);      //��߽�
            repair_line(R_Down_Pointy, R_Down_Pointx, R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//�ұ߽�
            re_midline();

            //�����ˣ���ȡ��Ч��
            cross_useful_line = (L_Up_Pointy < R_Up_Pointy ? L_Up_Pointy : R_Up_Pointy);//��Ч��ȡ���Ϲյ��иߵ�һ��
        }
        //�ϰ�ʮ�ִ���
        if (cross_half_flag == 1 && cross_full_flag == 0)
        {
            array_set_uniform(boundary_left, L_Up_Pointx, L_Up_Pointy + 1, IMG_H);       //���ڵ�������� �ѵ� up_left + 1(���Ϲյ㴦)�����һ�ζ��ߴ���������һ�У�����߽綼��Ϊ�յ㴦�����꣨ps��firstlose_left = IMG_H -1, ��1��ΪIMG_H�����˺�����������һ������Ԫ��ǡΪ����ֵ��IMG_H��-1)
            array_set_uniform(boundary_right, R_Up_Pointx, R_Up_Pointy + 1, IMG_H);      //���ڵ����ұ��� �ѵ� up_right + 1(���Ϲյ㴦)���ҵ�һ�ζ��ߴ���������һ�У����ұ߽綼��Ϊ�յ㴦������

            int adjust;             //��ȡ���Ҷ��������������  ����ԽСԽ��
            adjust = ((L_Up_Pointy <= R_Up_Pointy) ? L_Up_Pointy : R_Up_Pointy); //ȡֵ��С��

            for (int i = adjust; i <= (IMG_H - 1); i++)
            {
                middle_line[i] = (boundary_left[i] + boundary_right[i]) / 2;                //���ݵ�����ı��ߵ�������
            }

            //�����ˣ���ȡ��Ч��
            cross_useful_line = adjust;//��Ч��ȡ�������㴦
        }

        /***** ����ʮ�ֵ��ж��봦�� ******/
        //������ʮ��
        if (cross_full_flag == 0 && cross_half_flag == 0 && loseleftflag == 1)//��ȫ�����ް�ʮ�֣�����߶���
        {
            left_turn_to_cross();//����ʮ�ֵ��ж��봦��
        }
        //������������ʮ�֣���������ʮ�ֽ�����ļ�֡�ڣ��ſ�ʮ�ֵ�����
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
                //�ſ�ʮ������
                if(cross_full_flag == 0 && cross_half_flag == 0)//���Ѳ���ȫʮ�ֺ��ϰ�ʮ�ֵ�ǰ����
                {
                    //�ң�
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//�������¹յ㲢����־λ��ע�������ҹյ����ޣ���ֹ����Խ��
                    {
                        if (boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] >= boundary_right[i - 1] /*ԭ�����ұ߽������Խ��ԽС�������¹յ�ʱ�Ż�����*/
                            && boundary_right[i - 2] - boundary_right[i] >= 3 /*��������*/
                            && boundary_right[i + 1] > boundary_right[i] /*�յ��²���*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE  && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE )//�ҵ����¹յ���
                        {
                            R_Down_Pointy = i;                      //��¼���¹յ��������
                            R_Down_Pointx = boundary_right[i];
                            Cross_R_Down_flag = true;               //�ҵ����¹յ���
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)  //�����Ϲյ㲢����־λ
                    {
                        if (boundary_right[i] - boundary_right[i - 1] >=5  /*�Ϲյ������ͻȻ��С*/
                            && ((boundary_right[i - 2] - boundary_right[i - 3] < 3) || (boundary_right[i - 1] - boundary_right[i - 2] < 3))
                            && Binary_Image[i - 2][middle_line[i - 2]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE/*�����Ϲյ��Ϸ����������*/)
                        {
                            R_Up_Pointy = i - 3;                   //��¼���Ϲյ��������
                            R_Up_Pointx = boundary_right[i - 2];
                            Cross_R_Up_flag = true;                //�ҵ����Ϲյ���
                            break;
                        }
                    }
                    //��
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//�����¹յ㲢����־λ
                    {
                        if (boundary_left[i - 1] < boundary_left[i] && boundary_left[i - 2] <= boundary_left[i - 1] /*������ͻȻ��С*/
                            && boundary_left[i] - boundary_left[i - 2] > 3 /*��������*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)
                        {

                            L_Down_Pointy = i;
                            L_Down_Pointx = boundary_left[i];
                            Cross_L_Down_flag = true;
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)//�����Ϲյ㲢����־λ
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
                    if (Cross_R_Down_flag && Cross_R_Up_flag)        //�ҵõ������¹յ�
                    {
                        repair_line(R_Down_Pointy, R_Down_Pointx, R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//�ұ߽�
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_R_Up_flag)                        //�Ҳ������¹յ㣬ֻ�ҵ��Ϲյ�
                    {
                        repair_line(IMG_H - 1, boundary_right[IMG_H - 1], R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//�ұ߽�
                        cross_after_turn_flag = 1;
                    }
                    if (Cross_L_Down_flag && Cross_L_Up_flag)       //�ҵõ������¹յ�
                    {
                        repair_line(L_Down_Pointy, L_Down_Pointx, L_Up_Pointy, L_Up_Pointx, LEFT_DIR);      //��߽�
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_L_Up_flag)                       //�Ҳ������¹ֵ㣬ֻ�ҵ��Ϲյ�
                    {
                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], L_Up_Pointy, L_Up_Pointx, LEFT_DIR);
                        cross_after_turn_flag = 1;
                    }
                    re_midline();

                    //�����ˣ���ȡ��Ч��
                    if(Cross_R_Up_flag && Cross_L_Up_flag)
                        cross_useful_line = (L_Up_Pointy > R_Up_Pointy ? L_Up_Pointy : R_Up_Pointy);//��Ч��ȡ���Ϲյ��е͵�һ��
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

        //������ʮ��
        if(cross_full_flag == 0 && cross_half_flag == 0 && loserightflag == 1)//��ȫ�����ް�ʮ�֣����ұ߶���
        {
            right_turn_to_cross();//����ʮ�ֵ��ж��봦��
        }
        //������������ʮ�֣���������ʮ�ֽ�����ļ�֡�ڣ��ſ�ʮ�ֵ�����
        if((right_turn_cross_flag == 1)||cross_time>10)
        {
            right_cross_end_frame_flag = true;//���ֹ�����ʮ�֣���־λ��1
            right_cross_end_frame_count = 0;
        }
        if (right_cross_end_frame_flag && right_turn_cross_flag == 0)
        {
            right_cross_end_frame_count++;
            if(right_cross_end_frame_count <= 3)
            {
                //�ſ�ʮ������
                if (cross_full_flag == 0 && cross_half_flag == 0)//���Ѳ���ȫʮ�ֺ��ϰ�ʮ�ֵ�ǰ����
                {
                    //�ң�
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//�������¹յ㲢����־λ��ע�������ҹյ����ޣ���ֹ����Խ��
                    {
                        if (boundary_right[i - 1] > boundary_right[i] && boundary_right[i - 2] >= boundary_right[i - 1] /*ԭ�����ұ߽������Խ��ԽС�������¹յ�ʱ�Ż�����*/
                            && boundary_right[i - 2] - boundary_right[i] > 3 /*��������*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)//�ҵ����¹յ���
                        {
                            R_Down_Pointy = i;                      //��¼���¹յ��������
                            R_Down_Pointx = boundary_right[i];
                            Cross_R_Down_flag = true;               //�ҵ����¹յ���
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)  //�����Ϲյ㲢����־λ
                    {
                        if (boundary_right[i] - boundary_right[i - 1] > 5  /*�Ϲյ������ͻȻ��С*/
                            && ((boundary_right[i - 2] - boundary_right[i - 3] < 3) || (boundary_right[i - 1] - boundary_right[i - 2] < 3))
                            && Binary_Image[i - 2][middle_line[i - 2]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i][middle_line[i]] == IMG_WHITE/*�����Ϲյ��Ϸ����������*/)
                        {
                            R_Up_Pointy = i - 2;                   //��¼���Ϲյ��������
                            R_Up_Pointx = boundary_right[i - 2];
                            Cross_R_Up_flag = true;                //�ҵ����Ϲյ���
                            break;
                        }
                    }
                    //��
                    for (int i = (IMG_H - 2); i > useful_line_further; i--)//�����¹յ㲢����־λ
                    {
                        if (boundary_left[i - 1] < boundary_left[i] && boundary_left[i - 2] <= boundary_left[i - 1] /*������ͻȻ��С*/
                            && boundary_left[i] - boundary_left[i - 2] > 3 /*��������*/
                            && boundary_left[i + 1] < boundary_left[i] /*�յ��²���*/
                            && Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_WHITE && Binary_Image[i + 1][middle_line[i + 1]] == IMG_WHITE)
                        {

                            L_Down_Pointy = i;
                            L_Down_Pointx = boundary_left[i];
                            Cross_L_Down_flag = true;
                            break;
                        }
                    }
                    for (int i = IMG_H - 2; i >= useful_line_further; i--)//�����Ϲյ㲢����־λ
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
                    if (Cross_R_Down_flag && Cross_R_Up_flag)        //�ҵõ������¹յ�
                    {
                        repair_line(R_Down_Pointy, R_Down_Pointx, R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//�ұ߽�
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_R_Up_flag)                        //�Ҳ������¹յ㣬ֻ�ҵ��Ϲյ�
                    {
                        repair_line(IMG_H - 1, boundary_right[IMG_H - 1], R_Up_Pointy, R_Up_Pointx, RIGHT_DIR);//�ұ߽�
                        cross_after_turn_flag = 1;
                    }
                    if (Cross_L_Down_flag && Cross_L_Up_flag)       //�ҵõ������¹յ�
                    {
                        repair_line(L_Down_Pointy, L_Down_Pointx, L_Up_Pointy, L_Up_Pointx, LEFT_DIR);      //��߽�
                        cross_after_turn_flag = 1;
                    }
                    else if (Cross_L_Up_flag)                       //�Ҳ������¹ֵ㣬ֻ�ҵ��Ϲյ�
                    {
                        repair_line(IMG_H - 1, boundary_left[IMG_H - 1], L_Up_Pointy, L_Up_Pointx, LEFT_DIR);
                        cross_after_turn_flag = 1;
                    }
                    re_midline();

                    //�����ˣ���ȡ��Ч��
                    if(Cross_R_Up_flag && Cross_L_Up_flag)
                        cross_useful_line = (L_Up_Pointy > R_Up_Pointy ? L_Up_Pointy : R_Up_Pointy);//��Ч��ȡ���Ϲյ��е͵�һ��
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
