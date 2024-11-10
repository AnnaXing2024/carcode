/*
 * uart.c
 *
 *  Created on: 2024年10月23日
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "uart.h"
#include "ch32v30x_dma.h"
#include "ch32v30x_misc.h"



fifo_struct uart_data_fifo;
uint8 uart_get_data[64];                                                  // 串口接收数据缓冲区
uint8 fifo_get_data[64];                                                  // fifo 输出读出缓冲区
uint8 get_data = 0;                                                       // 接收数据变量
uint32 fifo_data_count = 0;                                                // fifo 数据个数

uint32_t dma_rxbuffer[50];

//接收：先dma后FIFO
void usart_init()
{

    fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // 初始化 fifo 挂载缓冲区
    uart_init(UART_2, 115200, UART2_MAP1_TX_D5, UART2_MAP1_RX_D6);             // 初始化编码器模块与引脚 正交解码编码器模式
    uart_rx_interrupt(UART_2, ZF_ENABLE);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    interrupt_set_priority(USART2_IRQn, (0<<5) || 1);                         // 设置对应 UART_INDEX 的中断抢占优先级0，子优先级1

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

//    uart_write_string(UART_2, "init");                     // 输出测试信息
    USART_Cmd(USART2, ENABLE);

}

void dma_init()
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    DMA_DeInit(DMA1_Channel6);                                              // DMA1通道6配置
    DMA_InitTypeDef DMA_InitStructure;                                      //定义结构体变量
    DMA_InitStructure.DMA_BufferSize=sizeof(dma_rxbuffer)/sizeof(*(dma_rxbuffer));// 数据大小
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;// 外设到内存
    DMA_InitStructure.DMA_M2M=DMA_M2M_Disable; // 外设到内存
    DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)dma_rxbuffer;// 内存数据缓冲区地址
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;// 内存数据大小
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;   // 内存地址增加
    DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;  // 正常模式，非循环
    DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)&USART2->DATAR;;  // 外设数据寄存器地址
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  // 外设数据大小
    DMA_InitStructure.DMA_PeripheralInc= DMA_PeripheralInc_Disable;  // 外设地址不增加
    DMA_InitStructure.DMA_Priority= DMA_Priority_VeryHigh;  // 优先级中等
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);
    DMA_SetCurrDataCounter(DMA1_Channel6,3);  // 重新设置DMA计数器

    DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);


    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
//
    DMA_Cmd(DMA1_Channel6, ENABLE); /* USART2 Rx */
    USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);//使能接收转运
    uart_write_string(UART_2, "dmainit");                     // 输出测试信息



}


void usart_receive()
{
    fifo_data_count = fifo_used(&uart_data_fifo);                           // 查看 fifo 是否有数据
   if(fifo_data_count != 0)                                                // 读取到数据了
   {
   //                    tft180_show_string(1, 100, "!= 0");
      fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // 将 fifo 中数据读出并清空 fifo 挂载的缓冲
      uart_write_string(UART_2, "UART get data:");                     // 输出测试信息
      uart_write_buffer(UART_2, fifo_get_data, fifo_data_count);       // 将读取到的数据发送出去
      uart_write_string(UART_2, "\r\n");                               // 输出测试信息
   }


}

void uart_rx_interrupt_handler()
{
//
//           uart_write_string(UART_2, "uart_rx_interrupt in");                     // 输出测试信息


        uart_query_byte(UART_2, &get_data);                                     // 接收数据 查询式 有数据会返回 TRUE 没有数据会返回 FALSE
        fifo_write_buffer(&uart_data_fifo, &get_data, 1);                           // 将数据写入 fifo 中
//
//        for(int i=50;i>0;i--)
//        { usart_receive();}



}


//void DMA1_Channel6_IRQHandler()
//{
//    if (DMA_GetFlagStatus(DMA1_FLAG_TC6) != RESET)
//    {
////        extern void DMA1_6_IRQHandler(void);
////        DMA1_6_IRQHandler();
//    }
//
//}

//void DMA1_6_IRQHandler()
//{
//    uart_write_string(UART_2, "DMA1_Channel6_IRQHandler in");
//    DMA_Cmd(DMA1_Channel6, DISABLE);  // 关闭DMA1通道6
//    uint16_t len=  DMA_GetCurrDataCounter(DMA1_Channel6);
//
//  // 添加调试输出
//  uart_write_string(UART_2, "Received length: ");
//  uart_write_string(UART_2,(uint8 *) len); // 输出接收长度
//
//  for (int i = 0; i < len; i++)
//  {
//      uart_write_byte(UART_2, dma_rxbuffer[i]); // 将读取到的数据发送出去
//  }
//
//  DMA_SetCurrDataCounter(DMA1_Channel6, 3);  // 重新设置DMA计数器
//  DMA_Cmd(DMA1_Channel6, ENABLE);  // 启动DMA1通道6
//  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);  // 开启串口接受中断以继续接收数据
//
//
//
//}
//将数据推入环形缓冲区


//void uart_rx_interrupt_handler(void)
//{
//
//        // IDLE
//
//
//
//
//}
////
/////*********************************************************************
//// * @fn      DMA1_Channel5_IRQHandler
//// *
//// * @brief   This function handles DMA1 Channel 6 global interrupt request.
//// *
//// * @return  none
//// */
//void DMA1_Channel6_IRQHandler(void)
//{
//    if (DMA_GetITStatus(DMA1_IT_TC6)) // 检查 DMA 完成中断
//    {
//        uint16 i;
//       uart_write_string(UART_2, "DMA1_Channel6_IRQHandler\n");
//
//
//
//
//        i=DMA_GetCurrDataCounter(DMA1_Channel6);
//
////         uart_write_string(UART_2, "get");
//         uart_write_byte(UART_2, i);
//
//         DMA_Cmd(DMA1_Channel6, DISABLE); // 先禁用 DMA
//DMA_SetCurrDataCounter(DMA1_Channel6,3);  // 重新设置DMA计数器
// DMA_Cmd(DMA1_Channel6, ENABLE); // 继续接收数据
//        DMA_ClearITPendingBit(DMA1_IT_TC6); // 清除中断标志
//    }
//}
