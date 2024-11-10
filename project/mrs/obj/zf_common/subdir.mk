################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_clock.c \
D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_debug.c \
D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_fifo.c \
D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_font.c \
D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_function.c \
D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: D:/����stuff/carcode/�������߷�xy/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

