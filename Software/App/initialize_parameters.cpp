/*
 * initialize_parameters.cpp
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#include "initialize_parameters.h"
#include "display.h"
#include "timer.h"
#include "motion.h"

void InitializeParameters::run()
{
    while(true)
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

	Power_Set_Screen_Type powerScreen = High_Power_Show_Screen;

	char showDescription[] = "Hstart to start";
	char setDescription[] = "Hstart to set";
	char startDescription[] = "Any key to abort";
	while(true)
	{
        userInputs.readInputs();

        /// User input management
        if(userInputs.isReturnBackRequest()){
            return;
        }
        if(userInputs.isBackRequest()){
        	powerScreen++;
        }
        if(userInputs.isNextRequest()){
        	powerScreen--;
        }
        int8_t leftPower = userInputs.getData0(-100, 100);
        int8_t rightPower = userInputs.getData1(-100, 100);
        switch (powerScreen) {
            case High_Power_Show_Screen:
            	Display_2_Power_Screen(
            			(char *)"High Power Show",
						powerLevels.highLeftPower,
						powerLevels.highRightPower,
						showDescription
					);
            	if(userInputs.isSelectRequest()){
            		powerScreen = High_Power_Set_Screen;
            	}else if(userInputs.isSetValueRequest()){
            		powerScreen = High_Power_Start_Screen;
            	}
                break;
            case High_Power_Set_Screen:
            	Display_2_Power_Screen(
					(char *)"High Power Set",
					rightPower,
					leftPower,
					setDescription
				);
            	if(userInputs.isSelectRequest()){
					powerScreen = High_Power_Show_Screen;
				}else if(userInputs.isSetValueRequest()){
					powerLevels.highLeftPower = leftPower;
					powerLevels.highRightPower = rightPower;
					powerScreen = High_Power_Show_Screen;
				}
                break;
            case High_Power_Start_Screen:
            	if(userInputs.isAnyKey()){
            		powerScreen = High_Power_Show_Screen;
            	}
            	Display_Clear();
            	strategist.testMotion(Motion_Forward_High);
            	Display_2_Power_Screen(
					(char *)"!High Power Start!",
					powerLevels.highLeftPower,
					powerLevels.highRightPower,
					startDescription
				);
                break;
            case Medium_Power_Show_Screen:
                 Display_2_Power_Screen(
                     (char *)"Medium Power Show",
                     powerLevels.mediumLeftPower,
                     powerLevels.mediumRightPower,
                     showDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Medium_Power_Set_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerScreen = Medium_Power_Start_Screen;
                 }
                 break;
             case Medium_Power_Set_Screen:
                 Display_2_Power_Screen(
                     (char *)"Medium Power Set",
                     rightPower,
                     leftPower,
                     setDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Medium_Power_Show_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerLevels.mediumLeftPower = leftPower;
                     powerLevels.mediumRightPower = rightPower;
                     powerScreen = Medium_Power_Show_Screen;
                 }
                 break;
             case Medium_Power_Start_Screen:

                 if(userInputs.isAnyKey()){
                     powerScreen = Medium_Power_Show_Screen;
                 }
                 Display_Clear();
                 strategist.testMotion(Motion_Forward_Medium);
                 Display_2_Power_Screen(
                     (char *)"!Medium Power Start!",
                     powerLevels.mediumLeftPower,
                     powerLevels.mediumRightPower,
                     startDescription
                 );
                 break;

             case Low_Power_Show_Screen:
                 Display_2_Power_Screen(
                     (char *)"Low Power Show",
                     powerLevels.lowLeftPower,
                     powerLevels.lowRightPower,
                     showDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Low_Power_Set_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerScreen = Low_Power_Start_Screen;
                 }
                 break;
             case Low_Power_Set_Screen:
                 Display_2_Power_Screen(
                     (char *)"Low Power Set",
                     rightPower,
                     leftPower,
                     setDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Low_Power_Show_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerLevels.lowLeftPower = leftPower;
                     powerLevels.lowRightPower = rightPower;
                     powerScreen = Low_Power_Show_Screen;
                 }
                 break;
             case Low_Power_Start_Screen:

                 if(userInputs.isAnyKey()){
                     powerScreen = Low_Power_Show_Screen;
                 }
                 Display_Clear();
                 strategist.testMotion(Motion_Forward_Low);
                 Display_2_Power_Screen(
                     (char *)"!Low Power Start!",
                     powerLevels.lowLeftPower,
                     powerLevels.lowRightPower,
                     startDescription
                 );
                 break;

             case Circle_50_Right_Power_Show_Screen:
                 Display_2_Power_Screen(
                     (char *)"Circle 50 Right Power Show",
                     powerLevels.highLeftPower,
                     powerLevels.circle50RightPower,
                     showDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Circle_50_Right_Power_Set_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerScreen = Circle_50_Right_Power_Start_Screen;
                 }
                 break;
             case Circle_50_Right_Power_Set_Screen:
                 Display_2_Power_Screen(
                     (char *)"Circle 50 Right Power Set",
                     powerLevels.highLeftPower,
                     rightPower,
                     setDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Circle_50_Right_Power_Show_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerLevels.circle50RightPower = rightPower;
                     powerScreen = Circle_50_Right_Power_Show_Screen;
                 }
                 break;
             case Circle_50_Right_Power_Start_Screen:

                 if(userInputs.isAnyKey()){
                     powerScreen = Circle_50_Right_Power_Show_Screen;
                 }
                 Display_Clear();
                 strategist.testMotion(Motion_Circle_Right_50);
                 Display_2_Power_Screen(
                     (char *)"!Circle 50 Right Power Start!",
                     powerLevels.highLeftPower,
                     powerLevels.circle50RightPower, // Assuming there's no left value for this
                     startDescription
                 );
                 break;

             case Circle_50_Left_Power_Show_Screen:
                 Display_2_Power_Screen(
                     (char *)"Circle 50 Left Power Show",
                     powerLevels.circle50LeftPower,
                     powerLevels.highRightPower,  // Assuming there's no right value for this
                     showDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Circle_50_Left_Power_Set_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerScreen = Circle_50_Left_Power_Start_Screen;
                 }
                 break;
             case Circle_50_Left_Power_Set_Screen:
                 Display_2_Power_Screen(
                     (char *)"Circle 50 Left Power Set",
                     leftPower,
                     powerLevels.highRightPower,  // Assuming there's no right value for this
                     setDescription
                 );
                 if(userInputs.isSelectRequest()){
                     powerScreen = Circle_50_Left_Power_Show_Screen;
                 }else if(userInputs.isSetValueRequest()){
                     powerLevels.circle50LeftPower = leftPower;
                     powerScreen = Circle_50_Left_Power_Show_Screen;
                 }
                 break;
             case Circle_50_Left_Power_Start_Screen:
                 if(userInputs.isAnyKey()){
                     powerScreen = Circle_50_Left_Power_Show_Screen;
                 }
                 Display_Clear();
                 strategist.testMotion(Motion_Circle_Left_50);
                 Display_2_Power_Screen(
                     (char *)"!Circle 50 Left Power Start!",
                     powerLevels.circle50LeftPower,
                     powerLevels.highRightPower,  // Assuming there's no right value for this
                     startDescription
                 );
                 break;
        }
	}

}

void InitializeParameters::runTimeSetApplication()
{

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
Power_Set_Screen_Type operator++(Power_Set_Screen_Type& screen, int) {
    Power_Set_Screen_Type current = screen;

    switch (screen) {
        case High_Power_Show_Screen:
            screen = Medium_Power_Show_Screen;
            break;
        case High_Power_Set_Screen:
            screen = Medium_Power_Show_Screen;
            break;
        case High_Power_Start_Screen:
            screen = Medium_Power_Show_Screen;
            break;

        case Medium_Power_Show_Screen:
            screen = Low_Power_Show_Screen;
            break;
        case Medium_Power_Set_Screen:
            screen = Low_Power_Show_Screen;
            break;
        case Medium_Power_Start_Screen:
            screen = Low_Power_Show_Screen;
            break;

        case Low_Power_Show_Screen:
            screen = Circle_50_Right_Power_Show_Screen;
            break;
        case Low_Power_Set_Screen:
            screen = Circle_50_Right_Power_Show_Screen;
            break;
        case Low_Power_Start_Screen:
            screen = Circle_50_Right_Power_Show_Screen;
            break;

        case Circle_50_Right_Power_Show_Screen:
            screen = Circle_50_Left_Power_Show_Screen;
            break;
        case Circle_50_Right_Power_Set_Screen:
            screen = Circle_50_Left_Power_Show_Screen;
            break;
        case Circle_50_Right_Power_Start_Screen:
            screen = Circle_50_Left_Power_Show_Screen;
            break;

        case Circle_50_Left_Power_Show_Screen:
            screen = High_Power_Show_Screen;
            break;
        case Circle_50_Left_Power_Set_Screen:
            screen = High_Power_Show_Screen;
            break;
        case Circle_50_Left_Power_Start_Screen:
            screen = High_Power_Show_Screen;
            break;

        default:
            screen = High_Power_Show_Screen; // Default to High_Power_Show_Screen
            break;
    }

    return current; // Return old value for postfix increment
}

Power_Set_Screen_Type operator--(Power_Set_Screen_Type& screen, int) {
    Power_Set_Screen_Type current = screen;

    switch (screen) {
        case High_Power_Show_Screen:
            screen = Circle_50_Left_Power_Show_Screen;
            break;
        case High_Power_Set_Screen:
            screen = High_Power_Show_Screen;
            break;
        case High_Power_Start_Screen:
            screen = High_Power_Show_Screen;
            break;

        case Medium_Power_Show_Screen:
            screen = High_Power_Show_Screen;
            break;
        case Medium_Power_Set_Screen:
            screen = Medium_Power_Show_Screen;
            break;
        case Medium_Power_Start_Screen:
            screen = Medium_Power_Show_Screen;
            break;

        case Low_Power_Show_Screen:
            screen = Medium_Power_Show_Screen;
            break;
        case Low_Power_Set_Screen:
            screen = Low_Power_Show_Screen;
            break;
        case Low_Power_Start_Screen:
            screen = Low_Power_Show_Screen;
            break;

        case Circle_50_Right_Power_Show_Screen:
            screen = Low_Power_Show_Screen;
            break;
        case Circle_50_Right_Power_Set_Screen:
            screen = Circle_50_Right_Power_Show_Screen;
            break;
        case Circle_50_Right_Power_Start_Screen:
            screen = Circle_50_Right_Power_Show_Screen;
            break;

        case Circle_50_Left_Power_Show_Screen:
            screen = Circle_50_Right_Power_Show_Screen;
            break;
        case Circle_50_Left_Power_Set_Screen:
            screen = Circle_50_Left_Power_Show_Screen;
            break;
        case Circle_50_Left_Power_Start_Screen:
            screen = Circle_50_Left_Power_Show_Screen;
            break;

        default:
            screen = High_Power_Show_Screen; // Default to High_Power_Show_Screen
            break;
    }

    return current; // Return old value for postfix decrement
}




