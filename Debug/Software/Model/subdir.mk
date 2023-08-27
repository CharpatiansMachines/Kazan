################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Software/Model/enemy_position.cpp \
../Software/Model/line_position.cpp \
../Software/Model/state.cpp 

OBJS += \
./Software/Model/enemy_position.o \
./Software/Model/line_position.o \
./Software/Model/state.o 

CPP_DEPS += \
./Software/Model/enemy_position.d \
./Software/Model/line_position.d \
./Software/Model/state.d 


# Each subdirectory must supply rules for building sources it contributes
Software/Model/%.o Software/Model/%.su Software/Model/%.cyclo: ../Software/Model/%.cpp Software/Model/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral" -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral/SSD1306" -I"D:/Proiecte/STMCUBE/Kazan/Software/Model" -I"D:/Proiecte/STMCUBE/Kazan/Software/Middleware" -I"D:/Proiecte/STMCUBE/Kazan/Software/App" -I"D:/Proiecte/STMCUBE/Kazan/Software/Helpers" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Software-2f-Model

clean-Software-2f-Model:
	-$(RM) ./Software/Model/enemy_position.cyclo ./Software/Model/enemy_position.d ./Software/Model/enemy_position.o ./Software/Model/enemy_position.su ./Software/Model/line_position.cyclo ./Software/Model/line_position.d ./Software/Model/line_position.o ./Software/Model/line_position.su ./Software/Model/state.cyclo ./Software/Model/state.d ./Software/Model/state.o ./Software/Model/state.su

.PHONY: clean-Software-2f-Model

