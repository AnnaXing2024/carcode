################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: D:/车队stuff/carcode/左右搜线法xy/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

