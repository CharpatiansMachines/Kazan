/*
 * tactician.h
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */

#ifndef MIDDLEWARE_TACTICIAN_H_
#define MIDDLEWARE_TACTICIAN_H_
#include "state.h"
#include "timed_motion.h"

class Tactician {
public:
	using Tactic = void (Tactician::*)(State);

	Tactician(Motor& motor);
	void config();
    void setTactic(Tactic newTactic);
    void runCurrentTactic(State state);
    bool hasTactic();


    void Tactic_Front_Attack(State state);
    void Tactic_Rotate_Towards_Enemy(State state);
    void Tactic_Search_Enemy_By_Rotation(State state);
    void Tactic_Escape_Line_Whatever_Enemy_Do(State state);
private:
    static const uint8_t MAX_MOTIONS_NO = 20;
    Motor& motor;
    Tactic currentTactic;
    TimedMotion motions[MAX_MOTIONS_NO];

    uint8_t totalMotionsNumber = 0;
    uint8_t currentMotionsNumber = 0;

    uint32_t stepStartClock = 0;
    uint8_t tacticStep = 0;

    void STOP_CURRENT_TACTIC();
    bool executesMotions();
    void addMotion(const TimedMotion& motion);
    void changeTacticStep(uint8_t step);
};






#endif /* MIDDLEWARE_TACTICIAN_H_ */
