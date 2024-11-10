################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_adc.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_bkp.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_can.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_crc.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dac.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dbgmcu.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dma.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dvp.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_eth.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_exti.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_flash.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_fsmc.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_gpio.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_i2c.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_iwdg.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_opa.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_pwr.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_rcc.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_rng.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_rtc.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_sdio.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_spi.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_tim.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_usart.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_usbotg_device.c \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_wwdg.c 

OBJS += \
./sdk/Peripheral/ch32v30x_adc.o \
./sdk/Peripheral/ch32v30x_bkp.o \
./sdk/Peripheral/ch32v30x_can.o \
./sdk/Peripheral/ch32v30x_crc.o \
./sdk/Peripheral/ch32v30x_dac.o \
./sdk/Peripheral/ch32v30x_dbgmcu.o \
./sdk/Peripheral/ch32v30x_dma.o \
./sdk/Peripheral/ch32v30x_dvp.o \
./sdk/Peripheral/ch32v30x_eth.o \
./sdk/Peripheral/ch32v30x_exti.o \
./sdk/Peripheral/ch32v30x_flash.o \
./sdk/Peripheral/ch32v30x_fsmc.o \
./sdk/Peripheral/ch32v30x_gpio.o \
./sdk/Peripheral/ch32v30x_i2c.o \
./sdk/Peripheral/ch32v30x_iwdg.o \
./sdk/Peripheral/ch32v30x_opa.o \
./sdk/Peripheral/ch32v30x_pwr.o \
./sdk/Peripheral/ch32v30x_rcc.o \
./sdk/Peripheral/ch32v30x_rng.o \
./sdk/Peripheral/ch32v30x_rtc.o \
./sdk/Peripheral/ch32v30x_sdio.o \
./sdk/Peripheral/ch32v30x_spi.o \
./sdk/Peripheral/ch32v30x_tim.o \
./sdk/Peripheral/ch32v30x_usart.o \
./sdk/Peripheral/ch32v30x_usbotg_device.o \
./sdk/Peripheral/ch32v30x_wwdg.o 

C_DEPS += \
./sdk/Peripheral/ch32v30x_adc.d \
./sdk/Peripheral/ch32v30x_bkp.d \
./sdk/Peripheral/ch32v30x_can.d \
./sdk/Peripheral/ch32v30x_crc.d \
./sdk/Peripheral/ch32v30x_dac.d \
./sdk/Peripheral/ch32v30x_dbgmcu.d \
./sdk/Peripheral/ch32v30x_dma.d \
./sdk/Peripheral/ch32v30x_dvp.d \
./sdk/Peripheral/ch32v30x_eth.d \
./sdk/Peripheral/ch32v30x_exti.d \
./sdk/Peripheral/ch32v30x_flash.d \
./sdk/Peripheral/ch32v30x_fsmc.d \
./sdk/Peripheral/ch32v30x_gpio.d \
./sdk/Peripheral/ch32v30x_i2c.d \
./sdk/Peripheral/ch32v30x_iwdg.d \
./sdk/Peripheral/ch32v30x_opa.d \
./sdk/Peripheral/ch32v30x_pwr.d \
./sdk/Peripheral/ch32v30x_rcc.d \
./sdk/Peripheral/ch32v30x_rng.d \
./sdk/Peripheral/ch32v30x_rtc.d \
./sdk/Peripheral/ch32v30x_sdio.d \
./sdk/Peripheral/ch32v30x_spi.d \
./sdk/Peripheral/ch32v30x_tim.d \
./sdk/Peripheral/ch32v30x_usart.d \
./sdk/Peripheral/ch32v30x_usbotg_device.d \
./sdk/Peripheral/ch32v30x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Peripheral/ch32v30x_adc.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_bkp.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_bkp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_can.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_can.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_crc.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_crc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_dac.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dac.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_dbgmcu.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dbgmcu.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_dma.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dma.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_dvp.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_eth.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_eth.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_exti.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_flash.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_fsmc.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_fsmc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_gpio.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_i2c.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_i2c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_iwdg.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_iwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_opa.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_opa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_pwr.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_pwr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_rcc.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_rcc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_rng.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_rng.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_rtc.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_rtc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_sdio.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_sdio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_spi.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_tim.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_tim.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_usart.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_usart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_usbotg_device.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_usbotg_device.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Peripheral/ch32v30x_wwdg.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Peripheral/ch32v30x_wwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

