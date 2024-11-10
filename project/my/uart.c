/*
 * uart.c
 *
 *  Created on: 2024��10��23��
 *      Author: 27384
 */
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "uart.h"
#include "ch32v30x_dma.h"
#include "ch32v30x_misc.h"



fifo_struct uart_data_fifo;
uint8 uart_get_data[64];                                                  // ���ڽ������ݻ�����
uint8 fifo_get_data[64];                                                  // fifo �������������
uint8 get_data = 0;                                                       // �������ݱ���
uint32 fifo_data_count = 0;                                                // fifo ���ݸ���

uint32_t dma_rxbuffer[50];

//���գ���dma��FIFO
void usart_init()
{

    fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // ��ʼ�� fifo ���ػ�����
    uart_init(UART_2, 115200, UART2_MAP1_TX_D5, UART2_MAP1_RX_D6);             // ��ʼ��������ģ�������� �������������ģʽ
    uart_rx_interrupt(UART_2, ZF_ENABLE);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    interrupt_set_priority(USART2_IRQn, (0<<5) || 1);                         // ���ö�Ӧ UART_INDEX ���ж���ռ���ȼ�0�������ȼ�1

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

//    uart_write_string(UART_2, "init");                     // ���������Ϣ
    USART_Cmd(USART2, ENABLE);

}

void dma_init()
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    DMA_DeInit(DMA1_Channel6);                                              // DMA1ͨ��6����
    DMA_InitTypeDef DMA_InitStructure;                                      //����ṹ�����
    DMA_InitStructure.DMA_BufferSize=sizeof(dma_rxbuffer)/sizeof(*(dma_rxbuffer));// ���ݴ�С
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;// ���赽�ڴ�
    DMA_InitStructure.DMA_M2M=DMA_M2M_Disable; // ���赽�ڴ�
    DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)dma_rxbuffer;// �ڴ����ݻ�������ַ
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;// �ڴ����ݴ�С
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;   // �ڴ��ַ����
    DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;  // ����ģʽ����ѭ��
    DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)&USART2->DATAR;;  // �������ݼĴ�����ַ
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  // �������ݴ�С
    DMA_InitStructure.DMA_PeripheralInc= DMA_PeripheralInc_Disable;  // �����ַ������
    DMA_InitStructure.DMA_Priority= DMA_Priority_VeryHigh;  // ���ȼ��е�
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);
    DMA_SetCurrDataCounter(DMA1_Channel6,3);  // ��������DMA������

    DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);


    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
//
    DMA_Cmd(DMA1_Channel6, ENABLE); /* USART2 Rx */
    USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);//ʹ�ܽ���ת��
    uart_write_string(UART_2, "dmainit");                     // ���������Ϣ



}


void usart_receive()
{
    fifo_data_count = fifo_used(&uart_data_fifo);                           // �鿴 fifo �Ƿ�������
   if(fifo_data_count != 0)                                                // ��ȡ��������
   {
   //                    tft180_show_string(1, 100, "!= 0");
      fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // �� fifo �����ݶ�������� fifo ���صĻ���
      uart_write_string(UART_2, "UART get data:");                     // ���������Ϣ
      uart_write_buffer(UART_2, fifo_get_data, fifo_data_count);       // ����ȡ�������ݷ��ͳ�ȥ
      uart_write_string(UART_2, "\r\n");                               // ���������Ϣ
   }


}

void uart_rx_interrupt_handler()
{
//
//           uart_write_string(UART_2, "uart_rx_interrupt in");                     // ���������Ϣ


        uart_query_byte(UART_2, &get_data);                                     // �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
        fifo_write_buffer(&uart_data_fifo, &get_data, 1);                           // ������д�� fifo ��
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
//    DMA_Cmd(DMA1_Channel6, DISABLE);  // �ر�DMA1ͨ��6
//    uint16_t len=  DMA_GetCurrDataCounter(DMA1_Channel6);
//
//  // ��ӵ������
//  uart_write_string(UART_2, "Received length: ");
//  uart_write_string(UART_2,(uint8 *) len); // ������ճ���
//
//  for (int i = 0; i < len; i++)
//  {
//      uart_write_byte(UART_2, dma_rxbuffer[i]); // ����ȡ�������ݷ��ͳ�ȥ
//  }
//
//  DMA_SetCurrDataCounter(DMA1_Channel6, 3);  // ��������DMA������
//  DMA_Cmd(DMA1_Channel6, ENABLE);  // ����DMA1ͨ��6
//  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);  // �������ڽ����ж��Լ�����������
//
//
//
//}
//���������뻷�λ�����


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
//    if (DMA_GetITStatus(DMA1_IT_TC6)) // ��� DMA ����ж�
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
//         DMA_Cmd(DMA1_Channel6, DISABLE); // �Ƚ��� DMA
//DMA_SetCurrDataCounter(DMA1_Channel6,3);  // ��������DMA������
// DMA_Cmd(DMA1_Channel6, ENABLE); // ������������
//        DMA_ClearITPendingBit(DMA1_IT_TC6); // ����жϱ�־
//    }
//}
