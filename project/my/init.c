#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "servo.h"
#include "uart.h"
#include "encoder.h"
#include "pid.h"
#include "control.h"
#include "motor.h"
#include "zf_device_mt9v03x_dvp.h"
//��������---A0 A1
//�Ҳ������---D12��D13
//���--- C6

//��ʼ����������


void all_init()
{

    pit_ms_init(TIM5_PIT, 1);                                                  // ��ʼ�� PIT_CH0 Ϊ�����ж� 1ms ����
    interrupt_set_priority(TIM5_IRQn, 0);                                    // ���� PIT1 �������жϵ��ж����ȼ�Ϊ 0


    #if(USE_ENCODER)
    Encoder_init();

    #endif
    #if(USE_SERVO)
        servo_init();

    #endif
    #if(USE_UART)
        usart_init();

    #endif
    #if(USE_DMA)
        dma_init();

    #endif
    #if(USE_TFT180)
        tft180_init();
        tft180_clear();

    #endif
    #if(USE_KALMAN)
        Kalman_Init();

    #endif
    #if(USE_MOTOR)

       Motor_init();

   #endif

       if(!mt9v03x_init())
       {
           gpio_init(C10, GPO, 1, GPIO_PIN_CONFIG);
       }
       mt9v03x_init();//����ͷ��ʼ��
       Image_CompressInit();
    data_init();



}




