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

#define FULL_POWER 100
#define SAFE_POWER 20

class Motor {
public:
	Motor(USART_TypeDef * UARTX);
	void init();
	void change_power(int8_t left_power, int8_t right_power);
	virtual ~Motor();


private:
	static const uint8_t HISTORY_SIZE = 12;
	static const uint8_t HISTORY_TIMESTAMP = 250;
	static const uint8_t MEAN_POWER_LIMIT = 50;

	UART_HandleTypeDef h_uart;
	int8_t last_left_power;
	int8_t last_right_power;

	uint32_t last_power_change_clock;
	uint8_t left_power_history[HISTORY_SIZE];
	uint8_t right_power_history[HISTORY_SIZE];

	bool is_Safe(uint8_t history[]);
	uint8_t power_to_motor_input(int8_t power, bool is_right_motor);
	void reprocess_History(uint8_t history[], uint8_t current_power);
};

#endif /* KAZAN_DRIVER_MOTOR_DRIVER_H_ */
