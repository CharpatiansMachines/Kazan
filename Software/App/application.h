/*
 * Application.h
 *
 *  Created on: May 28, 2023
 *      Author: BRG
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <state_control.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

#include "communication_driver.h"
#include "user_inputs.h"
#include "motor_driver.h"

enum Application_Screen{
	Information_Screen = 0x00,
	Hardware_Test,
	SoftwareTest,
	Battle_Application,
};

 Application_Screen operator++(Application_Screen& screen, int) ;

 Application_Screen operator--(Application_Screen& screen, int);

class Application {
	public:
	Application();
	void run();
private:
	UserInputs userInputs;
	StateControl stateControl;
	Motor motor;
	Communication_Driver communication;
	Application_Screen screen;


	void hardwareTest();

};

#endif /* APPLICATION_H_ */
