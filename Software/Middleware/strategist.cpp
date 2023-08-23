/*
 * strategist.cpp
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#include "strategist.h"
#include "motor_driver.h"


Strategist::Strategist(StateControl& stateCtrl, Motor& motor, Communication_Driver& communication)
	:motor(motor),
	communication(communication),
	stateControl(stateCtrl),
	tactician(motor)

{
   currentStrategy = nullptr;
}

void Strategist::setStrategy(void (Strategist::*newStrategy)(void)) {
    currentStrategy = newStrategy;
}

void Strategist::runCurrentSrategy() {
	bool start = communication.readStartModule();
	while(start && currentStrategy != nullptr)
	{
		(this->*currentStrategy)();
		start = communication.readStartModule();
	}
}
void Strategist::testMotion(void (*motionFunction)(Motor& motor))
{
	bool start = communication.readStartModule();
	if(start){
		motionFunction(motor);
	}
	while(start)
	{
		State state = stateControl.recalculateStates();
		if(state.linePosition.isNotNone()){
			Motion_Stop(motor);
		}
		start = communication.readStartModule();
	}
}

