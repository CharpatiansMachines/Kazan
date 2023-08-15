################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middleware/application.cpp \
../Middleware/button_driver.cpp \
../Middleware/communication_driver.cpp \
../Middleware/display.cpp \
../Middleware/enemy_detection.cpp \
../Middleware/enemy_position.cpp \
../Middleware/hardware_test.cpp \
../Middleware/line_detection.cpp \
../Middleware/motor_driver.cpp \
../Middleware/sensors_hub.cpp \
../Middleware/trimpot_driver.cpp \
../Middleware/user_inputs.cpp 

OBJS += \
./Middleware/application.o \
./Middleware/button_driver.o \
./Middleware/communication_driver.o \
./Middleware/display.o \
./Middleware/enemy_detection.o \
./Middleware/enemy_position.o \
./Middleware/hardware_test.o \
./Middleware/line_detection.o \
./Middleware/motor_driver.o \
./Middleware/sensors_hub.o \
./Middleware/trimpot_driver.o \
./Middleware/user_inputs.o 

CPP_DEPS += \
./Middleware/application.d \
./Middleware/button_driver.d \
./Middleware/communication_driver.d \
./Middleware/display.d \
./Middleware/enemy_detection.d \
./Middleware/enemy_position.d \
./Middleware/hardware_test.d \
./Middleware/line_detection.d \
./Middleware/motor_driver.d \
./Middleware/sensors_hub.d \
./Middleware/trimpot_driver.d \
./Middleware/user_inputs.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/%.o Middleware/%.su Middleware/%.cyclo: ../Middleware/%.cpp Middleware/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/STMCUBE/Kazan/Middleware" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware

clean-Middleware:
	-$(RM) ./Middleware/application.cyclo ./Middleware/application.d ./Middleware/application.o ./Middleware/application.su ./Middleware/button_driver.cyclo ./Middleware/button_driver.d ./Middleware/button_driver.o ./Middleware/button_driver.su ./Middleware/communication_driver.cyclo ./Middleware/communication_driver.d ./Middleware/communication_driver.o ./Middleware/communication_driver.su ./Middleware/display.cyclo ./Middleware/display.d ./Middleware/display.o ./Middleware/display.su ./Middleware/enemy_detection.cyclo ./Middleware/enemy_detection.d ./Middleware/enemy_detection.o ./Middleware/enemy_detection.su ./Middleware/enemy_position.cyclo ./Middleware/enemy_position.d ./Middleware/enemy_position.o ./Middleware/enemy_position.su ./Middleware/hardware_test.cyclo ./Middleware/hardware_test.d ./Middleware/hardware_test.o ./Middleware/hardware_test.su ./Middleware/line_detection.cyclo ./Middleware/line_detection.d ./Middleware/line_detection.o ./Middleware/line_detection.su ./Middleware/motor_driver.cyclo ./Middleware/motor_driver.d ./Middleware/motor_driver.o ./Middleware/motor_driver.su ./Middleware/sensors_hub.cyclo ./Middleware/sensors_hub.d ./Middleware/sensors_hub.o ./Middleware/sensors_hub.su ./Middleware/trimpot_driver.cyclo ./Middleware/trimpot_driver.d ./Middleware/trimpot_driver.o ./Middleware/trimpot_driver.su ./Middleware/user_inputs.cyclo ./Middleware/user_inputs.d ./Middleware/user_inputs.o ./Middleware/user_inputs.su

.PHONY: clean-Middleware

