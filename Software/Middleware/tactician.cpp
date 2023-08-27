/*
 * tactician.cpp
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */

#include "Tactician.h"
#include "Timer.h"
#include "motion.h"

Tactician::Tactician(Motor& motor) : motor(motor) {}

void Tactician::config() {
   STOP_CURRENT_TACTIC();
}

void Tactician::setTactic(void (Tactician::*newTactic)(State state)) {
    if (!hasTactic()) {
        STOP_CURRENT_TACTIC();
    }
    currentTactic = newTactic;
    changeTacticStep(0);
}

void Tactician::runCurrentTactic(State state) {
    if (!hasTactic()) {
        (this->*currentTactic)(state);
    }
}

bool Tactician::hasTactic() {
    return currentTactic != nullptr;
}

void Tactician::STOP_CURRENT_TACTIC() {
    // Reset all states
    currentTactic = nullptr;
    totalMotionsNumber = 0;
    currentMotionsNumber = 0;
    stepStartClock = 0;
    tacticStep = 0;
}

bool Tactician::executesMotions() {
    if (currentMotionsNumber >= totalMotionsNumber){
    	///Empty Queue
    	return true;
    }

    //If motion time has passed start the next motion
    if (motions[currentMotionsNumber].hasPassed()) {
        currentMotionsNumber++;
        motions[currentMotionsNumber].startMotion(motor);
        return false;
    }
    return true;
}

void Tactician::addMotion(const TimedMotion& motion) {
    if (totalMotionsNumber < MAX_MOTIONS_NO) {
        motions[totalMotionsNumber++] = motion;
    }
}

void Tactician::changeTacticStep(uint8_t step) {
    tacticStep = step;
    stepStartClock = Timer_Get_Now_Time();
}

void Tactician::Tactic_Front_Atack(State state)
{
	EnemyPosition& enemyPosition = state.enemyPosition;
	if(state.linePosition.isNone() || enemyPosition.isNotKnown()){
		STOP_CURRENT_TACTIC();
		return;
	}
	switch (enemyPosition.direction){
		case 4:
		case 5:
			 Motion_Circle_Left_50(motor);
		  break;

		case 6:
			Motion_Forward_High(motor);
		  break;

		case 7:
		case 8:
			 Motion_Circle_Right_50(motor);
		  break;
		default:
			STOP_CURRENT_TACTIC();
			break;
	}
}

void Tactician::Tactic_Escape_Line_Whatever_Enemy_Do(State state)
{
	if(tacticStep == 0)
	{
		switch (state.linePosition.getLinePosition()) {
		    case LinePositionType::FrontLeft:
		        addMotion(TimedMotion::BACKWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Right_High, 120));
		        break;

		    case LinePositionType::Front:
		        addMotion(TimedMotion::BACKWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Right_High, 160));
		        break;

		    case LinePositionType::FrontRight:
		        addMotion(TimedMotion::BACKWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Left_High, 120));
		        break;

		    case LinePositionType::BackLeft:
		        addMotion(TimedMotion::FORWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Right_High, 30));
		        break;

		    case LinePositionType::Back:
		        addMotion(TimedMotion::FORWARD_BRAKE());
		        break;

		    case LinePositionType::BackRight:
		        addMotion(TimedMotion::FORWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Left_High, 30));
		        break;

		    case LinePositionType::Left:
		        addMotion(TimedMotion::BACKWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Right_High, 90));
		        break;

		    case LinePositionType::Right:
		        addMotion(TimedMotion::BACKWARD_BRAKE());
		        addMotion(TimedMotion::fromDegree(Motion_Rotate_Left_High, 90));
		        break;

		    default:
		        STOP_CURRENT_TACTIC();
		        return;
		}
	    changeTacticStep(1);


	}
	////// STEP 1
	/// executes motions. If the motions has finished Stop current Tactic
	if(tacticStep == 1 && executesMotions()){
		STOP_CURRENT_TACTIC();
		return;
	}

}




