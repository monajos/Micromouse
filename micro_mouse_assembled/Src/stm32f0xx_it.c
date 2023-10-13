/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
  
  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    break;
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel 2 and 3 interrupts.
  */
void DMA1_Channel2_3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 0 */

  /* USER CODE END DMA1_Channel2_3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 1 */

  /* USER CODE END DMA1_Channel2_3_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  j_tim2 = j_tim2 + 1;


  /*uint8_t measure = 5;  // jede Milisekunde (5*0,2ms) wird gemessen
  if (measure_mode == 1)
  {
    if (j % measure == 0)
    {
      if (cnt == 10)
      {
        mean_f = sum_f/10;
        mean_r = sum_r/10;
        mean_l = sum_l/10;      
        
        sum_f = 0;
        sum_l = 0;
        sum_r = 0;      
        cnt = 0;
      }
      else
      {
        uint16_t dis_f = calc_distance_f();
        uint16_t dis_l = calc_distance_l();
        uint16_t dis_r = calc_distance_r();
        sum_f = dis_f + sum_f;
        sum_l = dis_l + sum_l;
        sum_r = dis_r + sum_r;
        cnt++;
      }
    }
  }*/
  
  if (turn_mode == 0)                       // going straight 
  {
    uint8_t everyxstep = (int)1000/(21*0.2*mv_speed); 
    
    if(j_tim2 % everyxstep == 0){               // wenn j_tim2 durch everyxstep teilbar ist
      if (k_step < abs(mv_distance)*21){
        if (mv_distance <0)
        {
          lre_stepper_setStep1(-i_step+7);
          lre_stepper_setStep2(-i_step+7); 
          k_step++;
        }
        else
        {
          lre_stepper_setStep1(i_step);
          lre_stepper_setStep2(i_step);   
          k_step++;   
        }  
        i_step++;
        
        if (i_step > 7){
          i_step=0;
        }
      }
      else if (k_step >= abs(mv_distance)*21)
        {
          mv_distance = 0;
          k_step = 0;            
        }   
    }
  }

  if (turn_mode == 1)                      // TURN MODE ON 
  {
    uint8_t everyxstep_left = (int)1000/(21*0.2*abs(mv_rt_left));
    uint8_t everyxstep_right = (int)1000/(21*0.2*abs(mv_rt_right));

    if(j_tim2 % everyxstep_left == 0){               // wenn j_tim2 durch everyxstep teilbar ist           // distance not applicable                     
      if (k_turn < mv_rt_deg*19){
        if (mv_rt_left<0){
          lre_stepper_setStep2(-i_left+7);} // links -> Pink
        else{
          lre_stepper_setStep2(i_left);}
        i_left++;
        if (i_left > 7){
          i_left=0;
        }
      }                
    }
    if (j_tim2 % everyxstep_right == 0){
      if (k_turn < mv_rt_deg*19){
        if (mv_rt_right<0){
          lre_stepper_setStep1(-i_right+7);}  // rechts -> Blau 
        else{
          lre_stepper_setStep1(i_right);}
        i_right++;
        k_turn++;
        if (i_right > 7){
          i_right=0;
        }
      }
      else if (k_turn >=  mv_rt_deg*19)
      {
        mv_rt_deg = 0;
        k_turn = 0; 
        turn_mode = 0;
      }
    }    
  }

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
