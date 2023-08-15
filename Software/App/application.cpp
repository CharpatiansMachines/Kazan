/*
 * Application.cpp
 *
 *  Created on: May 28, 2023
 *      Author: BRG
 */

#include "application.h"

#include "stm32f4xx_hal_gpio.h"
#include "main.h"
#include "display.h"
#include "hardware_test.h"


Application::Application()
    : userInputs(UserInputsConfig{
          { GPIOB, GPIO_PIN_7 },  // startButton
          { GPIOB, GPIO_PIN_6 },  // backButton
          { GPIOC, GPIO_PIN_7 },  // nextButton
          { &hadc2, TRIMPOT_0_CHANNEL },  // trimpotLeft
          { &hadc2, TRIMPOT_1_CHANNEL }   // trimpotRight
      }),
      sensorsHub(SensorsHubConfig{
          { // Line Detection Config
              &hadc1,
              {
                  LINE_SENSOR_FL_1_CHANNEL,
                  LINE_SENSOR_FL_2_CHANNEL,
                  LINE_SENSOR_FL_3_CHANNEL,
                  LINE_SENSOR_FR_1_CHANNEL,  // Note the comma here
                  LINE_SENSOR_FR_2_CHANNEL,
                  LINE_SENSOR_FR_3_CHANNEL
              },
              &hadc2,
              {
                  LINE_SENSOR_BL_CHANNEL,
                  LINE_SENSOR_BR_CHANNEL
              }
          },
          { // Enemy Detection Config
              { ENEMY_SENSOR_0_GPIO_Port, ENEMY_SENSOR_0_Pin },
              { ENEMY_SENSOR_1_GPIO_Port, ENEMY_SENSOR_1_Pin },
              { ENEMY_SENSOR_2_GPIO_Port, ENEMY_SENSOR_2_Pin },
              { ENEMY_SENSOR_3_GPIO_Port, ENEMY_SENSOR_3_Pin },
              { ENEMY_SENSOR_4_GPIO_Port, ENEMY_SENSOR_4_Pin },
              { ENEMY_SENSOR_5_GPIO_Port, ENEMY_SENSOR_5_Pin },
              { ENEMY_SENSOR_6_GPIO_Port, ENEMY_SENSOR_6_Pin },
              { ENEMY_SENSOR_7_GPIO_Port, ENEMY_SENSOR_7_Pin }
          }
          /// Initialize other sensor configs here...
      }),
      communication(USART2),     // communication driver
      screen(Hardware_Test)      //initial screen
{
    communication.config();
    Display_Init();
}

void Application::run()
{
	ComplexButton &startButton = userInputs.startButton;
	ComplexButton &backButton =  userInputs.backButton;
	ComplexButton &nextButton =  userInputs.nextButton;


	while(1)
	{
		/// User Input reading
		ButtonOutput startOutput = startButton.read();
		ButtonOutput backOutput = backButton.read();
		ButtonOutput nextOutput = nextButton.read();

		///user input management
		if(backOutput != NO_CLICK){
			screen--;
		}
		if(nextOutput != NO_CLICK){
			screen++;
		}

		///Screen
		switch(screen){
			case Information_Screen:
				Display_Title_Screen((char *)"Last Information");
				if(startOutput != NO_CLICK){

				}
				break;

			case Hardware_Test:
				Display_Title_Screen((char *)"Hardware Test");

				if(startOutput != NO_CLICK)
				{
					HardwareTestApp hardwareTestApp = HardwareTestApp(userInputs,sensorsHub, communication);
					hardwareTestApp.run();

				}
				break;
			case SoftwareTest:
				Display_Title_Screen((char *)"Software Test");
				if(startOutput != NO_CLICK){

				}
				break;
			case Battle_Application:
				Display_Title_Screen((char *)"Battle");
				if(startOutput != NO_CLICK){

				}
				break;
			default:
				Display_Error();
				break;
		}

	}
}

inline Application_Screen operator++(Application_Screen& screen, int) {
    Application_Screen current = screen;

    if (screen == Battle_Application) {
        screen = Information_Screen;
    } else {
        screen = static_cast<Application_Screen>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

inline Application_Screen operator--(Application_Screen& screen, int) {
    Application_Screen original = screen;
    if (screen == Information_Screen) {
        screen = Battle_Application;
    } else {
        screen = static_cast<Application_Screen>(static_cast<int>(screen) - 1);
    }
    return original;
}

