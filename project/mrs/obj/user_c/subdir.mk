################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/����stuff/carcode/�������߷�xy/project/user/src/isr.c \
D:/����stuff/carcode/�������߷�xy/project/user/src/main000.c 

OBJS += \
./user_c/isr.o \
./user_c/main000.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main000.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: D:/����stuff/carcode/�������߷�xy/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main000.o: D:/����stuff/carcode/�������߷�xy/project/user/src/main000.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����stuff\carcode\�������߷�xy\Libraries\doc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_components" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Core" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Ld" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Peripheral" -I"D:\����stuff\carcode\�������߷�xy\libraries\sdk\Startup" -I"D:\����stuff\carcode\�������߷�xy\project\user\inc" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_common" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_device" -I"D:\����stuff\carcode\�������߷�xy\project\code" -I"D:\����stuff\carcode\�������߷�xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

