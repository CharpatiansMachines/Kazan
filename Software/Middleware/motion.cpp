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

#define HIGH_LEFT_POWER 60
#define HIGH_RIGHT_POWER 60

#define MEDIUM_LEFT_POWER 40
#define MEDIUM_RIGHT_POWER 40

#define LOW_LEFT_POWER 20
#define LOW_RIGHT_POWER 20

#define CIRCLE_50_RIGHT_POWER 30
#define CIRCLE_50_LEFT_POWER 30

#define CIRCLE_100_RIGHT_POWER 50
#define CIRCLE_100_LEFT_POWER 50

void Motion_Forward_High(Motor& motor) {
    motor.changePower(HIGH_LEFT_POWER, HIGH_RIGHT_POWER);
}

void Motion_Forward_Medium(Motor& motor) {
    motor.changePower(MEDIUM_LEFT_POWER, MEDIUM_RIGHT_POWER);
}

void Motion_Forward_Low(Motor& motor) {
    motor.changePower(LOW_LEFT_POWER, LOW_RIGHT_POWER);
}

void Motion_Backward_Full(Motor& motor) {
    motor.changePower(-FULL_LEFT_POWER, -FULL_RIGHT_POWER);
}

void Motion_Backward_High(Motor& motor) {
    motor.changePower(-HIGH_LEFT_POWER, -HIGH_RIGHT_POWER);
}

void Motion_Backward_Medium(Motor& motor) {
    motor.changePower(-MEDIUM_LEFT_POWER, -MEDIUM_RIGHT_POWER);
}

void Motion_Backward_Low(Motor& motor) {
    motor.changePower(-LOW_LEFT_POWER, -LOW_RIGHT_POWER);
}

void Motion_Rotate_Right_High(Motor& motor) {
    motor.changePower(HIGH_LEFT_POWER, -HIGH_RIGHT_POWER);
}

void Motion_Rotate_Left_High(Motor& motor) {
    motor.changePower(-HIGH_LEFT_POWER, HIGH_RIGHT_POWER);
}

void Motion_Circle_Right_50(Motor& motor) {
    motor.changePower(HIGH_LEFT_POWER, CIRCLE_50_RIGHT_POWER);
}

void Motion_Circle_Left_50(Motor& motor) {
    motor.changePower(CIRCLE_50_LEFT_POWER, HIGH_RIGHT_POWER);
}

void Motion_Circle_Right_100(Motor& motor) {
    motor.changePower(HIGH_LEFT_POWER, CIRCLE_100_RIGHT_POWER);
}

void Motion_Circle_Left_100(Motor& motor) {
    motor.changePower(CIRCLE_100_LEFT_POWER, HIGH_RIGHT_POWER);
}













