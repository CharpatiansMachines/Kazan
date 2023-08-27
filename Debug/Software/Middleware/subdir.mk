################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Software/Middleware/display.cpp \
../Software/Middleware/motion.cpp \
../Software/Middleware/state_control.cpp \
../Software/Middleware/strategist.cpp \
../Software/Middleware/tactician.cpp \
../Software/Middleware/timed_motion.cpp \
../Software/Middleware/user_inputs.cpp 

OBJS += \
./Software/Middleware/display.o \
./Software/Middleware/motion.o \
./Software/Middleware/state_control.o \
./Software/Middleware/strategist.o \
./Software/Middleware/tactician.o \
./Software/Middleware/timed_motion.o \
./Software/Middleware/user_inputs.o 

CPP_DEPS += \
./Software/Middleware/display.d \
./Software/Middleware/motion.d \
./Software/Middleware/state_control.d \
./Software/Middleware/strategist.d \
./Software/Middleware/tactician.d \
./Software/Middleware/timed_motion.d \
./Software/Middleware/user_inputs.d 


# Each subdirectory must supply rules for building sources it contributes
Software/Middleware/%.o Software/Middleware/%.su Software/Middleware/%.cyclo: ../Software/Middleware/%.cpp Software/Middleware/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral" -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral/SSD1306" -I"D:/Proiecte/STMCUBE/Kazan/Software/Model" -I"D:/Proiecte/STMCUBE/Kazan/Software/Middleware" -I"D:/Proiecte/STMCUBE/Kazan/Software/App" -I"D:/Proiecte/STMCUBE/Kazan/Software/Helpers" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Software-2f-Middleware

clean-Software-2f-Middleware:
	-$(RM) ./Software/Middleware/display.cyclo ./Software/Middleware/display.d ./Software/Middleware/display.o ./Software/Middleware/display.su ./Software/Middleware/motion.cyclo ./Software/Middleware/motion.d ./Software/Middleware/motion.o ./Software/Middleware/motion.su ./Software/Middleware/state_control.cyclo ./Software/Middleware/state_control.d ./Software/Middleware/state_control.o ./Software/Middleware/state_control.su ./Software/Middleware/strategist.cyclo ./Software/Middleware/strategist.d ./Software/Middleware/strategist.o ./Software/Middleware/strategist.su ./Software/Middleware/tactician.cyclo ./Software/Middleware/tactician.d ./Software/Middleware/tactician.o ./Software/Middleware/tactician.su ./Software/Middleware/timed_motion.cyclo ./Software/Middleware/timed_motion.d ./Software/Middleware/timed_motion.o ./Software/Middleware/timed_motion.su ./Software/Middleware/user_inputs.cyclo ./Software/Middleware/user_inputs.d ./Software/Middleware/user_inputs.o ./Software/Middleware/user_inputs.su

.PHONY: clean-Software-2f-Middleware

