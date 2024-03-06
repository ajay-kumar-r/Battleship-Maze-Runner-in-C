#ifndef MAZERUNNER_H
#define MAZERUNNER_H
#include "mazerunner.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printMaze(Maze *maze);
void movePlayer(Maze *maze, char move);
void level1(Maze *maze);
void level2(Maze *maze);
void level3(Maze *maze);

#endif
