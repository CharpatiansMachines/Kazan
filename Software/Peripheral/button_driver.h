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
	ButtonOutput getLastValue() const ;


private:
  enum ButtonState {
		WaitForPress,
		WaitForRelease,
		CheckDoubleClick,
		IdleAfterClick
	};
	const uint16_t HOLD_CLICK_PRESSING_TIME_MS = 500;
	const uint16_t DOUBLE_CLICK_TIME_MS = 300;

	ButtonOutput lastValue;
	GPIO_TypeDef * GPIOX;
	uint16_t PIN;
	uint32_t clock;
	ButtonState buttonState;



};



#endif /* KAZAN_DRIVER_BUTTON_DRIVER_H_ */
