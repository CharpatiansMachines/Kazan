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
#include "tactician.h"

struct CommunicationDriverConfig {
    USART_TypeDef* uartx;
    GPIO_TypeDef* GPIOx_Start_Module;
    uint16_t PIIN_Start_Module;
};

class Communication_Driver{
public:
	Communication_Driver(const CommunicationDriverConfig& config);
	HAL_StatusTypeDef config();
	bool readStartModule();

	void inline resetBuffer();
	void downloadBuffer() ;
	void storeInBuffer(Tactician::Tactic tactic);
private:
	HAL_StatusTypeDef log(const char *format,...) ;
	GPIO_TypeDef* GPIOx_Start_Module;
	uint16_t PIN_Start_Module;
	UART_HandleTypeDef huart;

	enum BufferStoreType{
		TACTIC_BUFFER_TYPE = 0x00,
	};

	static constexpr uint16_t BUFFER_SIZE = 1000;
	uint8_t buffer[BUFFER_SIZE];
	uint16_t bufferIndex;
};



#endif /* KAZAN_DRIVER_COMMUNICATION_DRIVER_H_ */
