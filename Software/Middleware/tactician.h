/*
 * tactician.h
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */

#ifndef MIDDLEWARE_TACTICIAN_H_
#define MIDDLEWARE_TACTICIAN_H_
#include "motion.h"
#include "state.h"

class Tactician {
public:
	Tactician(Motor& motor);
	void config();
    void setTactic(void (Tactician::*newTactic)(State));
    void run(State state);
    bool hasTactic();


    void Tactic_Front_Atack(State state);
    void Tactic_Escape_Line_Whatever_Enemy_Do(State state);
private:
    static const uint8_t MAX_MOTIONS_NO = 20;
    Motor& motor;
    void (Tactician::*currentTactic)(State) = nullptr;
    TimedMotion motions[MAX_MOTIONS_NO];

    uint8_t totalMotionsNumber = 0;
    uint8_t currentMotionsNumber = 0;

    uint32_t stepStartClock = 0;
    uint8_t tacticStep = 0;

    void STOP_CURRENT_TACTIC();
    bool executesMotions();
    void addMotion(void (*motion)(Motor&), uint32_t time);
    void changeTacticStep(uint8_t step);
};






#endif /* MIDDLEWARE_TACTICIAN_H_ */
