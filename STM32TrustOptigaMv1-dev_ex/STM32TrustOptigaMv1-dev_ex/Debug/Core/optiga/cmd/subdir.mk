################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/optiga/cmd/optiga_cmd.c 

OBJS += \
./Core/optiga/cmd/optiga_cmd.o 

C_DEPS += \
./Core/optiga/cmd/optiga_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/optiga/cmd/%.o Core/optiga/cmd/%.su Core/optiga/cmd/%.cyclo: ../Core/optiga/cmd/%.c Core/optiga/cmd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/worker/Projects/STM32TrustOptigaMv1/Core/optiga/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-optiga-2f-cmd

clean-Core-2f-optiga-2f-cmd:
	-$(RM) ./Core/optiga/cmd/optiga_cmd.cyclo ./Core/optiga/cmd/optiga_cmd.d ./Core/optiga/cmd/optiga_cmd.o ./Core/optiga/cmd/optiga_cmd.su

.PHONY: clean-Core-2f-optiga-2f-cmd

