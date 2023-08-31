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

/**
 * Executes a frontal attack on the enemy based on its position.
 *
 * Stop Conditions:
 * 1. Current position is undefined.
 * 2. Enemy's position is unknown.
 * 3. Enemy's position is not between 4 and 8
 *
 * Behavior based on enemy's direction:
 * - Directions 4 and 5: Rotate left in a circle at 50% power.
 * - Direction 6: Move forward at high speed.
 * - Directions 7 and 8: Rotate right in a circle at 50% power.
 *
 * @param state Contains information about the current state including the enemy's position.
 */
void Tactician::Tactic_Front_Attack(State state) {
    EnemyPosition& enemyPosition = state.enemyPosition;

    // Check the stop conditions. If any of these hold true, stop the tactic.
    if (state.linePosition.isNone() || enemyPosition.isNotKnown()) {
        STOP_CURRENT_TACTIC();
        return;
    }

    switch (enemyPosition.direction) {
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
/**
 * Rotates until the enemy is in front
 *
 * Stop Conditions:
 * 1. line is detected.
 * 2. Enemy's position is unknown.
 * 3. Enemy is approximately in front.
 *
 * @param state Contains information about the current state including the enemy's position.
 */
void Tactician::Tactic_Rotate_Towards_Enemy(State state) {
    EnemyPosition& enemyPos = state.enemyPosition;

    // Check the stop conditions. If any of these hold true, stop the tactic.
    if (state.linePosition.isDetected() ||
        enemyPos.isNotKnown() ||
        enemyPos.isApproximatelyInFront()) {
        StopCurrentTactic();
        return;
    }

    // If the enemy is to the left, rotate left; otherwise, rotate right.
    if (enemyPos.isInLeft()) {
        RotateLeftHighSpeed(motor);
    } else {
        RotateRightHighSpeed(motor);
    }
}



/**
 * Tactic to search for the enemy by rotating until the enemy is detected.
 *
 * Stop Conditions:
 * 1. Current position is undefined.
 * 2. Enemy's position is known.
 *
 * Behavior based on tactic step:
 * - Step 0: Rotate left at high speed for 120 degrees
 * - Step 1: Rotate right at high speed for 420 degrees
 * - Step 2: Repeat
 *
 * @param state Contains information about the current state
 */
void Tactician::Tactic_Search_Enemy_By_Rotation(State state) {
    EnemyPosition& enemyPosition = state.enemyPosition;

    // Check the stop conditions. If any of these hold true, stop the tactic.
    if (state.linePosition.isNone() || enemyPosition.isKnown()) {
        STOP_CURRENT_TACTIC();
        return;
    }

    if (tacticStep == 0) {
        addMotion(TimedMotion::fromDegree(Motion_Rotate_Left_High, 120));
        addMotion(TimedMotion::fromDegree(Motion_Rotate_Right_High, 420));
        changeTacticStep(1);
    }

    if (tacticStep == 1 && executesMotions()) {
        changeTacticStep(0);
    }
}



/**
 * Tactic to escape the line regardless of the enemy's actions.
 *
 * Stop Conditions:
 * 1. All motions are completed.
 *
 * Behavior based on tactic step:
 * - Determine escape direction and motions based on the detected line position.

 *
 * @param state Contains information about the current state including the detected line's position.
 */
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
	// STEP 1
	// executes motions. If the motions has finished Stop current Tactic
	if(tacticStep == 1 && executesMotions()){
		STOP_CURRENT_TACTIC();
		return;
	}

}




