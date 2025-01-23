################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/optiga/comms/optiga_comms_ifx_i2c.c 

OBJS += \
./Core/optiga/comms/optiga_comms_ifx_i2c.o 

C_DEPS += \
./Core/optiga/comms/optiga_comms_ifx_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/optiga/comms/%.o Core/optiga/comms/%.su Core/optiga/comms/%.cyclo: ../Core/optiga/comms/%.c Core/optiga/comms/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/worker/Projects/STM32TrustOptigaMv1/Core/optiga/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-optiga-2f-comms

clean-Core-2f-optiga-2f-comms:
	-$(RM) ./Core/optiga/comms/optiga_comms_ifx_i2c.cyclo ./Core/optiga/comms/optiga_comms_ifx_i2c.d ./Core/optiga/comms/optiga_comms_ifx_i2c.o ./Core/optiga/comms/optiga_comms_ifx_i2c.su

.PHONY: clean-Core-2f-optiga-2f-comms

