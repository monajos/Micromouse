#include "main.h"
#include "distance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include "functions.h"

extern UART_HandleTypeDef huart1;


void clear_buffer()
{
    // Disable the UART DMA receive stream
    HAL_UART_DMAStop(&huart1);

    // Clear the receive buffer by filling it with zeroes
    memset(rxdata, 0, sizeof(rxdata));

    // Restart the UART DMA receive stream
    HAL_UART_Receive_DMA(&huart1, rxdata, sizeof(rxdata));
}

void scan_position()
{
    // function with orientation as input and no output
    // scans with all 3 sensors and converts front,left & right to north,west,east,south and fills the maze matrix at the (x,y) position
    // using the global variables x_coordinate and y_coordinate

    uint sum_mz_f = 0;
    uint sum_mz_r = 0;
    uint sum_mz_l = 0;
    int cnt_mz;

    for (cnt_mz=0; cnt_mz < 20; cnt_mz++)
    {
        sum_mz_f = sum_mz_f + calc_distance_f();
        sum_mz_l = sum_mz_l + calc_distance_l();
        sum_mz_r = sum_mz_r + calc_distance_r(); 
        
        HAL_Delay(1);
    }

    dis_mz_f = sum_mz_f/20;
    dis_mz_r = sum_mz_r/20;
    dis_mz_l = sum_mz_l/20; 
    
    if (dis_mz_f <= 8)
    {
        dis_mz_f = 1;
    }
    else
    {
        dis_mz_f = 0;
    }
    if (dis_mz_l <= 8)
    {
        dis_mz_l = 1;
    }
    else
    {
        dis_mz_l = 0;
    }
    if (dis_mz_r <= 8)
    {
        dis_mz_r = 1;
    }
    else
    {
        dis_mz_r = 0;
    }

    if (orientation == 'N')
    {
        maze[x_coordinate][y_coordinate]->wallNorth = dis_mz_f;
        maze[x_coordinate][y_coordinate]->wallEast = dis_mz_r;
        maze[x_coordinate][y_coordinate]->wallSouth = 0;
        maze[x_coordinate][y_coordinate]->wallWest = dis_mz_l;
        maze[x_coordinate][y_coordinate]->explored = 1;
    }
    else if (orientation == 'E')
    {
        maze[x_coordinate][y_coordinate]->wallNorth = dis_mz_l;
        maze[x_coordinate][y_coordinate]->wallEast = dis_mz_f;
        maze[x_coordinate][y_coordinate]->wallSouth = dis_mz_r;
        maze[x_coordinate][y_coordinate]->wallWest = 0;
        maze[x_coordinate][y_coordinate]->explored = 1;
    }
    else if (orientation == 'S')
    {
        maze[x_coordinate][y_coordinate]->wallNorth = 0;
        maze[x_coordinate][y_coordinate]->wallEast = dis_mz_l;
        maze[x_coordinate][y_coordinate]->wallSouth = dis_mz_f;
        maze[x_coordinate][y_coordinate]->wallWest = dis_mz_r;
        maze[x_coordinate][y_coordinate]->explored = 1;
    }
    else if (orientation == 'W')
    {
        maze[x_coordinate][y_coordinate]->wallNorth = dis_mz_r;
        maze[x_coordinate][y_coordinate]->wallEast = 0;
        maze[x_coordinate][y_coordinate]->wallSouth = dis_mz_l;
        maze[x_coordinate][y_coordinate]->wallWest = dis_mz_f;
        maze[x_coordinate][y_coordinate]->explored = 1;
    }
    
}


void turn_in_maze()
{
    
    if (dis_mz_r == 0)
    {
        turn_mode = 1; 
        mv_rt_deg = 90;
        mv_rt_right = -30;
        mv_rt_left = 30;

        while (k_turn <  mv_rt_deg*19)
        {
            // do nothing
            // just wait until turned
            if (k_turn == 0 &&  mv_rt_deg == 0)
            {
                break;
            } 
        }
        if (k_turn >=  mv_rt_deg*19)
        {
            k_turn = 0;
            mv_rt_deg = 0;
        }
        

        if (orientation == 'N')
        {
            orientation = 'E';
        }
        else if (orientation == 'E')
        {
           orientation = 'S';
        }
        else if (orientation == 'S')
        {
            orientation = 'W';
        }
        else if (orientation == 'W')
        {
            orientation = 'N';
        }        
    }
    else if (dis_mz_f == 0)
    {
        // do nothing 
        // orientation stays the same
    }
    else if (dis_mz_f == 1 && dis_mz_r == 1 && dis_mz_l == 0)
    {
        turn_mode = 1; 
        mv_rt_deg = 90;
        mv_rt_right = 30;
        mv_rt_left = -30;

        while (k_turn <  mv_rt_deg*19)
        {
            // do nothing
            // just wait until turned
            if (k_turn == 0 &&  mv_rt_deg == 0)
            {
                break;
            } 
        }
        if (k_turn >=  mv_rt_deg*19)
        {
            k_turn = 0;
            mv_rt_deg = 0;
        }

        if (orientation == 'N')
        {
            orientation = 'W';
        }
        else if (orientation == 'E')
        {
           orientation = 'N';
        }
        else if (orientation == 'S')
        {
            orientation = 'E';
        }
        else if (orientation == 'W')
        {
            orientation = 'S';
        } 
    }
    else if (dis_mz_f == 1 && dis_mz_r == 1 && dis_mz_l == 1)
    {
        turn_mode = 1; 
        mv_rt_deg = 180;
        mv_rt_right = -30;
        mv_rt_left = 30;

        while (k_turn <  mv_rt_deg*19)
        {
            // do nothing
            // just wait until turned
            if (k_turn == 0 &&  mv_rt_deg == 0)
            {
                break;
            }            
        }
        if (k_turn >=  mv_rt_deg*19)
        {
            k_turn = 0;
            mv_rt_deg = 0;
        }

        if (orientation == 'N')
        {
            orientation = 'S';
        }
        else if (orientation == 'E')
        {
           orientation = 'W';
        }
        else if (orientation == 'S')
        {
            orientation = 'N';
        }
        else if (orientation == 'W')
        {
            orientation = 'E';
        }
    }       
}



void turn_in_maze_fast()
{
  if (orientation == shortest_way_direction[maze_counter_fast])
  {
    // do nothing
  }
   else if (orientation == 'N' && shortest_way_direction[maze_counter_fast]== 'E' || 
            orientation == 'E' && shortest_way_direction[maze_counter_fast]== 'S' ||
            orientation == 'S' && shortest_way_direction[maze_counter_fast]== 'W' ||
            orientation == 'W' && shortest_way_direction[maze_counter_fast]== 'N') // rechts drehen
  {
    turn_mode = 1; 
    mv_rt_deg = 90;
    mv_rt_right = -30;
    mv_rt_left = 30;

    while (k_turn <  mv_rt_deg*19)
    {
        // do nothing
        // just wait until turned
        if (k_turn == 0 &&  mv_rt_deg == 0)
        {
            break;
        } 
    }
    if (k_turn >=  mv_rt_deg*19)
    {
        k_turn = 0;
        mv_rt_deg = 0;
    }
  }
   else if (orientation == 'N' && shortest_way_direction[maze_counter_fast]== 'W' || 
            orientation == 'E' && shortest_way_direction[maze_counter_fast]== 'N' ||
            orientation == 'S' && shortest_way_direction[maze_counter_fast]== 'E' ||
            orientation == 'W' && shortest_way_direction[maze_counter_fast]== 'S')  // links drehen
  {
    turn_mode = 1; 
    mv_rt_deg = 90;
    mv_rt_right = 30;
    mv_rt_left = -30;

    while (k_turn <  mv_rt_deg*19)
    {
        // do nothing
        // just wait until turned
        if (k_turn == 0 &&  mv_rt_deg == 0)
        {
            break;
        } 
    }
    if (k_turn >=  mv_rt_deg*19)
    {
        k_turn = 0;
        mv_rt_deg = 0;
    }
  }
  orientation = shortest_way_direction[maze_counter_fast];    
}




void drive_one_cell()
{
    turn_mode = 0;
    mv_distance = 150;

    while (k_step < abs(mv_distance)*21)
    {
        // do nothing
        // wait until finished driving
        if (k_step == 0 && mv_distance == 0)
        {
            break;
        }   
    }

    // measure distance front
    uint sum_mz_f2 = 0;
    int cnt_mz2;
    int dis_mz_f2;

    for (cnt_mz2=0; cnt_mz2 < 20; cnt_mz2++)
    {
        sum_mz_f2 = sum_mz_f2 + calc_distance_f();
        HAL_Delay(1);
    }
    dis_mz_f2 = sum_mz_f2/20;

    if (dis_mz_f2 > 10)
    {
        turn_mode = 0;
        mv_distance = 50;

        while (k_step < abs(mv_distance)*21)
        {
            // do nothing
            // wait until finished driving
            if (k_step == 0 && mv_distance == 0)
            {
                break;
            }   
        }
    }
    else if (10 >= dis_mz_f2 && dis_mz_f2 >= 7)
    {
        turn_mode = 0;
        mv_distance = 30;

        while (k_step < abs(mv_distance)*21)
        {
            // do nothing
            // wait until finished driving
            if (k_step == 0 && mv_distance == 0)
            {
                break;
            }   
        }
    }
    else if (7 > dis_mz_f2 && dis_mz_f2 >= 4)
    {
        turn_mode = 0;
        mv_distance = 20;

        while (k_step < abs(mv_distance)*21)
        {
            // do nothing
            // wait until finished driving
            if (k_step == 0 && mv_distance == 0)
            {
                break;
            }   
        }
    }
    else if (dis_mz_f2 < 4)
    {
        char buffer[30];
        int test = sprintf(buffer," Distanzz nach vorne: %i" "   \r\n \r\n", dis_mz_f2);
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, test, HAL_MAX_DELAY);
    }
    else
    {
        char buffer[30];
        int test = sprintf(buffer," Distanzz nach vorne: %i" "   \r\n \r\n", dis_mz_f2);
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, test, HAL_MAX_DELAY);
    }
    
    
    // save path
    if (solving_mode==1)
    {
        path[maze_counter]->direction = orientation;
        path[maze_counter]->x_pos = x_coordinate;
        path[maze_counter]->y_pos = y_coordinate;
    }
    
    // adjust position
    if (orientation == 'N')
    {
        y_coordinate++;
    }
    else if (orientation == 'E')
    {
        x_coordinate++;
    }
    else if (orientation == 'S')
    {
        y_coordinate--;
    }
    else if (orientation == 'W')
    {
        x_coordinate--;
    }    
}


