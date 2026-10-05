################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/sysmem.c 

OBJS += \
./startup/sysmem.o 

C_DEPS += \
./startup/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I"/home/massimo/Scrivania/MaterieRestantiTriennale/Laboratorio di Sistemi a Microcontrollori/en.stm32cubef4_v1-25-0/STM32Cube_FW_F4_V1.25.0/Drivers/CMSIS/Include" -I"/home/massimo/Scrivania/MaterieRestantiTriennale/Laboratorio di Sistemi a Microcontrollori/en.stm32cubef4_v1-25-0/STM32Cube_FW_F4_V1.25.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/massimo/Scrivania/MaterieRestantiTriennale/Laboratorio di Sistemi a Microcontrollori/stm32_unict_lib/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


