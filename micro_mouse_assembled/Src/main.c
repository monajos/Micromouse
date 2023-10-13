/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distance.h"
#include "maze.h"
#include "functions.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

char char_INPUT[18];
int8_t parameter_h;
int8_t parameter_d;
int8_t parameter_o;
int16_t parameter;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
uint8_t dis_f;
uint8_t dis_r;
uint8_t dis_l;
uint8_t onlyonce = 0;

uint8_t check = 0;
uint8_t controlvar;
uint8_t controlvar_corner = 0;
uint8_t controlvar_wall = 0;
uint8_t Number_of_cells = 0;
uint8_t goal_x;
uint8_t goal_y; 


// uint8_t Path[9] = {1,2,3,4,5,3,7,8,9};
//uint8_t cnt = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void usDelay(uint16_t uSec);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  initMaze();
  initPath();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_DMA(&huart1, rxdata, sizeof(rxdata));

  HAL_TIM_Base_Start (&htim1);

  __HAL_TIM_SET_PRESCALER(&htim2, SystemCoreClock/1000000 - 1);
  __HAL_TIM_SET_AUTORELOAD(&htim2, 200 - 1);   // 1500 desired delay length 
  __HAL_TIM_SET_COUNTER(&htim2,100);
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
  i_step = 0;
  j_tim2 = 0;
  k_step = 0;
  cnt = 0;
  k_turn = 0;
  // mean_f =1000;
  mv_distance = 0; //1000;
  mv_speed = 45; // speed in mm/s
  mv_rt_deg = 90; // turn in °        ----> FUNKTIONIERT NUR WENN BEIDE RÄDER MIT GLEICHER GESCHWINDIGKEIT DREHEN
  mv_rt_left = 30;  // speed left  
  mv_rt_right = 30;  // speed right 
  turn_mode = 0; // Turn mode, 0 = off, 1 = on 
  measure_mode_l = 0; 
  measure_mode_r = 0; 
  measure_mode_f = 0; 
  x_start = 0;
  y_start = 0;
  solving_mode = 0;
  solving_mode_fast = 0;

  mean_f = 100;
  mean_r = 100;
  mean_l = 100;       
  sum_f = 0;
  sum_l = 0;
  sum_r = 0;   
  goal_x = 3;
  goal_y = 3;

  // path[0]->x_pos = 1;
  // path[0]->y_pos = 1;
  // path[0]->direction = 'E';  

  // path[1]->x_pos = 2;
  // path[1]->y_pos = 1;
  // path[1]->direction = 'S';  

  // path[2]->x_pos = 2;
  // path[2]->y_pos = 0;
  // path[2]->direction = 'N';  

  // path[3]->x_pos = 2;
  // path[3]->y_pos = 1;
  // path[3]->direction = 'N';  

  // path[4]->x_pos = 2;
  // path[4]->y_pos = 2;
  // path[4]->direction = 'E';  

  // path[5]->x_pos = 3;
  // path[5]->y_pos = 2;
  // path[5]->direction = 'E';   

  // path[6]->x_pos = 4;
  // path[6]->y_pos = 2;
  // path[6]->direction = 'N';  

  // path[7]->x_pos = 4;
  // path[7]->y_pos = 3;
  // path[7]->direction = 'W';  

  // maze_counter = 7; 

  while (1)
  {
    strncpy(char_INPUT, (const char *)rxdata, 18);

    if (cnt == 20)
    {
      if (measure_mode_f==1)      // If measuremode for front activated
      {
        mean_f = sum_f/20;
        sum_f = 0;   
      }
      if (measure_mode_r==1)     // If measuremode for right activated
      {
        mean_r = sum_r/20;
        sum_r = 0;
      }
      if (measure_mode_l==1)      // If measuremode for left activated
      {
        mean_l = sum_l/20; 
        sum_l = 0; 
      }                 
      cnt = 0;     
    }
    else
    {
      if (measure_mode_f==1)
      {
        dis_f = calc_distance_f();
        sum_f = dis_f + sum_f;
      }
      if (measure_mode_l==1)
      {
        dis_l = calc_distance_l();
        sum_l = dis_l + sum_l;
      }
      if (measure_mode_r==1)
      {
        dis_r = calc_distance_r();     
        sum_r = dis_r + sum_r;
      }
      cnt++;
      HAL_Delay(1);
    } 
    
    if (strncmp(&char_INPUT[0], "mv", 2) == 0)
    {
      if (strncmp(&char_INPUT[2], "sp", 2) == 0) // define speed
      {
        // movement speed
        uint8_t* message1 = "You set the speed in mm/s. \r\n\r\n";
        HAL_UART_Transmit(&huart1, message1, strlen(message1),10);
        parameter_h = (int)char_INPUT[4] - 48;
        parameter_d = (int)char_INPUT[5] - 48;
        parameter_o = (int)char_INPUT[6] - 48;
        parameter = 100*parameter_h + 10*parameter_d + parameter_o;

        turn_mode = 0;
        mv_speed = parameter;
        clear_buffer();
        
      } 
      else if (strncmp(&char_INPUT[2], "ds", 2) == 0) // define distance
      {
        // movement distance
        uint8_t* message2 = "You set a distance in mm. \r\n\r\n";
        HAL_UART_Transmit(&huart1, message2, strlen(message2),100);
        parameter_h = (int)char_INPUT[4] - 48;
        parameter_d = (int)char_INPUT[5] - 48;
        parameter_o = (int)char_INPUT[6] - 48;

        if ((int)char_INPUT[4]==45) //falls das Erste ein Minus ist
        {
          parameter_h = 0;
        }        
        parameter = 100*parameter_h + 10*parameter_d + parameter_o;

        turn_mode = 0;
        
        mv_distance = parameter;
        
        if ((int)char_INPUT[4]==45) //falls das Erste ein Minus ist
        {
          mv_distance = -parameter;
        }

        clear_buffer();
      }
      else if (strncmp(&char_INPUT[2], "st", 2) == 0) // stop mausi
      {
        // movement stop
        uint8_t* message3 = "Mausi stops. \r\n\r\n";
        HAL_UART_Transmit(&huart1, message3, strlen(message3),100);

        turn_mode = 0;
        mv_distance = 0;
        solving_mode = 0;
        solving_mode_fast = 0;
        
        clear_buffer();
      }
      else if (strncmp(&char_INPUT[2], "rt", 2) == 0) // rotate mausi
      {
        // movement rotation
        uint8_t* message4 = "Mausi is turning with your given speed. \r\n";
        HAL_UART_Transmit(&huart1, message4, strlen(message4),100);       
        parameter_h = (int)char_INPUT[4] - 48;
        parameter_d = (int)char_INPUT[5] - 48;
        parameter_o = (int)char_INPUT[6] - 48;
        parameter = 100*parameter_h + 10*parameter_d + parameter_o;

        turn_mode = 1;
        mv_rt_left = parameter;   // so oder so ähnlich
        mv_rt_right = -parameter;
      }
      else if (strncmp(&char_INPUT[2], "pa", 2) == 0) // parking cmd
      {
        // parking cmd
        // mv_distance = 1000;
        if (mean_f<12)
        {
          check++;
        }
        if (check>=3 && onlyonce == 0)  // wenn mean drei mal unter 10 cm 
        {
          turn_mode = 1; 
          mv_rt_deg = 180;
          mv_rt_left = 30;
          mv_rt_right = -30;
          onlyonce = 1;
        }
        if (k_turn >= mv_rt_deg*19) // wenn 180° gedreht, nochmal 5cm zurücksetzen 
        {
          k_turn =0;
          k_step = 0;
          turn_mode = 0;
          mv_distance = -50;        
        }
                
      }
      else if (strncmp(&char_INPUT[2], "wa", 2) == 0)
      {
         // Follow a wall 
        if(controlvar_wall == 0){
          mv_distance = 2000;
          controlvar_wall = 1;
        }
         
        if (mean_l<6) //nur links
        {
          turn_mode = 1;
          mv_rt_left = 30;
          mv_rt_right = 25;
          k_turn = 0;
        }
        else if (mean_l>8)
        {
          turn_mode = 1;
          mv_rt_left = 25;
          mv_rt_right = 30;
          k_turn = 0;
        }
        else
        {
          //turn_mode = 0;
          //mv_speed = 30; 
        }
      }
      else if (strncmp(&char_INPUT[2], "co", 2) == 0)
      {
      // Follow a wall and corner 
      if (mean_l<6 && mean_f>15) //nur links
      {
        turn_mode = 1;
        mv_rt_left = 30;
        mv_rt_right = 25;
        k_turn = 0;
      }
      else if (mean_l>8 && mean_f >15)
      {
        turn_mode = 1;
        mv_rt_left = 25;
        mv_rt_right = 30;
        k_turn = 0;
      }
      else if (mean_f > 15)
      {
        turn_mode = 0;
        mv_speed = 30; 
      }
      // Follow a corner 
      if (mean_f<10)
        {
          check++;
        }
      if (check>3 && mean_l<12)  // Rechtskurve
      {
        if (controlvar_corner==0)
        {
          k_turn = 0; 
        }
        check =0;
        controlvar_corner=1;
        measure_mode_l = 0;
        measure_mode_f = 0;
        mv_rt_deg = 90;
        turn_mode = 1;
        mv_rt_left = 30;
        mv_rt_right = -30;
        
        //onlyonce = 1;
      }
        /*if (mean_f<10 && mean_r<12 && onlyonce == 0)  // Linkskurve
        {
          mv_rt_deg = 90;
          turn_mode = 1;
          mv_rt_left = -30;
          mv_rt_right = 30;
          onlyonce = 1;
        }*/
  
        if (k_turn >= mv_rt_deg*19)
        {
          turn_mode = 0;
          measure_mode_l =1;
          measure_mode_f =1;
        }
      }
      else /* unexpected input */
      {
        uint8_t* message = "Invalid input! Expected sp,ds,st or rt. \r\n";
        HAL_UART_Transmit(&huart1, message, strlen(message),100);
        clear_buffer();
      }
    } 
    else if  (strncmp(&char_INPUT[0], "tm", 2) == 0)
    {
      if (strncmp(&char_INPUT[2], "ds", 2) == 0) 
      {
        measure_mode_f = 1;
        measure_mode_l = 1;
        measure_mode_r = 1;

        // telemetry distance
        if (cnt == 1)
        {
          
          char buffer[20];
          int len_f=sprintf(buffer,"Front = %i" "cm   ", mean_f);
          HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len_f, HAL_MAX_DELAY);
          int len_l=sprintf(buffer,"Left = %i" "cm   ", mean_l);
          HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len_l, HAL_MAX_DELAY);
          int len_r=sprintf(buffer,"Right = %i" "cm   \r\n\r\n", mean_r);
          HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len_r, HAL_MAX_DELAY);
          // mean_f = 0;
          // mean_l = 0;
          // mean_r = 0;
          clear_buffer();
        }
        else
        {
        
        }
      } 
      else if (strncmp(&char_INPUT[2], "od", 2) == 0)
      {
        // telemetry odometry
        uint8_t* message6 = "We don't use this command.  \r\n\r\n";
        HAL_UART_Transmit(&huart1, message6, strlen(message6),100);
      }
      else if (strncmp(&char_INPUT[2], "vc", 2) == 0)
      {
        // telemetry vector
        uint8_t* message7 = "We don't use this command.  \r\n\r\n";
        HAL_UART_Transmit(&huart1, message7, strlen(message7),100);
      }
      else if (strncmp(&char_INPUT[2], "hd", 2) == 0)
      {
        // telemetry heading
        uint8_t* message8 = "We don't use this command. \r\n \r\n";
        HAL_UART_Transmit(&huart1, message8, strlen(message8),100);
      }
      else /* unexpected input */
      {
        uint8_t* message = "Invalid input! Expected ds. \r\n\r\n";
        HAL_UART_Transmit(&huart1, message, strlen(message),10);
        clear_buffer();
      }
    }
    else if (strncmp(&char_INPUT[0], "mz", 2) == 0)
    {    
      if (strncmp(&char_INPUT[2], "ds", 2) == 0)
      {
        // telemetry odometry
        uint8_t* message6 = "You commanded the number of cells Mausi shall drive. \r\n"; 
        HAL_UART_Transmit(&huart1, message6, strlen(message6),100);
        parameter_h = (int)char_INPUT[4] - 48;
        parameter_d = (int)char_INPUT[5] - 48;
        parameter_o = (int)char_INPUT[6] - 48;
        parameter = 100*parameter_h + 10*parameter_d + parameter_o;

        Number_of_cells = parameter;
        mv_distance = Number_of_cells * 200;
        clear_buffer();
        
      }
      else if (strncmp(&char_INPUT[2], "tu", 2) == 0)
      {
        // telemetry odometry
        uint8_t* message6 = "Mausi is turning the angle you gave her. \r\n"; 
        HAL_UART_Transmit(&huart1, message6, strlen(message6),100);
        parameter_h = (int)char_INPUT[4] - 48;
        parameter_d = (int)char_INPUT[5] - 48;
        parameter_o = (int)char_INPUT[6] - 48;

        if ((int)char_INPUT[4]==45) //falls das Erste ein Minus ist
        {
          parameter_h = 0;
        }
        
        parameter = 100*parameter_h + 10*parameter_d + parameter_o;

        // if ((int)char_INPUT[4]==45)
        // {
        //   parameter *= -1;
        // }

        turn_mode = 1;
        mv_rt_deg = parameter; 
        if ((int)char_INPUT[4]==45)
        {
          mv_rt_left = -30;
          mv_rt_right = 30;          
        }
        else
        {
          mv_rt_left = 30;
          mv_rt_right = -30;
        }
        
        clear_buffer();
        
      }
      else if (strncmp(&char_INPUT[2], "ps", 2) == 0)
      {
        // return postion in maze
        char buffer[20];
        int pos_maze = sprintf(buffer,"Position: %i %i" "   \r\n \r\n", x_coordinate, y_coordinate);
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, pos_maze, HAL_MAX_DELAY);
        clear_buffer();
      }
      else if (strncmp(&char_INPUT[2], "gl", 2) == 0) // define destination
      {     
        maze_counter = 0;   
        uint8_t* message6 = "You defined the destination. \r\n \r\n"; 
        HAL_UART_Transmit(&huart1, message6, strlen(message6),100);

        // read (x,y) goal coordinates 
        goal_x = (int)char_INPUT[5] - 48; // x
        goal_y = (int)char_INPUT[6] - 48; // y       

        clear_buffer();             
        
      }
      else if (strncmp(&char_INPUT[2], "sv", 2) == 0) // solve
      {     
        maze_counter = 0;   
        uint8_t* message6 = "Mausi is solving the maze. \r\n \r\n"; 
        HAL_UART_Transmit(&huart1, message6, strlen(message6),100);

        // read (x,y) starting coordinates and starting orientation from user input
        x_coordinate = (int)char_INPUT[4] - 48; // x
        y_coordinate = (int)char_INPUT[5] - 48; // y
        orientation = (char)char_INPUT[6];            

        x_start = x_coordinate;
        y_start = y_coordinate;
        orientation_start = orientation;

        solving_mode = 1;

        clear_buffer();             
        
      }
      else if (strncmp(&char_INPUT[2], "rd", 2) == 0) // Read labyrinth cell walls from memory
      {
        int x_read = (int)char_INPUT[5] - 48; // x
        int y_read = (int)char_INPUT[6] - 48; // y

        char buffer[20];
        int read_walls = sprintf(buffer,"N E S W = %i %i %i %i" "   \r\n \r\n", maze[x_read][y_read]->wallNorth, 
                                                                          maze[x_read][y_read]->wallEast, 
                                                                          maze[x_read][y_read]->wallSouth, 
                                                                          maze[x_read][y_read]->wallWest);
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, read_walls, HAL_MAX_DELAY);
        clear_buffer();
      }
      else if (strncmp(&char_INPUT[2], "sw", 2) == 0) // shortest way 
      {
        maze_counter_fast = 0;
        int n = maze_counter;
        uint8_t k = 0;
        int doppelj = 0;

        for (int i = 0; i < n - 1; i++) {
          int control_var = 0;
          for (int j = i + 1; j < n; j++) {
            if (path[i]->x_pos == path[j]->x_pos && path[i]->y_pos == path[j]->y_pos) { // //Path[i]== Path[j]

              char buffer[10];
              int test = sprintf(buffer,"%i %i" "   \r\n \r\n", i,j);
              HAL_UART_Transmit(&huart1, (uint8_t*)buffer, test, HAL_MAX_DELAY);

              control_var = 1;
              doppelj = j;
              // i = j+1; 
            }
          }
          shortest_way[k][0] = path[i]->x_pos;
          shortest_way[k][1] = path[i]->y_pos;
          shortest_way_direction[k] = path[i]->direction;                     

          if (control_var == 1)
          {
            i = doppelj;
            shortest_way_direction[k] = path[doppelj]->direction;
          }     
          k++;      
        }
        shortest_way[k][0] = path[n-1]->x_pos;
        shortest_way[k][1] = path[n-1]->y_pos;
        shortest_way_direction[k] = path[n-1]->direction;

        shortest_way[k+1][0] = path[n]->x_pos;
        shortest_way[k+1][1] = path[n]->y_pos;
        shortest_way_direction[k+1] = path[n]->direction;
        // somehow delete everything after k 

        solving_mode_fast = 1; 
        x_coordinate = x_start;
        y_coordinate = y_start;
        orientation = orientation_start;
        uint8_t* fast_mode = "Mausi is now trying to find the fastest way! Vroom vroom! \r\n \r\n";
        HAL_UART_Transmit(&huart1, fast_mode, strlen(fast_mode),100);
        clear_buffer();       
      }    
      else if (strncmp(&char_INPUT[2], "wr", 2) == 0) // write labyrinth cell walls into memory
      {
        int parameter_x = (int)char_INPUT[4] - 48;
        int parameter_y = (int)char_INPUT[5] - 48;
        int parameter_wall_n = (int)char_INPUT[6] - 48;
        int parameter_wall_e = (int)char_INPUT[7] - 48;
        int parameter_wall_s = (int)char_INPUT[8] - 48;
        int parameter_wall_w = (int)char_INPUT[9] - 48;

        maze[parameter_x][parameter_y]->wallNorth = parameter_wall_n;
        maze[parameter_x][parameter_y]->wallEast = parameter_wall_e;
        maze[parameter_x][parameter_y]->wallSouth = parameter_wall_s;
        maze[parameter_x][parameter_y]->wallWest = parameter_wall_w;
      }
    }
    else if (strncmp(&char_INPUT[0], "\r\n", 2) == 0)
    {
      clear_buffer();
    }
    
    





    if (solving_mode == 1)
    {  
      if (x_coordinate == goal_x && y_coordinate == goal_y) // check if finishing position is reached (x,y) = (4,4)
      {
        uint8_t* congrats = "Congrats! You made it! \r\n \r\n";
        HAL_UART_Transmit(&huart1, congrats, strlen(congrats),100);
        // maze_counter = 0;  
        solving_mode = 0;      
      }
      else
      {
        scan_position(); // function that scans f,r,l distance and writes maze matrix, input = orientation
        turn_in_maze(); 
        
        char buffer[50];
        int pos_maze = sprintf(buffer,"Position: %i %i Orientation: %c" "   \r\n \r\n", x_coordinate, y_coordinate, orientation);
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, pos_maze, HAL_MAX_DELAY);
        

        drive_one_cell();

        maze_counter++;
      }     
    }
    else if (solving_mode_fast == 1)
    {

      if (x_coordinate == goal_x && y_coordinate == goal_y) // check if finishing position is reached (x,y) = (4,4)
      {
        uint8_t* congrats = "Congrats! You made it! \r\n \r\n";
        HAL_UART_Transmit(&huart1, congrats, strlen(congrats),100);
        // maze_counter = 0;  
        solving_mode_fast = 0;      
      }
      else
      {        
        turn_in_maze_fast(); 
        drive_one_cell();

        char buffer_fast[50];
        int pos_maze = sprintf(buffer_fast,"Position: %i %i Orientation: %c" "   \r\n \r\n", x_coordinate, y_coordinate, orientation);
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer_fast, pos_maze, HAL_MAX_DELAY);
        maze_counter_fast++;
      } 

    }
    
    






    
   
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 47;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 47;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TRIG_RIGHT_GPIO_Port, TRIG_RIGHT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MOTOR_RIGHT_4_Pin|MOTOR_RIGHT_3_Pin|MOTOR_RIGHT_2_Pin|MOTOR_RIGHT_1_Pin
                          |TRIG_FRONT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MOTOR_LEFT_4_Pin|MOTOR_LEFT_3_Pin|MOTOR_LEFT_2_Pin|MOTOR_LEFT_1_Pin
                          |TRIG_LEFT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ECHO_RIGHT_Pin */
  GPIO_InitStruct.Pin = ECHO_RIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ECHO_RIGHT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TRIG_RIGHT_Pin */
  GPIO_InitStruct.Pin = TRIG_RIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TRIG_RIGHT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR_RIGHT_4_Pin MOTOR_RIGHT_3_Pin MOTOR_RIGHT_2_Pin MOTOR_RIGHT_1_Pin
                           TRIG_FRONT_Pin */
  GPIO_InitStruct.Pin = MOTOR_RIGHT_4_Pin|MOTOR_RIGHT_3_Pin|MOTOR_RIGHT_2_Pin|MOTOR_RIGHT_1_Pin
                          |TRIG_FRONT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : ECHO_FRONT_Pin */
  GPIO_InitStruct.Pin = ECHO_FRONT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ECHO_FRONT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR_LEFT_4_Pin MOTOR_LEFT_3_Pin MOTOR_LEFT_2_Pin MOTOR_LEFT_1_Pin
                           TRIG_LEFT_Pin */
  GPIO_InitStruct.Pin = MOTOR_LEFT_4_Pin|MOTOR_LEFT_3_Pin|MOTOR_LEFT_2_Pin|MOTOR_LEFT_1_Pin
                          |TRIG_LEFT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ECHO_LEFT_Pin */
  GPIO_InitStruct.Pin = ECHO_LEFT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ECHO_LEFT_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void usDelay(uint16_t uSec)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < uSec);  // wait for the counter to reach the us input in the parameter
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
  //HAL_UART_Transmit(&huart1, rxdata, sizeof(rxdata), 100);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
