/*
 * Button_Driver.hpp
 *
 *  Created on: May 28, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_BUTTON_DRIVER_H_
#define KAZAN_DRIVER_BUTTON_DRIVER_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

enum ButtonOutput { NO_CLICK, CLICK, HOLD_CLICK, DOUBLE_CLICK };


class ComplexButton{
public:
	ComplexButton(GPIO_TypeDef * GPIOX,uint16_t PIN);
	void config();
	ButtonOutput read();


private:
	const uint16_t HOLD_CLICK_PRESSING_TIME_MS = 500;
	const uint16_t DOUBLE_CLICK_TIME_MS = 300;
	GPIO_TypeDef * GPIOX;
	uint16_t PIN;
	uint32_t clock;
	uint8_t state;



};



#endif /* KAZAN_DRIVER_BUTTON_DRIVER_H_ */
