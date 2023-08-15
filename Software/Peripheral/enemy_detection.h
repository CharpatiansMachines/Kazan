/*
 * enemy_detection.h
 *
 *  Created on: Aug 12, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_ENEMY_DETECTION_H_
#define KAZAN_DRIVER_ENEMY_DETECTION_H_

#include "stdint.h"
#include "stm32f4xx.h"

#include "enemy_position.h"



struct EnemyDetectionConfig {
	GPIO_TypeDef* gpio;
	uint16_t pin;
};


class EnemyDetection {
public:
	static constexpr uint8_t NUMBER_OF_SENSORS = 8;
	EnemyDetection(const EnemyDetectionConfig config[NUMBER_OF_SENSORS]);


    void init();
    uint32_t readSensors();
    uint8_t takeSensorsVotes(int8_t sensors_votes[EnemyPosition::POSITIONED_NO]);
    EnemyPosition getMostVotedPosition();

private:

	static constexpr uint8_t FIRST_VOTE = 7;
	static constexpr uint8_t SECOND_VOTE = 6;
	static constexpr uint8_t THIRD_VOTE = 4;


    GPIO_TypeDef* SENSOR_GPIO[NUMBER_OF_SENSORS];
    uint16_t SENSOR_PIN[NUMBER_OF_SENSORS];






};



#endif /* KAZAN_DRIVER_ENEMY_DETECTION_H_ */
