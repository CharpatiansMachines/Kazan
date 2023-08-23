/*
 * initialize_parameters.h
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#ifndef APP_INITIALIZE_PARAMETERS_H_
#define APP_INITIALIZE_PARAMETERS_H_
#include <state_control.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

#include "button_driver.h"
#include "communication_driver.h"
#include "user_inputs.h"
#include "motor_driver.h"
#include "strategist.h"

enum Initialize_Parameters_Screen_Type{
	SET_POWER_SCREEN = 0x00,
	TIME_SET_SCREEN
};
Initialize_Parameters_Screen_Type operator++(Initialize_Parameters_Screen_Type& screen, int);

Initialize_Parameters_Screen_Type operator--(Initialize_Parameters_Screen_Type& screen, int);

class InitializeParameters {
public:
	InitializeParameters(UserInputs& userInputs,
					StateControl& sensorsHub,
					Motor& motor,
					Communication_Driver& comm)
	        : userInputs(userInputs),
			  sensorsHub(sensorsHub),
			  motor(motor),
	          communication(comm),
			  strategist(sensorsHub, motor, comm),
			  screen(SET_POWER_SCREEN){}
	void run();
private:
	UserInputs &userInputs;
	StateControl &sensorsHub;
	Motor& motor;
	Communication_Driver &communication;
	Strategist strategist;
	Initialize_Parameters_Screen_Type screen;
	void runPowerSetApplication();
	void runTimeSetApplication();

};





#endif /* APP_INITIALIZE_PARAMETERS_H_ */
