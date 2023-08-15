/*
 * user_inputs.h
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#ifndef USER_INPUTS_H_
#define USER_INPUTS_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

#include "button_driver.h"
#include "trimpot_driver.h"

struct UserInputsConfig {

    struct ButtonConfig {
        GPIO_TypeDef* port;
        uint16_t pin;
    } startButton, backButton, nextButton;

    struct TrimpotConfig {
        ADC_HandleTypeDef* hadc;
        uint32_t channel;
    } trimpotLeft, trimpotRight;
};

class UserInputs{
public:
	UserInputs(const UserInputsConfig& config);
	ComplexButton startButton;
	ComplexButton backButton;
	ComplexButton nextButton;

	Trimpot trimpotLeft;
	Trimpot trimpotRight;


private:
};





#endif /* USER_INPUTS_H_ */
