/*
 * hardware_test.cpp
 *
 *  Created on: Jul 25, 2023
 *      Author: BRG
 */

#include "hardware_test.h"
#include "hardware_test.h"

#include "stm32f4xx_hal_gpio.h"

#include "display.h"
#include "timer.h"

void HardwareTestApp::run()
{

	while(1)
	{
		userInputs.readAll();

		///user input management
		if(userInputs.isReturnBackRequest()){
			return;
		}
		if(userInputs.isBackRequest()){
			screen--;
		}
		if(userInputs.isNextRequest()){
			screen++;
		}

		/// UI Displayinh
		switch(screen){
			case TRIMPOTS_TEST:
				Display_2_Numbers(
						(char *)"Trimpots values",
						userInputs.getData0() ,
						userInputs.getData1()
						);
				break;
			case LINE_SENSORS_TEST:
				Display_Small_Title_Screen((char *)"Line Detection Output Test");
				if(userInputs.isSelectRequest()){
					runLineDetectionTest();
				}
				break;
			case ENEMY_SENSORS_TEST:
				Display_Title_Screen((char *)"Enemy Sensor Test");
				if(userInputs.isSelectRequest()){
					runEnemySensorsTest();
				}
				break;
			case MOTOR_TEST:
				Display_Title_Screen((char *)"Motor Test");
				if(userInputs.isSelectRequest()){
					runMotorTest();
				}
				break;
			default:
				Display_Error();
				break;
		}


	}
}
void HardwareTestApp::runEnemySensorsTest(){
	///Extract components

	EnemyDetection enemyDetection = sensorsHub.enemyDetection;

	Enemy_Detection_Screen_Type  enemySensorsScren = ENEMY_SENSORS_OUTPUT_SCREEN;

	while(true)
	{
		userInputs.readAll();

		///user input management
		if(userInputs.isReturnBackRequest()){
			return;
		}
		if(userInputs.isBackRequest()){
			enemySensorsScren--;
		}
		if(userInputs.isNextRequest()){
			enemySensorsScren++;
		}


		 switch(enemySensorsScren) {
				case ENEMY_SENSORS_OUTPUT_SCREEN:
				{
					uint32_t sensorsValues = enemyDetection.readSensors();
					uint8_t values[EnemyDetection::NUMBER_OF_SENSORS];
					for(uint8_t i = 0; i < EnemyDetection::NUMBER_OF_SENSORS; i ++){
						values[i] = (sensorsValues & (1 << i)) != 0;
					}
					Display_N_Values_Screen(values, EnemyDetection::NUMBER_OF_SENSORS);
					break;

				}

				case ENEMY_POSITION_VOTING_SCREEN:
				{
					int8_t votes[EnemyPosition::KNOWN_POSITIONS_NO];
					enemyDetection.readAndTakeSensorsVotes(votes);
					Display_Enemy_Sensors_Votes(votes);

					break;
				}


				default:
					Display_Error();
					break;
			}
	}
}

void HardwareTestApp::runLineDetectionTest()
{

	LineDetection& lineDetecion = sensorsHub.lineDetection;
	Line_Detection_Screen_Type lineDetectionScreen = LINE_POSITION_SCREEN;

	///LOOP
	while(true)
	{
		userInputs.readAll();

		///user input management
		if(userInputs.isReturnBackRequest()){
			return;
		}
		if(userInputs.isBackRequest()){
			lineDetectionScreen--;
		}
		if(userInputs.isNextRequest()){
			lineDetectionScreen++;
		}

		///UI
		switch(lineDetectionScreen){
			case LINE_POSITION_SCREEN:
			{
				/// Line Position Screen
				LinePosition linePosition = lineDetecion.readAndConvertToLinePosition();
				Display_Line_Position_Screen(
							linePosition,
							lineDetecion.isWhiteFilter, //whiteFilter
							lineDetecion.isBlackFilter, //BlackFilter
							(char *)"Hstart to reset>"     //description
				);
				if(userInputs.isSetValueRequest()){
					lineDetecion.resetFiltersToDefault();
				}
				break;
			}


			case FILTER_CHANGE_SCREEN:
			{
				///Change Filter Screen;
				LinePosition linePosition = lineDetecion.readAndConvertToLinePosition();
				float data0 = userInputs.getData0(0, 255);
				float data1 = userInputs.getData1(0, 255);

				Display_Line_Position_Screen(
						linePosition,
						data0, //whiteFilter
						data1, //BlackFilter
						(char *)"Hstart to change>"              //description
				);
				if(userInputs.isSetValueRequest()){
					lineDetecion.isWhiteFilter = data0;
					lineDetecion.isBlackFilter = data1;
					lineDetectionScreen = LINE_POSITION_SCREEN;
				}
				break;
			}

			case SENSORS_OUTPUT_SCREEN:
			{
				///Sensors Output View
				uint8_t sensorsValues[LineDetection::LINE_SENSORS_NUMBER];
				lineDetecion.readAll(sensorsValues);
				Display_N_Values_Screen(sensorsValues, LineDetection::LINE_SENSORS_NUMBER);

			}
				break;
			default:
				Display_Error();
		}

	}
}

void HardwareTestApp::runMotorTest()
{
	const uint32_t MIN_TIMER = 500;
	const uint32_t MAX_TIMER = 10000;
	uint32_t timer = MIN_TIMER * 2;           ///Set Default Timer
	uint32_t clock;
	Motor_Test_Screen_Type motorScreen = MOTOR_SET_POWER_SCREEN;
	///LOOP
	while(true)
	{
		userInputs.readAll();
		///user input management
		if(userInputs.isReturnBackRequest()){
			motor.stop();
			return;
		}
		if(userInputs.isBackRequest()){
			motorScreen--;
		}
		if(userInputs.isNextRequest()){
			motorScreen++;
		}
		int8_t leftPower = userInputs.getData0(Motor::MAX_REVERSE_POWER, Motor::MAX_POWER);
		int8_t rightPower = userInputs.getData1(Motor::MAX_REVERSE_POWER,Motor::MAX_POWER);

	    switch(motorScreen) {
	        case MOTOR_SET_POWER_SCREEN:
	        	Display_2_Power_And_Time_Screen((char *)"Start Motor", leftPower, rightPower, timer, (char *)"Hstart to start");
	        	if(userInputs.isSetValueRequest()){
	        		motorScreen = MOTOR_RUN_SCREEN;
	        		clock = Timer_Set_Clock(timer);
	        	}
	            break;
	        case MOTOR_RUN_SCREEN:
	        {
	        	int64_t remainTime = Timer_Get_Remain_Time(clock);
	        	if(userInputs.isAnyKey() || remainTime <= 0){
	        		// STOP Conditiion
	        		motor.stop();
	        		motorScreen = MOTOR_SET_POWER_SCREEN;
	        	}else{
					Display_2_Power_And_Time_Screen((char *)"Motor On", leftPower, rightPower, remainTime,(char *) "Any key to stop");
	        		motor.changePower(leftPower, rightPower);
	        	}
	        	break;
	        }
	        case MOTOR_SET_TIMER_SCREEN:
	        {
	        	uint32_t setTime = (uint32_t) userInputs.getData0(MIN_TIMER,MAX_TIMER);
	        	Display_2_Power_And_Time_Screen((char *)"Set Timer", leftPower, rightPower, setTime, (char *)"Hstart to set");
	        	if(userInputs.isSetValueRequest()){
	        		timer = setTime;
	        		motorScreen = MOTOR_SET_POWER_SCREEN;
	        	}
	        	break;
	        }
			default:
				Display_Error();
	    }
	}
}

///                       Implementation of Types Operations
///
///
Hardware_Test_Screen_Type operator++(Hardware_Test_Screen_Type& screen, int) {
    Hardware_Test_Screen_Type current = screen;

    if (screen == MOTOR_TEST) {
        screen = TRIMPOTS_TEST;
    } else {
        screen = static_cast<Hardware_Test_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

// The actual implementation
Hardware_Test_Screen_Type operator--(Hardware_Test_Screen_Type& screen, int) {
    Hardware_Test_Screen_Type current = screen;

    if (screen == TRIMPOTS_TEST) {
        screen = MOTOR_TEST;
    } else {
        screen = static_cast<Hardware_Test_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix increment
}

// Increment (++) operator
Line_Detection_Screen_Type operator++(Line_Detection_Screen_Type& screen, int) {
    Line_Detection_Screen_Type current = screen;

    if (screen == SENSORS_OUTPUT_SCREEN) {
        screen = LINE_POSITION_SCREEN;  // loop back to the start if at the end
    } else {
        screen = static_cast<Line_Detection_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

// Decrement (--) operator
Line_Detection_Screen_Type operator--(Line_Detection_Screen_Type& screen, int) {
    Line_Detection_Screen_Type current = screen;

    if (screen == LINE_POSITION_SCREEN) {
        screen = SENSORS_OUTPUT_SCREEN;  // loop back to the end if at the start
    } else {
        screen = static_cast<Line_Detection_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}

Enemy_Detection_Screen_Type operator++(Enemy_Detection_Screen_Type& screen, int) {
    Enemy_Detection_Screen_Type current = screen;

    if (screen == ENEMY_POSITION_VOTING_SCREEN) {
        screen = ENEMY_SENSORS_OUTPUT_SCREEN;  // loop back to the start if at the end
    } else {
        screen = static_cast<Enemy_Detection_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

Enemy_Detection_Screen_Type operator--(Enemy_Detection_Screen_Type& screen, int) {
    Enemy_Detection_Screen_Type current = screen;

    if (screen == ENEMY_SENSORS_OUTPUT_SCREEN) {
        screen = ENEMY_POSITION_VOTING_SCREEN;  // loop back to the end if at the start
    } else {
        screen = static_cast<Enemy_Detection_Screen_Type>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}

// Increment (++) operator
Motor_Test_Screen_Type operator++(Motor_Test_Screen_Type& screen, int) {
    Motor_Test_Screen_Type current = screen;
    switch(screen) {
        case MOTOR_SET_POWER_SCREEN:
            screen = MOTOR_SET_TIMER_SCREEN;
            break;
        case MOTOR_RUN_SCREEN:
            screen = MOTOR_SET_POWER_SCREEN;
            break;
        case MOTOR_SET_TIMER_SCREEN:
            screen = MOTOR_SET_POWER_SCREEN;  // loop back to the start
            break;
    }
    return current; // Return old value for postfix increment
}

// Decrement (--) operator
Motor_Test_Screen_Type operator--(Motor_Test_Screen_Type& screen, int) {
    Motor_Test_Screen_Type current = screen;
    switch(screen) {
        case MOTOR_SET_POWER_SCREEN:
            screen = MOTOR_SET_TIMER_SCREEN;
            break;
        case MOTOR_RUN_SCREEN:
            screen = MOTOR_SET_POWER_SCREEN;
            break;
        case MOTOR_SET_TIMER_SCREEN:
            screen = MOTOR_SET_POWER_SCREEN;  // loop back to the start
            break;
    }
    return current; //
}






