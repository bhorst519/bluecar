/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define TURN_R_Pin GPIO_PIN_0
#define TURN_R_GPIO_Port GPIOC
#define TURN_L_Pin GPIO_PIN_1
#define TURN_L_GPIO_Port GPIOC
#define HIGHBEAM_Pin GPIO_PIN_2
#define HIGHBEAM_GPIO_Port GPIOC
#define OIL_Pin GPIO_PIN_3
#define OIL_GPIO_Port GPIOC
#define TEMP_Pin GPIO_PIN_0
#define TEMP_GPIO_Port GPIOA
#define FUEL_Pin GPIO_PIN_1
#define FUEL_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define BATT_12V_ADC_Pin GPIO_PIN_4
#define BATT_12V_ADC_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LAP_STARTER_Pin GPIO_PIN_6
#define LAP_STARTER_GPIO_Port GPIOA
#define HESD_Pin GPIO_PIN_7
#define HESD_GPIO_Port GPIOA
#define FAULT_INDICATOR_Pin GPIO_PIN_4
#define FAULT_INDICATOR_GPIO_Port GPIOC
#define NEUTRAL_Pin GPIO_PIN_5
#define NEUTRAL_GPIO_Port GPIOC
#define HEADLIGHT_RELAY_Pin GPIO_PIN_0
#define HEADLIGHT_RELAY_GPIO_Port GPIOB
#define LAP_RELAY_Pin GPIO_PIN_1
#define LAP_RELAY_GPIO_Port GPIOB
#define FIFTH_Pin GPIO_PIN_2
#define FIFTH_GPIO_Port GPIOB
#define RELAY_C_Pin GPIO_PIN_10
#define RELAY_C_GPIO_Port GPIOB
#define RELAY_D_Pin GPIO_PIN_12
#define RELAY_D_GPIO_Port GPIOB
#define TA_SIG_Pin GPIO_PIN_6
#define TA_SIG_GPIO_Port GPIOC
#define SP_SIG_Pin GPIO_PIN_7
#define SP_SIG_GPIO_Port GPIOC
#define FUEL_PULSE_Pin GPIO_PIN_8
#define FUEL_PULSE_GPIO_Port GPIOC
#define FIRST_Pin GPIO_PIN_9
#define FIRST_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SECOND_Pin GPIO_PIN_10
#define SECOND_GPIO_Port GPIOC
#define THIRD_Pin GPIO_PIN_11
#define THIRD_GPIO_Port GPIOC
#define FOURTH_Pin GPIO_PIN_12
#define FOURTH_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SIXTH_Pin GPIO_PIN_4
#define SIXTH_GPIO_Port GPIOB
#define MCP2021_FLT_Pin GPIO_PIN_5
#define MCP2021_FLT_GPIO_Port GPIOB
#define RELAY_A_Pin GPIO_PIN_8
#define RELAY_A_GPIO_Port GPIOB
#define RELAY_B_Pin GPIO_PIN_9
#define RELAY_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
