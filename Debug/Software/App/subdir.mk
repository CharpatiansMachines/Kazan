################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Software/App/application.cpp \
../Software/App/hardware_test.cpp 

OBJS += \
./Software/App/application.o \
./Software/App/hardware_test.o 

CPP_DEPS += \
./Software/App/application.d \
./Software/App/hardware_test.d 


# Each subdirectory must supply rules for building sources it contributes
Software/App/%.o Software/App/%.su Software/App/%.cyclo: ../Software/App/%.cpp Software/App/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral" -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral/SSD1306" -I"D:/Proiecte/STMCUBE/Kazan/Software/Model" -I"D:/Proiecte/STMCUBE/Kazan/Software/Middleware" -I"D:/Proiecte/STMCUBE/Kazan/Software/App" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Software-2f-App

clean-Software-2f-App:
	-$(RM) ./Software/App/application.cyclo ./Software/App/application.d ./Software/App/application.o ./Software/App/application.su ./Software/App/hardware_test.cyclo ./Software/App/hardware_test.d ./Software/App/hardware_test.o ./Software/App/hardware_test.su

.PHONY: clean-Software-2f-App

