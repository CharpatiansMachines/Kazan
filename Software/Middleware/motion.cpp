/*
 * motion.c
 *
 *  Created on: Aug 22, 2023
 *      Author: BRG
 */
#include "motion.h"

///Forward Backward Rotate Power
#define FULL_LEFT_POWER 100
#define FULL_RIGHT_POWER 100

PowerLevels powerLevels = {
    .highLeftPower = 60,
    .highRightPower = 60,

    .mediumLeftPower = 40,
    .mediumRightPower = 40,

    .lowLeftPower = 20,
    .lowRightPower = 20,

    .circle50RightPower = 30,
    .circle50LeftPower = 30
};

void Motion_Stop(Motor& motor)
{
	motor.changePower(0, 0);
}

void Motion_Forward_High(Motor& motor) {
    motor.changePower(powerLevels.highLeftPower, powerLevels.highRightPower);
}

void Motion_Forward_Medium(Motor& motor) {
    motor.changePower(powerLevels.mediumLeftPower, powerLevels.mediumRightPower);
}

void Motion_Forward_Low(Motor& motor) {
    motor.changePower(powerLevels.lowLeftPower, powerLevels.lowRightPower);
}

void Motion_Backward_Full(Motor& motor) {
    motor.changePower(-FULL_LEFT_POWER, -FULL_RIGHT_POWER);
}

void Motion_Backward_High(Motor& motor) {
    motor.changePower(-powerLevels.highLeftPower, -powerLevels.highRightPower);
}

void Motion_Backward_Medium(Motor& motor) {
    motor.changePower(-powerLevels.mediumLeftPower, -powerLevels.mediumRightPower);
}

void Motion_Backward_Low(Motor& motor) {
    motor.changePower(-powerLevels.lowLeftPower, -powerLevels.lowRightPower);
}

void Motion_Rotate_Right_High(Motor& motor) {
    motor.changePower(powerLevels.highLeftPower, -powerLevels.highRightPower);
}

void Motion_Rotate_Left_High(Motor& motor) {
    motor.changePower(-powerLevels.highLeftPower, powerLevels.highRightPower);
}

void Motion_Circle_Right_50(Motor& motor) {
    motor.changePower(powerLevels.highLeftPower, powerLevels.circle50RightPower);
}

void Motion_Circle_Left_50(Motor& motor) {
    motor.changePower(powerLevels.circle50LeftPower, powerLevels.highRightPower);
}













