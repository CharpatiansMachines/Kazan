/*
 * strategy_selector.h
 *
 *  Created on: Aug 31, 2023
 *      Author: BRG
 */

#ifndef APP_STRATEGY_SELECTOR_H_
#define APP_STRATEGY_SELECTOR_H_

#include "strategist.h"
#include "user_inputs.h"

enum Strategy_Selector_Screen_Type{
	Search_And_Attack_Screen
};
Strategy_Selector_Screen_Type operator++(Strategy_Selector_Screen_Type& screen, int);

Strategy_Selector_Screen_Type operator--(Strategy_Selector_Screen_Type& screen, int);


class StrategySelector {
public:
	StrategySelector(UserInputs& userInputs,
					StateControl& sensorsHub,
					Motor& motor,
					Communication_Driver& comm)
	        : userInputs(userInputs),
			  sensorsHub(sensorsHub),
			  motor(motor),
	          communication(comm),
			  strategist(sensorsHub, motor, comm){}
	void run();
private:
	UserInputs &userInputs;
	StateControl &sensorsHub;
	Motor& motor;
	Communication_Driver &communication;
	Strategist strategist;
};


#endif /* APP_STRATEGY_SELECTOR_H_ */
