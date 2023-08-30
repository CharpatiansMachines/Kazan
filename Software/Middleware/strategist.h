/*
 * strategist.h
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#ifndef MIDDLEWARE_STRATEGIST_H_
#define MIDDLEWARE_STRATEGIST_H_
#include "tactician.h"
#include "state_control.h"
#include "communication_driver.h"


class Strategist{
public:
	Strategist(StateControl& stateCtrl, Motor& motor, Communication_Driver& communication);
	void setStrategy(void (Strategist::*currentStrategy)(void));
	void runCurrentSrategy();
	void runTestMotion(void (*motionFunction)(Motor& motor));
	void runTestTimedMotion(TimedMotion timeMotion);


private:
	Motor& motor;
	Communication_Driver& communication;
	StateControl &stateControl;
	Tactician tactician;
	void (Strategist::*currentStrategy)(void) = nullptr;
};





#endif /* MIDDLEWARE_STRATEGIST_H_ */
