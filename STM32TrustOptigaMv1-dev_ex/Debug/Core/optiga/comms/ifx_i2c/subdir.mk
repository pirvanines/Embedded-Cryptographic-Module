################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/optiga/comms/ifx_i2c/ifx_i2c.c \
../Core/optiga/comms/ifx_i2c/ifx_i2c_config.c \
../Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.c \
../Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.c \
../Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.c \
../Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.c 

OBJS += \
./Core/optiga/comms/ifx_i2c/ifx_i2c.o \
./Core/optiga/comms/ifx_i2c/ifx_i2c_config.o \
./Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.o \
./Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.o \
./Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.o \
./Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.o 

C_DEPS += \
./Core/optiga/comms/ifx_i2c/ifx_i2c.d \
./Core/optiga/comms/ifx_i2c/ifx_i2c_config.d \
./Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.d \
./Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.d \
./Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.d \
./Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/optiga/comms/ifx_i2c/%.o Core/optiga/comms/ifx_i2c/%.su Core/optiga/comms/ifx_i2c/%.cyclo: ../Core/optiga/comms/ifx_i2c/%.c Core/optiga/comms/ifx_i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/worker/Projects/STM32TrustOptigaMv1/Core/optiga/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-optiga-2f-comms-2f-ifx_i2c

clean-Core-2f-optiga-2f-comms-2f-ifx_i2c:
	-$(RM) ./Core/optiga/comms/ifx_i2c/ifx_i2c.cyclo ./Core/optiga/comms/ifx_i2c/ifx_i2c.d ./Core/optiga/comms/ifx_i2c/ifx_i2c.o ./Core/optiga/comms/ifx_i2c/ifx_i2c.su ./Core/optiga/comms/ifx_i2c/ifx_i2c_config.cyclo ./Core/optiga/comms/ifx_i2c/ifx_i2c_config.d ./Core/optiga/comms/ifx_i2c/ifx_i2c_config.o ./Core/optiga/comms/ifx_i2c/ifx_i2c_config.su ./Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.cyclo ./Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.d ./Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.o ./Core/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.su ./Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.cyclo ./Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.d ./Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.o ./Core/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.su ./Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.cyclo ./Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.d ./Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.o ./Core/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.su ./Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.cyclo ./Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.d ./Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.o ./Core/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.su

.PHONY: clean-Core-2f-optiga-2f-comms-2f-ifx_i2c

