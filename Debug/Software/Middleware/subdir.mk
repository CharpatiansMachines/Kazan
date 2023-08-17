################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Software/Middleware/communication_driver.cpp \
../Software/Middleware/display.cpp \
../Software/Middleware/state_control.cpp \
../Software/Middleware/user_inputs.cpp 

OBJS += \
./Software/Middleware/communication_driver.o \
./Software/Middleware/display.o \
./Software/Middleware/state_control.o \
./Software/Middleware/user_inputs.o 

CPP_DEPS += \
./Software/Middleware/communication_driver.d \
./Software/Middleware/display.d \
./Software/Middleware/state_control.d \
./Software/Middleware/user_inputs.d 


# Each subdirectory must supply rules for building sources it contributes
Software/Middleware/%.o Software/Middleware/%.su Software/Middleware/%.cyclo: ../Software/Middleware/%.cpp Software/Middleware/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral" -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral/SSD1306" -I"D:/Proiecte/STMCUBE/Kazan/Software/Model" -I"D:/Proiecte/STMCUBE/Kazan/Software/Middleware" -I"D:/Proiecte/STMCUBE/Kazan/Software/App" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Software-2f-Middleware

clean-Software-2f-Middleware:
	-$(RM) ./Software/Middleware/communication_driver.cyclo ./Software/Middleware/communication_driver.d ./Software/Middleware/communication_driver.o ./Software/Middleware/communication_driver.su ./Software/Middleware/display.cyclo ./Software/Middleware/display.d ./Software/Middleware/display.o ./Software/Middleware/display.su ./Software/Middleware/state_control.cyclo ./Software/Middleware/state_control.d ./Software/Middleware/state_control.o ./Software/Middleware/state_control.su ./Software/Middleware/user_inputs.cyclo ./Software/Middleware/user_inputs.d ./Software/Middleware/user_inputs.o ./Software/Middleware/user_inputs.su

.PHONY: clean-Software-2f-Middleware

