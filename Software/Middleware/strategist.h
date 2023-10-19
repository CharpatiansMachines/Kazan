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
	using Strategy = void (Strategist::*)(void);
	Strategist(StateControl& stateCtrl, Motor& motor, Communication_Driver& communication);
	void setStrategy(Strategy newStrategy);
	void runCurrentSrategy();
	void runTestMotion(void (*motionFunction)(Motor& motor));
	void runTestTimedMotion(TimedMotion timeMotion);

	void Strategy_Search_And_Attack(void);
private:
	Motor& motor;
	Communication_Driver& communication;
	StateControl &stateControl;
	Tactician tactician;
	Strategy currentStrategy;
};





#endif /* MIDDLEWARE_STRATEGIST_H_ */
