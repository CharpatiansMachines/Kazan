/*
 * motion.h
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */

#ifndef MIDDLEWARE_MOTION_H_
#define MIDDLEWARE_MOTION_H_
#include "motor_driver.h"
#include "timer.h"


class TimedMotion {
private:
    void (*motionFunction)(Motor& motor);
    uint32_t duration; // or appropriate time type

public:
    TimedMotion() : motionFunction(nullptr), duration(0) {}
    TimedMotion(void (*motionFunc)(Motor& motor), uint32_t time)
        : motionFunction(motionFunc), duration(time) {}

    void startMotion(Motor& motor) {
    	if(motionFunction != nullptr)
    		motionFunction(motor);
        duration = Timer_Set_Clock(duration);
    }
    bool hasPassed()const{
    	return Timer_Has_Passed(duration);
    }
};

void Motion_Forward_High(Motor& motor);
void Motion_Forward_Medium(Motor& motor);
void Motion_Forward_Low(Motor& motor);

void Motion_Backward_Full(Motor& motor);
void Motion_Backward_High(Motor& motor);
void Motion_Backward_Medium(Motor& motor);
void Motion_Backward_Low(Motor& motor);

void Motion_Rotate_Right_High(Motor& motor);

void Motion_Rotate_Left_High(Motor& motor);


void Motion_Circle_Right_50(Motor& motor);

void Motion_Circle_Left_50(Motor& motor);
//
//void Motion_Circle_Right_100(Motor& motor);
//
//void Motion_Circle_Left_100(Motor& motor);






#endif /* MIDDLEWARE_MOTION_H_ */
