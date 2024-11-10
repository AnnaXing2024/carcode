
/*********************************************************************************************************************
 * CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
 * Copyright (c) 2022 SEEKFREE ��ɿƼ�
 *
 * ���ļ���CH32V307VCT6 ��Դ���һ����
 *
 * CH32V307VCT6 ��Դ�� ��������
 * �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
 * �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
 *
 * ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
 * ����û�������������Ի��ʺ��ض���;�ı�֤
 * ����ϸ����μ� GPL
 *
 * ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
 * ���û�У������<https://www.gnu.org/licenses/>
 *
 * ����ע����
 * ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
 * �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
 * ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
 * ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
 *
 * �ļ�����          main
 * ��˾����          �ɶ���ɿƼ����޹�˾
 * �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
 * ��������          MounRiver Studio V1.8.1
 * ����ƽ̨          CH32V307VCT6
 * ��������          https://seekfree.taobao.com/
 *

 ********************************************************************************************************************/

#include "zf_common_headfile.h"
#include <stdint.h>
#include <stdbool.h>
uint8_t exposure = 0;
uint8_t Rx_flag = 0;
uint8_t show_flag = 255;
float mid_error_out = 0;

int main(void)
{
    clock_init(SYSTEM_CLOCK_120M); // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                  // ��ʼ��Ĭ�� Debug UART

  // �˴���д�û����� ���������ʼ�������

    tft180_set_dir(TFT180_CROSSWISE);    // ��Ҫ�Ⱥ��� ��Ȼ��ʾ����
    tft180_init();
    all_init();

    while(1)
    {
        if(mt9v03x_init())
            tft180_show_string(0, 16, "mt9v03x reinit.");
        else
            break;
        system_delay_ms(1000);                                                  // ���Ʊ�ʾ�쳣
    } // ��ʼ������ͷ

    while (1){
        if (mt9v03x_finish_flag == 1){

            Image_Recognition();

            mid_error_out = middle_error;

            tft180_show_gray_image(0, 0, (const uint8 *)Binary_Image, MT9V03X_W, MT9V03X_H,MT9V03X_W,MT9V03X_H,img_thread);

            mt9v03x_finish_flag = 0;
        }

        TaskProcess();
    }
}
