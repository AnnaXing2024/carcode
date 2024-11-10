
/*********************************************************************************************************************
 * CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
 * Copyright (c) 2022 SEEKFREE 逐飞科技
 *
 * 本文件是CH32V307VCT6 开源库的一部分
 *
 * CH32V307VCT6 开源库 是免费软件
 * 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
 * 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
 *
 * 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
 * 甚至没有隐含的适销性或适合特定用途的保证
 * 更多细节请参见 GPL
 *
 * 您应该在收到本开源库的同时收到一份 GPL 的副本
 * 如果没有，请参阅<https://www.gnu.org/licenses/>
 *
 * 额外注明：
 * 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
 * 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
 * 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
 * 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
 *
 * 文件名称          main
 * 公司名称          成都逐飞科技有限公司
 * 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
 * 开发环境          MounRiver Studio V1.8.1
 * 适用平台          CH32V307VCT6
 * 店铺链接          https://seekfree.taobao.com/
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
    clock_init(SYSTEM_CLOCK_120M); // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                  // 初始化默认 Debug UART

  // 此处编写用户代码 例如外设初始化代码等

    tft180_set_dir(TFT180_CROSSWISE);    // 需要先横屏 不然显示不下
    tft180_init();
    all_init();

    while(1)
    {
        if(mt9v03x_init())
            tft180_show_string(0, 16, "mt9v03x reinit.");
        else
            break;
        system_delay_ms(1000);                                                  // 闪灯表示异常
    } // 初始化摄像头

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
