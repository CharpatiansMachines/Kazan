/*
 * hardware_test.h
 *
 *  Created on: Jul 25, 2023
 *      Author: BRG
 */

#ifndef HARDWARE_TEST_H_
#define HARDWARE_TEST_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

#include "button_driver.h"
#include "communication_driver.h"
#include "sensors_hub.h"
#include "user_inputs.h"

enum Hardware_Test_Screen{
	TRIMPOTS_TEST = 0x00,
	LINE_SENSORS_TEST,
	ENEMY_SENSORS_TEST,
	MOTOR_TEST,
};
Hardware_Test_Screen operator++(Hardware_Test_Screen& screen, int);
Hardware_Test_Screen operator--(Hardware_Test_Screen& screen, int);

enum Line_Detection_Test_Screen{
	LINE_POSITION_SCREEN = 0x00,
	FILTER_CHANGE_SCREEN,
	SENSORS_OUTPUT_SCREEN,
};
Line_Detection_Test_Screen operator++(Line_Detection_Test_Screen& screen, int);
Line_Detection_Test_Screen operator--(Line_Detection_Test_Screen& screen, int);



class HardwareTestApp {
	public:
	HardwareTestApp(UserInputs& userInputs,
					SensorsHub& sensorsHub,
					Communication_Driver& comm)
	        : userInputs(userInputs),
			  sensorsHub(sensorsHub),
	          communication(comm),
			  screen(TRIMPOTS_TEST){}
	void run();
private:
	UserInputs &userInputs;
	SensorsHub &sensorsHub;
	Communication_Driver &communication;
	Hardware_Test_Screen screen;
	void runLineDetectionTest();
	void runEnemySensorsTest();

};





#endif /* HARDWARE_TEST_H_ */
