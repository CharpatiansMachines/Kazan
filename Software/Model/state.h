/*
 * state.h
 *
 *  Created on: Aug 17, 2023
 *      Author: BRG
 */

#ifndef MODEL_STATE_H_
#define MODEL_STATE_H_

#include "line_position.h"
#include "enemy_position.h"
#include "stdint.h"

class State
{
public:
	State();
	uint32_t linePositionClock;
	LinePosition linePosition;
	uint32_t enemyPositionClock;
	EnemyPosition enemyPosition;
private:

};







#endif /* MODEL_STATE_H_ */
