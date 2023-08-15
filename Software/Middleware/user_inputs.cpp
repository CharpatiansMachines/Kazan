/*
 * user_inputs.cpp
 *
 *  Created on: Aug 9, 2023
 *      Author: BRG
 */

#include "user_inputs.h"

#include "main.h"


UserInputs::UserInputs(const UserInputsConfig& config)
: startButton(config.startButton.port, config.startButton.pin),
  backButton(config.backButton.port, config.backButton.pin),
  nextButton(config.nextButton.port, config.nextButton.pin),
  trimpotLeft(config.trimpotLeft.hadc, config.trimpotLeft.channel),
  trimpotRight(config.trimpotRight.hadc, config.trimpotRight.channel)
{
	startButton.config();
	backButton.config();
	nextButton.config();
}




