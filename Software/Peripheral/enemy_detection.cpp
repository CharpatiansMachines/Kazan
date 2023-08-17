/*
 * enemy_detection.cpp
 *
 *  Created on: Aug 12, 2023
 *      Author: BRG
 */

#include "enemy_detection.h"

// Constructor
EnemyDetection::EnemyDetection(const EnemyDetectionConfig config[NUMBER_OF_SENSORS]) {
    for(uint8_t i = 0; i < NUMBER_OF_SENSORS; i++) {
        SENSOR_GPIO[i] = config[i].gpio;
        SENSOR_PIN[i] = config[i].pin;
    }
}

// Initialize the sensors
void EnemyDetection::init() {
	// Here, you can initialize your GPIOs or any startup configuration for the sensors.
	for (uint8_t i = 0; i < NUMBER_OF_SENSORS; i++) {
		// Example: Initialize each sensor using GPIO and pin information
	}
}

// Read the sensors and return their combined readings
uint32_t EnemyDetection::readSensors() {
	uint32_t result = 0;
	for (uint8_t i = 0; i < NUMBER_OF_SENSORS; i++) {
		// Read each sensor and combine their readings into result
		// This is just an example. The exact implementation depends on your sensor's behavior.
		if (HAL_GPIO_ReadPin(SENSOR_GPIO[i], SENSOR_PIN[i]) == GPIO_PIN_SET) {
			result |= (1 << i);
		}
	}
	return result;
}

// Evaluate the votes of each sensor
uint8_t EnemyDetection::readAndTakeSensorsVotes(int8_t sensors_votes[EnemyPosition::POSITIONED_NO]) {

	for(uint8_t i = 0; i <= EnemyPosition::POSITIONED_NO;i++){
		sensors_votes[i] = 0;
	}
	uint32_t sensorsOutput = readSensors();
	uint8_t number_of_active_sensors = 0;

	///Sensor 0
	if(sensorsOutput & 0x01){
		number_of_active_sensors++;
		sensors_votes[0] += FIRST_VOTE;       ///
		sensors_votes[13] += FIRST_VOTE;       /// center line
		sensors_votes[26] += FIRST_VOTE;       ///

		sensors_votes[1] += SECOND_VOTE;       ///
		sensors_votes[14] += SECOND_VOTE;       ///

		sensors_votes[2] += THIRD_VOTE;       ///

	}
	///Sensor 1
	if(sensorsOutput & 0x02){
		number_of_active_sensors++;

		sensors_votes[1] += SECOND_VOTE;       ///
		sensors_votes[14] += SECOND_VOTE;       ///

		sensors_votes[2] += FIRST_VOTE;       ///
		sensors_votes[15] += FIRST_VOTE;       /// center line
		sensors_votes[27] += FIRST_VOTE;       ///

		sensors_votes[3] += SECOND_VOTE;       ///
		sensors_votes[16] += SECOND_VOTE;       ///

		sensors_votes[4] += THIRD_VOTE;       ///

	}
	///Sensor 2
	if(sensorsOutput & 0x04){
		number_of_active_sensors++;

		sensors_votes[2] += THIRD_VOTE;       ///

		sensors_votes[3] += SECOND_VOTE;       ///
		sensors_votes[16] += SECOND_VOTE;       ///

		sensors_votes[4] += FIRST_VOTE;       ///
		sensors_votes[17] += FIRST_VOTE;       /// center line
		sensors_votes[28] += FIRST_VOTE;       ///

		sensors_votes[5] += SECOND_VOTE;       ///
		sensors_votes[18] += SECOND_VOTE;       ///

		sensors_votes[6] += THIRD_VOTE;       ///
	}
	///Sensor 3
	if(sensorsOutput & 0x08){
		number_of_active_sensors++;

		sensors_votes[3] += THIRD_VOTE;       ///
		sensors_votes[18] += THIRD_VOTE;       ///

		sensors_votes[4] += SECOND_VOTE;       ///
		sensors_votes[19] += SECOND_VOTE;       ///

		sensors_votes[5] += FIRST_VOTE;       ///
		sensors_votes[20] += FIRST_VOTE;       /// center line


		sensors_votes[6] +=  SECOND_VOTE;       ///
		sensors_votes[21] += SECOND_VOTE;       ///
		sensors_votes[29] += SECOND_VOTE;       ///

		sensors_votes[7] += THIRD_VOTE;       ///

	}
	///Sensor 4
	if(sensorsOutput & 0x10){
		number_of_active_sensors++;
		sensors_votes[5] += THIRD_VOTE;        ///

		sensors_votes[6] += SECOND_VOTE;       ///
		sensors_votes[17] += SECOND_VOTE;      ///
		sensors_votes[28] += SECOND_VOTE;      ///

		sensors_votes[7] += FIRST_VOTE;        ///
		sensors_votes[18] += FIRST_VOTE;       /// center line


		sensors_votes[8] += SECOND_VOTE;       ///
		sensors_votes[19] += SECOND_VOTE;      ///

		sensors_votes[9] += THIRD_VOTE;        ///
		sensors_votes[20] += THIRD_VOTE;        ///
	}
	///Sensor 5
	if(sensorsOutput & 0x20){
		number_of_active_sensors++;
		sensors_votes[6] += THIRD_VOTE;       ///

		sensors_votes[7] += SECOND_VOTE;       ///
		sensors_votes[20] += SECOND_VOTE;       ///

		sensors_votes[8] += FIRST_VOTE;       ///
		sensors_votes[21] += FIRST_VOTE;       /// center line
		sensors_votes[29] += FIRST_VOTE;       ///

		sensors_votes[9] += SECOND_VOTE;       ///
		sensors_votes[22] += SECOND_VOTE;       ///

		sensors_votes[10] += THIRD_VOTE;       ///
	}
	///Sensor 6
	if(sensorsOutput & 0x40){
		number_of_active_sensors++;

		sensors_votes[8] += THIRD_VOTE;       ///

		sensors_votes[9] += SECOND_VOTE;       ///
		sensors_votes[22] += SECOND_VOTE;       ///

		sensors_votes[10] += FIRST_VOTE;       ///
		sensors_votes[23] += FIRST_VOTE;       /// center line
		sensors_votes[30] += FIRST_VOTE;       ///

		sensors_votes[11] += SECOND_VOTE;       ///
		sensors_votes[24] += SECOND_VOTE;       ///
	}
	///Sensor 7
	if(sensorsOutput & 0x80){
		number_of_active_sensors++;

		sensors_votes[10] += THIRD_VOTE;       ///

		sensors_votes[11] += SECOND_VOTE;      ///
		sensors_votes[24] += SECOND_VOTE;      ///

		sensors_votes[12] += FIRST_VOTE;       ///
		sensors_votes[25] += FIRST_VOTE;       /// center line
		sensors_votes[31] += FIRST_VOTE;       ///
	}

	return 0;
}

// Get the position with the most votes
EnemyPosition EnemyDetection::getMostVotedPosition() {
	int8_t sensors_votes[EnemyPosition::POSITIONED_NO];

	uint8_t votingSensorsNo = readAndTakeSensorsVotes(sensors_votes);
	if(votingSensorsNo == 0){
		return EnemyPosition(); ///Unknown
	}

    int8_t maxVotes = sensors_votes[0]; // Start with the first position's votes
    uint8_t maxPosition = 0;            // Assume the first position has the most votes

    // Iterate through the array to find the position with the most votes
    for(uint8_t i = 1; i < EnemyPosition::POSITIONED_NO; i++) {
        if(sensors_votes[i] > maxVotes) {
            maxVotes = sensors_votes[i];
            maxPosition = i;
        }
    }
    return EnemyPosition (maxPosition, maxVotes);
}




