/*
 * motion.h
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */

#ifndef MIDDLEWARE_MOTION_H_
#define MIDDLEWARE_MOTION_H_
#include "motor_driver.h"

struct PowerLevels {
    int highLeftPower;
    int highRightPower;

    int mediumLeftPower;
    int mediumRightPower;

    int lowLeftPower;
    int lowRightPower;

    int circle50RightPower;
    int circle50LeftPower;
};

extern PowerLevels powerLevels;

void Motion_Stop(Motor& motor);

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
