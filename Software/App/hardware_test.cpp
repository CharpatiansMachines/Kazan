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

void HardwareTestApp::run()
{

	while(1)
	{
		userInputs.readInputs();

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
						(double) userInputs.getData0() ,
						(double) userInputs.getData1()
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
		userInputs.readInputs();

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
					int8_t votes[EnemyPosition::POSITIONED_NO];
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
		userInputs.readInputs();

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






