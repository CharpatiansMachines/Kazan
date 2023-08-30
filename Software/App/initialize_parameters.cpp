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

struct PowerSet {
	const char *const title;
	int8_t *const leftPower;
	int8_t *const rightPower;
	void (*const motion)(Motor&);
};
const PowerSet powerSets[] __attribute__((section(".rodata"))) = {
	{"High Power Set", &powerLevels.highLeftPower, &powerLevels.highRightPower, Motion_Forward_High},
	{"Medium Power Set", &powerLevels.mediumLeftPower, &powerLevels.mediumRightPower, Motion_Forward_Medium},
	{"Low Power Set", &powerLevels.lowLeftPower, &powerLevels.lowRightPower, Motion_Forward_Low},
	{"Circle Left 50 Power Set", &powerLevels.circleLeft50LeftPower, &powerLevels.highRightPower, Motion_Circle_Left_50},
	{"Circle Right 50 Power Set", &powerLevels.highLeftPower, &powerLevels.circleRight50RightPower, Motion_Circle_Right_50}
};
const char *const descriptions[] __attribute__((section(".rodata"))) = {
		"<Show screen>",
		"HStart to Set",
		"!Start Screen!"
};
void InitializeParameters::runPowerSetApplication()
{
	Power_Set_Screen_Type powerScreen = High_Power_Screen;
	Secondary_Screen_Type secondScreen = Show_Screen;
	while(true)
	{
        userInputs.readInputs();

        /// User input management
        if(userInputs.isReturnBackRequest()) return;
        uint8_t screenId = static_cast<int>(powerScreen);
        const PowerSet powerSet = powerSets[screenId];

        switch (secondScreen) {
			case Show_Screen:
				if(userInputs.isBackRequest()) powerScreen--;
				if(userInputs.isNextRequest()) powerScreen++;
				Display_2_Power_Screen(
					 powerSet.title,
					 *powerSet.leftPower,
					 *powerSet.rightPower, // Assuming there's no left value for this
					 descriptions[0]
				 );

				if(userInputs.isSelectRequest()){
					secondScreen = Set_Screen;
				}else if(userInputs.isSetValueRequest()){
					secondScreen = Start_Screen;
				}
				break;

			case Set_Screen:
			{
				int8_t leftPower = userInputs.getData0(-100, 100);
				int8_t rightPower = userInputs.getData1(-100, 100);
				Display_2_Power_Screen(
					powerSet.title,
					 leftPower,
					 rightPower, // Assuming there's no left value for this
					 descriptions[1]
				 );
			       if(userInputs.isSelectRequest()){
			    	   secondScreen = Show_Screen;
					 }else if(userInputs.isSetValueRequest()){
						 *powerSet.leftPower = leftPower;
						 *powerSet.rightPower = rightPower;
						 secondScreen = Show_Screen;
					 }
			       break;
			}

			case Start_Screen:
				if(userInputs.isAnyKey()){
					secondScreen = Show_Screen;
				 }
				Display_Clear();
				strategist.runTestMotion(Motion_Forward_Medium);
				 Display_2_Power_Screen(
					 powerSet.title,
					 *powerSet.leftPower,
					 *powerSet.rightPower,
					 descriptions[2]
				 );
				break;
			default:
				Display_Error();
				break;
		}
	}

}

struct TimeSet {
	const char *const title;
	uint16_t *const time;
	int8_t *const leftPower;
	int8_t *const rightPower;
	void (*const motion)(Motor&);
};
const TimeSet timeSets[] __attribute__((section(".rodata"))) = {
	{"Braking Time", &actionTimes.brakingTime, &powerLevels.highLeftPower, &powerLevels.highRightPower, Motion_Forward_Medium},
	{"Power 10 Time", &actionTimes.mediumPower10cm, &powerLevels.mediumLeftPower, &powerLevels.mediumRightPower, Motion_Forward_Medium},
	{"Power 20 Time", &actionTimes.mediumPower20cm, &powerLevels.mediumLeftPower, &powerLevels.mediumRightPower, Motion_Forward_Medium},
	{"Power 50 Time", &actionTimes.mediumPower50cm, &powerLevels.mediumLeftPower, &powerLevels.mediumRightPower, Motion_Forward_Medium},
	{"Power 100 Time", &actionTimes.mediumPower100cm, &powerLevels.mediumLeftPower, &powerLevels.mediumRightPower, Motion_Forward_Medium},
	{"Rotation 30* Time", &actionTimes.rotation30degree, &powerLevels.highLeftPower, &powerLevels.highRightPower, Motion_Rotate_Left_High},
	{"Rotation 60* Time", &actionTimes.rotation60degree, &powerLevels.highLeftPower, &powerLevels.highRightPower, Motion_Rotate_Left_High},
	{"Rotation 90* Time", &actionTimes.rotation90degree, &powerLevels.highLeftPower, &powerLevels.highRightPower, Motion_Rotate_Left_High},
	{"Rotation 120* Time", &actionTimes.rotation120degree, &powerLevels.highLeftPower, &powerLevels.highRightPower, Motion_Rotate_Left_High}
};

void InitializeParameters::runTimeSetApplication()
{
	Time_Set_Screen_Type timeSetScreen = Braking_Time_Screen;
	Secondary_Screen_Type secondScreen = Show_Screen;
	while(true)
	{
        userInputs.readInputs();

        /// User input management
        if(userInputs.isReturnBackRequest()) return;
        uint8_t screenId = static_cast<int>(timeSetScreen);
        const TimeSet timeSet = timeSets[screenId];

        switch (secondScreen) {
			case Show_Screen:
				if(userInputs.isBackRequest()) timeSetScreen--;
				if(userInputs.isNextRequest()) timeSetScreen++;
				Display_2_Power_And_Time_Screen(
					 timeSet.title,
					 *timeSet.leftPower,
					 *timeSet.rightPower,
					 *timeSet.time,
					 descriptions[0]
				 );

				if(userInputs.isSelectRequest()){
					secondScreen = Set_Screen;
				}else if(userInputs.isSetValueRequest()){
					secondScreen = Start_Screen;
				}
				break;

			case Set_Screen:
			{
				uint16_t time = userInputs.getData0(0, 3000);
				Display_2_Power_And_Time_Screen(
					 timeSet.title,
					 *timeSet.leftPower,
					 *timeSet.rightPower,
					 time,
					 descriptions[1]
				 );
			       if(userInputs.isSelectRequest()){
			    	   secondScreen = Show_Screen;
					 }else if(userInputs.isSetValueRequest()){
						 *timeSet.time = time;
						 secondScreen = Show_Screen;
					 }
			       break;
			}

			case Start_Screen:
				if(userInputs.isAnyKey()){
					secondScreen = Show_Screen;
				 }
				Display_Clear();
				if(timeSetScreen == Braking_Time_Screen){
					strategist.runTestMotion(timeSet.motion);
				}else{
					strategist.runTestTimedMotion(TimedMotion(timeSet.motion,(uint32_t) timeSet.time));
				}

				Display_2_Power_And_Time_Screen(
					 timeSet.title,
					 *timeSet.leftPower,
					 *timeSet.rightPower,
					 *timeSet.time,
					 descriptions[2]
				 );
				break;
			default:
				Display_Error();
				break;
		}
	}

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

    if (screen == Circle_50_Right_Power_Screen) {
        screen = High_Power_Screen;  // loop back to the start if at the end
    } else {
        screen = static_cast<Power_Set_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

Power_Set_Screen_Type operator--(Power_Set_Screen_Type& screen, int) {
    Power_Set_Screen_Type current = screen;

    if (screen == High_Power_Screen) {
        screen = Circle_50_Left_Power_Screen;  // loop back to the end if at the start
    } else {
        screen = static_cast<Power_Set_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}

Secondary_Screen_Type operator++(Secondary_Screen_Type& screen, int) {
    Secondary_Screen_Type current = screen;

    if (screen == Start_Screen) {
        screen = Show_Screen;  // loop back to the start if at the end
    } else {
        screen = static_cast<Secondary_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

Secondary_Screen_Type operator--(Secondary_Screen_Type& screen, int) {
    Secondary_Screen_Type current = screen;

    if (screen == Show_Screen) {
        screen = Start_Screen;  // loop back to the end if at the start
    } else {
        screen = static_cast<Secondary_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}

Time_Set_Screen_Type operator++(Time_Set_Screen_Type& screen, int) {
    Time_Set_Screen_Type current = screen;

    if (screen == Rotation_120_Time_Screen) {
        screen = Braking_Time_Screen;  // loop back to the start if at the end
    } else {
        screen = static_cast<Time_Set_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

Time_Set_Screen_Type operator--(Time_Set_Screen_Type& screen, int) {
    Time_Set_Screen_Type current = screen;

    if (screen == Braking_Time_Screen) {
        screen = Power_100_Time_Screen;  // loop back to the end if at the start
    } else {
        screen = static_cast<Time_Set_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}




