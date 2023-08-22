/*
 * enemy_position.cpp
 *
 *  Created on: Aug 12, 2023
 *      Author: BRG
 */

#include "enemy_position.h"

#include <cstdlib>
#include <cstdio>

EnemyPosition::EnemyPosition() : direction(0), proximity(PROXIMITY_NO) {}

EnemyPosition::EnemyPosition(int8_t dir, int8_t prox) : direction(dir), proximity(prox) {}

EnemyPosition::EnemyPosition(uint8_t enemyPositionId) {
	if(enemyPositionId >= NOT_KNOWN_POSITION_ID) {
	        proximity = PROXIMITY_NO;
	        return;
	}
	proximity = enemyPositionId / DIRECTIONS_NO;
	direction = enemyPositionId % DIRECTIONS_NO;
	if(proximity == 2) {
		if(direction > 2)
			direction++;
		direction = direction << 1;
	}
}

bool EnemyPosition::operator==(const EnemyPosition& other) const {
    return this->toID() == other.toID();
}

bool EnemyPosition::operator!=(const EnemyPosition& other) const {
    return !(*this == other);  // Or alternatively, return this->toID() != other.toID();
}

uint8_t EnemyPosition::toID() const {
    if(proximity == PROXIMITY_NO)
        return NOT_KNOWN_POSITION_ID;
    uint8_t newDirection = direction;
    if(proximity == 2){
        if(direction > 6){
        	newDirection -= 2;
        }

        newDirection = newDirection >> 1;
    }
    return proximity * DIRECTIONS_NO + newDirection;
}

uint8_t EnemyPosition::getCenterDirection() {
    // Assuming center direction is halfway through DIRECTIONS_NO
    return DIRECTIONS_NO / 2;
}

uint8_t EnemyPosition::getDistanceFromCenterDirection() {
    int8_t center = getCenterDirection();
    return std::abs(direction - center);
}
bool EnemyPosition::isNotKnown(){
	return proximity >= PROXIMITY_NO;
}
bool EnemyPosition::isKnown(){
	return !isNotKnown();
}


EnemyPosition EnemyPosition::notKnownEnemyPosition(){
	return EnemyPosition();
}
EnemyPosition EnemyPosition::frontEnemyPosition(){
	return EnemyPosition(19);
}
EnemyPosition EnemyPosition::frontNearLeftEnemyPosition(){
	return EnemyPosition(28);
}
EnemyPosition EnemyPosition::frontNearRightEnemyPosition(){
	return EnemyPosition(29);
}




