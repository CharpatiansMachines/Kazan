/*
 * Trimpot_Driver.h
 *
 *  Created on: Jun 2, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_TRIMPOT_DRIVER_H_
#define KAZAN_DRIVER_TRIMPOT_DRIVER_H_

#include "stm32f4xx.h"
#include  "stdint.h"
#include "stm32f4xx_hal_adc.h"

class Trimpot {
public:
	Trimpot(ADC_HandleTypeDef *hadc,uint32_t ADC_CHANNEL);
	void config();

	float read();
	float getData() const;
	float getData(float min, float max) const;
private:
	static const uint16_t MIN_DATA_VALUE = 40;
	static const uint16_t MAX_DATA_VALUE = 4000;
	ADC_HandleTypeDef *hadc;
	uint32_t ADC_CHANNEL;
	// data is always between 0 and 1
	float data;

};

#endif /* KAZAN_DRIVER_TRIMPOT_DRIVER_H_ */
