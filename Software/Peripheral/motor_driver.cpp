		/*
 * Motor_Driver.cpp
 *
 *  Created on: Jun 3, 2023
 *      Author: BRG
 */

#include "motor_driver.h"

#include "stm32f4xx_hal_uart.h"

Motor::Motor(USART_TypeDef * UARTX):
leftPower(0),
rightPower(0)
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
	stop();
}
void Motor::stop(){
	changePower(0, 0);
}
void Motor::changePower(int8_t leftPower, int8_t rightPower)
{
	leftPower = boundedPowerValue(leftPower);
	rightPower = boundedPowerValue(rightPower);


	if(this->leftPower != leftPower || this->rightPower != rightPower){
		this->leftPower = leftPower;
		this->rightPower = rightPower;

		uint8_t motor_input_left_right[2];
		motor_input_left_right[0] = power_to_motor_input(leftPower, false);
		motor_input_left_right[1] = power_to_motor_input(rightPower, true);

		//Transmit Three Times
		while(HAL_UART_Transmit(&h_uart, motor_input_left_right, 2, 100) != HAL_OK);
		while(HAL_UART_Transmit(&h_uart, motor_input_left_right, 2, 100) != HAL_OK);
		while(HAL_UART_Transmit(&h_uart, motor_input_left_right, 2, 100) != HAL_OK);
	}
}


uint8_t Motor::power_to_motor_input(int8_t power, bool is_right_motor)
{
	float convert;
	if(is_right_motor){
		if(power <= 0){
			convert = 100 + power;
			convert = convert * 64/MAX_POWER + 128;
		}else{
			convert = power;
			convert = convert * 63/MAX_POWER + 192;
		}
	}else{
		convert = MAX_POWER + power;
		convert = convert * 126/200 + 1;
	}
	return (uint8_t) convert;
}
uint8_t Motor::boundedPowerValue(int8_t power){
	if(power > MAX_POWER)
		return MAX_POWER;
	if(power < MAX_REVERSE_POWER){
		return MAX_REVERSE_POWER;
	}
	return power;
}
