#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 6
#define NUM_BOATS 6
#define BOAT_SIZE 4
#define MAX_TRIES 7
typedef struct
{
    int row;
    int col;
} Coordinate;

typedef struct
{
    Coordinate start;
    Coordinate end;
} Boat;

typedef struct
{
    char symbol;
    int isHit;
} Cell;

typedef struct
{
    Cell board[BOARD_SIZE][BOARD_SIZE];
} GameBoard;

void initializeGameBoard(GameBoard *playerBoard)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            playerBoard->board[i][j].symbol = '.';
            playerBoard->board[i][j].isHit = 0;
        }
    }
}

void printGameBoard(GameBoard *playerBoard)
{
    printf("\nYour Battle Space:\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (playerBoard->board[i][j].isHit)
            {
                printf("%c ", playerBoard->board[i][j].symbol);
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int isValidBoatPlacement(GameBoard *playerBoard, int startRow, int startCol, int isVertical)
{
    for (int i = 0; i < BOAT_SIZE; i++)
    {
        if (isVertical && playerBoard->board[startRow + i][startCol].symbol != '.')
        {
            return 0; // Boat overlaps with another
        }
        else if (!isVertical && playerBoard->board[startRow][startCol + i].symbol != '.')
        {
            return 0; // Boat overlaps with another
        }
    }
    return 1; // Valid placement
}

void placeBoatsRandom(GameBoard *playerBoard)
{
    srand(time(NULL));

    for (int boatIndex = 0; boatIndex < NUM_BOATS; boatIndex++)
    {
        int isVertical = rand() % 2;
        int startRow, startCol;

        do
        {
            if (isVertical)
            {
                startRow = rand() % (BOARD_SIZE - BOAT_SIZE + 1);
                startCol = rand() % BOARD_SIZE;
            }
            else
            {
                startRow = rand() % BOARD_SIZE;
                startCol = rand() % (BOARD_SIZE - BOAT_SIZE + 1);
            }
        } while (!isValidBoatPlacement(playerBoard, startRow, startCol, isVertical));

        for (int i = 0; i < BOAT_SIZE; i++)
        {
            if (isVertical)
            {
                playerBoard->board[startRow + i][startCol].symbol = '<';
            }
            else
            {
                playerBoard->board[startRow][startCol + i].symbol = '<';
            }
        }
    }
}

int isValidMove(GameBoard *playerBoard, Coordinate move)
{
    return move.row > 0 && move.row <= BOARD_SIZE && move.col > 0 && move.col <= BOARD_SIZE &&
           !playerBoard->board[move.row - 1][move.col - 1].isHit;
}

int isHit(GameBoard *playerBoard, Coordinate move)
{
    return playerBoard->board[move.row - 1][move.col - 1].symbol == '<';
}

void markHit(GameBoard *playerBoard, Coordinate move)
{
    playerBoard->board[move.row - 1][move.col - 1].isHit = 1;
    playerBoard->board[move.row - 1][move.col - 1].symbol = 'x';
}

int areAllBoatsSunk(GameBoard *playerBoard)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (playerBoard->board[i][j].symbol == '<' && !playerBoard->board[i][j].isHit)
            {
                return 0;
            }
        }
    }
    return 1;
}

float calculateScore(int attempts, int hits)
{
    if (attempts > 0)
    {
        return ((double)hits / attempts) * 100.0;
    }
    else
    {
        return 0.0;
    }
}

float playLimitedTries(GameBoard *playerBoard)
{
    Coordinate move;
    int attempts = 0;
    int hits = 0;
    int missesLeft = MAX_TRIES;

    printf("\nLet the Battle Begin!\n");

    while (!areAllBoatsSunk(playerBoard) && missesLeft > 0)
    {
        printf("\nMisses Left: %d\n", missesLeft);
        printf("For Exit: Enter Row = -1 & Col = -1 \n");
        printf("Enter your guess (row and column, starting from 1): ");
        scanf("%d %d", &move.row, &move.col);
        if (move.row == -1 && move.col == -1)
        {
            printf("You Quit!");
            return 0.0;
        }
        if (!isValidMove(playerBoard, move))
        {
            printf("Invalid coordinate. Please enter a different coordinate.\n");
            continue;
        }

        attempts++;

        if (isHit(playerBoard, move))
        {
            printf("Hit at (%d, %d)!\n", move.row, move.col);
            markHit(playerBoard, move);
            hits++;
        }
        else
        {
            printf("Miss at (%d, %d)!\n", move.row, move.col);
            missesLeft--;
        }

        // Check if all boats are sunk after player's move
        if (areAllBoatsSunk(playerBoard))
        {
            double accuracy = calculateScore(attempts, hits);
            printf("Congratulations! You sank all the enemy boats in %d attempts. Your accuracy is: %.2f%%\n", attempts, accuracy);
            break;
        }

        // CPU's move
        Coordinate cpuMove;
        do
        {
            cpuMove.row = rand() % BOARD_SIZE + 1;
            cpuMove.col = rand() % BOARD_SIZE + 1;
        } while (!isValidMove(playerBoard, cpuMove)); // Ensure CPU doesn't repeat moves

        if (isHit(playerBoard, cpuMove))
        {
            printf("CPU hit at (%d, %d)!\n", cpuMove.row, cpuMove.col);
            markHit(playerBoard, cpuMove);
        }
        else
        {
            printf("CPU miss at (%d, %d)!\n", cpuMove.row, cpuMove.col);
        }

        printGameBoard(playerBoard);
    }

    if (!areAllBoatsSunk(playerBoard))
    {
        double accuracy = calculateScore(attempts, hits);
        printf("Game over. The CPU sank all your boats in %d attempts. Your accuracy is: %.2f%%. Better luck next time!\n", attempts, accuracy);
        return accuracy;
    }
}
