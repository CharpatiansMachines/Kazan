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
clock(0),
state(0)
{};


void ComplexButton::config()
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


ButtonOutput ComplexButton::read()
{
	uint8_t value =( HAL_GPIO_ReadPin(GPIOX, PIN) == 0 );
	switch(state){
	case 0 :
		if(value == 1){
			clock = HAL_GetTick();
			state = 1;
		}
		break;
	case 1 :
		if(value == 0){
			state = 2;
		}
		if(HAL_GetTick() - clock >= HOLD_CLICK_PRESSING_TIME_MS){
			state = 3;
			return HOLD_CLICK;
		}
		break;
	case 2:
		if(value == 1){
			state = 3;
			return DOUBLE_CLICK;
		}
		if(HAL_GetTick() - clock >= DOUBLE_CLICK_TIME_MS){
			state = 0;
			return CLICK;
		}
		break;
	case 3:
		if(value == 0)
			state = 0;
		break;
	default:
		break;
	}
	return NO_CLICK;
}



