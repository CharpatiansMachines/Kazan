/*
 * Trimpot_Driver.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: BRG
 */

#include "trimpot_driver.h"


#define MIN_DATA_VALUE 40
#define MAX_DATA_VALUE 4000

Trimpot::Trimpot(ADC_HandleTypeDef *hadc,uint32_t ADC_CHANNEL):
hadc(hadc),
ADC_CHANNEL(ADC_CHANNEL),
data(0)
{

}
uint16_t Trimpot::read()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	{

	}
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 1000);
	this->data = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);

	if(data <= MIN_DATA_VALUE){
		data = 0;
	}else if(data >= MAX_DATA_VALUE + MIN_DATA_VALUE){
		data = MAX_DATA_VALUE;
	}else{
		data -= MIN_DATA_VALUE;
	}
	return data;
}

int32_t Trimpot::scale_data(int32_t min, int32_t max)
{
	float diff = max - min;
	diff = diff / MAX_DATA_VALUE * data;
	return min + diff;
}



Trimpot::~Trimpot() {
}

