/*
 * Motor_Driver.h
 *
 *  Created on: Jun 3, 2023
 *      Author: BRG
 */

#ifndef KAZAN_DRIVER_MOTOR_DRIVER_H_
#define KAZAN_DRIVER_MOTOR_DRIVER_H_

#include "stm32f4xx.h"
#include "stdint.h"

class Motor {
public:
	static const int8_t MAX_POWER = 100;
	static const int8_t MAX_REVERSE_POWER = -MAX_POWER;
	static const int8_t STOP_POWER = 0;

	Motor(USART_TypeDef * UARTX);
	void init();
	void changePower(int8_t leftPower, int8_t rightPower);
	void stop();


private:
	UART_HandleTypeDef h_uart;
	int8_t leftPower;
	int8_t rightPower;

	uint8_t boundedPowerValue(int8_t power);
	uint8_t power_to_motor_input(int8_t power, bool is_right_motor);

};

#endif /* KAZAN_DRIVER_MOTOR_DRIVER_H_ */
