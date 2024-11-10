#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "servo.h"
#include "uart.h"
#include "encoder.h"
#include "pid.h"
#include "control.h"
#include "motor.h"
#include "zf_device_mt9v03x_dvp.h"
//左侧编码器---A0 A1
//右侧编码器---D12，D13
//舵机--- C6

//初始化所有外设


void all_init()
{

    pit_ms_init(TIM5_PIT, 1);                                                  // 初始化 PIT_CH0 为周期中断 1ms 周期
    interrupt_set_priority(TIM5_IRQn, 0);                                    // 设置 PIT1 对周期中断的中断优先级为 0


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
       mt9v03x_init();//摄像头初始化
       Image_CompressInit();
    data_init();



}




