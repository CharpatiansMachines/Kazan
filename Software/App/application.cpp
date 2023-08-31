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
#include "initialize_parameters.h"
#include "strategy_selector.h"


Application::Application()
    : userInputs(UserInputsConfig{
          { B1_SELECT_GPIO_Port, B1_SELECT_Pin },  // startButton
          { B2_DOWN_GPIO_Port, B2_DOWN_Pin },  // backButton
          { B0_UP_GPIO_Port, B0_UP_Pin },  // nextButton
          { &hadc2, TRIMPOT_0_CHANNEL },  // trimpot0
          { &hadc2, TRIMPOT_1_CHANNEL }   // trimpot1
      }),
      stateControl(SensorsHubConfig{
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
	  motor(SABERTOOTH_UART),
      communication(CommunicationDriverConfig{
		DATA_UART,
		START_MODULE_GPIO_Port,
		START_MODULE_Pin,
	  })  // communication driver

{

}

void Application::run()
{


	userInputs.configAll();
	stateControl.configAll();
	communication.config();
	motor.init();
	Display_Init();
	Application_Screen screen = Hardware_Test;
	while(1)
	{
		userInputs.readInputs();

		///user input management
		if(userInputs.isBackRequest()){
			screen--;
		}
		if(userInputs.isNextRequest()){
			screen++;
		}

		///Screen
		switch(screen){
			case Information_Screen:
				Display_Title_Screen((char *)"Last Information");
				if(userInputs.isSelectRequest()){

				}
				break;

			case Hardware_Test:
				Display_Title_Screen((char *)"Hardware Test");

				if(userInputs.isSelectRequest())
				{
					HardwareTestApp hardwareTestApp = HardwareTestApp(userInputs,stateControl,motor, communication);
					hardwareTestApp.run();

				}
				break;
			case Initialize_Parameters_Screen:
				Display_Title_Screen((char *)"Initialize Parameters");
				if(userInputs.isSelectRequest()){
					InitializeParameters initializeParameters = InitializeParameters(userInputs,stateControl,motor, communication);
					initializeParameters.run();
				}
				break;
			case Battle_Application:
				Display_Title_Screen((char *)"Battle");
				if(userInputs.isSelectRequest()){
					StrategySelector strategySelectorApp = StrategySelector(userInputs,stateControl,motor, communication);
					strategySelectorApp.run();
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

