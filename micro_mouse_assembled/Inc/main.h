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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
uint8_t i_step;
uint8_t i_left;
uint8_t i_right;
uint32_t j_tim2;
uint16_t k_step;
uint8_t cnt;
uint16_t k_turn;
int16_t mv_rt_deg;
uint8_t mean_f;
uint8_t mean_r;
uint8_t mean_l;
uint16_t sum_f;
uint16_t sum_l;
uint16_t sum_r;
int16_t mv_distance;
uint8_t mv_stop; 
uint16_t mv_speed;
int16_t mv_rt_left;
int16_t mv_rt_right;
uint8_t turn_mode;
uint8_t measure_mode_l; 
uint8_t measure_mode_r; 
uint8_t measure_mode_f; 
uint8_t rxdata[20];
uint8_t maze_counter; // maze iteration counter
uint8_t maze_counter_fast; 
uint8_t x_coordinate;
uint8_t y_coordinate;
uint8_t x_start;
uint8_t y_start;
uint8_t shortest_way[50][2];
char shortest_way_direction[50];
uint8_t solving_mode;
uint8_t solving_mode_fast;

uint16_t dis_mz_f;
uint16_t dis_mz_r;
uint16_t dis_mz_l; 
char orientation;   // should be N, E, S or W 
char orientation_start;

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
#define ECHO_RIGHT_Pin GPIO_PIN_4
#define ECHO_RIGHT_GPIO_Port GPIOA
#define TRIG_RIGHT_Pin GPIO_PIN_5
#define TRIG_RIGHT_GPIO_Port GPIOA
#define MOTOR_RIGHT_4_Pin GPIO_PIN_6
#define MOTOR_RIGHT_4_GPIO_Port GPIOC
#define MOTOR_RIGHT_3_Pin GPIO_PIN_7
#define MOTOR_RIGHT_3_GPIO_Port GPIOC
#define MOTOR_RIGHT_2_Pin GPIO_PIN_8
#define MOTOR_RIGHT_2_GPIO_Port GPIOC
#define MOTOR_RIGHT_1_Pin GPIO_PIN_9
#define MOTOR_RIGHT_1_GPIO_Port GPIOC
#define ECHO_FRONT_Pin GPIO_PIN_10
#define ECHO_FRONT_GPIO_Port GPIOC
#define TRIG_FRONT_Pin GPIO_PIN_11
#define TRIG_FRONT_GPIO_Port GPIOC
#define MOTOR_LEFT_4_Pin GPIO_PIN_3
#define MOTOR_LEFT_4_GPIO_Port GPIOB
#define MOTOR_LEFT_3_Pin GPIO_PIN_4
#define MOTOR_LEFT_3_GPIO_Port GPIOB
#define MOTOR_LEFT_2_Pin GPIO_PIN_5
#define MOTOR_LEFT_2_GPIO_Port GPIOB
#define MOTOR_LEFT_1_Pin GPIO_PIN_6
#define MOTOR_LEFT_1_GPIO_Port GPIOB
#define ECHO_LEFT_Pin GPIO_PIN_8
#define ECHO_LEFT_GPIO_Port GPIOB
#define TRIG_LEFT_Pin GPIO_PIN_9
#define TRIG_LEFT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
