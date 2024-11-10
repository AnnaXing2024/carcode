/*
 * show_send.c
 *
 *  Created on: 2024年6月12日
 *      Author: 86139
 */
#include "zf_common_headfile.h"
#define IPCH MT9V03X_H // 上位机显示图像高度
#define IPCW MT9V03X_W // 上位机显示图像宽度
#define RED 1
#define BLUE 2
#define YELLOW 3
#define GREEN 4
#define IPS200_TYPE     (IPS200_TYPE_PARALLEL8)                                 // 双排排针 并口两寸屏 这里宏定义填写 IPS200_TYPE_PARALLEL8

float Mh = MT9V03X_H;
float Lh = IPCH;
float Mw = MT9V03X_W;
float Lw = IPCW;

uint8 Image_Use[IPCH][IPCW];
//将图像压缩到上位机的尺寸
void Compressimage()
{
  int i, j, row, line;
  const float div_h = Mh / Lh, div_w = Mw / Lw;
  for (i = 0; i < IPCH; i++)
  {
    row = i * div_h + 0.5;
    for (j = 0; j < IPCW; j++)
    {
      line = j * div_w + 0.5;
Image_Use[i][j] = mt9v03x_image[row][line];//灰度
//  Image_Use[i][j] = Binary_Image[row][line];//二值

    }
  }
}

void show()
{
 put_int32(0,error_all);
 put_int32(1,judge_2);
put_int32(2,flag_send);
put_int32(3,brick_time);
put_int32(4,state_continue_frame_count);
put_int32(5,right_roundabout_to_out_flag_count);
put_int32(6,left_roundabout_to_out_flag_count);
put_int32(7,error_else);
sendline_clear(swj_BLACK,IPCW,IPCH);//清屏 背景黑色
sendline_type(4,(pico_uint8 *)middle_line,IMG_H,4);
sendline_type(2,(pico_uint8 *)boundary_right,IMG_H,4);
sendline_type(2,(pico_uint8 *)boundary_left,IMG_H,4);
//sendline_type(4,(pico_uint8 *)Road_Refer_Left,IMG_H,4);
//sendline_type(2,(pico_uint8 *)Road_Refer_Right,IMG_H,4);
////右环岛
//sendpoint(swj_YELLOW,roundabout_right_down_x,roundabout_right_down_y,swj_point_type3);//下拐点
//sendpoint(swj_GREEN,roundabout_right_up_x,roundabout_right_up_y,swj_point_type3);//上拐点
////左环岛
//sendpoint(swj_YELLOW,roundabout_left_down_x,roundabout_left_down_y,swj_point_type3);//下拐点
//sendpoint(swj_GREEN,roundabout_left_up_x,roundabout_left_up_y,swj_point_type3);//上拐点
//路障
sendpoint(swj_YELLOW,brick_down_x,brick_down_y,swj_point_type3);//下拐点
sendpoint(swj_GREEN,brick_up_x,brick_up_y,swj_point_type3);//上拐点

//sendpoint(swj_ORANGE,10,firstloseline_left,swj_point_type9); //左边第一次丢线行
//sendpoint(swj_ORANGE,10,firstloseline_right,swj_point_type9);//右边第一次丢线行
//sendpoint(swj_ORANGE,10,finalloseline_right,swj_point_type9);//右边最终丢线行
//sendpoint(swj_ORANGE,10,finalloseline_left,swj_point_type9);  //左边最终丢线行
sendpoint(swj_ORANGE,10,finalloseline,swj_point_type9);    //最终有效行
sendimg((pico_uint8 *)Binary_Image, IPCW,IPCH); // 发送图像

//sendimg((pico_uint8 *)mt9v03x_image, IPCW,IPCH); // 发送图像

if(show_flag==255){
ips114_show_gray_image(0, 0, Binary_Image[0], MT9V03X_W, MT9V03X_H, 240, 100, 0);//屏幕显示
   // ips114_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 240, 100, 0);//屏幕显示
for(int i=0;i<MT9V03X_H*2;i++)
{
if(middle_line[i/2]>5&&middle_line[i/2]<115){
ips114_draw_point(middle_line[i/2]*2, i, RGB565_RED);
ips114_draw_point(middle_line[i/2]*2+1, i, RGB565_RED);
ips114_draw_point(middle_line[i/2]*2-1, i, RGB565_RED);
}
if(boundary_left[i/2]>5&&boundary_left[i/2]<115){
ips114_draw_point(boundary_left[i/2]*2, i, RGB565_GREEN);
ips114_draw_point(boundary_left[i/2]*2+1, i, RGB565_GREEN);
ips114_draw_point(boundary_left[i/2]*2+2, i, RGB565_GREEN);
}
if(boundary_left[i/2]>5&&boundary_left[i/2]<115){
ips114_draw_point(boundary_right[i/2]*2, i, RGB565_GREEN);
ips114_draw_point(boundary_right[i/2]*2-1, i, RGB565_GREEN);
ips114_draw_point(boundary_right[i/2]*2-2, i, RGB565_GREEN);
}
}
}
if(show_flag==188)
{}
}
void send()
{
    uart_write_byte(UART_6,middle_error_last);
uart_write_byte(UART_6,middle_error_2);
uart_write_byte(UART_4,flag_send);
//uart_write_byte(UART_4,middle_error_last);

}
