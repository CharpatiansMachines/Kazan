/*
 * strategist.cpp
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#include "strategist.h"
#include "motion.h"


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
	Motion_Stop(motor);
}

void Strategist::runTestMotion(void (*motionFunction)(Motor& motor))
{
	bool start = communication.readStartModule();
	bool lineWasDetected = false;

	while(start)
	{
		State state = stateControl.recalculateStates();
		if(lineWasDetected)
		{
			if(tactician.hasTactic()){
				tactician.runCurrentTactic(state);
			}else{
				lineWasDetected = false;
			}
		}else{
			if(state.linePosition.isNotNone())
			{
				lineWasDetected = true;
				tactician.setTactic(&Tactician::Tactic_Escape_Line_Whatever_Enemy_Do);
				tactician.runCurrentTactic(state);
			}else{
				motionFunction(motor);
			}
		}
		start = communication.readStartModule();
	}
	Motion_Stop(motor);
}




void Strategist::runTestTimedMotion(TimedMotion timeMotion){
	bool start = communication.readStartModule();
	bool lineWasDetected = false;
	if(start){
		timeMotion.startMotion(motor);
	}

	while(start)
	{
		State state = stateControl.recalculateStates();
		if(lineWasDetected)
		{
			if(tactician.hasTactic()){
				tactician.runCurrentTactic(state);
			}else{
				lineWasDetected = false;
			}
		}else{
			if(state.linePosition.isNotNone())
			{
				lineWasDetected = true;
				tactician.setTactic(&Tactician::Tactic_Escape_Line_Whatever_Enemy_Do);
				tactician.runCurrentTactic(state);
			}else{
				if(timeMotion.hasPassed()){
					break;
				}
			}
		}
		start = communication.readStartModule();
	}
	Motion_Stop(motor);
}

