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
	static const uint8_t POSITIONED_NO = 33;
    // Constructors
	EnemyPosition();
	EnemyPosition(uint8_t enemyPositionId);
	EnemyPosition(int8_t direction, int8_t proximity);
    uint8_t toID() const;

private:
    // Member variables
    int8_t direction;
    int8_t proximity;

    // Constants
    static const uint8_t DIRECTIONS_NO = 13;
    static const uint8_t PROXIMITY_NO = 3;
    static const uint8_t NOT_KNOWN_POSITION = POSITIONED_NO -1;
};


#endif /* KAZAN_DRIVER_ENEMY_POSITION_H_ */
