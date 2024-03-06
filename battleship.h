#ifndef btlship

#include <stdio.h>
#include <stdlib.h>
#include "battleship.c"

void initializeGameBoard(GameBoard *playerBoard);
void printGameBoard(GameBoard *playerBoard);
int isValidBoatPlacement(GameBoard *playerBoard, int startRow, int startCol, int isVertical);
void placeBoatsRandom(GameBoard *playerBoard);
int isValidMove(GameBoard *playerBoard, Coordinate move);
int isHit(GameBoard *playerBoard, Coordinate move);
void markHit(GameBoard *playerBoard, Coordinate move);
int areAllBoatsSunk(GameBoard *playerBoard);
float calculateScore(int attempts, int hits);
float playLimitedTries(GameBoard *playerBoard);

#endif
