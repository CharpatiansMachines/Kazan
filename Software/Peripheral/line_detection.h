/*
 * line_detection.h
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_LINE_DETECTION_H_
#define KAZAN_DRIVER_LINE_DETECTION_H_


#include "stdint.h"
#include "stm32f4xx.h"
#include "line_position.h"


class LineDetection {
public:
	static constexpr uint8_t LINE_FRONT_SENSORS_NUMBER = 6;
	static constexpr uint8_t LINE_BACK_SENSORS__NUMBER = 2;
	static constexpr uint8_t LINE_SENSORS_NUMBER = LINE_FRONT_SENSORS_NUMBER + LINE_BACK_SENSORS__NUMBER;

	struct LineDetectionConfig {
	    ADC_HandleTypeDef *hadcFront;
	    uint32_t frontChannels[LINE_FRONT_SENSORS_NUMBER];
	    ADC_HandleTypeDef *hadcBack;
	    uint32_t backChannels[LINE_BACK_SENSORS__NUMBER];
	};

	LineDetection(const LineDetectionConfig &config);

    void init();
    void read(uint8_t values[LINE_SENSORS_NUMBER]);
    void resetFiltersToDefault();
    LinePosition readAndConvert();
    uint8_t isWhiteFilter = DEFAULT_IS_WHITE_FILTER;
    uint8_t isBlackFilter = DEFAULT_IS_BLACK_FILTER;


private:
    static constexpr uint8_t LINE_DETECTION_FRONTL_MASK = 0x01;
    static constexpr uint8_t LINE_DETECTION_FRONTR_MASK = 0x02;
    static constexpr uint8_t LINE_DETECTION_BACKL_MASK = 0x04;
    static constexpr uint8_t LINE_DETECTION_BACKR_MASK = 0x08;


    static constexpr uint8_t DEFAULT_IS_WHITE_FILTER = 25;
    static constexpr uint8_t DEFAULT_IS_BLACK_FILTER = 70;

    LineDetectionConfig configData;

    uint8_t selectAndRead(ADC_HandleTypeDef *hadc, uint32_t ADC_CHANNEL);
    uint8_t outputToValue(uint32_t sensor_output);
};






#endif /* KAZAN_DRIVER_LINE_DETECTION_H_ */
