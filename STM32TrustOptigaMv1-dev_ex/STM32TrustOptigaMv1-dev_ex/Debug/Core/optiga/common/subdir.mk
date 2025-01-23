################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/optiga/common/optiga_lib_common.c \
../Core/optiga/common/optiga_lib_logger.c 

OBJS += \
./Core/optiga/common/optiga_lib_common.o \
./Core/optiga/common/optiga_lib_logger.o 

C_DEPS += \
./Core/optiga/common/optiga_lib_common.d \
./Core/optiga/common/optiga_lib_logger.d 


# Each subdirectory must supply rules for building sources it contributes
Core/optiga/common/%.o Core/optiga/common/%.su Core/optiga/common/%.cyclo: ../Core/optiga/common/%.c Core/optiga/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/worker/Projects/STM32TrustOptigaMv1/Core/optiga/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-optiga-2f-common

clean-Core-2f-optiga-2f-common:
	-$(RM) ./Core/optiga/common/optiga_lib_common.cyclo ./Core/optiga/common/optiga_lib_common.d ./Core/optiga/common/optiga_lib_common.o ./Core/optiga/common/optiga_lib_common.su ./Core/optiga/common/optiga_lib_logger.cyclo ./Core/optiga/common/optiga_lib_logger.d ./Core/optiga/common/optiga_lib_logger.o ./Core/optiga/common/optiga_lib_logger.su

.PHONY: clean-Core-2f-optiga-2f-common

