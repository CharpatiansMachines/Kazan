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

void Strategist::setStrategy(Strategy newStrategy) {
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
		//Line was detected
		if(lineWasDetected)
		{
			if(tactician.hasTactic()){
				tactician.runCurrentTactic(state);
			}else{
				lineWasDetected = false;
			}
		}

		//Line Wasn't detected
		if(state.linePosition.isDetected())
		{
			lineWasDetected = true;
			tactician.setTactic(&Tactician::Tactic_Escape_Line_Whatever_Enemy_Do);
			tactician.runCurrentTactic(state);
		}else{
			motionFunction(motor);
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
		//Line was detected
		if(lineWasDetected)
		{
			if(tactician.hasTactic()){
				tactician.runCurrentTactic(state);
			}else{
				lineWasDetected = false;
			}
			continue;
		}

		// Line was not detected
		if(state.linePosition.isDetected())
		{
			lineWasDetected = true;
			tactician.setTactic(&Tactician::Tactic_Escape_Line_Whatever_Enemy_Do);
			tactician.runCurrentTactic(state);
		}else if(timeMotion.hasPassed()){
				break;
		}
		start = communication.readStartModule();
	}
	Motion_Stop(motor);
}



/**
 * Strategy Logic:
 * 1. If a tactics is already active, continue its execution.
 * 2. Escape if a line is detected.
 * 3. If the enemy's position is unknown, search for the enemy by rotation.
 * 4. If the enemy is approximately in front, attack.
 * 5. Otherwise, rotate to face the enemy.
 */
void Strategist::Strategy_Search_And_Attack()
{
    // Obtain the latest state information
    State currentState = stateControl.recalculateStates();

    // Continue executing a tactic if one is active
    if (tactician.hasTactic())
    {
        tactician.runCurrentTactic(currentState);
        return;
    }

    // Escape tactic when a line is detected
    if (currentState.linePosition.isDetected())
    {
        tactician.setTactic(&Tactician::Tactic_Escape_Line_Whatever_Enemy_Do);
        return;
    }

    EnemyPosition enemyPos = currentState.enemyPosition;

    // Search for the enemy by rotation if its position is unknown
    if (enemyPos.isNotKnown())
    {
        tactician.setTactic(&Tactician::Tactic_Search_Enemy_By_Rotation);
        return;  // Added to ensure subsequent checks aren't executed
    }

    // Attack if the enemy is approximately in front otherwise rotate to it
    if (enemyPos.isApproximatelyInFront())
    {
        tactician.setTactic(&Tactician::Tactic_Front_Attack);
    }else
    {
        tactician.setTactic(&Tactician::Tactic_Rotate_Towards_Enemy);
    }
}

