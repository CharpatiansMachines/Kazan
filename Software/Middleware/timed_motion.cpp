/*
 * timed_motion.cpp
 *
 *  Created on: Aug 27, 2023
 *      Author: BRG
 */

#include <math.hpp>
#include "timed_motion.h"
#include "timer.h"
#include "motion.h"

ActionTimes actionTimes = {
    .brakingTime = 50,

    .mediumPower10cm = 20,
    .mediumPower20cm = 35,
    .mediumPower50cm = 80,
    .mediumPower100cm = 150,

    .rotation30degree = 25,
    .rotation60degree = 45,
    .rotation90degree = 70,
    .rotation120degree = 90
};

// Definitions for the TimedMotion class methods

TimedMotion::TimedMotion() : motionFunction(nullptr), duration(0) {}

TimedMotion::TimedMotion(void (*motionFunc)(Motor& motor), uint32_t time)
    : motionFunction(motionFunc), duration(time) {}


TimedMotion TimedMotion::FORWARD_BRAKE() {
    return TimedMotion(Motion_Backward_High, actionTimes.brakingTime);
}

TimedMotion TimedMotion::BACKWARD_BRAKE() {
    return TimedMotion(Motion_Forward_High, actionTimes.brakingTime);
}

TimedMotion TimedMotion::fromDistance(void (*motionFunc)(Motor& motor), uint16_t cm) {
	uint32_t time = 0;
    if (cm <= 10) {
        time = (int)(Math::linearInterpolation(0, 0, 10, actionTimes.mediumPower10cm, cm));
    } else if (cm <= 20) {
        time = (int)(Math::linearInterpolation(10, actionTimes.mediumPower10cm, 20, actionTimes.mediumPower20cm, cm));
    } else if (cm <= 50) {
        time = (int)(Math::linearInterpolation(20, actionTimes.mediumPower20cm, 50, actionTimes.mediumPower50cm, cm));
    } else if (cm <= 100) {
        time = (int)(Math::linearInterpolation(50, actionTimes.mediumPower50cm, 100, actionTimes.mediumPower100cm, cm));
    }
    return TimedMotion(motionFunc, time);
}

TimedMotion TimedMotion::fromDegree(void (*motionFunc)(Motor& motor), uint16_t degree) {
	uint32_t time = 0;
	if (degree <= 30) {
		time = (int)(Math::linearInterpolation(0, 0, 30, actionTimes.rotation30degree, degree));
	} else if (degree <= 60) {
		time = (int)(Math::linearInterpolation(30, actionTimes.rotation30degree, 60, actionTimes.rotation60degree, degree));
	} else if (degree <= 90) {
		time = (int)(Math::linearInterpolation(60, actionTimes.rotation60degree, 90, actionTimes.rotation90degree, degree));
	} else if (degree <= 120) {
		time = (int)(Math::linearInterpolation(90, actionTimes.rotation90degree, 120, actionTimes.rotation120degree, degree));
	}

	return TimedMotion(motionFunc, time);
}

void TimedMotion::startMotion(Motor& motor) {
    if(motionFunction != nullptr) {
        motionFunction(motor);
    }
    duration = Timer_Set_Clock(duration);
}

bool TimedMotion::hasPassed() const {
    return Timer_Has_Passed(duration);
}


