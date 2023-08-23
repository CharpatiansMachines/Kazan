/*
 * tactician.cpp
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */

#include "Tactician.h"
#include "Timer.h"


///  SPECIAL ACTIONS TIMES
#define SYMBOLYC_TIME 0
#define BRAKING_SLOW_TIME 2
#define BRAKING_TIME 50
#define FORCE_FORWARD_BACKWARD_TIME 40

/// FORWARD BACKWARD TIMES
#define LOW_POWER_10_CM 30
#define LOW_POWER_20_CM 50
#define LOW_POWER_50_CM 130
#define LOW_POWER_1_M 240

#define MEDIUM_POWER_10_CM 20
#define MEDIUM_POWER_20_CM 35
#define MEDIUM_POWER_50_CM 80
#define MEDIUM_POWER_1_M 150

#define HIGH_POWER_10_CM 15
#define HIGH_POWER_20_CM 25
#define HIGH_POWER_50_CM 50
#define HIGH_POWER_1_M 90

#define FULL_POWER_10_CM 10
#define FULL_POWER_20_CM 18
#define FULL_POWER_50_CM 40
#define FULL_POWER_1_M 75


/// Rotation TIMES
#define ROTATION_5_DEGREE   5
#define ROTATION_10_DEGREE  8
#define ROTATION_15_DEGREE  14
#define ROTATION_30_DEGREE  25
#define ROTATION_60_DEGREE  45
#define ROTATION_90_DEGREE  70
#define ROTATION_120_DEGREE 90
#define ROTATION_140_DEGREE 105
#define ROTATION_160_DEGREE 110
#define ROTATION_180_DEGREE 120

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

void Tactician::runCurrentStrategy(State state) {
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

void Tactician::addMotion(void (*motion)(Motor&), uint32_t time) {
    if (totalMotionsNumber < MAX_MOTIONS_NO) {
        motions[totalMotionsNumber++] = TimedMotion(motion, time);
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
	        	addMotion(Motion_Backward_Full, BRAKING_TIME);
				addMotion(Motion_Rotate_Right_High, ROTATION_120_DEGREE);
	            break;

	        case LinePositionType::Front:
	        	addMotion(Motion_Backward_Full, BRAKING_TIME);
	        	addMotion(Motion_Rotate_Right_High, ROTATION_160_DEGREE);


	            break;

	        case LinePositionType::FrontRight:
	        	addMotion(Motion_Backward_Full, BRAKING_TIME);
				addMotion(Motion_Rotate_Left_High, ROTATION_120_DEGREE);

	            break;

	        case LinePositionType::BackLeft:
	        	addMotion(Motion_Forward_High, BRAKING_TIME);
				addMotion(Motion_Rotate_Right_High, ROTATION_30_DEGREE);
	            break;

	        case LinePositionType::Back:
	        	addMotion(Motion_Forward_High, BRAKING_TIME);
	            break;

	        case LinePositionType::BackRight:
	        	addMotion(Motion_Forward_High, BRAKING_TIME);
				addMotion(Motion_Rotate_Left_High, ROTATION_30_DEGREE);

	            break;

	        case LinePositionType::Left:
	        	addMotion(Motion_Backward_Full, BRAKING_SLOW_TIME);
				addMotion(Motion_Rotate_Right_High, ROTATION_90_DEGREE);

	            break;

	        case LinePositionType::Right:
	        	addMotion(Motion_Backward_Full, BRAKING_SLOW_TIME);
				addMotion(Motion_Rotate_Left_High, ROTATION_90_DEGREE);

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




