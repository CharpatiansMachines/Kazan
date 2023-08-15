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
	if(enemyPositionId >= NOT_KNOWN_POSITION) {
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

uint8_t EnemyPosition::toID() const {
    if(proximity == PROXIMITY_NO)
        return NOT_KNOWN_POSITION;
    uint8_t newDirection = direction;
    if(proximity == 2){
        if(direction > 6){
        	newDirection -= 2;
        }

        newDirection = newDirection >> 1;
    }
    return proximity * DIRECTIONS_NO + newDirection;
}




