/*
 * sensors_hub.cpp
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#include <state_control.h>
#include "timer.h"


StateControl:: StateControl(const SensorsHubConfig& config)
		: lineDetection(config.lineDetectionConfig),
		  enemyDetection(config.enemyDetectionConfig){}

void StateControl::configAll()
{
	lineDetection.config();
	enemyDetection.config();

}

void StateControl::recalculateStates()
{
	LinePosition linePosition = lineDetection.readAndConvertToLinePosition();
	setLinePosition(linePosition);
	EnemyPosition enemyPosition = readAndGetMostVotedEnemyPosition()ș
	if(enemyPosition.isntNotKnown()){
		setEnemyPosition(enemyPosition);
	}
	else{
		///TODO
		if()
	}
}

EnemyPosition StateControl::readAndGetMostVotedEnemyPosition(){
	///Reading sensor Votes
	int8_t sensors_votes[EnemyPosition::KNOWN_POSITIONS_NO];
	uint8_t votingSensorsNo = readAndTakeSensorsVotes(sensors_votes);

	///If no one vote return
	if(votingSensorsNo == 0){
		return EnemyPosition(); ///Unknown
	}

	int8_t maxVotes = sensors_votes[0]; // Start with the first position's votes
	uint8_t maxPositionID = 0;            // Assume the first position has the most votes

	// Iterate through the array to find the position with the most votes
	for(uint8_t i = 1; i < EnemyPosition::KNOWN_POSITIONS_NO; i++) {
		if(sensors_votes[i] > maxVotes) {
			maxVotes = sensors_votes[i];
			maxPositionID = i;
		}
	}
	return EnemyPosition(maxPositionID);
}

void StateControl::setEnemyPosition(EnemyPosition enemyPosition)
{
	if(state.enemyPosition != enemyPosition){
		state.enemyPosition = enemyPosition;
		state.enemyPositionClock = Timer_Get_Now_Time();
	}
}
void StateControl::setLinePosition(LinePosition linePosition)
{
	if(state.linePosition != linePosition){
		state.linePosition = linePosition;
		state.linePositionClock = Timer_Get_Now_Time();
	}
}
State StateControl::getState()const{
	return state;
}





