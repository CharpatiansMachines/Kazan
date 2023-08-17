/*
 * Button_Driver.cpp
 *
 *  Created on: May 28, 2023
 *      Author: BRG
 */
#include "button_driver.h"

#include "stm32f4xx_hal.h"


ComplexButton::ComplexButton(GPIO_TypeDef * GPIOX,uint16_t PIN):
GPIOX(GPIOX),
PIN(PIN),
clock(HAL_GetTick()),
buttonState(WaitForPress)
{};


void ComplexButton::config()
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

ButtonOutput ComplexButton::getLastValue() const {
	return lastValue;
}


ButtonOutput ComplexButton::read()
{
	GPIO_PinState pinState = (HAL_GPIO_ReadPin(GPIOX, PIN) == GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET;

	switch(buttonState) {
		case ButtonState::WaitForPress:
			if(pinState == GPIO_PIN_SET) {
				clock = HAL_GetTick(); // Capture press time
				buttonState = ButtonState::WaitForRelease;
			}
			break;
		case ButtonState::WaitForRelease:
			if(pinState == GPIO_PIN_RESET) {
				buttonState = ButtonState::CheckDoubleClick;
			}
			// Check for hold duration
			if(HAL_GetTick() - clock >= HOLD_CLICK_PRESSING_TIME_MS) {
				buttonState = ButtonState::IdleAfterClick;
				lastValue = HOLD_CLICK;
				return HOLD_CLICK;
			}
			break;
		case ButtonState::CheckDoubleClick:
			if(pinState == GPIO_PIN_SET) {
				buttonState = ButtonState::IdleAfterClick;
				lastValue = DOUBLE_CLICK;
				return DOUBLE_CLICK;
			}
			// If no second click for a certain duration
			if(HAL_GetTick() - clock >= DOUBLE_CLICK_TIME_MS) {
				buttonState = ButtonState::WaitForPress;
				lastValue = CLICK;
				return CLICK;
			}
			break;
		case ButtonState::IdleAfterClick:
			if(pinState == GPIO_PIN_RESET) {
				buttonState = ButtonState::WaitForPress;
			}
			break;
		}

		lastValue = ButtonOutput::NO_CLICK;
		return ButtonOutput::NO_CLICK;
}



