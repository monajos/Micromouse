#include "stm32f0xx.h"
#include "main.h"
// #include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_buffer();
void scan_position();
void turn_in_maze();
void turn_in_maze_fast();
void drive_one_cell();