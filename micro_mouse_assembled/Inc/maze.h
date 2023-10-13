#include "stm32f0xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    uint8_t wallNorth;
    uint8_t wallEast;
    uint8_t wallSouth;
    uint8_t wallWest;        
    uint8_t explored;
}MazeCell;

MazeCell *maze[7][7];

typedef struct
{
    char direction;
    uint8_t x_pos;
    uint8_t y_pos;
}Pathstruct;

Pathstruct *path[150];

void initMaze();
void initPath();
void printMaze();
void finalMaze();



