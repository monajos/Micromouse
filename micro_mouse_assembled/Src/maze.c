
#include "maze.h"

void initMaze()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            MazeCell *cell = malloc(sizeof(MazeCell));
            cell->wallNorth = 0;
            cell->wallEast = 0;
            cell->wallSouth = 0;
            cell->wallWest = 0;

            cell->explored = 0;
            maze[j][i] = cell;
        };
    }
};

void initPath()
{

    for (int j = 0; j < 150; j++)
    {
        Pathstruct *myPath = malloc(sizeof(Pathstruct));
        myPath->x_pos = 0;
        myPath->y_pos = 0;
        myPath->direction = ' ';

        path[j] = myPath;
    };

};


void finalMaze()
{
    // MazeCell maze[7][7] = {
    // {{0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 1}},
    // {{1, 1, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 1}, {1, 1, 0, 1}, {0, 0, 1, 1}, {1, 0, 0, 1}},
    // {{1, 0, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {1, 0, 1, 0}, {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}},
    // {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 0, 0, 1}, {0, 1, 0, 0}, {0, 0, 1, 1}, {1, 1, 0, 1}, {0, 0, 1, 1}},
    // {{1, 1, 0, 0}, {0, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 0, 1, 0}, {1, 1, 0, 1}, {0, 0, 1, 1}},
    // {{0, 1, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}},
    // {{1, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 1, 0}}
    // };
    MazeCell maze[7][7] = {
    {{0,1,0,1,1}, {0,1,1,0,1}, {0,1,1,0,1}, {0,1,1,1,1}, {0,1,1,1,1}, {0,0,1,0,1}, {0,0,0,1,1}},
    {{1,1,0,1,1}, {0,1,1,0,1}, {0,0,1,0,1}, {1,0,0,1,1}, {1,1,0,1,1}, {0,0,1,1,1}, {1,0,0,1,1}},
    {{1,0,0,0,1}, {0,1,0,1,1}, {0,1,1,0,1}, {1,0,1,0,1}, {1,0,0,0,1}, {1,0,0,1,1}, {1,0,0,1,1}},
    {{0,1,0,1,1}, {1,0,1,0,1}, {0,0,0,1,1}, {0,1,0,0,1}, {0,0,1,1,1}, {1,1,0,1,1}, {0,0,1,1,1}},
    {{1,1,0,0,1}, {0,0,1,1,1}, {1,1,0,1,1}, {1,1,1,0,1}, {1,0,1,0,1}, {1,1,0,1,1}, {0,0,1,1,1}},
    {{0,1,0,1,1}, {1,0,1,0,1}, {1,0,1,1,1}, {0,1,1,0,1}, {0,1,1,0,1}, {1,0,1,0,1}, {1,0,0,1,1}},
    {{1,1,0,0,1}, {0,0,1,0,1}, {1,0,0,0,1}, {0,1,0,0,1}, {0,1,1,0,1}, {0,1,1,0,1}, {1,0,1,0,1}}
};

}


void printMaze(UART_HandleTypeDef huart1)
{
    char buffer[50];
    for (int i = 6; i >= 0; i--)
    {
        int l = 0;
        for (int j = 0; j < 7; j++)
        {
            if (maze[j][i]->wallWest == 1)
            {
                l += sprintf(buffer + l, "┃");
            }
            else
            {
                l += sprintf(buffer + l, " ");
            }
            if (maze[j][i]->wallNorth == 1 && maze[j][i]->wallSouth == 1)
            {
                l += sprintf(buffer + l, "═");
            }
            else if (maze[j][i]->wallNorth == 1)
            {
                l += sprintf(buffer + l, "▔");
            }
            else if (maze[j][i]->wallSouth == 1)
            {
                l += sprintf(buffer + l, "_");
            }
            else
            {
                // no walls North or South
                if (maze[j][i]->explored == 0)
                {
                    l += sprintf(buffer + l, "0");
                }
                else
                {
                    l += sprintf(buffer + l, " ");
                }
            }
            if (maze[j][i]->wallEast == 1)
            {
                l += sprintf(buffer + l, "┃");
            }
            else
            {
                l += sprintf(buffer + l, " ");
            }
        }
        sprintf(buffer + l, "\r\n");
        HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 200);
    }
}