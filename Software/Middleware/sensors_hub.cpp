/*
 * sensors_hub.cpp
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#include "sensors_hub.h"


SensorsHub:: SensorsHub(const SensorsHubConfig& config)
		: lineDetection(config.lineDetectionConfig),
		  enemyDetection(config.enemyDetectionConfig){}






