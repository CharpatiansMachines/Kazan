################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Software/Peripheral/button_driver.cpp \
../Software/Peripheral/communication_driver.cpp \
../Software/Peripheral/enemy_detection.cpp \
../Software/Peripheral/line_detection.cpp \
../Software/Peripheral/motor_driver.cpp \
../Software/Peripheral/trimpot_driver.cpp 

OBJS += \
./Software/Peripheral/button_driver.o \
./Software/Peripheral/communication_driver.o \
./Software/Peripheral/enemy_detection.o \
./Software/Peripheral/line_detection.o \
./Software/Peripheral/motor_driver.o \
./Software/Peripheral/trimpot_driver.o 

CPP_DEPS += \
./Software/Peripheral/button_driver.d \
./Software/Peripheral/communication_driver.d \
./Software/Peripheral/enemy_detection.d \
./Software/Peripheral/line_detection.d \
./Software/Peripheral/motor_driver.d \
./Software/Peripheral/trimpot_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Software/Peripheral/%.o Software/Peripheral/%.su Software/Peripheral/%.cyclo: ../Software/Peripheral/%.cpp Software/Peripheral/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/stm/Kazan/Software/Peripheral" -I"D:/Proiecte/stm/Kazan/Software/Peripheral/SSD1306" -I"D:/Proiecte/stm/Kazan/Software/Model" -I"D:/Proiecte/stm/Kazan/Software/Middleware" -I"D:/Proiecte/stm/Kazan/Software/App" -I"D:/Proiecte/stm/Kazan/Software/Helpers" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Software-2f-Peripheral

clean-Software-2f-Peripheral:
	-$(RM) ./Software/Peripheral/button_driver.cyclo ./Software/Peripheral/button_driver.d ./Software/Peripheral/button_driver.o ./Software/Peripheral/button_driver.su ./Software/Peripheral/communication_driver.cyclo ./Software/Peripheral/communication_driver.d ./Software/Peripheral/communication_driver.o ./Software/Peripheral/communication_driver.su ./Software/Peripheral/enemy_detection.cyclo ./Software/Peripheral/enemy_detection.d ./Software/Peripheral/enemy_detection.o ./Software/Peripheral/enemy_detection.su ./Software/Peripheral/line_detection.cyclo ./Software/Peripheral/line_detection.d ./Software/Peripheral/line_detection.o ./Software/Peripheral/line_detection.su ./Software/Peripheral/motor_driver.cyclo ./Software/Peripheral/motor_driver.d ./Software/Peripheral/motor_driver.o ./Software/Peripheral/motor_driver.su ./Software/Peripheral/trimpot_driver.cyclo ./Software/Peripheral/trimpot_driver.d ./Software/Peripheral/trimpot_driver.o ./Software/Peripheral/trimpot_driver.su

.PHONY: clean-Software-2f-Peripheral

