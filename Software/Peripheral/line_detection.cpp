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

void LineDetection::config() {
    // Initialization code as in Line_Sensors_Init(void)
}
void LineDetection::resetFiltersToDefault(){
	isWhiteFilter = DEFAULT_IS_WHITE_FILTER;
	isBlackFilter = DEFAULT_IS_BLACK_FILTER;
}

void LineDetection::readAll(uint8_t values[LINE_SENSORS_NUMBER]) {

	///Read Front Values
	for(uint8_t i = 0 ; i < LINE_SENSORS_NUMBER;i++){
		uint32_t channel = configData.channels[i];
		values[i] = selectAndRead(configData.hadc,channel);
	}
}

LinePosition LineDetection::readAndConvertToLinePosition() {
    uint8_t sensorsOutput[LINE_SENSORS_NUMBER];

    // Read sensors' output
    readAll(sensorsOutput);

    // Check if the sensors see the white line
    // Grouped for FrontLeft, FrontRight, BackLeft, and BackRight respectively
    bool isWhite[4];
    isWhite[0] = sensorOutputToBool(sensorsOutput[0]) ||
                 sensorOutputToBool(sensorsOutput[1]) ||
                 sensorOutputToBool(sensorsOutput[2]);

    isWhite[1] = sensorOutputToBool(sensorsOutput[3]) ||
                 sensorOutputToBool(sensorsOutput[4]) ||
                 sensorOutputToBool(sensorsOutput[5]);

    isWhite[2] = sensorOutputToBool(sensorsOutput[6]);
    isWhite[3] = sensorOutputToBool(sensorsOutput[7]);

    LinePosition output;

    // Determine robot's position based on the sensors' reading
    if (isWhite[0] && isWhite[1]) {
        output.setLinePosition(LinePositionType::Front);
    } else if (isWhite[2] && isWhite[3]) {
        output.setLinePosition(LinePositionType::Back);
    } else if (isWhite[1] && isWhite[2]) {
        output.setLinePosition(LinePositionType::Left);
    } else if (isWhite[0] && isWhite[3]) {
        output.setLinePosition(LinePositionType::Right);
    } else if (isWhite[0]) {
        output.setLinePosition(LinePositionType::FrontLeft);
    } else if (isWhite[1]) {
        output.setLinePosition(LinePositionType::FrontRight);
    } else if (isWhite[2]) {
        output.setLinePosition(LinePositionType::BackLeft);
    } else if (isWhite[3]) {
        output.setLinePosition(LinePositionType::BackRight);
    } else {
        output.setLinePosition(LinePositionType::None);
    }

    return output;
}


uint8_t LineDetection:: selectAndRead(ADC_HandleTypeDef *hadc, uint32_t ADC_CHANNEL) {
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
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

bool LineDetection::sensorOutputToBool(uint32_t sensor_output) {
	if(sensor_output <= isWhiteFilter)
		return true;
	return false;
}


