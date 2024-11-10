

#include "zf_common_headfile.h"
/*---------------------����ֵ��������------------------------*/
uint8 img_thread = 0;                                                                               //��ֵ����ֵ
uint8 Binary_Image[MT9V03X_H][MT9V03X_W];                               //��ֵ���������
/*---------------------����ֵ��������------------------------*/

/*-------------------��ͼ������Ԥ�����----------------------*/

/*------------����ߣ������꣩���������-----------*/
int boundary_left[IMG_H] = { 0 };                 //��߽������
int boundary_right[IMG_H] = { 0 };                //�ұ߽������
int middle_line[IMG_H] = { 0 };                   //���ߺ����꣨ÿ������Ԫ�ش洢ĳһ�е����ߺ����꣩

int Road_Refer_Left[IMG_H] = { 0 };               //�ο�·����߽������
int Road_Refer_Right[IMG_H] = { 0 };              //�ο�·���ұ߽������
int Road_Width[IMG_H] = { 0 };                    //�ο�·��·��
/*--------------------���߱���--------------------*/
int firstloseline_left = 0;                     //��ߵ�һ�ζ�����
int firstloseline_right = 0;                    //�ұߵ�һ�ζ�����

int finalloseline_right = 0;                    //�ұ����ն�����
int finalloseline_left = 0;                     //������ն�����

int finalloseline = 0;                          //������Ч��

int loserightflag = 0;                          //�ж��ұ��Ƿ��� 1���ж���
int loseleftflag = 0;                           //�ж�����Ƿ��� 1���ж���

int lost_right_flag[IMG_H] = { 0 };             //��¼�ұ߶����У�����Ϊ1������Ϊ0
int lost_left_flag[IMG_H] = { 0 };                //��¼��߶����У�����Ϊ1������Ϊ0

/*-------------------��ͼ������Ԥ�����----------------------*/

/*--------------------������Ԫ��ʶ���-----------------------*/
/*-------------------�������ýṹ�壿��--------------------*/
/*----------��־λ-----------*/
uint8 flag_send=0;
/*--------------------���Ԫ��--------------------*/
/*----------��־λ-----------*/
#define TURN_PROCESS_WAY            1           //1Ϊƽ�Ʋ��߷���0Ϊ����ֱ�ߴ�Ƿ�
u8 left_turn_flag = 0;                                              //��ת��־λ
u8 right_turn_flag = 0;                                             //��ת��־λ

/*--------------------ʮ��Ԫ��--------------------*/
/*----------��־λ-----------*/
u8 cross_full_flag = 0;                                             //ȫʮ�ֱ�־λ         1Ϊʶ��ʮ��
u8 cross_half_flag = 0;                                             //�ϰ�ʮ�ֱ�־λ 1Ϊʶ��Ϊ�ϰ�ʮ��
int left_turn_cross_flag = 0;           //ʶ��������ʮ��·�ڵı�־λ
int right_turn_cross_flag = 0;          //ʶ��������ʮ��·�ڵı�־λ
int cross_after_turn_flag = 0;          //б��ʮ�ֺ�Ĳ��߱�־����ʱб��ʮ�ֱ�־��1ת0�ĺ�֡�����������־Ϊ1��
bool left_cross_end_frame_flag = false;//������������ʮ�֣���������ʮ�ֽ����󣬿�ʼ֡�����ı�־���Էſ�ʮ��������
int left_cross_end_frame_count = 0; //����ʮ�ֽ���֡����ֵ

bool right_cross_end_frame_flag = false;//������������ʮ�֣���������ʮ�ֽ����󣬿�ʼ֡�����ı�־���Էſ�ʮ��������
int right_cross_end_frame_count = 0; //����ʮ�ֽ���֡����ֵ

/*--------------------����Ԫ��--------------------*/
#if USE_ROUNDABOUT_FSM
Roundabout_FSM  Left_Roundabout_State;//�󻷵�״̬��״̬ö�ٱ���
Roundabout_FSM  Right_Roundabout_State;//�һ���״̬��״̬ö�ٱ���
#endif
int Roundabout_size=0;//Բ����С����ʼΪ0,1ΪС��2Ϊ��
int time_in=0;//Բ��״̬����ʱ�䣬���ڿ���Բ��״̬�ĸ���

/*-----------------------��-----------------------*/
#define LEFT_ROUNDABOUT_ONLY_ONE                    1  //�����Ƿ�ֻ��һ���󻷵�����if_left_roundabout_recog��־��ϣ���ֻ��һ�λ����򽫴˺궨����1�����ִ����һ�λ��������if_left_roundabout_recog ��0������ִ�л�������
u8  if_left_roundabout_recog = 1;  //if_left_roundabout_recogĬ��Ϊ1���������ˡ�ֻ��һ�λ�����ʱ�����ڻ���ʶ�𲢴��������0��
int LEFT_Roundabout_State_step=0;
/*------���뻷����Ϊ��λˢ�µı���-----*/
/*----------������������������---------*/
u8  left_roundabout_flag = 0;   //�󻷵��ܱ�־λ
int LEFR_Roundabout_State_step=0;//�󻷵���־λ��������
//�뻷֮ǰʶ�𻷵�
bool left_roundabout_discerning = true;//�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
int left_roundabout_discern_flag_count = 0;//�󻷵��뻷֮ǰ����ʶ��֡��������
bool left_roundabout_only_up_point_flag = false; //�󻷵�ֻ���Ϲյ��ж��뻷��־������������
int left_roundabout_only_up_point_count = 0; //�󻷵�ֻ���Ϲյ��ж��뻷֡��������������������
int left_roundabout_state1_repairline_count = 0; //�󻷵���һ�׶β���֡���������ڸ����жϵ�һ�׶εĽ���
bool left_roundabout_state1_repairline_to_end = false; //�󻷵���һ�׶β��߼���������־
//�뻷����
int left_roundabout_state2_left_repairline_count = 0; //�󻷵���һ���ڶ����ɽ׶���߽粹��֡����������Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ�������
bool left_roundabout_in_left_repair_line = true;//�󻷵�����ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
int left_roundabout_in_left_repair_line_count = 0; //�󻷵�����ʱ��߽粹�߼���������ÿ��һ֡��߽�ײ�������Ҫ���ߣ���+1��
bool left_roundabout_in_right_repair_line = true;  //�󻷵�����ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
bool left_roundabout_in_change_angle = false;   //ǿ��Ǳ�־���뻷���ڣ�
int left_roundabout_to_in_count = 0;  //�󻷵����������ļ������������ұ߽�ײ����ٶ���ʱ����ϴ�����(>0)���жϳɹ����뻷���ڲ���
//���ڴ���
bool left_roundabout_in_flag = false;  //�󻷵��ɹ����뻷���ڲ���־λ
int left_roundabout_in_to_out_count = 0; //�󻷵��ڲ�ʶ�����֡�����������жϳ���������֮һ��
int right_break_point_y_to_out = 0;     //����ʱ�ҹյ㣬���ڳ������
//��������
bool left_roundabout_to_out_flag = false;  //�󻷵����������ֱ�־λ
int left_roundabout_to_out_flag_count = 0; //�󻷵����������־λ��������
bool left_roundabout_out_left_repair_line = false; //�󻷵�����ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
bool left_roundabout_out_right_repair_line = true; //�󻷵�����ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
bool left_roundabout_out_flag = false;   //�󻷵������ɹ���־

/*--------��֡Ϊ��λˢ�µı���--------*/
/*----�����뻷��һ�׶Σ�ʶ�𻷵���----*/
bool find_roundabout_left_down = false; //�󻷵��¹յ�ʶ���־
bool find_roundabout_left_up = false; //�󻷵��Ϲյ�ʶ���־
bool find_roundabout_left_up_only = false; //�󻷵�ֻ�ҵ��Ϲյ��־
int roundabout_left_down_y = 0;     //�󻷵����¹յ�������
int roundabout_left_down_x = 0;     //�󻷵����¹յ������
int roundabout_left_up_y = 0;     //�󻷵����Ϲյ�������
int roundabout_left_up_x = 0;     //�󻷵����Ϲյ������
float right_boundary_slope = 0;     //�ұ���б��
int lefty=0;//�󻷵�˺�ѵ�
int state_continue_frame_count = 0;//����ĳһ��״̬����ת֡����ֵ��������ĳ��ֵ����ֱ�ӽ�״̬��Ϊ��ʼ״̬��

/*-----------------------��-----------------------*/
#define RIGHT_ROUNDABOUT_ONLY_ONE                    1  //�����Ƿ�ֻ��һ���һ�������if_right_roundabout_recog��־��ϣ���ֻ��һ�λ����򽫴˺궨����1�����ִ����һ�λ��������if_right_roundabout_recog ��0������ִ�л�������
u8  if_right_roundabout_recog = 1;  //if_right_roundabout_recog Ĭ��Ϊ1���������ˡ�ֻ��һ�λ�����ʱ�����ڻ���ʶ�𲢴��������0��

/*------���뻷����Ϊ��λˢ�µı���-----*/
/*----------������������������---------*/
u8  right_roundabout_flag = 0;  //�һ����ܱ�־λ
int RIGHT_Roundabout_State_step=0;//�����ñ�־λ
//�뻷֮ǰʶ�𻷵�
bool right_roundabout_discerning = true; //�����뻷֮ǰ�Ļ���ʶ��ֻҪ��Ϊ1�������л���ʶ���Լ�ʶ�𵽻������ǻ�û�н���ڶ��׶εĲ��ߣ��൱�ڵ�һ�β��߱�־����״̬1��Ч��
int right_roundabout_discern_flag_count = 0; //�һ����뻷֮ǰ����ʶ��֡��������
bool right_roundabout_only_up_point_flag = false; //�һ���ֻ���Ϲյ��ж��뻷��־������������
int right_roundabout_only_up_point_count = 0; //�һ���ֻ���Ϲյ��ж��뻷֡��������������������
int right_roundabout_state1_repairline_count = 0; //�һ�����һ�׶β���֡���������ڸ����жϵ�һ�׶εĽ���
bool right_roundabout_state1_repairline_to_end = false; //�һ�����һ�׶β��߼���������־
//�뻷����
int right_roundabout_state2_right_repairline_count = 0; //�һ�����һ���ڶ����ɽ׶��ұ߽粹��֡����������Ϊ����һ�׶θ��õĹ��ɣ�����һ�׶ε�ǰ��֡��Ȼ���ұ���
bool right_roundabout_in_right_repair_line = true; //�һ�������ʱ�ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
int right_roundabout_in_right_repair_line_count = 0; //�һ�������ʱ�ұ߽粹�߼���������ÿ��һ֡�ұ߽�ײ�������Ҫ���ߣ���+1��
bool right_roundabout_in_left_repair_line = true; //�һ�������ʱ��߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
bool right_roundabout_in_change_angle = false; //ǿ��Ǳ�־���뻷���ڣ�
int right_roundabout_to_in_count = 0; //�һ������������ļ�������������߽�ײ����ٶ���ʱ����ϴ�����(>0)���жϳɹ����뻷���ڲ���
//���ڴ���
bool right_roundabout_in_flag = false; //�һ����ɹ����뻷���ڲ���־λ
int right_roundabout_in_to_out_count = 0; //�һ����ڲ�ʶ�����֡�����������жϳ���������֮һ��
int left_break_point_y_to_out = 0;           //����ʱ��յ㣬���ڳ������
//��������
bool right_roundabout_to_out_flag = false; //�һ������������ֱ�־λ
int right_roundabout_to_out_flag_count = 0; //�һ������������־λ��������
bool right_roundabout_out_right_repair_line = false;    //�һ�������ʱ����ұ߽粹�ߴ���=1��ʾ�ұ߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
bool right_roundabout_out_left_repair_line = true;     //�һ�������ʱ�����߽粹�ߴ���=1��ʾ��߽�ײ��Դ��ڶ��ߣ���Ҫ���ߣ�
bool right_roundabout_out_flag = false;          //�һ����ɹ�������־//����һ��


/*--------��֡Ϊ��λˢ�µı���--------*/
/*----�����뻷��һ�׶Σ�ʶ�𻷵���----*/
bool  find_roundabout_right_down = false; //�һ����¹յ�ʶ���־
bool  find_roundabout_right_up = false; //�һ����Ϲյ�ʶ���־
bool find_roundabout_right_up_only = false; //�һ���ֻ�ҵ��Ϲյ��־
int roundabout_right_down_y = 0;     //�һ������¹յ�������
int roundabout_right_down_x = 0;     //�һ������¹յ������
int roundabout_right_up_y = 0;     //�һ������Ϲյ�������
int roundabout_right_up_x = 0;     //�һ������Ϲյ������
float left_boundary_slope = 0;     //�����б��
int righty=0;//�һ���˺�ѵ�


/*--------------------������Ԫ��ʶ���-----------------------*/


/*---------------------����Ч���йء�------------------------*/
int useful_line_initial = 0;                             //��ʼ��Ч�У������ն�����
int useful_line_further = 0;                             //��Զ�����У�����Ԫ���ж�
int useful_line = 0;                                     //��ȡ��Ч��
int left_roundabout_useful_line = 0;                     //����Ч��
int right_roundabout_useful_line = 0;                     //�һ���Ч��
int cross_useful_line = 0;                              //ʮ��·����Ч��



/*---------------------����Ч���йء�------------------------*/

/*------------------����ȡ��������ƫ���---------------------*/
float middle_error = 0;                                  //���µĵ�ǰ��������ƫ��
float middle_error_filter = 0;                          //�˲���ĵ�ǰ��������ƫ��
uint8 middle_error_2=0;
uint8 middle_error_last=0;
int error_else=0;
int error_all=0;
void get_error(){error_all=(0.7*middle_error+0.5*(middle_error_2-200));}
/*------------------����ȡ��������ƫ���---------------------*/

//-------------------------------------------------------------------------------------------------------------------
// @brief       ͼ��ʶ��������
// @param       void
// @return  void
// @note        �ڴ˺�����ʵ���˻�ȡ��ֵ��ͼ�����ߣ�����Ԫ��ʶ�𣬼�������ƫ���
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void Image_Recognition()
{
    Get_Binary_Image();     //��ȡ��ֵ��ͼ�񣬰�����ͨ����򷨻�ȡ��̬��ֵ��ʹ�õõ��Ķ�̬��ֵ��ͼ���ֵ����
    //��ͼ����г�������
    findboundary(IMG_MIDDLE - 1, IMG_H - 1, 0); //�ѱ���
    findloseline(IMG_H - 1, USEFUL_FOR_LOSELINE, USEFUL_FOR_LOSELINE);              //�Ѷ���

    Road_Refer_Generate(); //���ɲο�·��

    cross_recog();//ʶ��ʮ��

#if USE_ROUNDABOUT_FSM//״̬����������һ����һ����ֻ��ǰһ��״̬λ�����Żᴥ����һ״̬λ��ʼ��
    left_roundabout_recog_by_FSM();     //ʶ���󻷵�
    right_roundabout_recog_by_FSM();    //ʶ���һ���
#else//��״̬��������ɾ������״̬λ�໥������
    left_roundabout_recog();          //ʶ���󻷵�
    right_roundabout_recog();         //ʶ���һ���
#endif
    turn_recog();                       //ʶ����������ȼ���ʮ�֡�������Ҫ�ͣ�
    useful_line = Dynamic_useful_line();//������Ч��
//    find_brick();//ʶ��·��

    middle_error=Middle_Error()+error_else;//����ƫ��
    middle_error_last=middle_error+60;//�޷��ŵ�����ƫ�������
    get_error();//��ƫ���ȡ����λ����
    detectStraightRoad();//ֱ���б�
    flag_send_get();//��ȡ��Ԫ��״̬λ��������
    find_startline();//ʶ��������
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       ʹ���Զ���ֵ�������ɷ����õ���ֵ����ֵ
// @param       image �ɼ�����ͼ��
// @return      int ��ֵ����ֵ
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
            hist[(int)data[i * MT9V03X_W + j]]++;  //����ͼ����ÿ�ֻҶȼ����صĸ���ni��hist[i]Ϊ�Ҷ�ֵΪi�����ص�ĸ���
        }
    }
    area = MT9V03X_H*MT9V03X_W; //ͼ���������N

    for (int i = 0; i < 256; i++)
    {
        pi_value[i] = (float)hist[i] / area;//ͳ��ͼ����ÿ�ֻҶ�ֵi���ֵĸ���pi�����е�pi_value������Ӧ����1��
        mg = mg + i * pi_value[i];//����ͼ���ƽ���Ҷ�
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
            xitaB[i] = (float)fenzi / fenmu; //��䷽��
            if (xitaB[i] > compare_value)
            {
                compare_value = xitaB[i];
                thresh_value = i;
            }
        }
    }
    return thresh_value;
}
int otsuthreshold_update(uint8 *image)//���ɷ���ֵ�����Ż��棩
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

    /*����ͼ��Ĵ�СΪ1/4ԭͼ��ÿ4����ȡһ�Σ�*/
    for(int i=0;i< MT9V03X_H/4;i++)
    {
        for (int j = 0; j < MT9V03X_W/4; j++)
        {
            hist[(int)data[4 * i * MT9V03X_W + 4*j]]++;  //����ͼ����ÿ�ֻҶȼ����صĸ���ni��hist[i]Ϊ�Ҷ�ֵΪi�����ص�ĸ���
        }
    }
    area = (MT9V03X_H / 4) * (MT9V03X_W / 4); //ͼ���������N
    for (int i = 0; i < 256; i++)
    {
        pi_value[i] = (float)hist[i] / area;//ͳ��ͼ����ÿ�ֻҶ�ֵi���ֵĸ���pi�����е�pi_value������Ӧ����1��
        mg = mg + i * pi_value[i];//����ͼ���ƽ���Ҷ�
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
            xitaB[i] = (float)fenzi / fenmu; //��䷽��
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
            hist[(int)data[i * MT9V03X_W + j]]++;  //����ͼ����ÿ�ֻҶȼ����صĸ���ni��hist[i]Ϊ�Ҷ�ֵΪi�����ص�ĸ���
        }
    }
    area = MT9V03X_H*MT9V03X_W; //ͼ���������N

    for (int i = 0; i < 256; i++)
    {
        pi_value[i] = 1000 * hist[i] / area;//ͳ��ͼ����ÿ�ֻҶ�ֵi���ֵĸ���pi�����е�pi_value������Ӧ����1��,ÿһ��pi������1000
        mg = mg + i * pi_value[i];//����ͼ���ƽ���Ҷȣ�mgҲ����1000��
    }

    for (int i = 0; i < 256; i++)
    {
        p1k = p1k + pi_value[i];   //plkҲ����1000
        if (p1k != 0)
        {
            mk = mk + i * pi_value[i];//mkҲ����1000
            uint64_t fenzi, fenmu;
            fenzi = (mg*p1k / 1000  - mk)*(mg*p1k / 1000 - mk);  // (1000*mg*plk - 1000*mk)^2 = 1000 ^ 2 *(mg*plk - mk)^2
            fenmu = p1k * (1000 - p1k);    //1000*plk * (1000 - 1000*plk) =  1000 * 1000 * plk * (1 - plk) = 1000^2 * plk * (1 - plk)
            xitaB[i] = 1000 *fenzi / fenmu; //��䷽�� (����1000)
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
// @brief       ʹ��ȫ����ֵ�������õ���ֵ����ֵ
// @param       image �ɼ�����ͼ��
// @return      int ��ֵ����ֵ
// Sample usage:    img_thread = IterativeThSegment(mt9v03x_image[0]);
//-------------------------------------------------------------------------------------------------------------------
int IterativeThSegment(uint8 * image)
{

    uint8 * data = image;
    int Binaryzation_Value = 0;
    int T0=0,T1=0,G1=0,G2=0,G1_Count=0,G2_Count=0;

    T0=125; //��ʼ��ֵ
    for (int i = 5; i < IMG_H - 5; i+=2)
    {
        for (int j = 0; j < IMG_W; j+=2)
        {
                if(data[i * IMG_W + j]>T0)
                {
                    G1+=data[i * IMG_W + j];//����ȳ�ʼ��ֵ�󣬹���G1����
                    G1_Count++;
                }
                else
                {
                    G2+=data[i * IMG_W + j];
                    G2_Count++;
                }
        }
    }
    T1=(G1/G1_Count+G2/G2_Count)/2; //ȡ��������ĻҶȾ�ֵ��ƽ��ֵ
    while((T1-T0) > 1 || (T0 - T1) > 1)
    {
        T0=T1; //�Լ�������ķֶ�ֵ�����ʼ��ֵ�����¼���
        G1=0,G2=0,G1_Count=0,G2_Count=0;
        for (int i = 5; i < IMG_H - 5; i+=2)
        {
            for (int j = 0; j < IMG_W; j+=2)
            {
                    if(data[i * IMG_W + j]>T0)
                    {
                        G1+=data[i * IMG_W + j];//����ȳ�ʼ��ֵ�󣬹���G1����
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
//    //�޷�
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
// @brief       ��ȡ��ֵ��ͼ�� ����
// @param       void
// @return  void
// Sample usage:    Get_Binary_Image();
//-------------------------------------------------------------------------------------------------------------------
void Get_Binary_Image(void)
{
    //img_thread = otsuthreshold_integer(mt9v03x_image[0]);//����������ֵ���򷨣�Ч���ϲ������ʱ�����

    img_thread = 1.00*otsuthreshold(mt9v03x_image[0]);//��򷨣�ȷ����ֵ����ֵ���õ�����ֵ����img_thread

    //img_thread = otsuthreshold_update(mt9v03x_image[0]);//���ƵĴ�򷨣�ȷ����ֵ����ֵ���õ�����ֵ����img_thread

    //img_thread = IterativeThSegment(mt9v03x_image[0]);//ȫ����ֵ��������ȷ����ֵ����ֵ���õ�����ֵ����img_thread

    /*��ֵ����ֵ�޷���֮������Ҫ�ټ�*/
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
            //������ֵ����Ϊ��ɫ��255����С����ֵ����Ϊ��ɫ��0��
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
// @brief       ����ֵͳһ���ú���
// @param       array                       Ҫ���������
// @param       value                       ÿ������Ԫ��Ҫ����ֵ
// @param       start                       ��ʼ��
// @param       end                         �յ㣨end>start��
// @return  void
// @note        ˼·����ѡ����Χ�ڱ������飬����Ӧ��ֵ��ΪҪ����ֵ
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void array_set_uniform(int array[], int value, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        array[i] = value;
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       ��С���˷����б��
// @param       direction           ����LEFT_DIR / RIGHT_DIR
// @param       downy               ��ʼ������
// @param       upy                 ��ֹ������
// @return      float               б��
// @note        ����û��FPU��mm32�����ܷ�ʱ�Ͼã�����ʹ��
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
float leastSquareLinearFit(int direction, int downy, int upy)
{
    float k;
    int i, count;
    int num = downy - upy - 1;//���������
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
    if (count >= 0.95 * num)//�ӽ���ֱ
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
// @brief       ���������䣨�߽磩����
// @param   startx                  ���ߵ���ʼ������
// @param       direction               RIGHT_DIR / LEFT_DIR ���ߵķ��򡪡�����RIGHT_DIRΪ���ұߣ�LEFT_DIRΪ�����
// @param       row                         Ҫ����һ��������
// @param   color_change        IMG_BLACK / IMG_WHITE���ڵ��׵����䣨IMG_WHITE�����ǰ׵��ڵ����䣨IMG_BLACK��
// @param       fail_boundary       ���Ҳ������ϵı߽�ʱ�ѱ߽��趨��ֵ
// @param       left                        ���������Ҫ�м���ͬ��ɫ��
// @param       right                       �����ұ���Ҫ�м���ͬ��ɫ��
// @return  int                         �ѵ������еĺ�����
// @note        left��right�����������ѵ��װ׺ںڻ��ǰ׺ڻ��ǰ׺ںڵȣ�����������
//                  fail_boundary��һ��Ӧ�����ӣ��ұ߽�ʱ�����û�з�������������㣬�Ѹ�ֵ��Ϊ119������еı߽��Ϊ119
//                  ˼·������ʼ�㿪ʼ����ѡ���ķ�����������㣬�����ѵ����ߵĺ�����
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
int findchange(int startx, int direction, int row, int color_change, int fail_boundary, int left, int right)
{
    int j, i;
    bool leftachieve = 1;   //�ж�����Ƿ�ﵽ�����������
    bool rightachieve = 1;  //�ж��ұ��Ƿ�ﵽ�����������
    if (direction == RIGHT_DIR)//���ұ���
    {
        for (j = startx; j < IMG_W - right - 1; j++) //���ҵ�������
        {
            leftachieve = 1;
            rightachieve = 1;
            if (Binary_Image[row][j + 1] == color_change)//jΪ����ǰ�ĵ㣬j+1Ϊ�����ĵ�
            {
                for (i = j + 1; i < j + 1 + right; i++)//�ұ�����������right����������ɫ�ĵ�
                {
                    if (Binary_Image[row][i] != color_change)
                    {
                        rightachieve = 0;//���������˳�
                        break;
                    }
                }
                if (!rightachieve)
                {
                    continue;
                }
                else
                {
                    for (i = j; i > j - left; i--)//�ұ���������������£��ж�����Ƿ�������left����color_change��ɫ�෴�ĵ�
                    {
                        if (Binary_Image[row][i] != (IMG_WHITE - color_change))  //color_changeΪ�ڣ���IMG_WHITE - color_change = 255 Ϊ�ף�color_change Ϊ�ף���IMG_WHITE - color_change = 0 Ϊ��
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
                    return j;//����������������ϣ������ҵ��ı߽��
                }
            }
        }
        return fail_boundary;
    }
    else//��ߣ�˼·���ұ�һ��
    {
        for (j = startx; j > left; j--)
        {
            leftachieve = 1;
            rightachieve = 1;
            if (Binary_Image[row][j - 1] == color_change)//jΪ����ǰ�ĵ㣬j-1Ϊ�����ĵ�
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
// @brief       �����ж϶��ߺ���
// @param       direction               RIGHT_DIR / LEFT_DIR  �жϵķ��򡪡�����RIGHT_DIRΪ���ұߣ�LEFT_DIRΪ�����
// @param       arrayfind               ��Ҫ�Ҷ�����������飨����Ԫ��Ϊÿ�еı߽�����꣩
// @param       row                         Ҫ�ڵڼ���Ѱ�Ҷ������
// @return  int                         1Ϊ���ߣ�0Ϊ������
// @note        ʲô�Ƕ��ߡ��������������߽�Ϊͼ��ı߽磨һ����û��ֱ���ѵ����䣬�ʽ�ͼ��߽���Ϊ�����߽磩
//                  ˼·����ĳ���ѵ��߽�ĺ�����Ϊͼ��ı߽磬�򷵻�1
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
int findlose(int direction, int arrayfind[], int row)
{
    if (direction == RIGHT_DIR)
    {
        if (arrayfind[row] == IMG_W - 1 && Binary_Image[row][middle_line[row]] == IMG_WHITE)  //�ұ��ߣ�ע������Ϊ�����������������Ϊ�ڵ㴦Ҳ�ᶪ�ߣ�        //������ʼΪ0�����ֵΪIMG_W-1
        {
            return 1;
        }
    }
    else
    {
        if (arrayfind[row] == 0 && Binary_Image[row][middle_line[row]] == IMG_WHITE)          //����ߣ�ע������Ϊ����
        {
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       ���ߵ�������
// @param       middle_old          ԭ���������е�
// @param       row                         Ҫ�ڵڼ��е���
// @return  int                         ��������е������
// @note
// Sample usage��
//                  middle_line[i - 1] = middleadjust(IMG_MIDDLE, i - 1)
//                  һ������ �ѱ��ߺ�����ȷ��ĳ�������е�ʱ������������е�Ϊ��ɫ����ͼ���е�ҲΪ��ɫ ʱ�����
//-------------------------------------------------------------------------------------------------------------------
int middleadjust(int middle_old, int row)
{
    int adjustedleft = 0;//��߽��
    int adjustedright = 0;//�ұ߽��
    int left_distance = 0;//��ߵ����ľ���
    int right_distance = 0;//�ұߵ����ľ���

    //��middle_old��ʼ������������������������ɫ�㣨��������
    adjustedright = findchange(middle_old, RIGHT_DIR, row, IMG_WHITE, (IMG_W - 1), 1, 2);//���ұ߿ɵ����㣨�Һڵ�������㣬��������
    adjustedleft = findchange(middle_old, LEFT_DIR, row, IMG_WHITE, 0, 2, 1);//����߿ɵ����㣨�Һڵ�������㣩

    if (adjustedright == (IMG_W - 1) && adjustedleft == 0)//�������߶�û���ҵ����Ե����ĵ㣨������Ұ��û��������������ԭֵ
    {
        return middle_old;
    }

    //�����������߷ֱ𾭹����پ�������ѵ�����
    left_distance = middle_old - adjustedleft;
    right_distance = adjustedright - middle_old;

    //ȡ���о����С���Ǹ������߽���Ϊ��������е�
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
// @brief       �����ѱ����Ӻ����������ߵ�����Ѱ�Ҷ��������δʹ�ã�
// @param       now_row                 ��������
// @param       last_middle_point       ��һ���е㣬Ҳ������������ʼ��
// @param       upy                     ���ߵ������У������������ߣ���ֹԽ��
// @return      int                     �����е�
// @note
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
int find_one_boundary(int now_row, int last_middle_point)
{
    //�������ߣ�������������ʼ�㣬ʹ����������ʼ��Ǻ�
    if (Binary_Image[now_row][last_middle_point] == IMG_BLACK)   //������һ�е��е���Ϊ����������ʼ���Ϊ��ɫ��������������ʱ���ѱ�����ʼ����Ϊͼ���е㣨��IMG_MIDDLE��
    {
        if (Binary_Image[now_row][IMG_MIDDLE] == IMG_BLACK)      //ͼ���е�ҲΪ��ɫ��ִ�е����е�ĺ���
        {
            last_middle_point = middleadjust(IMG_MIDDLE, now_row);
        }
        else
        {
            last_middle_point = IMG_MIDDLE; //ͼ���е㲻Ϊ��ɫ������ʼ����Ϊͼ���е�
        }

    }//������ʼ�㲻Ϊ��ɫʱ��ֱ�ӽ���һ�е��е���Ϊ���е���ʼ�㣬�������

    //�ѱ��ߣ�last_middle_pointΪ������ʼ�㣩
    boundary_left[now_row] = findchange(last_middle_point, LEFT_DIR, now_row, IMG_BLACK, 0, 2, 1);           //�������
    boundary_right[now_row] = findchange(last_middle_point, RIGHT_DIR, now_row, IMG_BLACK, (IMG_W - 1), 1, 2); //���ұ���

     //��ȡ���е��е㣬Ϊ��һ�е������ṩ��ʼ��
    middle_line[now_row] = (boundary_left[now_row] + boundary_right[now_row]) / 2;

    //Ѱ�Ҷ�������������еı߽�Ϊͼ��߽磬���߱�־Ϊ1��
   lost_left_flag[now_row] = findlose(LEFT_DIR, boundary_left, now_row);        //Ѱ����߶������
lost_right_flag[now_row] = findlose(RIGHT_DIR, boundary_right, now_row);     //Ѱ���ұ߶������

    return middle_line[now_row];
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       ԭ�ѱ��ߣ���ȷ�����ߣ�����
// @param       firstx                  ��ʼ��x����
// @param       downy                       ��ʼ��y���꣨ͼ��ƫ�·�����ֵ�ϴ�
// @param       upy                         ������y���꣨ͼ��ƫ�Ϸ�����ֵ��С��
// @param       iffindlose          �Ƿ��Ҷ���
// @param       ifadjust                �Ƿ��������
// @return  void
// @note        ���Լ���Ҫ�ķ�ΧѰ�ұ���
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void findboundary(int firstx, int downy, int upy)
{
    array_set_uniform(boundary_left, 0, 0, IMG_H);//�����߽�����
    array_set_uniform(boundary_right, 0, 0, IMG_H);//����ұ߽�����
    array_set_uniform(middle_line,0,0,IMG_H);//������ߺ���������

    array_set_uniform(lost_right_flag, 0, 0, IMG_H);
    array_set_uniform(lost_left_flag, 0, 0, IMG_H);

    middle_line[downy] = firstx;//�涨��ʼ�еĺ����ֻ꣨����ʼ�е���ʼ�������ǹ涨Ϊfirstx�ģ������е���ʼ������Ϊ��һ�е����ߺ�����

    int i;
    for (i = downy; i >= upy; i--)
    {
        boundary_left[i]  = findchange(middle_line[i], LEFT_DIR , i, IMG_BLACK, 0, 1, 1);                         //������ߣ�����ĵ�һ������������ʾ������ʼ����ѣ������Ǹ������ߺ����꣩
        boundary_right[i] = findchange(middle_line[i], RIGHT_DIR, i, IMG_BLACK, (IMG_W - 1), 1, 1);               //���ұ���


        lost_left_flag[i] = findlose(LEFT_DIR, boundary_left, i);  //����i�еı߽�Ϊͼ��߽磬���߱�־Ϊ1        //Ѱ����߶������
        lost_right_flag[i] = findlose(RIGHT_DIR, boundary_right, i);                        //Ѱ���ұ߶������


        middle_line[i] = (boundary_left[i] + boundary_right[i]) / 2;        //���¸��е��е㣬��Ϊi-1�е���ʼ��

        if (i != upy)//ȷ�������������ߺ���������
        {
            if (Binary_Image[i - 1][middle_line[i]] == IMG_BLACK)                  //����i���е���Ϊi-1�е�������ʼ���Ϊ��ɫ��������������ʱ������ʼ����Ϊͼ���е㣨������IMG_MIDDLE��
            {
                if (Binary_Image[i - 1][IMG_MIDDLE] == IMG_BLACK)         //ͼ���е�ҲΪ��ɫ��ִ�е����е�ĺ���
                {
                    middle_line[i - 1] = middleadjust(IMG_MIDDLE, i - 1);
                }
                else
                {
                    middle_line[i - 1] = IMG_MIDDLE; //ͼ���е㲻Ϊ��ɫ���������е���Ϊͼ���е�
                }

            }
            else                                   //������ʼ�㲻Ϊ��ɫʱ��ֱ�ӽ�i�е��е���Ϊi-1�е���ʼ��
            {
                middle_line[i - 1] = middle_line[i];
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       Ѱ�ҵ�һ�ζ����к���
// @param       downy                   ��ʼ��y���꣨ͼ��ƫ�·�����ֵ�ϴ�
// @param       upy                     ������y���꣨ͼ��ƫ�Ϸ�����ֵ��С��
// @param       direction               RIGHT_DIR / LEFT_DIR ����
// @return      int                     �ҵ��ĵ�һ�ζ����е������꣨��ͼ���·���ʼѰ�ҵ��״ζ��ߵ�������-- ��û�ж����򷵻�-1
// @note        ˼·����һ����Χ��Ѱ��lost_right_flag����lost_left_flag�����е�һ�γ���1��Ӧ������ֵ
//              ��һ�������Ƕ��ߵ�
// Sample usage��firstloseline_left = findfirstlose(firstlosedown, firstloseup, LEFT_DIR);
//-------------------------------------------------------------------------------------------------------------------
int findfirstlose(int downy, int upy, int direction)
{
    int i;
    if (direction == RIGHT_DIR)//�ұ�
    {
        for (i = downy; i >= upy; i--)
        {
            if (lost_right_flag[i] == 1 && lost_right_flag[i - 1] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//��ͼ���·������ң��ҵ����߱�־��������Ϊ1�������ߴ�Ϊ��ɫ
            {
                return i;
            }
        }
    }
    else
    {
        for (i = downy; i >= upy; i--)
        {
            if (lost_left_flag[i] == 1 && lost_left_flag[i - 1] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//��ͼ���·������ң��ҵ����߱�־��������Ϊ1�������ߴ�Ϊ��ɫ
            {
                return i;
            }
        }
    }
    return -1;//û�ж��ߣ���ʱ ��һ������ Ϊ��������������Խ�磡����

}
//-------------------------------------------------------------------------------------------------------------------
// @brief       Ѱ�����ն����к���
// @param       firstlosey          ��ʼ��y���꣨ͼ��ƫ�·�����ֵ�ϴ󣩣�Ϊ�Ѿ��ҵ��ĵ�һ�ζ�����
// @param       upy                         ������y���꣨ͼ��ƫ�Ϸ�����ֵ��С��
// @param       direction               RIGHT_DIR / LEFT DIR ����
// @return      int                         �ҵ�����߻����ұ��������һ�ζ����е�������
// @note        ˼·                      �ӵ�һ�ζ��߿�ʼ������������������
//              ���ն������Ƕ��ߵ�
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
int findfinallose(int firstlosey, int upy, int direction)
{
    int i;
    if (direction == RIGHT_DIR)
    {
        i = firstlosey;
        while (lost_right_flag[i] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//�����Ѷ��ߣ���Ҫ��֤�������е����ܵ��ϣ�
        {
            i--;
            if (i < upy)//���ն����в��ܳ�������ֵ
            {
                i++;
                break;
            }
            if (lost_right_flag[i] == 0 && lost_right_flag[i - 1] == 1 && lost_right_flag[i - 2] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)
            {
                i--;
            }//����һ��4����û��֤���������Ե�һ������ǰ�ж���������һ�в����ߣ��������Ϸ������������ж��ߣ���i--��������һ��
        }
        return i + 1;//����һ��4��ȷ�����ն������������Ƕ��ߵ�
    }
    else
    {
        i = firstlosey;
        while (lost_left_flag[i] == 1 && Binary_Image[i][middle_line[i]] == IMG_WHITE)//�����Ѷ��ߣ���Ҫ��֤�������е����ܵ��ϣ�
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
            }//����һ��4����û��֤���������Ե�һ������ǰ�ж���������һ�в����ߣ��������Ϸ������������ж��ߣ���i--��������һ��
        }
        return i + 1;//����һ��4��ȷ�����ն������������Ƕ��ߵ�
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       ���ն����е�������
// @param       finalloseline_init      ԭ���ն�����
// @param       direction               RIGHT_DIR / LEFT DIR ����
// @param       useful_length           ��Ч���ȣ��Ϸ����߶δ��ڴ˲ŵ���
// @return      int                     ����������ն�����
// @note        ˼·                  ��ԭ���ն����������д�ζ��ߣ������ն���������
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
int finalloseline_adjust(int finalloseline_init, int direction, int useful_length)

{int adjust_temp = finalloseline_init;
if (direction == RIGHT_DIR)//�ұ�
{
    for (int j = finalloseline_init - 1; j >= useful_length + USEFUL_FOR_LOSELINE; j--)
    {
        if (lost_right_flag[j] == 1)
        {
            int k = j;                     //��¼��ʼ����
            while (lost_right_flag[j] == 1) //�����Ѷ���
            {
                j--;
                if (j <= USEFUL_FOR_LOSELINE)
                {
                    j = USEFUL_FOR_LOSELINE;
                    break;
                }
            }
            if ((k - j) >= useful_length)//�����ڴ�ζ��ߣ����ն���������
            {
                adjust_temp = j;
                break;
            }
        }
    }
}
else //���
{
    for (int j = finalloseline_init - 1; j >= useful_length + USEFUL_FOR_LOSELINE; j--)
    {
        if (lost_left_flag[j] == 1)
        {
            int k = j;                    //��¼��ʼ����
            while (lost_left_flag[j] == 1) //�����Ѷ���
            {
                j--;
                if (j <= USEFUL_FOR_LOSELINE)
                {
                    j = USEFUL_FOR_LOSELINE;
                    break;
                }
            }
            if ((k - j) >= useful_length)//�����ڴ�ζ��ߣ���Ч������
            {
                adjust_temp = j;
                break;
            }
        }
    }
}
//�ж����ն����е��е��ǲ��ǻ����ܵ��ϣ�����ھ�ȷ������Ϊ��Ч�У�������ڣ�������ж�����һ���Ƿ���������
while (Binary_Image[adjust_temp][middle_line[adjust_temp]] == IMG_BLACK || Binary_Image[adjust_temp + 1][middle_line[adjust_temp + 1]] == IMG_BLACK)
{
    adjust_temp++;
    if (adjust_temp >= finalloseline_init)
    {
        adjust_temp = finalloseline_init;
        break;
    }
}

//������Ҫ����������ԭ��ֵ(��Ҫ�����������ֵһ��С��ԭֵ)
return (adjust_temp <= finalloseline_init ? adjust_temp : finalloseline_init);
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       �����е�������
// @param       direction               RIGHT_DIR / LEFT DIR ����
// @param       useful_length           ��Ч���ȣ��Ϸ����߶δ��ڴ˲ŵ���
// @note        ��ԭ���ն����������д�ζ��ߣ������������·���Ҫ�ࣩ������һ�����к����ն����о���������ʹ���ζ��߳�Ϊһ�ζ���
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void loseline_adjust(int direction, int useful_length)
{
    if (direction == RIGHT_DIR)
    {
        int lose_right_length_1 = 0, lose_right_length_2 = 0;             //�ֱ��ȡ��һ�Ρ��ڶ��Σ�����еĻ��������еĳ���
        int lose_right_first_2 = 0, lose_right_final_2 = 0;               //�ֱ��ȡ�ڶ��ζ����У�����еĻ������������������������
        lose_right_length_1 = firstloseline_right - finalloseline_right;    //��ȡ��һ�ζ����еĳ���

        lose_right_first_2 = findfirstlose(finalloseline_right - 1, useful_line_further, RIGHT_DIR);//finalloseline_right - 1�ز����ߣ������Ǵ���һ�б���----�ö�һ��
        if (lose_right_first_2 != -1)//�ҵ���һ�������ˣ�finalloseline_right - 1 ,useful_line_further]
        {
            lose_right_final_2 = findfinallose(lose_right_first_2 - 1, useful_line_further, RIGHT_DIR);//�����ҵ��ĵ�һ������������//lose_right_first_2 - 1�ض���
            //���ն����з�Χ [lose_right_first_2 - 1,useful_line_further]//���lose_right_first_2���� useful_line_further �����յõ����ն�����Ҳ�� useful_line_further

            lose_right_length_2 = lose_right_first_2 - lose_right_final_2;    //��ȡ�ڶ��ζ��߳���

            if (lose_right_length_2 > lose_right_length_1 || lose_right_length_2 > useful_length)    //�ڶ��ζ��߱ȵ�һ�γ������һ��ֵ
            {
                firstloseline_right = lose_right_first_2;                   //���ڶ��ζ���ʶ��Ϊ��һ�Σ������϶̵ĵ�һ�ζ���
                finalloseline_right = lose_right_final_2;
            }
        }   //����Ϊ�Դ������ζ��ߵ�����Ĵ���ʹ֮��Ϊ��ֻ��һ�ζ��ߡ���
    }
    else
    {
        int lose_left_length_1 = 0, lose_left_length_2 = 0;             //�ֱ��ȡ��һ�Ρ��ڶ��Σ�����еĻ��������еĳ���
        int lose_left_first_2 = 0, lose_left_final_2 = 0;               //�ֱ��ȡ�ڶ��ζ����У�����еĻ������������������������

        lose_left_length_1 = firstloseline_left - finalloseline_left;    //��ȡ��һ�ζ����еĳ���

        lose_left_first_2 = findfirstlose(finalloseline_left - 1, useful_line_further, LEFT_DIR);//finalloseline_right - 1�ز����ߣ������Ǵ���һ�б���----�ö�һ��

        if (lose_left_first_2 != -1)//�ҵ���һ�������ˣ�finalloseline_left - 1 ,useful_line_further]
        {
            lose_left_final_2 = findfinallose(lose_left_first_2 - 1, useful_line_further, LEFT_DIR);//�����ҵ��ĵ�һ������������//lose_left_first_2 - 1�ض���
            //���ն����з�Χ [lose_left_first_2 - 1,useful_line_further]//���lose_left_first_2���� useful_line_further �����յõ����ն�����Ҳ�� useful_line_further

            lose_left_length_2 = lose_left_first_2 - lose_left_final_2;            //��ȡ�ڶ��ζ��߳���

            if (lose_left_length_2 > lose_left_length_1 || lose_left_length_2 > useful_length)       //�ڶ��ζ��߱ȵ�һ�γ������һ��ֵ
            {
                firstloseline_left = lose_left_first_2;                   //���ڶ��ζ���ʶ��Ϊ��һ�Σ������϶̵ĵ�һ�ζ���
                finalloseline_left = lose_left_final_2;
            }
        }//����Ϊ�Դ������ζ��ߵ�����Ĵ���ʹ֮��Ϊ��ֻ��һ�ζ��ߡ���
    }

}

//-------------------------------------------------------------------------------------------------------------------
// @brief       ȷ�������к���
// @param       firstlosedown       �ҵ�һ�ζ���ʱѰ�ҷ�Χ������
// @param       firstloseup         �ҵ�һ�ζ���ʱѰ�ҷ�Χ������
// @param       finalloseup         ����������ն�����ʱѰ�ҷ�Χ������
// @return  void
// @note        ���յõ����������ߵĵ�һ�ζ����У��Լ�ͼ������ն����У������Ƿ��ߵı�־�Լ����ߵ�������Ϊȫ�ֱ����ڽ�������Ԫ�ؼ��ʱҲҪ�õ�
//              ���Ҳ�����һ�ζ����У�����ֵΪ-1�������ն����и�Ϊ-1����ʱ�����б�־Ϊ0����Ϊ�����߽粻���ߣ�
//              ���ҵõ���һ�ζ����еĻ����ϣ������������ն����У���ʱ�����б�־Ϊ1
// Sample usage��findloseline(49,9,9);
//-------------------------------------------------------------------------------------------------------------------
void findloseline(int firstlosedown, int firstloseup, int finalloseup)
{
    //���ñ������־
    firstloseline_left = 0;
    firstloseline_right = 0;
    loserightflag = 0;

    finalloseline_right = 0;
    finalloseline_left = 0;
    loserightflag = 0;

    finalloseline = 0;
    useful_line_initial = 0;

    /******���*******/
    firstloseline_left = findfirstlose(firstlosedown, firstloseup, LEFT_DIR); //�ڸ���Ѱ�ҷ�Χ�����ұߵĵ�һ�ζ�����

    if (firstloseline_left == (-1))//���û�ж���
    {
        loseleftflag = 0;//���߱�־��0
        finalloseline_left = -1;//����һ��4
    }
    else //��һ�ζ������ҵ��˲������ն�����
    {
        loseleftflag = 1;
        finalloseline_left = findfinallose(firstloseline_left, finalloseup, LEFT_DIR);//���ն������ǵ�һ�ζ����еĻ����������ҵģ�������ͼ���Ϸ���

        //�����ն����е������ж��Ƿ��Ϸ��Դ��ڴ�ζ��ߣ�
        if (finalloseline_left > 25)//ƫ��
        {
            loseline_adjust(LEFT_DIR, 10);
            //finalloseline_left = finalloseline_adjust(finalloseline_left, LEFT_DIR, 10);
        }
    }

    /******�ұ�*******/
    firstloseline_right = findfirstlose(firstlosedown, firstloseup, RIGHT_DIR);//�ڸ���Ѱ�ҷ�Χ������ߵĵ�һ�ζ�����

    if (firstloseline_right == -1)//�ұ�û�ж���
    {
        loserightflag = 0;//�Ҷ��߱�־��0
        finalloseline_right = -1;//����һ��4
    }
    else //��һ�ζ������ҵ��˲������ն�����
    {
        loserightflag = 1;
        finalloseline_right = findfinallose(firstloseline_right, finalloseup, RIGHT_DIR);

        //�����ն����е������ж��Ƿ��Ϸ��Դ��ڴ�ζ��ߣ�
        if (finalloseline_right > 25)//ƫ��
        {
            loseline_adjust(RIGHT_DIR, 10);
            //finalloseline_right = finalloseline_adjust(finalloseline_right, RIGHT_DIR, 10);
        }
    }



    /*******ȷ�����ն�����*******/
    if (finalloseline_right >= finalloseline_left) //����ͼ���Ϸ��ֽ����У�ѡһ��ƫ�·���ֵ�ϴ󣩵���Ϊ���ն��ߣ���ĳһ�಻���ߣ�ֵΪ-1��С���ж�����һ������Ҳ��ȡ�Ƿ��ж��ߵģ�
    {
        if ((finalloseline_right >= 45 && firstloseline_left - finalloseline_left >= 5) || (firstloseline_left - finalloseline_left >= 15))//������ѡ�ұߣ������ұ߶�����̫�ͣ�����ߴ��ڴ�ζ��ߣ���ȡ��ߣ���ֹ�ײ����ߵ��²�ʶ������ת��
            finalloseline = finalloseline_left;
        else
            finalloseline = finalloseline_right;

    }
    else
    {
        if ((finalloseline_left >= 45 && firstloseline_right - finalloseline_right >= 5) || (firstloseline_left - finalloseline_left >= 15))//������ѡ��ߣ�������߶�����̫�ͣ����ұߴ��ڴ�ζ��ߣ���ȡ�ұߣ���ֹ�ײ����ߵ��²�ʶ������ת��
            finalloseline = finalloseline_right;
        else
            finalloseline = finalloseline_left;
    }


    if (loseleftflag == 1 && (firstloseline_left < finalloseline))//�����ߵ�һ�����и������ն����У������Ϊ�����ߣ������ǣ�
    {
        loseleftflag = 0;
    }
    if (loserightflag == 1 && firstloseline_right < finalloseline)//����ұߵ�һ�����и������ն����У��ұ���Ϊ�����ߣ������ǣ�
    {
        loserightflag = 0;
    }


    useful_line_further = USEFUL_FOR_LOSELINE;
    //ȷ����Զ��Ч�У�����Ԫ���жϵ���Զ
    for (int i = IMG_H - 1; i >= USEFUL_FOR_LOSELINE; i--)
    {
        if (Binary_Image[i][middle_line[i]] == IMG_WHITE && Binary_Image[i - 1][middle_line[i - 1]] == IMG_BLACK && Binary_Image[i - 2][middle_line[i - 2]] == IMG_BLACK)//����������������Ϊ�ڣ���Ч���������ڴ�
        {
            useful_line_further = i;//����Զ����Ч����
            break;
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
// @brief       ����ͼ��ڵ�ռ�ȣ�����ʮ��·�ڼ�⣩
// @param       left_down               ���¹յ�������
// @param       left_up                 ���Ϲյ�������
// @param       right_down          ���¹յ�������
// @param       right_up                ���¹յ�������
// @return  float                       ͼ��ڵ�ռ��
// @note
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
float cross_bw_judge(int left_down, int left_up, int right_down, int right_up)
{
    int white_piont = 0, black_point = 0, totalpoint = 0;//�ۼƺڵ㡢�׵㡢�����ص�
    int x = 0, y = 0, xmax = 0, ymax = 0;//����������꣬�����������꣬�����Һ����꣬�����º�����

    y = ((left_up >= right_up) ? right_up : left_up);//��������С(ƫ�Ϸ�)���Ϲյ㸳��y

    ymax = ((left_down >= right_down) ? left_down : right_down);//���������(ƫ�·�)���¹յ㸳��ymax

    x = ((boundary_left[left_up] >= boundary_left[left_down])? boundary_left[left_down] : boundary_left[left_up]);//��������С����յ㸳��x

    xmax = ((boundary_right[right_up] >= boundary_right[right_down]) ? boundary_right[right_up]: boundary_right[right_down]);//�����������ҹյ㸳��xmax


    for (int i = x; i < xmax; i++)//������ص�
    {
        for (int j = y; j < ymax; j++)
        {
            if (Binary_Image[j][i] == IMG_BLACK)//���ص�Ϊ��ɫ
                black_point++;
            if (Binary_Image[j][i] == IMG_WHITE)//���ص�Ϊ��ɫ
                white_piont++;
            totalpoint++;//�ۼ������ص�
        }
    }
    float per = 0;
    if (totalpoint != 0)
        per = (float)black_point / totalpoint;//�����ɫ���ص�ռ��
    else
        per = 1;

    return per;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       ����ͼ������˾��κ�����ռ�ȣ�����·��ʶ��
// @param       x1  �����0.5����
// @param       y1����ĸ�
// @note
// return       per��0-1��
//-------------------------------------------------------------------------------------------------------------------
float cross_judge(int x1, int y1)//x1Ϊ����0.5���Ŀ�y1Ϊ���εĸ�
{
    int white_piont = 0, black_point = 0, totalpoint = 0;//�ۼƺڵ㡢�׵㡢�����ص�
    int x = 0, y = 0, xmax = 0, ymax = 0;//����������꣬�����������꣬�����Һ����꣬�����º�����

    y=IMG_H-1-y1;
    ymax=IMG_H-1;
    x=IMG_W/2-x1;
    xmax=IMG_W/2+x1;

    for (int i = x; i < xmax; i++)//������ص�
    {
        for (int j = y; j < ymax; j++)
        {
            if (Binary_Image[j][i] == IMG_BLACK)//���ص�Ϊ��ɫ
                black_point++;
            if (Binary_Image[j][i] == IMG_WHITE)//���ص�Ϊ��ɫ
                white_piont++;
            totalpoint++;//�ۼ������ص�
        }
    }
    float per = 0;
    if (totalpoint != 0)
        per = (float)black_point / totalpoint;//�����ɫ���ص�ռ��
    else
        per = 1;

    return per;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       ���ұ߽粹�ߺ�������Ҫ����ʮ��·�ڲ��ߣ�
// @param       down_y                  �¹յ�������
// @param       down_x                  �¹յ������
// @param       up_y                        �Ϲյ�������
// @param       up_x                        �Ϲյ������
// @param       dir                     RIGHT_DIR / LEFT_DIR    ����
// @return  void
// @note        �����¹յ��ı���дΪһ��ֱ��
// Sample usage��repair_line(down_left, boundary_left[down_left], up_left, boundary_left[up_left], LEFT_DIR);
//-------------------------------------------------------------------------------------------------------------------
void repair_line(int down_y, int down_x, int up_y, int up_x, int dir)
{
    // x = ky + b    �� boundry_left[y] = k * y + b

    float k, b;

    if (up_y - down_y != 0)
    {
        k = (float)(up_x - down_x) / (float)(up_y - down_y);
        b = (float)up_x - k * (float)up_y;
        if (dir == LEFT_DIR)
        {
                for (int i = up_y; i <= down_y; i++)
                        boundary_left[i] = (int)(k * i + b);  //����x = ky + b ����ÿ�е���߽������
        }
        if (dir == RIGHT_DIR)
        {
                for (int i = up_y; i <= down_y; i++)
                        boundary_right[i] = (int)(k * i + b); //����x = ky + b ����ÿ�е��ұ߽������
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       ����������������
// @param       downx                   �¹յ������
// @param       downy                   �¹յ�������
// @param       upx                     �Ϲյ������
// @param       upy                     �Ϲյ�������
// @return  void
// @note
// Sample usage��repair_middline(middle_line[imgheight - 1], (imgheight - 1), boundary_left[finalloseline_left + 1], (finalloseline_left + 1));
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
// @brief       ����ƫ�ƺ���
// @param       downy                   �¹յ�������
// @param       upy                     �Ϲյ�������
// @param       num                     ƫ��������
// @return  void
// @note
// Sample usage��repair_middline(middle_line[imgheight - 1], (imgheight - 1), boundary_left[finalloseline_left + 1], (finalloseline_left + 1));
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
// @brief       �������ұ߽���д���ߺ���
// @param       void
// @return  void
// @note
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void re_midline()
{
    for(int i = 0; i < IMG_H; i++)
        middle_line[i] = (boundary_left[i] + boundary_right[i])/2;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       �ο�·�����ɺ���������·��
// @param       void
// @return      void
// @note        �ڵ������ߺ������ٵ��ô˺���
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void Road_Refer_Generate()
{
    if (cross_full_flag == 0 && cross_half_flag == 0 && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && cross_after_turn_flag == 0
        && left_roundabout_flag == 0 && right_roundabout_flag == 0 )//����Ԫ�ز�����
    {
        int i, count;
        float leftk, rightk;            //б��
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
// @brief       ���ʶ������
// @param       void
// @return  void
// @note        ʶ���������д���ߣ�����Ӧ��־λ
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
void turn_recog()
{
    right_turn_flag = 0;                                                                                                    //��ת���־λ����
    left_turn_flag = 0;                                                                                                     //��ת���־λ����

    if (cross_full_flag == 0 && cross_half_flag == 0 \
        && left_turn_cross_flag == 0 && right_turn_cross_flag == 0 && left_cross_end_frame_flag == false && right_cross_end_frame_flag == false \
        && (left_roundabout_flag == 0 || (left_roundabout_flag == 1 && left_roundabout_in_flag == 1)) \
        && (right_roundabout_flag == 0 || (right_roundabout_flag == 1 && right_roundabout_in_flag)) \


        )
        //����ȫʮ�֡��ϰ�ʮ�ֺ����һ�����ǰ���£��������������������������ڲ���û�в��ߣ�Ҳ����ת�䴦��
    {
        if (loserightflag == 1 /*&& loseleftflag == 0*/)        //�ұ��ж��ߣ��ҵ�һ�����в�Ϊ-1��<=49������Ҫ�����ն����еͣ�      ��ת���ж�                                                                                      //�ұ��ж���      ������ת���ж�
        {
            //����һ��4
            if (firstloseline_right == IMG_H - 1)      //�ұ�����ж���(���ն�����<49)���ж��Ƿ��еڶ��θ����Ķ���
            {
                loseline_adjust(RIGHT_DIR, 8);  //�����е���
            }
            if (finalloseline_right < (IMG_H - 5) && finalloseline_right >= useful_line_further && firstloseline_right - finalloseline_right >= 8/*10*//*6*/)
            {   /* ���ն������޶���45-5֮�䣬�����г���>=10 */

                int leftcount = 0;            //��߽��������Ƽ���

                for (int i = IMG_H - 1; i > IMG_H - 30; i--) //��߽�������������
                {
                    if (boundary_left[i - 1] > boundary_left[i])
                        leftcount++;                                  //��߽������̶���������
                }

                if (leftcount > 15/*10*/)//����һ��4
                {
                    if (Binary_Image[finalloseline_right][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_right - 1][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_right - 2][IMG_MIDDLE] == IMG_BLACK)
                    {
                        right_turn_flag = 1;                          //ʶ������ת�䣨��־λ��1��
                    }
                }

            }

        }
        if (loseleftflag == 1 /*&& loserightflag == 1*/)         //����ж��� �����һ�����в�Ϊ-1��<=49������Ҫ�����ն����е� ��    ��ת���ж�                                                                                     //����ж���      ��ת���ж�
        {


            if (firstloseline_left == IMG_H - 1)      //��ߵ�һ������==49(���ն�����<49)���ж��Ƿ��еڶ��θ����Ķ���
            {
                loseline_adjust(LEFT_DIR, 8);   //�����е���
            }
            if (finalloseline_left < (IMG_H - 5) && finalloseline_left >= USEFUL_FOR_LOSELINE /*����һ��4*/ && firstloseline_left - finalloseline_left >= /*10*/8)
            {   /* �������޶���45-5֮�䣬�����г���>=10 */

                int rightcot = 0;             //�ұ߽����

                //��ת�����ұ߽�������������
                for (int i = IMG_H - 1; i > IMG_H - 30; i--)
                {
                    if (boundary_right[i - 1] < boundary_right[i])
                        rightcot++;                                  //�ұ߽������̶���������
                }
                if (rightcot > 15)
                {
                    if (Binary_Image[finalloseline_left][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_left - 1][IMG_MIDDLE] == IMG_BLACK || Binary_Image[finalloseline_left - 2][IMG_MIDDLE] == IMG_BLACK)
                    {
                        left_turn_flag = 1;                          //ʶ������ת�䣨��־λ��1��
                    }
                }
            }
        }


        //-------------------------------------��ת�䴦��-------------------------------//
        if (right_turn_flag == 1 && left_turn_flag == 0)
        {
#if TURN_PROCESS_WAY
            // ��һ������ת�䴦����
            int temp = 0, temp1 = 0;//�洢����������������ߺ������ֵ����д������
            temp = middle_line[(IMG_H - 1)] - boundary_left[(IMG_H - 1)];
            for (int i = IMG_H - 2; i >= finalloseline_right; i--)/*����һ��4���ӵ����ڶ��м����������ն�����*/
            {
                temp1 = boundary_left[i] + temp;//�൱����������Ϊ��׼������ȷ��������е��е�λ�ã�����ÿһ���е�������ߺ�����ֵ��һ���������е��Ѿ�Խ��ͼ���ұ߽�������
                if (temp1 < IMG_W)
                    middle_line[i] = temp1;
                else    //�е㳬����ͼ���ұ߽磬���������Ҵ�
                    middle_line[i] = IMG_W - 1;
            }
#else //����ֱ�ߴ�ǣ�Ч��һ��
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
        //-------------------------------------��ת�䴦��-------------------------------//
        if (left_turn_flag == 1 && right_turn_flag == 0)
        {
#if TURN_PROCESS_WAY
            //��һ������ת�䴦����
            int temp = 0, temp1 = 0;//�洢�������������ұ��ߺ������ֵ����д������
            temp = boundary_right[(IMG_H - 1)] - middle_line[(IMG_H - 1)];
            for (int i = IMG_H - 2; i >= finalloseline_left; i--)/*����һ��4���ӵ����ڶ��м����������ն�����*/
            {
                temp1 = boundary_right[i] - temp;
                if (temp1 > 0)
                    middle_line[i] = temp1;
                else
                    middle_line[i] = 0;
            }
#else //����ֱ�ߴ�ǣ�Ч��һ��
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
// @brief       ������Ч�к���
// @param       void
// @return      void
// @note
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
u8 Dynamic_useful_line()/*����һ��4*/
{
    u8 useful_line_temp = 0; //��ȡÿһ֡��Ч��ǰ�ȸ�λ����Ϊ��Ч����ʱ����

    //��ת����Ч��
    if (right_turn_flag == 1 && left_turn_flag == 0) //��ת���־λ1 �� ��ת���־λ0
        useful_line_temp = finalloseline_right;           //��Ч��ֻ���ұ����ն����С�����Χ[USEFUL_FOR_LOSELINE(9)��45��

    //��ת����Ч��
    if (left_turn_flag == 1 && right_turn_flag == 0)
        useful_line_temp = finalloseline_left;           //��Ч��ֻ��������ն����С�����Χ[USEFUL_FOR_LOSELINE(9)��45��

    //ʮ����Ч��
    if (cross_useful_line != 0)
        useful_line_temp = cross_useful_line;

    //�󻷵���Ч��START
    if (left_roundabout_useful_line >= useful_line_further && left_roundabout_useful_line < IMG_H - 1)
    {
        useful_line_temp = left_roundabout_useful_line;
    }
    //�󻷵���Ч��END

    //�һ�����Ч��START
    if (right_roundabout_useful_line >= useful_line_further && right_roundabout_useful_line < IMG_H - 1)
    {
        useful_line_temp = right_roundabout_useful_line;
    }
    //�һ�����Ч��END


    if (useful_line_temp == 0)
    {
        //һ���������Ч�еĴ���START
        bool middle_line_mutation = false;//����ͻ��
        for (int i = IMG_H - 1; i >= useful_line_further; i--)
        {
            int judge1 = middle_line[i - 1] - middle_line[i];   //��ȡ��ֵ
            int judge2 = middle_line[i - 2] - middle_line[i];   //��ȡ��ֵ
            if ((judge1 > 10 || judge1 < -10) || (judge2 > 10 || judge2 < -10))//�仯����(-10,10)֮�⣬��˵���ҵ�������ͻ���
            {
                //��ȡ������Ч�� Ϊ �������ֵ����������޶�ƫ��ĵ㣨�������е���Ч�� Ϊ ��Ч����Щ�����е�������ֵ����������޶�ƫ��(10)�������Ͼ���Ч�ˣ�
                useful_line_temp = i;
                middle_line_mutation = true;  //��ȡ����ָ���㣬�˳�ѭ��
                break;
            }
        }
        if (middle_line_mutation == false)//��û�л�ȡ��ָ����
        {
            useful_line_temp = useful_line_further;//��������������Ҳ��������㣬��ֱ��ȡ��Ч�� Ϊ useful_line_further
        }
        //һ���������Ч�еĴ���END

        //��Ч����ʶ��ͼ������У�����Ч�е�ͼ���м�
        if (useful_line_temp == (IMG_H - 1))
            useful_line_temp = IMG_H / 2;
    }

    return useful_line_temp;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       ������������ƫ��
// @param       void
// @return      float   ������������ƫ��
// @note        ���ڲ���ϵͳʱ�������⣬�ڽ���ͼ����Ĺ����г���᲻�ϵر����ȼ����ߵĿ��ƴ��
//              ���Ծ���������ʱ��������ֹ�������ڼ����оͱ����ݵ����������У�������⣡
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------

float Middle_Error()
{
    int i;

    float middle_error_temp = 0;


    /*����ƫ����㷽ʽ*/
    /*����*/
    if(right_roundabout_flag||left_roundabout_flag )
    {
        for (i = (IMG_H - 1); i >= useful_line; i--)
        {
            middle_error_temp += (IMG_MIDDLE - middle_line[i]);  //����ͷ�����ܴ��ھ������ߣ���Ҫ��Ϊ������60
        }
        middle_error_temp = middle_error_temp / (IMG_H  - useful_line); //ÿһ�е�����������ƽ��
    }
    else
    {

        /************���ֶ�Ȩֵ����**************/
        if (useful_line < (IMG_H - 1) && useful_line >= useful_line_further)
        {

            int line_temp = IMG_H - (int)((IMG_H - useful_line) / 2);
            float middle_error_temp1 = 0, middle_error_temp2 = 0;
            //�ȼ����²����������
            for (i = (IMG_H - 1); i >= line_temp; i--)
            {
                middle_error_temp1 += (IMG_MIDDLE - middle_line[i]);  //����ͷ�����ܴ��ھ������ߣ���Ҫ��Ϊ������60
            }
            middle_error_temp1 = middle_error_temp1 / (IMG_H - line_temp);
            //�ȼ����ϲ����������
            for (i = line_temp - 1; i >= useful_line; i--)
            {
                middle_error_temp2 += (IMG_MIDDLE - middle_line[i]);  //����ͷ�����ܴ��ھ������ߣ���Ҫ��Ϊ������60
            }
            middle_error_temp2 = middle_error_temp2 / (line_temp - useful_line);
            //�²���ȨֵΪ0.7���ϲ���ȨֵΪ0.5
           middle_error_temp = (float)0.7 * middle_error_temp1/*�²��֣�������*/ + (float)0.5* middle_error_temp2/*�ϲ��֣���*/;


        }
    }



    /**************����������������ƫ���ϵ��*************/
    /****************��******************/
    switch (Left_Roundabout_State)
    {
    case State3_Roundabout_To_In_3th_Repairline://״̬�����뻷�ұ߽粹��
    {
        if (!left_roundabout_in_change_angle)
            middle_error_temp = middle_error_temp * (float)1.8;//0.6;//��ͨ����
        else
            middle_error_temp = middle_error_temp * (float)1.6/*1.1*/;//ǿ���

    }
    break;
    case State4_Roundabout_In://״̬�ģ��ڲ�����
    {
        middle_error_temp = middle_error_temp * (float)1.0;
    }
    break;
    case State5_Roundabout_To_Out_Repairline:
    {
        //�������
        if (left_roundabout_out_right_repair_line)//�������ұ���ʱ��������ǣ�
        {
            middle_error_temp = middle_error_temp * (float)1.7;
            if(middle_error_temp<35){middle_error_temp=35;}
        }
        else if (left_roundabout_out_left_repair_line)//����������ߣ����������Ľ׶Σ�
        {
            middle_error_temp = middle_error_temp * (float)1.0;
        }
    }
    break;
    default:
        break;

    }
    /****************��******************/
    switch(Right_Roundabout_State)
    {
        case State3_Roundabout_To_In_3th_Repairline://״̬�����뻷�ұ߽粹��
            {
                if (!right_roundabout_in_change_angle)
                    middle_error_temp = middle_error_temp * (float)1.8/*1.5*//*0.6*/;//��ͨ����
                else
                    middle_error_temp = middle_error_temp * (float)1.6/*1.0*/;//ǿ���
            }
            break;
        case State4_Roundabout_In://״̬�ģ��ڲ�����
            {
                middle_error_temp = middle_error_temp * (float)/*0.8*/1.0;
            }
            break;
        case State5_Roundabout_To_Out_Repairline:
            {
                //�������
                if (right_roundabout_out_left_repair_line)//������߽磨������ǣ�
                {
                    middle_error_temp = middle_error_temp * (float)1.7;
                    if(middle_error_temp<-35){middle_error_temp=-35;}


                }
                else if(right_roundabout_out_right_repair_line)//�����ұ߽磨���������Ľ׶Σ�
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

    /***************ƫ��ͻ���޷�*****************/

    /*******************ƫ���޷�*****************/
    if (middle_error_temp > 50)
        middle_error_temp = 50;
    if (middle_error_temp < -50)
        middle_error_temp = -50;

    return middle_error_temp;
}


//-------------------------------------------------------------------------------------------------------------------
        // @brief       �����ߺ���
        // @param       void
        // @return      void
        // @note
        // Sample usage��
        //-------------------------------------------------------------------------------------------------------------------
        int startpoint_count_line = 0;//�������Ҫ�������(ÿһ֡����һ��)
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
                              //��ʼ����������
                      int in_ku_change_NUM = 0;//���ڴ洢�ж��������������
                      for (int i = IMG_H - 5; i > 20; i--)
                      {
                          int in_ku_change = 0;//���ڴ洢ÿһ�кڰ������ص���Ŀ

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
                // @brief       ��־λ��ȡ
                // @param       void
                // @return      void
                // @note
                // Sample usage��
                //-------------------------------------------------------------------------------------------------------------------
      void flag_send_get()
        {        //����1-5
      if( straight_flag ==1){flag_send=8;}//ֱ��

      else if(RIGHT_Roundabout_State_step>0)
          {flag_send=RIGHT_Roundabout_State_step;}
          else if(LEFT_Roundabout_State_step>0)
          {flag_send=LEFT_Roundabout_State_step;}

        else if(left_turn_flag==1){flag_send=9;}//��ת
        else if(right_turn_flag==1){flag_send=10;}//��ת
        else if(cross_full_flag==1||cross_half_flag==1||left_turn_cross_flag == 1||right_turn_cross_flag == 1)
            {flag_send=11;}//ʮ�֣������ڿ�ʼ��ʶ��
        else if(brick_right_flag==1&&judge_2<1){flag_send=6;}//��·��
        else if(brick_left_flag==1&&judge_2<1){flag_send=7;}//��·��
        else if(brick_time_end>0){flag_send=0;}
//        else if(brick_right_flag==1||brick_end_left==1){flag_send=6;}//��·��
//        else if(brick_left_flag==1||brick_end_right==1){flag_send=7;}//��·��
        else if(startline_flag==1){flag_send=12;}//������

        else{flag_send=0;}
        }

//-------------------------------------------------------------------------------------------------------------------
// @brief       ֱ���б���
// @param
// @return
// @note
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
      int straight_flag = 0;
      // ������������ķ������Ϊ����ƫ��
      int calculateMiddleLineVarianceSum() {
          double sum = 0.0;//���ڴ洢������ܺ�
          double mean = 0.0;//���ڴ洢�������ƽ��ֵ
          for (int i = 0; i < useful_line; i++){
              mean += middle_line[i];
          }
          mean /= useful_line;

          for (int i = 0; i < useful_line; i++) {
              sum += (middle_line[i] - mean) * (middle_line[i] - mean);
          }
          return sum;
      }

      // ֱ���б���
    void detectStraightRoad() {
          // ������������ķ������Ϊ����ƫ��
          int middleLineVarianceSum = calculateMiddleLineVarianceSum();
          int continuation_left=0;
          int continuation_right=0;
    for (int i = 5; i < IMG_H-10; i++) {//����ߵ�������
        if(boundary_left[i]>=boundary_left[i+1]||boundary_left[i]>=boundary_left[i+2])
        {
            if(boundary_left[i]-boundary_left[i+1]<=2){continuation_left=1;}
            else{     continuation_left=0;
             break;}
        }}

    for (int i = 5; i < IMG_H-10; i++) {//�б��ߵ�������
        if(boundary_right[i]<=boundary_right[i+1]||boundary_right[i]<=boundary_right[i+2])
        {
            if(boundary_right[i+1]-boundary_right[i]<=1){continuation_right=1;}
            else{     continuation_right=0;break;}

        }
          }
          // ���ݷ�����ж��Ƿ�Ϊֱ��
          if (middleLineVarianceSum <2000&&(firstloseline_left<30&&firstloseline_right<30)//���˲�����
              // ||(finalloseline_left>35||finalloseline_right>35))
                  && cross_full_flag==0&&cross_half_flag==0&&left_turn_cross_flag == 0&&right_turn_cross_flag == 0//
                  && left_roundabout_flag == 0//�ǻ���
                  && right_roundabout_flag == 0//�ǻ���
                  &&right_turn_flag == 0//����ת
                  &&left_turn_flag == 0//����ת
                  &&continuation_right==1//��������
                  &&continuation_left==1//��������
                  &&brick_right_flag==0//��·��
                  &&brick_left_flag==0//��·��
                  ) {
              straight_flag = 1; // ��ֱ��
          } else {
              straight_flag = 0; //����ֱ��
          }
      }
//-------------------------------------------------------------------------------------------------------------------
// @brief      ·��ʶ����
// @param
// @return
// @note
// Sample usage��
//-------------------------------------------------------------------------------------------------------------------
int brick_down_x;//�½ǵ������
int brick_down_y;//�½ǵ�������
int brick_up_x;//�Ͻǵ������
int brick_up_y;//�Ͻǵ�������
int brick_down_left_flag;//��·���½ǵ��־λ
int brick_up_left_flag;//��·���Ͻǵ��־��
int brick_left_flag;//��·�ϱ�־λ
int brick_down_right_flag;//��·���½ǵ��־λ
int brick_up_right_flag;//��·���Ͻǵ��־λ
int brick_right_flag;//��·�ϱ�־λ
int brick_time=0;//·��ʱ��
int brick_end_left=0;//��·�Ͻ�����־λ
int brick_end_right=0;//��·�Ͻ�����־λ
int brick_time_end=0;//·�Ͻ����׶�ʱ��
int judge_2=0;//��ȡ�����˾��κ�ɫ���ص�ռ��

 void find_brick()
 {
        brick_down_x=0;
        brick_down_y=0;
        brick_up_x=0;
        brick_up_y=0;
        judge_2=cross_judge(20,10)*10;//��ΧΪ0-10,0Ϊȫ�ף�10Ϊȫ��

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

     //����·�Ͻǵ�
            for (int i = (IMG_H-1); i >= 1; i--)
                {
                   if ((boundary_left[i] - boundary_left[i + 1] > 6 || boundary_left[i] - boundary_left[i + 2] > 6)/*���������ͻ��*/
                   && boundary_left[i-1] - boundary_left[i] <= 4 && boundary_left[i-2 ] - boundary_left[i] <= 4 /*���ƹյ����Ϸ��������Ĳ��*/
                   )//���½ǵ�
                   {

                       //�жϹյ���Χ�׵����
                           int whitecount_right_point = 0;
                           for (int k = -1; k < 2; k++)
                           {
                               for (int k = -1; k < 2; k++)
                                           {
                                               for (int g = -1; g < 2; g++)
                                               {
                                                   if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_left[i] + g >= 0 && boundary_left[i] + g <= IMG_W - 1)//��ֹ����Խ��
                                                   {
                                                       if (Binary_Image[i + k][boundary_left[i] + g] == IMG_WHITE)
                                                           whitecount_right_point++;
                                                   }
                                               }
                                           }
                           }
                           if (whitecount_right_point >= 4)//�׵�������һ��ֵ
                           {
                               brick_down_x=boundary_left[i];
                                  brick_down_y=i;
                                  brick_down_left_flag=1;
                                  break;
                           }
                     }}
  if(   brick_down_left_flag==1){  for (int i = (IMG_H-1); i >= 1; i--)
    {
     if (   (boundary_left[i] - boundary_left[i -1] >= 1|| boundary_left[i] - boundary_left[i - 2] >= 1)/*���������ͻ��*/
    && boundary_left[i] - boundary_left[i + 1] <= 4 && boundary_left[i +1] - boundary_left[i+2] <= 4 /*���ƹյ����·��������Ĳ��*/
  )//���Ͻǵ�
    {
         //�жϹյ���Χ�׵����
              int whitecount_right_point = 0;
              for (int k = -1; k < 2; k++)
              {
                  for (int k = -1; k < 2; k++)
                              {
                                  for (int g = -1; g < 2; g++)
                                  {
                                      if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_left[i] + g >= 0 && boundary_left[i] + g <= IMG_W - 1)//��ֹ����Խ��
                                      {
                                          if (Binary_Image[i + k][boundary_left[i] + g] == IMG_WHITE)
                                              whitecount_right_point++;
                                      }
                                  }
                              }
              }
              if (whitecount_right_point >= 4)//�׵�������һ��ֵ
              {
                  brick_up_x=boundary_left[i];
                  brick_up_y=i;
                  brick_up_left_flag=1;
                  break;
              }
    }
    }}




     //����·�Ͻǵ�
     for (int i = (IMG_H-1); i >= 1; i--)
     {
         if ((boundary_right[i+1] - boundary_right[i] >5 || boundary_right[i+2] - boundary_right[i ] > 5)/*���������ͻ��*/
             && boundary_right[i] - boundary_right[i-1] <= 4 && boundary_right[i-1] - boundary_right[i-2] <= 4 /*���ƹյ����Ϸ��������Ĳ��*/
         )//���½ǵ�
         {
             //�жϹյ���Χ�׵����
                 int whitecount_right_point = 0;
                 for (int k = -1; k < 2; k++)
                 {
                     for (int k = -1; k < 2; k++)
                                 {
                                     for (int g = -1; g < 2; g++)
                                     {
                                         if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)//��ֹ����Խ��
                                         {
                                             if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                                                 whitecount_right_point++;
                                         }
                                     }
                                 }
                 }
                 if (whitecount_right_point >= 4)//�׵�������һ��ֵ
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
            if (  (boundary_right[i-1] - boundary_right[i] >=1 || boundary_right[i-2] - boundary_right[i] >=1)/*���������ͻ��*/
             && boundary_right[i+1] - boundary_right[i] <= 4 && boundary_right[i +2] - boundary_right[i+1] <= 4 /*���ƹյ����·��������Ĳ��*/
)//���Ͻǵ�
         {
            //�жϹյ���Χ�׵����
            int whitecount_right_point = 0;
            for (int k = -1; k < 2; k++)
            {
             for (int k = -1; k < 2; k++)
             {
                 for (int g = -1; g < 2; g++)
                 {
                     if (i + k >= 0 && i + k <= IMG_H - 1 && boundary_right[i] + g >= 0 && boundary_right[i] + g <= IMG_W - 1)//��ֹ����Խ��
                     {
                         if (Binary_Image[i + k][boundary_right[i] + g] == IMG_WHITE)
                             whitecount_right_point++;
                     }
                 }
             }
            }
            if (whitecount_right_point >= 4)//�׵�������һ��ֵ
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
     //���ߵ���������
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
//����Ϊ����·�ϵ�ʶ��
if(brick_end_left==0&&continuation_right==1&&brick_up_left_flag&&brick_down_left_flag&&brick_down_y-brick_up_y<30
   &&brick_down_y-brick_up_y>5&&boundary_right[brick_down_y]-brick_down_x>2)
    //���¹յ㶼�ҵ����ұ��߾��������ԣ����½ǵ���������С��30�Ҵ���5�����½ǵ���ͬ��������ұ��ߵ�ĺ�������½ǵ�ĺ���������2
{
    for(int i=brick_up_y;i<=brick_down_y-1;i++)
    {  if(boundary_left[i]>=boundary_left[i+1]&&boundary_left[i]-boundary_left[i+1]<2&&boundary_right[i]-boundary_left[i]<=60//ȷ������ߵĵ����ԣ�·��С��60
        &&lost_left_flag[brick_up_y-1]==0&&lost_left_flag[brick_up_y-2]==0&&lost_left_flag[brick_down_y+1]==0&&lost_left_flag[brick_down_y+2]==0//·�ϵ����½ǵ�䲻����
        )
    {
           double judge;//��ȡ��ɫ���ص�ռ��
     judge = cross_bw_judge(brick_down_y, brick_up_y, brick_down_y, brick_up_y);
     if (judge < 0.3)
     {
         brick_time=0;
         brick_left_flag = 1;//��·��ʶ��ɹ�
    }
    }
    }
}
  //����Ϊʶ����·��
     if(brick_end_right==0&&continuation_left==1&&brick_up_right_flag&&brick_down_right_flag&&brick_down_y-brick_up_y<30&&brick_down_y-brick_up_y>5&&brick_down_x-boundary_left[brick_down_y]>2){
         for(int i=brick_up_y;i<=brick_down_y-1;i++)
         {
           if(boundary_right[i]<=boundary_right[i+1]&&boundary_right[i+1]-boundary_right[i]<2&&boundary_right[i]-boundary_left[i]<=60
           &&lost_right_flag[brick_up_y-1]==0&&lost_right_flag[brick_up_y-2]==0&&lost_right_flag[brick_down_y+1]==0&&lost_right_flag[brick_down_y+2]==0
           )
        {
               double judge;//��ȡ��ɫ���ص�ռ��
         judge = cross_bw_judge(brick_down_y, brick_up_y, brick_down_y, brick_up_y);
         if (judge < 0.3)
         {
             brick_right_flag = 1;//��·��ʶ��ɹ�
             brick_time=0;
         } }}}


     //��·�ϵĿ���Ӧ�ԣ����������洬����������������ƿ��Ʒ�ʽ��
  if(brick_left_flag==1){error_else=-15;brick_time++;//ͨ��ֱ��������ƫ��Ļ����ϼ�error_else��ʵ����������ƫ�ƣ���ʱ��ƫ����
  if(judge_2>5){brick_end_left=1;}
  }
     if((brick_time>5&&brick_left_flag==1)||brick_end_left==1){//��ʶ��·��ʱ�ļ�ʱ�����洬��ʱ��Ư5֡��ʱ��
    error_else=0;
    brick_down_left_flag=0;
    brick_up_left_flag=0;
    brick_down_right_flag=0;
    brick_up_right_flag=0;
    brick_left_flag=0;
     brick_right_flag=0;
     brick_time=0;
     brick_end_left=1;}
     if(brick_end_left==1){brick_time_end++;if(judge_2>1&&brick_time_end<10){error_else=45;}else{error_else=0;}}//��judge_2�ж��Ƿ����س��磬�ı�ƫ����ʹ��ͷת��
     if(brick_time_end>20){brick_end_left=0;brick_time_end=0; }//��������

     //��·��
     if(brick_right_flag==1){error_else=15;brick_time++;//ͨ��ֱ��������ƫ��Ļ����ϼ�error_else��ʵ����������ƫ�ƣ���ʱ��ƫ����
     if(judge_2>5){brick_end_right=1;}
     }
          if((brick_time>5&&brick_right_flag==1)||brick_end_right==1){//��ʶ��·��ʱ�ļ�ʱ�����洬��ʱ��Ư5֡��ʱ��
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
          if(brick_end_right==1){brick_time_end++;if(judge_2>1&&brick_time_end<10){error_else=-45;}else{error_else=0;}}//��judge_2�ж��Ƿ����س��磬�ı�ƫ����ʹ��ͷת��
          if(brick_time_end>20){brick_end_right=0;brick_time_end=0;}//��������

        }}
