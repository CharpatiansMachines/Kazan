/*
 * Communication.cpp
 *
 *  Created on: May 26, 2023
 *      Author: BRG
 */

#include "communication_driver.h"

#include "stdio.h"
#include <stdarg.h>
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_def.h"

Communication_Driver::Communication_Driver(const CommunicationDriverConfig& config)
    : GPIOx_Start_Module(config.GPIOx_Start_Module),
      PIN_Start_Module(config.PIIN_Start_Module)
{
	huart.Instance = config.uartx;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
}

HAL_StatusTypeDef Communication_Driver::config(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = PIN_Start_Module;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOx_Start_Module, &GPIO_InitStruct);
	return HAL_HalfDuplex_Init(&huart);
}

HAL_StatusTypeDef Communication_Driver::log(const char *format,...)
{
    char buffer[1024];
    va_list args;

    va_start(args, format);
    int rc = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    return HAL_UART_Transmit(&huart, (uint8_t *)buffer, rc , 100);

}

bool Communication_Driver::readStartModule()
{
	return HAL_GPIO_ReadPin(GPIOx_Start_Module, PIN_Start_Module) == GPIO_PIN_SET;
}




