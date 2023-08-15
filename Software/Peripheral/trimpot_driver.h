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

	uint16_t read();
	int32_t scale_data(int32_t min, int32_t max);
	virtual ~Trimpot();
private:

	ADC_HandleTypeDef *hadc;
	uint32_t ADC_CHANNEL;
	uint16_t data;

};

#endif /* KAZAN_DRIVER_TRIMPOT_DRIVER_H_ */
