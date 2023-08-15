################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Software/Peripheral/SSD1306/ssd1306.c \
../Software/Peripheral/SSD1306/ssd1306_fonts.c \
../Software/Peripheral/SSD1306/ssd1306_tests.c 

C_DEPS += \
./Software/Peripheral/SSD1306/ssd1306.d \
./Software/Peripheral/SSD1306/ssd1306_fonts.d \
./Software/Peripheral/SSD1306/ssd1306_tests.d 

OBJS += \
./Software/Peripheral/SSD1306/ssd1306.o \
./Software/Peripheral/SSD1306/ssd1306_fonts.o \
./Software/Peripheral/SSD1306/ssd1306_tests.o 


# Each subdirectory must supply rules for building sources it contributes
Software/Peripheral/SSD1306/%.o Software/Peripheral/SSD1306/%.su Software/Peripheral/SSD1306/%.cyclo: ../Software/Peripheral/SSD1306/%.c Software/Peripheral/SSD1306/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral" -I"D:/Proiecte/STMCUBE/Kazan/Software/Peripheral/SSD1306" -I"D:/Proiecte/STMCUBE/Kazan/Software/Model" -I"D:/Proiecte/STMCUBE/Kazan/Software/Middleware" -I"D:/Proiecte/STMCUBE/Kazan/Software/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Software-2f-Peripheral-2f-SSD1306

clean-Software-2f-Peripheral-2f-SSD1306:
	-$(RM) ./Software/Peripheral/SSD1306/ssd1306.cyclo ./Software/Peripheral/SSD1306/ssd1306.d ./Software/Peripheral/SSD1306/ssd1306.o ./Software/Peripheral/SSD1306/ssd1306.su ./Software/Peripheral/SSD1306/ssd1306_fonts.cyclo ./Software/Peripheral/SSD1306/ssd1306_fonts.d ./Software/Peripheral/SSD1306/ssd1306_fonts.o ./Software/Peripheral/SSD1306/ssd1306_fonts.su ./Software/Peripheral/SSD1306/ssd1306_tests.cyclo ./Software/Peripheral/SSD1306/ssd1306_tests.d ./Software/Peripheral/SSD1306/ssd1306_tests.o ./Software/Peripheral/SSD1306/ssd1306_tests.su

.PHONY: clean-Software-2f-Peripheral-2f-SSD1306

