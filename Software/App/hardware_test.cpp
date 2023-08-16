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
	ComplexButton &startButton = userInputs.startButton;
	ComplexButton &backButton =  userInputs.backButton;
	ComplexButton &nextButton =  userInputs.nextButton;

	Trimpot trimpotLeft = userInputs.trimpotLeft;
	Trimpot trimpotRight = userInputs.trimpotRight;

	while(1)
	{
		ButtonOutput backOutput = backButton.read();
		ButtonOutput nextOutput = nextButton.read();
		ButtonOutput startOutput = startButton.read();

		trimpotLeft.read();
		trimpotRight.read();

		/// BACK Button
		switch(backOutput){
			case HOLD_CLICK:
				/// EXIT
				return ;
			case NO_CLICK:
				///NOTHING
				break;
			default :
				screen--;
		}


		if(nextOutput != NO_CLICK){
			screen++;
		 }

		/// UI Displayinh
		switch(screen){
			case TRIMPOTS_TEST:
				Display_2_Numbers(
						(char *)"Trimpots values",
						(double)trimpotLeft.read() ,
						(double) trimpotRight.read()
						);
				break;
			case LINE_SENSORS_TEST:
				Display_Small_Title_Screen((char *)"Line Detection Output Test");
				if(startOutput != NO_CLICK){
					runLineDetectionTest();
				}
				break;
			case ENEMY_SENSORS_TEST:
				Display_Title_Screen((char *)"Enemy Sensor Test");
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
	ComplexButton &startButton = userInputs.startButton;
	ComplexButton &backButton =  userInputs.backButton;
	ComplexButton &nextButton =  userInputs.nextButton;


	Trimpot trimpotLeft = userInputs.trimpotLeft;
	Trimpot trimpotRight = userInputs.trimpotRight;

	EnemyDetection enemyDetection = sensorsHub.enemyDetection;

	uint8_t enemySensorsScren = 0;



	while(true){
		switch(enemySensorsScren){
		case 0:

		case 1:

		case 2:

		default:
			Display_Error();
		}

	}


}

void HardwareTestApp::runLineDetectionTest(){

	///Extract components
	ComplexButton &startButton = userInputs.startButton;
	ComplexButton &backButton =  userInputs.backButton;
	ComplexButton &nextButton =  userInputs.nextButton;


	Trimpot trimpotLeft = userInputs.trimpotLeft;
	Trimpot trimpotRight = userInputs.trimpotRight;

	LineDetection& lineDetecion = sensorsHub.lineDetection;
	Line_Detection_Test_Screen lineDetectionScreen = LINE_POSITION_SCREEN;

	///LOOP
	while(true){
		///Read values
		ButtonOutput backOutput = backButton.read();
		ButtonOutput nextOutput = nextButton.read();
		ButtonOutput startOutput = startButton.read();

		Trimpot trimpotLeft = userInputs.trimpotLeft;
		Trimpot trimpotRight = userInputs.trimpotRight;


		if(backOutput == HOLD_CLICK){
			return; ///get out
		}else if(backOutput != NO_CLICK){
			lineDetectionScreen--;
		}
		if(nextOutput != NO_CLICK){
			lineDetectionScreen ++;
		}

		///UI
		switch(lineDetectionScreen){
			case LINE_POSITION_SCREEN:
			{
				/// Line Position Screen
				LinePosition linePosition = lineDetecion.readAndConvert();
				Display_Line_Position_Screen(
							linePosition,
							lineDetecion.isWhiteFilter, //whiteFilter
							lineDetecion.isBlackFilter, //BlackFilter
							(char *)"Hstart to reset>"     //description
				);
				if(startOutput == HOLD_CLICK){
					lineDetecion.resetFiltersToDefault();
				}
				break;
			}


			case FILTER_CHANGE_SCREEN:
			{
				///Change Filter Screen;
				trimpotLeft.read();
				trimpotRight.read();
				LinePosition linePosition = lineDetecion.readAndConvert();

				Display_Line_Position_Screen(
						linePosition,
						trimpotLeft.scale_data(0, 255), //whiteFilter
						trimpotRight.scale_data(0, 255), //BlackFilter
						(char *)"Hstart to change>"              //description
				);
				if(startOutput == HOLD_CLICK){
					lineDetecion.isWhiteFilter = trimpotLeft.scale_data(0, 255);
					lineDetecion.isBlackFilter = trimpotRight.scale_data(0, 255);
					lineDetectionScreen = LINE_POSITION_SCREEN;
				}
				break;
			}

			case SENSORS_OUTPUT_SCREEN:
			{
				///Sensors Output View
				uint8_t sensorsValues[LineDetection::LINE_SENSORS_NUMBER];
				lineDetecion.read(sensorsValues);
				Display_Line_Sensors_Output(sensorsValues, LineDetection::LINE_SENSORS_NUMBER);

			}
				break;
			default:
				Display_Error();
		}

	}
}

// The actual implementation
Hardware_Test_Screen operator++(Hardware_Test_Screen& screen, int) {
    Hardware_Test_Screen current = screen;

    if (screen == MOTOR_TEST) {
        screen = TRIMPOTS_TEST;
    } else {
        screen = static_cast<Hardware_Test_Screen>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

// The actual implementation
Hardware_Test_Screen operator--(Hardware_Test_Screen& screen, int) {
    Hardware_Test_Screen current = screen;

    if (screen == TRIMPOTS_TEST) {
        screen = MOTOR_TEST;
    } else {
        screen = static_cast<Hardware_Test_Screen>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix increment
}

// Increment (++) operator
Line_Detection_Test_Screen operator++(Line_Detection_Test_Screen& screen, int) {
    Line_Detection_Test_Screen current = screen;

    if (screen == SENSORS_OUTPUT_SCREEN) {
        screen = LINE_POSITION_SCREEN;  // loop back to the start if at the end
    } else {
        screen = static_cast<Line_Detection_Test_Screen>(static_cast<int>(screen) + 1);
    }

    return current; // Return old value for postfix increment
}

// Decrement (--) operator
Line_Detection_Test_Screen operator--(Line_Detection_Test_Screen& screen, int) {
    Line_Detection_Test_Screen current = screen;

    if (screen == LINE_POSITION_SCREEN) {
        screen = SENSORS_OUTPUT_SCREEN;  // loop back to the end if at the start
    } else {
        screen = static_cast<Line_Detection_Test_Screen>(static_cast<int>(screen) - 1);
    }

    return current; // Return old value for postfix decrement
}






