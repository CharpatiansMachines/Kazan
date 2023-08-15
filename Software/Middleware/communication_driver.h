/*
 * Communication.hpp
 *
 *  Created on: May 26, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_COMMUNICATION_DRIVER_H_
#define KAZAN_DRIVER_COMMUNICATION_DRIVER_H_
#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_def.h"


class Communication_Driver{
public:
	Communication_Driver(USART_TypeDef * uartx);
	HAL_StatusTypeDef config();
	HAL_StatusTypeDef log(const char *format,...);
private:
	UART_HandleTypeDef huart;
};



#endif /* KAZAN_DRIVER_COMMUNICATION_DRIVER_H_ */
