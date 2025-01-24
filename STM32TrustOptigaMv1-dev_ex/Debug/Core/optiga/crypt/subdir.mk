################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/optiga/crypt/optiga_crypt.c 

OBJS += \
./Core/optiga/crypt/optiga_crypt.o 

C_DEPS += \
./Core/optiga/crypt/optiga_crypt.d 


# Each subdirectory must supply rules for building sources it contributes
Core/optiga/crypt/%.o Core/optiga/crypt/%.su Core/optiga/crypt/%.cyclo: ../Core/optiga/crypt/%.c Core/optiga/crypt/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/worker/Projects/STM32TrustOptigaMv1/Core/optiga/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-optiga-2f-crypt

clean-Core-2f-optiga-2f-crypt:
	-$(RM) ./Core/optiga/crypt/optiga_crypt.cyclo ./Core/optiga/crypt/optiga_crypt.d ./Core/optiga/crypt/optiga_crypt.o ./Core/optiga/crypt/optiga_crypt.su

.PHONY: clean-Core-2f-optiga-2f-crypt

