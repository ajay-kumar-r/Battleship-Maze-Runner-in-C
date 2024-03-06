#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 10
#define COLS 12
#define ROWS 10
#define COLS 12
typedef struct
{
    int maze[ROWS][COLS];
    int playerRow;
    int playerCol;
    bool gameOver;
    int hits;
} Maze;

void printMaze(Maze *maze)
{
    printf("\n");
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (i == maze->playerRow && j == maze->playerCol)
            {
                printf("P ");
            }
            else
            {
                switch (maze->maze[i][j])
                {
                case 0:
                    printf("# ");
                    break;
                case 1:
                    printf(". ");
                    break;
                case 5:
                    printf("E ");
                    break;
                }
            }
        }
        printf("\n");
    }
}

void movePlayer(Maze *maze, char move)
{
    int newRow = maze->playerRow;
    int newCol = maze->playerCol;

    switch (move)
    {
    case 'w':
        newRow -= 1;
        break;
    case 's':
        newRow += 1;
        break;
    case 'a':
        newCol -= 1;
        break;
    case 'd':
        newCol += 1;
        break;
    default:
        printf("Invalid move!\n");
        return;
    }

    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS || maze->maze[newRow][newCol] == 0)
    {
        printf("You hit a wall! Try another direction.\n");
        maze->hits++;
    }
    else
    {
        switch (maze->maze[newRow][newCol])
        {
        case 1:
            maze->playerRow = newRow;
            maze->playerCol = newCol;
            break;
        case 5:
            printf("Congratulations! You found the exit!\n");
            maze->gameOver = true;
            break;
        }
    }
}
void level1(Maze *maze)
{

    int firstLevel[ROWS][COLS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 0}};
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            maze->maze[i][j] = firstLevel[i][j];
        }
    }

    maze->playerRow = 1;
    maze->playerCol = 0;
    maze->gameOver = false;
    maze->hits = 0;

    printf("Welcome to the Maze Game!\n");
    printf("Level 1\n");

    while (!maze->gameOver)
    {
        printMaze(maze);

        printf("Enter your move (w/a/s/d): ");
        char move;
        scanf(" %c", &move);

        movePlayer(maze, move);
    }
    return;
}
void level2(Maze *maze)
{

    printf("\nLevel 2\n");

    int secondLevel[ROWS][COLS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            maze->maze[i][j] = secondLevel[i][j];
        }
    }

    maze->playerRow = 9;
    maze->playerCol = 8;
    maze->gameOver = false;
    maze->hits = 0;

    while (!maze->gameOver)
    {
        printMaze(maze);

        printf("Enter your move (w/a/s/d): ");
        char move;
        scanf(" %c", &move);

        movePlayer(maze, move);
    }
}
void level3(Maze *maze)
{
    printf("\nLevel 3\n");

    int thirdLevel[ROWS][COLS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            maze->maze[i][j] = thirdLevel[i][j];
        }
    }

    maze->playerRow = 9;
    maze->playerCol = 10;
    maze->gameOver = false;
    maze->hits = 0;

    while (!maze->gameOver)
    {
        printMaze(maze);

        printf("Enter your move (w/a/s/d): ");
        char move;
        scanf(" %c", &move);

        movePlayer(maze, move);
    }
}
