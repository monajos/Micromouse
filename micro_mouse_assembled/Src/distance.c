#include "distance.h"
#include "main.h"

void usDelay(uint16_t uSec);
uint16_t wait_couter_f = 0;
uint16_t wait_couter_r = 0;
uint16_t wait_couter_l = 0;


int calc_distance_f(void)
{

    uint16_t numTicks;
    float distance_f;

    // HAL_GPIO_WritePin(TRIG_FRONT_GPIO_Port, TRIG_FRONT_Pin, GPIO_PIN_RESET);
    // usDelay(3);

    // Trigger-Pin für 10 uSec auf high
    HAL_GPIO_WritePin(TRIG_FRONT_GPIO_Port, TRIG_FRONT_Pin, GPIO_PIN_SET);
    usDelay(5);
    HAL_GPIO_WritePin(TRIG_FRONT_GPIO_Port, TRIG_FRONT_Pin, GPIO_PIN_RESET);

    wait_couter_f = 0;
    // auf Signal vom Echo-Pin warten
    while(HAL_GPIO_ReadPin(ECHO_FRONT_GPIO_Port, ECHO_FRONT_Pin) == GPIO_PIN_RESET)
    {
      wait_couter_f++;
      if(wait_couter_f >= 0xFFFF)
      {
        wait_couter_f = 0;
        break;
      }
    };

    // sobald Signal am Echo-Pin auf high, Zeitmessung starten
    numTicks = 0;
    while(HAL_GPIO_ReadPin(ECHO_FRONT_GPIO_Port, ECHO_FRONT_Pin) == GPIO_PIN_SET)
    {
      if (numTicks > 1000) break;
      numTicks++;
      usDelay(1); 
    }

    // Entfernung berechnen
    distance_f = numTicks * 2 * 0.03432 / 2;

  
  return distance_f;
}

int calc_distance_r(void)
{
    uint16_t numTicks;
    float distance_r;

    // HAL_GPIO_WritePin(TRIG_RIGHT_GPIO_Port, TRIG_RIGHT_Pin, GPIO_PIN_RESET);
    // usDelay(3);

    // Trigger-Pin für 10 uSec auf high
    HAL_GPIO_WritePin(TRIG_RIGHT_GPIO_Port, TRIG_RIGHT_Pin, GPIO_PIN_SET);
    usDelay(5);
    HAL_GPIO_WritePin(TRIG_RIGHT_GPIO_Port, TRIG_RIGHT_Pin, GPIO_PIN_RESET);

    wait_couter_r = 0;
    // auf Signal vom Echo-Pin warten
    while(HAL_GPIO_ReadPin(ECHO_RIGHT_GPIO_Port, ECHO_RIGHT_Pin) == GPIO_PIN_RESET)
    {
      wait_couter_r++;
      if(wait_couter_r >= 0xFFFF)
      {
        wait_couter_r = 0;
        break;
      }
    };

    // sobald Signal am Echo-Pin auf high, Zeitmessung starten
    numTicks = 0;
    while(HAL_GPIO_ReadPin(ECHO_RIGHT_GPIO_Port, ECHO_RIGHT_Pin) == GPIO_PIN_SET)
    {
      if (numTicks > 1000) break;
      numTicks++;
      usDelay(1); 
    }

    // Entfernung berechnen
    distance_r = numTicks * 2 * 0.03432 / 2;

  
  return distance_r;
}

int calc_distance_l(void)
{
    uint16_t numTicks;
    float distance_l;

    // HAL_GPIO_WritePin(TRIG_LEFT_GPIO_Port, TRIG_LEFT_Pin, GPIO_PIN_RESET);
    // usDelay(3);

    // Trigger-Pin für 10 uSec auf high
    HAL_GPIO_WritePin(TRIG_LEFT_GPIO_Port, TRIG_LEFT_Pin, GPIO_PIN_SET);
    usDelay(5);
    HAL_GPIO_WritePin(TRIG_LEFT_GPIO_Port, TRIG_LEFT_Pin, GPIO_PIN_RESET);
    
    wait_couter_l = 0;
    // auf Signal vom Echo-Pin warten
    while(HAL_GPIO_ReadPin(ECHO_LEFT_GPIO_Port, ECHO_LEFT_Pin) == GPIO_PIN_RESET)
    {
      wait_couter_l++;
      if(wait_couter_l >= 0xFFFF)
      {
        wait_couter_l = 0;
        break;
      }
    };

    // sobald Signal am Echo-Pin auf high, Zeitmessung starten
    numTicks = 0;
    while(HAL_GPIO_ReadPin(ECHO_LEFT_GPIO_Port, ECHO_LEFT_Pin) == GPIO_PIN_SET)
    {
      if (numTicks > 1000) break;
      numTicks++;
      usDelay(1); 
    }

    // Entfernung berechnen
    distance_l = numTicks * 2 * 0.03432 / 2;

  
  return distance_l;
}

