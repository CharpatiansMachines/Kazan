/*
 * line_detection.cpp
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#include "line_detection.h"


LineDetection::LineDetection(const LineDetectionConfig &config)
    : configData(config) {
}

void LineDetection::init() {
    // Initialization code as in Line_Sensors_Init(void)
}
void LineDetection::resetFiltersToDefault(){
	isWhiteFilter = DEFAULT_IS_WHITE_FILTER;
	isBlackFilter = DEFAULT_IS_BLACK_FILTER;
}

void LineDetection::read(uint8_t values[LINE_SENSORS_NUMBER]) {

	for(uint8_t i = 0 ; i < LINE_FRONT_SENSORS_NUMBER;i++){
		uint32_t channel = configData.frontChannels[i];
		values[i] = selectAndRead(configData.hadcFront,channel);
	}
}

LinePosition LineDetection::readAndConvert() {
//    uint8_t values[LINE_SENSORS_NUMBER];
//    read(values);
//
    LinePosition output;
//
//    // Assuming that a value of 1 means the line is detected.
//    if (values[0] && values[1]) {
//        output.setLinePosition(LineOutput::LinePosition::Front);
//    } else if (values[2] && values[3]) {
//        output.setLinePosition(LineOutput::LinePosition::Back);
//    } else if (values[1] && values[2]) {
//        output.setLinePosition(LineOutput::LinePosition::Left);
//    } else if (values[0] && values[3]) {
//        output.setLinePosition(LineOutput::LinePosition::Right);
//    } else if (values[0]) {
//        output.setLinePosition(LineOutput::LinePosition::FrontLeft);
//    } else if (values[1]) {
//        output.setLinePosition(LineOutput::LinePosition::FrontRight);
//    } else if (values[2]) {
//        output.setLinePosition(LineOutput::LinePosition::BackLeft);
//    } else if (values[3]) {
//        output.setLinePosition(LineOutput::LinePosition::BackRight);
//    } else {
//        output.setLinePosition(LineOutput::LinePosition::None);
//    }

    return output;
}


uint8_t LineDetection:: selectAndRead(ADC_HandleTypeDef *hadc, uint32_t ADC_CHANNEL) {
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	  if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	  {
//		Error_Handler();
	  }

	  HAL_ADC_Start(hadc);
	  HAL_ADC_PollForConversion(hadc, 1000);
	  uint32_t value = HAL_ADC_GetValue(hadc);
	  HAL_ADC_Stop(hadc);
	  return value;
}

uint8_t LineDetection::outputToValue(uint32_t sensor_output) {
	if(sensor_output >= isBlackFilter)
		return 0;
	if(sensor_output <= isWhiteFilter)
		return 1;
	return 2;
}


