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

struct SensorsHubConfig {
    LineDetection::LineDetectionConfig lineDetectionConfig;
    EnemyDetectionConfig enemyDetectionConfig[EnemyDetection::NUMBER_OF_SENSORS];
    // Add other sensor configs here...
};

class SensorsHub{
public:
	LineDetection lineDetection;
	EnemyDetection enemyDetection;

	SensorsHub(const SensorsHubConfig& config);
private:


};




#endif /* SENSORS_HUB_ */
