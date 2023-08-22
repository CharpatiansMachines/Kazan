/*
 * hardware_components.h
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#ifndef SENSORS_HUB_
#define SENSORS_HUB_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"

#include "enemy_detection.h"
#include "line_detection.h"
#include "state.h"

struct SensorsHubConfig {
    LineDetection::LineDetectionConfig lineDetectionConfig;
    EnemyDetectionConfig enemyDetectionConfig[EnemyDetection::NUMBER_OF_SENSORS];
    // Add other sensor configs here...
};

class StateControl{
public:
	LineDetection lineDetection;
	EnemyDetection enemyDetection;

	StateControl(const SensorsHubConfig& config);
	void configAll();
	State recalculateStates();
	State getState()const;

private:
	State state;
	EnemyPosition readAndGetMostVotedEnemyPosition();
	void setEnemyPosition(EnemyPosition enemyPosition);
	void setLinePosition(LinePosition linePosition);
	// Time duration after which, if no enemy is detected, the enemy position is considered unknown or expired.
	static const uint32_t ENEMY_POSITION_EXPIRY_TIME = 1500;

};




#endif /* SENSORS_HUB_ */
