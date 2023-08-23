/*
 * initialize_parameters.cpp
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#include "initialize_parameters.h"
#include "display.h"
#include "timer.h"

void InitializeParameters::run()
{
    while(1)
    {
        userInputs.readInputs();

        /// User input management
        if(userInputs.isReturnBackRequest()){
            return;
        }
        if(userInputs.isBackRequest()){
            screen--;
        }
        if(userInputs.isNextRequest()){
            screen++;
        }

        /// UI Displaying
        switch(screen) {
            case SET_POWER_SCREEN:
            	Display_Title_Screen((char *)"Set Power");
            	if(userInputs.isSelectRequest()){
            		runPowerSetApplication();
            	}

                break;
            case SET_TIME_SCREEN:
            	Display_Title_Screen((char *)"Set Time");
            	if(userInputs.isSelectRequest()){
            	   runTimeSetApplication();
				}
                break;
            default:
                Display_Error();
                break;
        }
    }
}

void InitializeParameters::runPowerSetApplication()
{
    // Power Setting Logic Here. For example:
    int8_t powerLevel = userInputs.getData0();  // Assuming getData0 fetches desired power level
//    motor.setPower(powerLevel);  // Assuming Motor has setPower method
//    Display_Value((char *)"Power Level", powerLevel); // Assuming such display function exists
//    if(userInputs.isSetValueRequest()){
//        strategist.updatePowerLevel(powerLevel); // Assuming strategist can handle this information
//    }
}

void InitializeParameters::runTimeSetApplication()
{
    // Time Setting Logic Here. For example:
    uint32_t timeDuration = userInputs.getData1(); // Assuming getData1 fetches desired time duration
//    Display_Value((char *)"Time Duration", timeDuration); // Assuming such display function exists
//    if(userInputs.isSetValueRequest()){
//        strategist.updateTimeDuration(timeDuration); // Assuming strategist can handle this information
//    }
}

Initialize_Parameters_Screen_Type operator++(Initialize_Parameters_Screen_Type& screen, int) {
    Initialize_Parameters_Screen_Type current = screen;

    if (screen == SET_TIME_SCREEN) {
        screen = SET_POWER_SCREEN;  // loop back to the start if at the end
    } else {
        screen = static_cast<Initialize_Parameters_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

Initialize_Parameters_Screen_Type operator--(Initialize_Parameters_Screen_Type& screen, int) {
    Initialize_Parameters_Screen_Type current = screen;

    if (screen == SET_POWER_SCREEN) {
        screen = SET_TIME_SCREEN;  // loop back to the end if at the start
    } else {
        screen = static_cast<Initialize_Parameters_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}




