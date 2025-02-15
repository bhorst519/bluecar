/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KLINE_EN_Pin GPIO_PIN_2
#define KLINE_EN_GPIO_Port GPIOF
#define MAIN_RLY_EN_Pin GPIO_PIN_3
#define MAIN_RLY_EN_GPIO_Port GPIOF
#define ENG_ON_EN_Pin GPIO_PIN_4
#define ENG_ON_EN_GPIO_Port GPIOF
#define ENG_START_EN_Pin GPIO_PIN_5
#define ENG_START_EN_GPIO_Port GPIOF
#define BRAKE_LIGHT_EN_Pin GPIO_PIN_6
#define BRAKE_LIGHT_EN_GPIO_Port GPIOF
#define HIGHBEAM_EN_Pin GPIO_PIN_7
#define HIGHBEAM_EN_GPIO_Port GPIOF
#define L_TURN_SIG_EN_Pin GPIO_PIN_8
#define L_TURN_SIG_EN_GPIO_Port GPIOF
#define R_TURN_SIG_EN_Pin GPIO_PIN_9
#define R_TURN_SIG_EN_GPIO_Port GPIOF
#define HORN_EN_Pin GPIO_PIN_10
#define HORN_EN_GPIO_Port GPIOF
#define VSS_Pin GPIO_PIN_4
#define VSS_GPIO_Port GPIOC
#define FAULT_IND_Pin GPIO_PIN_5
#define FAULT_IND_GPIO_Port GPIOC
#define PB2_Pin GPIO_PIN_2
#define PB2_GPIO_Port GPIOB
#define OIL_P_LOW_Pin GPIO_PIN_11
#define OIL_P_LOW_GPIO_Port GPIOF
#define TACH_Pin GPIO_PIN_12
#define TACH_GPIO_Port GPIOF
#define NEUTRAL_Pin GPIO_PIN_13
#define NEUTRAL_GPIO_Port GPIOF
#define LOWBEAM_Pin GPIO_PIN_14
#define LOWBEAM_GPIO_Port GPIOF
#define HIGHBEAM_Pin GPIO_PIN_15
#define HIGHBEAM_GPIO_Port GPIOF
#define TURN_L_Pin GPIO_PIN_0
#define TURN_L_GPIO_Port GPIOG
#define TURN_R_Pin GPIO_PIN_1
#define TURN_R_GPIO_Port GPIOG
#define SIXTH_Pin GPIO_PIN_7
#define SIXTH_GPIO_Port GPIOE
#define FIFTH_Pin GPIO_PIN_8
#define FIFTH_GPIO_Port GPIOE
#define FOURTH_Pin GPIO_PIN_9
#define FOURTH_GPIO_Port GPIOE
#define THIRD_Pin GPIO_PIN_10
#define THIRD_GPIO_Port GPIOE
#define SECOND_Pin GPIO_PIN_11
#define SECOND_GPIO_Port GPIOE
#define FIRST_Pin GPIO_PIN_12
#define FIRST_GPIO_Port GPIOE
#define HL_RLY_EN_Pin GPIO_PIN_13
#define HL_RLY_EN_GPIO_Port GPIOE
#define LAP_RLY_EN_Pin GPIO_PIN_14
#define LAP_RLY_EN_GPIO_Port GPIOE
#define LED2_R_Pin GPIO_PIN_12
#define LED2_R_GPIO_Port GPIOD
#define LED2_G_Pin GPIO_PIN_13
#define LED2_G_GPIO_Port GPIOD
#define RS485_DIR_Pin GPIO_PIN_4
#define RS485_DIR_GPIO_Port GPIOD
#define VSSB5_Pin GPIO_PIN_5
#define VSSB5_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_8
#define LED1_GPIO_Port GPIOB
#define LED2_B_Pin GPIO_PIN_9
#define LED2_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
