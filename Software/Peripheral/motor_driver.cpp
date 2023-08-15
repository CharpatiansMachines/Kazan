/*
 * Motor_Driver.cpp
 *
 *  Created on: Jun 3, 2023
 *      Author: BRG
 */

#include "motor_driver.h"

#include "stm32f4xx_hal_uart.h"

Motor::Motor(USART_TypeDef * UARTX)
{
	h_uart.Instance = UARTX;

}
void Motor::init()
{
	h_uart.Init.BaudRate = 38400;
	h_uart.Init.WordLength = UART_WORDLENGTH_8B;
	h_uart.Init.StopBits = UART_STOPBITS_1;
	h_uart.Init.Parity = UART_PARITY_NONE;
	h_uart.Init.Mode = UART_MODE_TX_RX;
	h_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	h_uart.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_HalfDuplex_Init(&h_uart);
}
void Motor::change_power(int8_t left_power, int8_t right_power)
{
//	if(last_left_power > SAFE_POWER || last_right_power > SAFE_POWER)
//	{
//		if(calculate_safety(left_power_history) == 0 ||
//					calculate_safety(right_power_history) == 0){
//			float convert = last_left_power;
//			convert *= SAFE_POWER / 100;
//			last_left_power =convert;
//			convert = last_right_power;
//			convert *= SAFE_POWER / 100;
//			last_right_power  = convert;
//		}
//
//	}

	reprocess_History(left_power_history,last_left_power);
	reprocess_History(right_power_history,last_right_power);

	// TO DO
//	last_power_change_clock = Communication_Driver_GetClock();

	if(left_power != last_left_power || right_power != last_right_power){
		last_left_power = left_power;
		last_right_power = right_power;
		uint8_t motor_input_left_right[2];
		motor_input_left_right[0] = power_to_motor_input(left_power, false);
		motor_input_left_right[1] = power_to_motor_input(right_power, true);

		//Transmit Three Times
		while(HAL_UART_Transmit(&h_uart, motor_input_left_right, 2, 100) != HAL_OK);
		while(HAL_UART_Transmit(&h_uart, motor_input_left_right, 2, 100) != HAL_OK);
		while(HAL_UART_Transmit(&h_uart, motor_input_left_right, 2, 100) != HAL_OK);
	}
}
bool Motor::is_Safe(uint8_t history[])
{
	int8_t current_index = (HAL_GetTick() / HISTORY_TIMESTAMP) % HISTORY_SIZE;
	uint16_t sum = 0;
	for(int i = (current_index + 1) % HISTORY_SIZE ; i != current_index ; i = ( i + 1 ) % HISTORY_SIZE )
	{
		sum += history[i];
	}
	sum /= ( HISTORY_SIZE - 1 );
	if(sum > MEAN_POWER_LIMIT)
		return 0;
	return 1;
}
void Motor::reprocess_History(uint8_t history[], uint8_t current_power)
{
	uint32_t last_clock = last_power_change_clock;
	uint32_t current_clock = HAL_GetTick();

	int8_t last_index = (last_clock / HISTORY_TIMESTAMP) % HISTORY_SIZE;
	int8_t current_index = (current_clock / HISTORY_TIMESTAMP) % HISTORY_SIZE;
	if(last_index != current_index){
		history[current_index] = current_power;
	}else{
		uint32_t oldTime = last_clock % HISTORY_TIMESTAMP;
		uint32_t oldMecanicalWORK = history[current_index];
		oldMecanicalWORK *= oldTime;

		uint32_t newTime = current_clock % HISTORY_TIMESTAMP - oldTime;
		uint32_t newMecanicalWORK = current_power;
		newMecanicalWORK *= newTime;
		uint32_t total_Time = (oldTime + newTime);
		if(total_Time > 0)
			history[current_index] = (oldMecanicalWORK + newMecanicalWORK) / (total_Time);
		else
			history[current_index] = current_power;
	}
}

uint8_t Motor::power_to_motor_input(int8_t power, bool is_right_motor)
{
	float convert = 100 + power;
	if(is_right_motor){
		if(power <= 0){
			convert = 100 + power;
			convert = convert * 64/100 + 128;
		}else{
			convert = power;
			convert = convert * 63/100 + 192;
		}
	}else{
		convert = 100 + power;
		convert = convert * 126/200 + 1;
	}
	return (uint8_t) convert;

}


Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

