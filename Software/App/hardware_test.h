/*
 * hardware_test.h
 *
 *  Created on: Jul 25, 2023
 *      Author: BRG
 */

#ifndef HARDWARE_TEST_H_
#define HARDWARE_TEST_H_

#include <state_control.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

#include "button_driver.h"
#include "communication_driver.h"
#include "user_inputs.h"
#include "motor_driver.h"

enum Hardware_Test_Screen_Type{
	TRIMPOTS_TEST = 0x00,
	LINE_SENSORS_TEST,
	ENEMY_SENSORS_TEST,
	MOTOR_TEST,
};
Hardware_Test_Screen_Type operator++(Hardware_Test_Screen_Type& screen, int);
Hardware_Test_Screen_Type operator--(Hardware_Test_Screen_Type& screen, int);

enum Line_Detection_Screen_Type{
	LINE_POSITION_SCREEN = 0x00,
	FILTER_CHANGE_SCREEN,
	SENSORS_OUTPUT_SCREEN,
};
Line_Detection_Screen_Type operator++(Line_Detection_Screen_Type& screen, int);
Line_Detection_Screen_Type operator--(Line_Detection_Screen_Type& screen, int);

enum Enemy_Detection_Screen_Type{
	ENEMY_SENSORS_OUTPUT_SCREEN,
	ENEMY_POSITION_VOTING_SCREEN,
};
Enemy_Detection_Screen_Type operator++(Enemy_Detection_Screen_Type& screen, int);

Enemy_Detection_Screen_Type operator--(Enemy_Detection_Screen_Type& screen, int);

enum Motor_Test_Screen_Type{
	MOTOR_SET_POWER_SCREEN,
	MOTOR_RUN_SCREEN,
	MOTOR_SET_TIMER_SCREEN,
};

Motor_Test_Screen_Type operator++(Motor_Test_Screen_Type& screen, int);

Motor_Test_Screen_Type operator--(Motor_Test_Screen_Type& screen, int);

class HardwareTestApp {
	public:
	HardwareTestApp(UserInputs& userInputs,
					StateControl& sensorsHub,
					Motor& motor,
					Communication_Driver& comm)
	        : userInputs(userInputs),
			  sensorsHub(sensorsHub),
			  motor(motor),
	          communication(comm),
			  screen(TRIMPOTS_TEST){}
	void run();
private:
	UserInputs &userInputs;
	StateControl &sensorsHub;
	Motor& motor;
	Communication_Driver &communication;
	Hardware_Test_Screen_Type screen;
	void runLineDetectionTest();
	void runEnemySensorsTest();
	void runMotorTest();

};





#endif /* HARDWARE_TEST_H_ */
