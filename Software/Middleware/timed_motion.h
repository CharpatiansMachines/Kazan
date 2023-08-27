/*
 * timed_motion.h
 *
 *  Created on: Aug 27, 2023
 *      Author: BRG
 */

#ifndef MIDDLEWARE_TIMED_MOTION_H_
#define MIDDLEWARE_TIMED_MOTION_H_
#include "motor_driver.h"
#include <cstdint> // for uint32_t, uint16_t

struct ActionTimes {
    // SPECIAL ACTIONS TIMES
	static const uint16_t symbolicTime = 0;
    uint16_t brakingTime;

    // FORWARD BACKWARD TIMES
    uint16_t mediumPower10cm;
    uint16_t mediumPower20cm;
    uint16_t mediumPower50cm;
    uint16_t mediumPower1m;

    // ROTATION TIMES
    uint16_t rotation30degree;
    uint16_t rotation60degree;
    uint16_t rotation90degree;
    uint16_t rotation120degree;
};

extern const ActionTimes actionTimes; // Declaring the extern variable for linkage

class TimedMotion {
private:
    void (*motionFunction)(Motor& motor);
    uint32_t duration; // or appropriate time type

public:
    TimedMotion();
    TimedMotion(void (*motionFunc)(Motor& motor), uint32_t time);

    static TimedMotion FORWARD_BRAKE();
    static TimedMotion BACKWARD_BRAKE();
    static TimedMotion fromDistance(void (*motionFunc)(Motor& motor),uint16_t cm);
    static TimedMotion fromDegree(void (*motionFunc)(Motor& motor), uint16_t degree);

    void startMotion(Motor& motor);
    bool hasPassed() const;
};





#endif /* MIDDLEWARE_TIMED_MOTION_H_ */
