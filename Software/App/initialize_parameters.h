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
	SET_TIME_SCREEN
};
Initialize_Parameters_Screen_Type operator++(Initialize_Parameters_Screen_Type& screen, int);

Initialize_Parameters_Screen_Type operator--(Initialize_Parameters_Screen_Type& screen, int);

enum Power_Set_Screen_Type{
	High_Power_Screen,
	Medium_Power_Screen,
	Low_Power_Screen,
	Circle_50_Left_Power_Screen,
	Circle_50_Right_Power_Screen,
};
Power_Set_Screen_Type operator++(Power_Set_Screen_Type& screen, int);

Power_Set_Screen_Type operator--(Power_Set_Screen_Type& screen, int);

enum Secondary_Screen_Type{
	Show_Screen,
	Set_Screen,
	Start_Screen,
};
Secondary_Screen_Type operator++(Secondary_Screen_Type& screen, int);

Secondary_Screen_Type operator--(Secondary_Screen_Type& screen, int);

enum Time_Set_Screen_Type{
	Braking_Time_Screen,
	Power_10_Time_Screen,
	Power_20_Time_Screen,
	Power_50_Time_Screen,
	Power_100_Time_Screen,
	Rotation_30_Time_Screen,
	Rotation_60_Time_Screen,
	Rotation_90_Time_Screen,
	Rotation_120_Time_Screen,
};
Time_Set_Screen_Type operator++(Time_Set_Screen_Type& screen, int);

Time_Set_Screen_Type operator--(Time_Set_Screen_Type& screen, int);

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
