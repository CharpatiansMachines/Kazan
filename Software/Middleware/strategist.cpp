/*
 * strategist.cpp
 *
 *  Created on: Aug 23, 2023
 *      Author: BRG
 */

#include "strategist.h"
#include "motor_driver.h"


Strategist::Strategist(StateControl& stateCtrl, Motor& motor)
	:stateControl(stateCtrl),
     tactician(motor)  // Assuming StateControl provides a getMotor() method
{
   currentStrategy = nullptr;
}

void Strategist::setStrategy(void (Strategist::*newStrategy)(void)) {
    currentStrategy = newStrategy;
}

void Strategist::runCurrentSrategy() {
    if (currentStrategy != nullptr) {
        (this->*currentStrategy)();
    }
}

