################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/车队stuff/carcode/左右搜线法xy/project/code/circle.c \
D:/车队stuff/carcode/左右搜线法xy/project/code/cross.c \
D:/车队stuff/carcode/左右搜线法xy/project/code/img.c \
D:/车队stuff/carcode/左右搜线法xy/project/code/pico_gy.c \
D:/车队stuff/carcode/左右搜线法xy/project/code/pico_link_ii.c \
D:/车队stuff/carcode/左右搜线法xy/project/code/show_send.c 

OBJS += \
./code/circle.o \
./code/cross.o \
./code/img.o \
./code/pico_gy.o \
./code/pico_link_ii.o \
./code/show_send.o 

C_DEPS += \
./code/circle.d \
./code/cross.d \
./code/img.d \
./code/pico_gy.d \
./code/pico_link_ii.d \
./code/show_send.d 


# Each subdirectory must supply rules for building sources it contributes
code/circle.o: D:/车队stuff/carcode/左右搜线法xy/project/code/circle.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/cross.o: D:/车队stuff/carcode/左右搜线法xy/project/code/cross.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/img.o: D:/车队stuff/carcode/左右搜线法xy/project/code/img.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pico_gy.o: D:/车队stuff/carcode/左右搜线法xy/project/code/pico_gy.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pico_link_ii.o: D:/车队stuff/carcode/左右搜线法xy/project/code/pico_link_ii.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/show_send.o: D:/车队stuff/carcode/左右搜线法xy/project/code/show_send.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\车队stuff\carcode\左右搜线法xy\Libraries\doc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_components" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Core" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Ld" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Peripheral" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\sdk\Startup" -I"D:\车队stuff\carcode\左右搜线法xy\project\user\inc" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_common" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_device" -I"D:\车队stuff\carcode\左右搜线法xy\project\code" -I"D:\车队stuff\carcode\左右搜线法xy\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

