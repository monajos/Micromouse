#include "stepper.h"

void lre_stepper_setStep1(uint8_t step){
    switch (step)
    {
    case 0:
    
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_9, GPIO_PIN_RESET);
        break;
    case 4:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_RESET);
        break;
    case 5:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);
        break;
    case 6:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_RESET);
        break;
    case 7:
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6 | GPIO_PIN_9, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_RESET);
        break;
    
    default:
        break;
    }

}


void lre_stepper_setStep2(uint8_t step){
    switch (step)
    {
    case 0:
    
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_6, GPIO_PIN_RESET);
        break;
    case 4:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6, GPIO_PIN_RESET);
        break;
    case 5:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);
        break;
    case 6:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
        break;
    case 7:
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
        break;
    
    default:
        break;
    }

}
