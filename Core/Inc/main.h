/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TRIMPOT_0_Pin GPIO_PIN_0
#define TRIMPOT_0_GPIO_Port GPIOC
#define START_MODULE_Pin GPIO_PIN_1
#define START_MODULE_GPIO_Port GPIOC
#define CEVA_LED_Pin GPIO_PIN_2
#define CEVA_LED_GPIO_Port GPIOC
#define UART4_TX_DATA_Pin GPIO_PIN_0
#define UART4_TX_DATA_GPIO_Port GPIOA
#define LINE_SENSOR_2_1_Pin GPIO_PIN_1
#define LINE_SENSOR_2_1_GPIO_Port GPIOA
#define LINE_SENSOR_2_2_Pin GPIO_PIN_2
#define LINE_SENSOR_2_2_GPIO_Port GPIOA
#define LINE_SENSOR_2_3_Pin GPIO_PIN_3
#define LINE_SENSOR_2_3_GPIO_Port GPIOA
#define TRIMPOT_1_Pin GPIO_PIN_4
#define TRIMPOT_1_GPIO_Port GPIOA
#define LINE_SENSOR_3_1_Pin GPIO_PIN_5
#define LINE_SENSOR_3_1_GPIO_Port GPIOA
#define LINE_SENSOR_3_2_Pin GPIO_PIN_6
#define LINE_SENSOR_3_2_GPIO_Port GPIOA
#define LINE_SENSOR_3_3_Pin GPIO_PIN_7
#define LINE_SENSOR_3_3_GPIO_Port GPIOA
#define LINE_SENSOR_0_Pin GPIO_PIN_0
#define LINE_SENSOR_0_GPIO_Port GPIOB
#define LINE_SENSOR_1_Pin GPIO_PIN_1
#define LINE_SENSOR_1_GPIO_Port GPIOB
#define ENEMY_SENSOR_0_Pin GPIO_PIN_2
#define ENEMY_SENSOR_0_GPIO_Port GPIOB
#define ENEMY_SENSOR_5_Pin GPIO_PIN_13
#define ENEMY_SENSOR_5_GPIO_Port GPIOB
#define ENEMY_SENSOR_6_Pin GPIO_PIN_14
#define ENEMY_SENSOR_6_GPIO_Port GPIOB
#define ENEMY_SENSOR_7_Pin GPIO_PIN_15
#define ENEMY_SENSOR_7_GPIO_Port GPIOB
#define B0_UP_Pin GPIO_PIN_6
#define B0_UP_GPIO_Port GPIOC
#define USART1_TX_SABERTOOTH_Pin GPIO_PIN_9
#define USART1_TX_SABERTOOTH_GPIO_Port GPIOA
#define B2_DOWN_Pin GPIO_PIN_11
#define B2_DOWN_GPIO_Port GPIOA
#define B1_SELECT_Pin GPIO_PIN_12
#define B1_SELECT_GPIO_Port GPIOA
#define ENEMY_SENSOR_1_Pin GPIO_PIN_6
#define ENEMY_SENSOR_1_GPIO_Port GPIOB
#define ENEMY_SENSOR_2_Pin GPIO_PIN_7
#define ENEMY_SENSOR_2_GPIO_Port GPIOB
#define ENEMY_SENSOR_3_Pin GPIO_PIN_8
#define ENEMY_SENSOR_3_GPIO_Port GPIOB
#define ENEMY_SENSOR_4_Pin GPIO_PIN_9
#define ENEMY_SENSOR_4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define SABERTOOTH_UART USART1
#define DATA_UART UART4

///ADC 1

#define LINE_SENSOR_2_1_CHANNEL ADC_CHANNEL_1
#define LINE_SENSOR_2_2_CHANNEL ADC_CHANNEL_2
#define LINE_SENSOR_2_3_CHANNEL ADC_CHANNEL_3
#define LINE_SENSOR_3_1_CHANNEL ADC_CHANNEL_5
#define LINE_SENSOR_3_2_CHANNEL ADC_CHANNEL_6
#define LINE_SENSOR_3_3_CHANNEL ADC_CHANNEL_7

#define LINE_SENSOR_FL_1_CHANNEL LINE_SENSOR_2_1_CHANNEL
#define LINE_SENSOR_FL_2_CHANNEL LINE_SENSOR_2_2_CHANNEL
#define LINE_SENSOR_FL_3_CHANNEL LINE_SENSOR_2_3_CHANNEL
#define LINE_SENSOR_FR_1_CHANNEL LINE_SENSOR_3_1_CHANNEL
#define LINE_SENSOR_FR_2_CHANNEL LINE_SENSOR_3_2_CHANNEL
#define LINE_SENSOR_FR_3_CHANNEL LINE_SENSOR_3_3_CHANNEL

///ADC2


#define LINE_SENSOR_0_CHANNEL ADC_CHANNEL_9
#define LINE_SENSOR_1_CHANNEL ADC_CHANNEL_14

#define LINE_SENSOR_BL_CHANNEL LINE_SENSOR_0_CHANNEL
#define LINE_SENSOR_BR_CHANNEL LINE_SENSOR_1_CHANNEL

#define TRIMPOT_0_CHANNEL ADC_CHANNEL_10
#define TRIMPOT_1_CHANNEL ADC_CHANNEL_4

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
