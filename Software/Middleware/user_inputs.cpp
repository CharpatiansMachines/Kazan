/*
 * user_inputs.cpp
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#include "user_inputs.h"

#include "main.h"


UserInputs::UserInputs(const UserInputsConfig& config)
: startButton(config.startButton.port, config.startButton.pin),
  backButton(config.backButton.port, config.backButton.pin),
  nextButton(config.nextButton.port, config.nextButton.pin),
  trimpot0(config.trimpotLeft.hadc, config.trimpotLeft.channel),
  trimpot1(config.trimpotRight.hadc, config.trimpotRight.channel)
{

}

void UserInputs::configAll(){
	startButton.config();
	backButton.config();
	nextButton.config();
	trimpot0.config();
	trimpot1.config();
}
void UserInputs::readInputs(){
	startButton.read();
	backButton.read();
	nextButton.read();
	trimpot0.read();
	trimpot1.read();
}

bool UserInputs::isAnyKey(){
	return backButton.getLastValue() != NO_CLICK ||
			nextButton.getLastValue() != NO_CLICK ||
			startButton.getLastValue() != NO_CLICK;
}
bool UserInputs::isReturnBackRequest(){
	ButtonOutput backOutput = backButton.getLastValue();
	return backOutput == HOLD_CLICK;
}
bool UserInputs::isBackRequest(){
	ButtonOutput backOutput = backButton.getLastValue();
	return backOutput == CLICK ||
			backOutput == DOUBLE_CLICK;
}
bool UserInputs::isNextRequest(){
	ButtonOutput nextOutput = nextButton.getLastValue();
	return nextOutput == CLICK ||
			nextOutput == DOUBLE_CLICK;
}
bool UserInputs::isSelectRequest(){
	ButtonOutput startOutput = startButton.getLastValue();
	return startOutput == CLICK ||
			startOutput == DOUBLE_CLICK;
}
bool UserInputs::isSetValueRequest(){
	ButtonOutput startOutput = startButton.getLastValue();
	return startOutput == HOLD_CLICK;
}



uint16_t UserInputs::getData0() const {
    return trimpot0.getData();
}

uint16_t UserInputs::getData1() const {
    return trimpot1.getData();
}

float UserInputs::getData0(float min, float max) const {
    return trimpot0.getData(min, max);
}

float UserInputs::getData1(float min, float max) const {
    return trimpot1.getData(min, max);
}




