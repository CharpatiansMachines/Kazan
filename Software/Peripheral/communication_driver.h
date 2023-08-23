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

struct CommunicationDriverConfig {
    USART_TypeDef* uartx;
    GPIO_TypeDef* GPIOx_Start_Module;
    uint16_t PIIN_Start_Module;
};

class Communication_Driver{
public:
	Communication_Driver(const CommunicationDriverConfig& config);
	HAL_StatusTypeDef config();
	HAL_StatusTypeDef log(const char *format,...);
	bool readStartModule();
private:
	GPIO_TypeDef* GPIOx_Start_Module;
	uint16_t PIN_Start_Module;
	UART_HandleTypeDef huart;
};



#endif /* KAZAN_DRIVER_COMMUNICATION_DRIVER_H_ */
