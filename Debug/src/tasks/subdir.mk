################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tasks/main_task.c \
../src/tasks/pc_task.c \
../src/tasks/read_task.c 

OBJS += \
./src/tasks/main_task.o \
./src/tasks/pc_task.o \
./src/tasks/read_task.o 

C_DEPS += \
./src/tasks/main_task.d \
./src/tasks/pc_task.d \
./src/tasks/read_task.d 


# Each subdirectory must supply rules for building sources it contributes
src/tasks/%.o src/tasks/%.su src/tasks/%.cyclo: ../src/tasks/%.c src/tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../Core/Inc -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Drivers/STM32F0xx_HAL_Driver/Inc -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Drivers/CMSIS/Device/ST/STM32F0xx/Include -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Drivers/CMSIS/Include -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Middlewares/Third_Party/FreeRTOS/Source/include -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I/home/mkac/STM32Cube/Repository/STM32Cube_FW_F0_V1.11.4/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I"/home/mkac/STM32CubeIDE/workspace_1.15.1/BMS/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-tasks

clean-src-2f-tasks:
	-$(RM) ./src/tasks/main_task.cyclo ./src/tasks/main_task.d ./src/tasks/main_task.o ./src/tasks/main_task.su ./src/tasks/pc_task.cyclo ./src/tasks/pc_task.d ./src/tasks/pc_task.o ./src/tasks/pc_task.su ./src/tasks/read_task.cyclo ./src/tasks/read_task.d ./src/tasks/read_task.o ./src/tasks/read_task.su

.PHONY: clean-src-2f-tasks

