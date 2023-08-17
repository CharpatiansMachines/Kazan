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
	void configAll();
	void readInputs();

	bool isAnyKey();
	bool isReturnBackRequest();
	bool isBackRequest();
	bool isNextRequest();
	bool isSelectRequest();
	bool isSetValueRequest();

	uint16_t getData0() const;
	uint16_t getData1() const;
	float getData0(float min,float max) const;
	float getData1(float min, float max) const;


private:
	ComplexButton startButton;
	ComplexButton backButton;
	ComplexButton nextButton;

	Trimpot trimpot0;
	Trimpot trimpot1;

};





#endif /* USER_INPUTS_H_ */
