################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FLITF.c \
../src/FPEC_program.c \
../src/GPIO_Program.c \
../src/LOGIC_BL.c \
../src/RCC_program.c \
../src/SCB_Program.c \
../src/USART_program.c \
../src/_write.c \
../src/main.c 

OBJS += \
./src/FLITF.o \
./src/FPEC_program.o \
./src/GPIO_Program.o \
./src/LOGIC_BL.o \
./src/RCC_program.o \
./src/SCB_Program.o \
./src/USART_program.o \
./src/_write.o \
./src/main.o 

C_DEPS += \
./src/FLITF.d \
./src/FPEC_program.d \
./src/GPIO_Program.d \
./src/LOGIC_BL.d \
./src/RCC_program.d \
./src/SCB_Program.d \
./src/USART_program.d \
./src/_write.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


