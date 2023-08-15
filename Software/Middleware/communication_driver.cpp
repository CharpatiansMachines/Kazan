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

Communication_Driver::Communication_Driver(USART_TypeDef * uartx)
{
	huart.Instance = uartx;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
}

HAL_StatusTypeDef Communication_Driver::config(){
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




