################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/startup_stm32f401xe.s 

C_SRCS += \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/adc.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/console.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/display.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/gpio.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/i2c.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/syscalls.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/system_init.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/systick.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/timers.c \
/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/usart.c 

OBJS += \
./stm32_unict_lib/src/adc.o \
./stm32_unict_lib/src/console.o \
./stm32_unict_lib/src/display.o \
./stm32_unict_lib/src/gpio.o \
./stm32_unict_lib/src/i2c.o \
./stm32_unict_lib/src/startup_stm32f401xe.o \
./stm32_unict_lib/src/syscalls.o \
./stm32_unict_lib/src/system_init.o \
./stm32_unict_lib/src/systick.o \
./stm32_unict_lib/src/timers.o \
./stm32_unict_lib/src/usart.o 

C_DEPS += \
./stm32_unict_lib/src/adc.d \
./stm32_unict_lib/src/console.d \
./stm32_unict_lib/src/display.d \
./stm32_unict_lib/src/gpio.d \
./stm32_unict_lib/src/i2c.d \
./stm32_unict_lib/src/syscalls.d \
./stm32_unict_lib/src/system_init.d \
./stm32_unict_lib/src/systick.d \
./stm32_unict_lib/src/timers.d \
./stm32_unict_lib/src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_unict_lib/src/adc.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/console.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/console.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/display.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/display.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/gpio.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/i2c.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/startup_stm32f401xe.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/startup_stm32f401xe.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/syscalls.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/syscalls.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/system_init.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/system_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/systick.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/systick.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/timers.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

stm32_unict_lib/src/usart.o: /home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xE -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/codewalker23/Scrivania/RisorseUniCT/EsercitazioniMCU/stm32_unict_lib/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


