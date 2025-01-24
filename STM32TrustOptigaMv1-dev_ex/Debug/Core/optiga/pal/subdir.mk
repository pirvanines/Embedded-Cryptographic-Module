################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/optiga/pal/pal.c \
../Core/optiga/pal/pal_gpio.c \
../Core/optiga/pal/pal_i2c.c \
../Core/optiga/pal/pal_ifx_i2c_config.c \
../Core/optiga/pal/pal_logger.c \
../Core/optiga/pal/pal_os_datastore.c \
../Core/optiga/pal/pal_os_event.c \
../Core/optiga/pal/pal_os_lock.c \
../Core/optiga/pal/pal_os_memory.c \
../Core/optiga/pal/pal_os_timer.c 

OBJS += \
./Core/optiga/pal/pal.o \
./Core/optiga/pal/pal_gpio.o \
./Core/optiga/pal/pal_i2c.o \
./Core/optiga/pal/pal_ifx_i2c_config.o \
./Core/optiga/pal/pal_logger.o \
./Core/optiga/pal/pal_os_datastore.o \
./Core/optiga/pal/pal_os_event.o \
./Core/optiga/pal/pal_os_lock.o \
./Core/optiga/pal/pal_os_memory.o \
./Core/optiga/pal/pal_os_timer.o 

C_DEPS += \
./Core/optiga/pal/pal.d \
./Core/optiga/pal/pal_gpio.d \
./Core/optiga/pal/pal_i2c.d \
./Core/optiga/pal/pal_ifx_i2c_config.d \
./Core/optiga/pal/pal_logger.d \
./Core/optiga/pal/pal_os_datastore.d \
./Core/optiga/pal/pal_os_event.d \
./Core/optiga/pal/pal_os_lock.d \
./Core/optiga/pal/pal_os_memory.d \
./Core/optiga/pal/pal_os_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/optiga/pal/%.o Core/optiga/pal/%.su Core/optiga/pal/%.cyclo: ../Core/optiga/pal/%.c Core/optiga/pal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/worker/Projects/STM32TrustOptigaMv1/Core/optiga/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-optiga-2f-pal

clean-Core-2f-optiga-2f-pal:
	-$(RM) ./Core/optiga/pal/pal.cyclo ./Core/optiga/pal/pal.d ./Core/optiga/pal/pal.o ./Core/optiga/pal/pal.su ./Core/optiga/pal/pal_gpio.cyclo ./Core/optiga/pal/pal_gpio.d ./Core/optiga/pal/pal_gpio.o ./Core/optiga/pal/pal_gpio.su ./Core/optiga/pal/pal_i2c.cyclo ./Core/optiga/pal/pal_i2c.d ./Core/optiga/pal/pal_i2c.o ./Core/optiga/pal/pal_i2c.su ./Core/optiga/pal/pal_ifx_i2c_config.cyclo ./Core/optiga/pal/pal_ifx_i2c_config.d ./Core/optiga/pal/pal_ifx_i2c_config.o ./Core/optiga/pal/pal_ifx_i2c_config.su ./Core/optiga/pal/pal_logger.cyclo ./Core/optiga/pal/pal_logger.d ./Core/optiga/pal/pal_logger.o ./Core/optiga/pal/pal_logger.su ./Core/optiga/pal/pal_os_datastore.cyclo ./Core/optiga/pal/pal_os_datastore.d ./Core/optiga/pal/pal_os_datastore.o ./Core/optiga/pal/pal_os_datastore.su ./Core/optiga/pal/pal_os_event.cyclo ./Core/optiga/pal/pal_os_event.d ./Core/optiga/pal/pal_os_event.o ./Core/optiga/pal/pal_os_event.su ./Core/optiga/pal/pal_os_lock.cyclo ./Core/optiga/pal/pal_os_lock.d ./Core/optiga/pal/pal_os_lock.o ./Core/optiga/pal/pal_os_lock.su ./Core/optiga/pal/pal_os_memory.cyclo ./Core/optiga/pal/pal_os_memory.d ./Core/optiga/pal/pal_os_memory.o ./Core/optiga/pal/pal_os_memory.su ./Core/optiga/pal/pal_os_timer.cyclo ./Core/optiga/pal/pal_os_timer.d ./Core/optiga/pal/pal_os_timer.o ./Core/optiga/pal/pal_os_timer.su

.PHONY: clean-Core-2f-optiga-2f-pal

