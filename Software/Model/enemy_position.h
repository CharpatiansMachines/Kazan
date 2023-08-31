/*
 * enemy_position.h
 *
 *  Created on: Aug 12, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_ENEMY_POSITION_H_
#define KAZAN_DRIVER_ENEMY_POSITION_H_


#include <cstdint>

class EnemyPosition {
public:
	static const uint8_t ALL_POSITIONS_NO = 33;
	static const uint8_t KNOWN_POSITIONS_NO = ALL_POSITIONS_NO - 1;  ///32

    static const uint8_t DIRECTIONS_NO = 13;
    static const uint8_t PROXIMITY_NO = 3;
    // Constructors
	EnemyPosition();
	EnemyPosition(uint8_t enemyPositionId);
	EnemyPosition(int8_t direction, int8_t proximity);

    bool operator==(const EnemyPosition& other) const;
    bool operator!=(const EnemyPosition& other) const;


    uint8_t toID() const;
    int8_t direction;
    int8_t proximity;
    uint8_t getCenterDirection();
    uint8_t getDistanceFromCenterDirection();
    bool isNotKnown() const;
    bool isKnown() const;
    bool isApproximatelyInFront() const;
    bool isInLeft() const;
    bool isInRight() const;
    bool isKnown();

    static EnemyPosition notKnownEnemyPosition();
    static EnemyPosition frontEnemyPosition();
    static EnemyPosition frontNearLeftEnemyPosition();
    static EnemyPosition frontNearRightEnemyPosition();

private:
    // Member variables

    // Constants
    static const uint8_t NOT_KNOWN_POSITION_ID = KNOWN_POSITIONS_NO;
    static const uint8_t FRONT_DIRECTION = (DIRECTIONS_NO - 1) / 2;
};


#endif /* KAZAN_DRIVER_ENEMY_POSITION_H_ */
