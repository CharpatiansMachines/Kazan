/*
 * Trimpot_Driver.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: BRG
 */

#include "trimpot_driver.h"
#include "math_helper.hpp"

Trimpot::Trimpot(ADC_HandleTypeDef *hadc,uint32_t ADC_CHANNEL):
hadc(hadc),
ADC_CHANNEL(ADC_CHANNEL),
data(0)
{

}

void Trimpot::config(){

}
float Trimpot::read()
{
	//read data
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	{

	}
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 1000);
	this->data = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
	data = MathHelper::normalizeData(data, MIN_DATA_VALUE, MAX_DATA_VALUE);

	return data;
}
float Trimpot::getData()const{
	return data;
}

float Trimpot::getData(float min, float max) const
{
	return (max - min) * data + min;
}

