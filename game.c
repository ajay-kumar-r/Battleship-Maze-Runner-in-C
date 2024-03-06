#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battleship.h"
#include "mazzerunner.h"

typedef struct Player
{
    char name[20];
    char type[20];
    float score;
    struct Player *next;
} Player;

void displayMenu()
{
    printf("\nSelect a game to play:\n");
    printf("1. Battleship\n");
    printf("2. Maze Runner\n");
    printf("Enter your choice: ");
}
Player *findPlayerWithType(Player *head, const char *name, const char *type)
{
    Player *current = head;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0 && strcmp(current->type, type) == 0)
        {
            return current; // Player found
        }

        current = current->next;
    }

    return NULL; // Player not found
}

void insertPlayer(Player **head, const char *name, int score, char *t)
{
    // Check if the player already exists in the list
    Player *existingPlayer = findPlayerWithType(*head, name, t);

    // If the player exists and the new score is not higher, do nothing
    if (existingPlayer != NULL && score <= existingPlayer->score)
    {
        return;
    }

    // Allocate memory for the new player
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if (newPlayer == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Set the values for the new player
    strcpy(newPlayer->name, name);
    newPlayer->score = score;
    strcpy(newPlayer->type, t);
    newPlayer->next = NULL;

    // If the player already exists, update the score
    if (existingPlayer != NULL)
    {
        existingPlayer->score = score;
        printf("Updated score for player %s.\n", name);
        free(newPlayer); // Free the allocated memory as the player already exists
        return;
    }

    // Insert in descending order of score
    if (*head == NULL || score > (*head)->score)
    {
        newPlayer->next = *head;
        *head = newPlayer;
    }
    else
    {
        Player *current = *head;
        while (current->next != NULL && score <= current->next->score)
        {
            current = current->next;
        }

        newPlayer->next = current->next;
        current->next = newPlayer;
    }
}

void displayLeaderboard(Player *head)
{
    printf("\nLeaderboard:\n");
    printf("\nName\tScore[%%]\tGame\n");
    printf("--------------------------------\n\n");
    while (head != NULL)
    {
        printf("%s\t%0.2f \t\t%s\n\n", head->name, head->score, head->type);
        head = head->next;
    }
}
int main()
{
    int choice;
    Player *leaderboard = NULL;

    do
    {
        int i;
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {

            GameBoard playerBoard;
            initializeGameBoard(&playerBoard);

            printf("\nWelcome to Battleship!!\nThis is a console-based game.\n\nFew Infos:\n1. There will be 6 boats, each of size 4, that will be placed randomly across a 6x6 coordinate plane.\n");

            printf("2. You should randomly guess and enter a coordinate.\n3. If it hits, it will be denoted by an 'x'.\n4. You will be given a maximum of 7 wrong guesses\nThe game will end only when all boats are sunk or when you miss all your chances.\n\nThe winner will be decided based on who sank the last boat!\nAll the best!!!\n");

            placeBoatsRandom(&playerBoard);

            printGameBoard(&playerBoard);

            float score = playLimitedTries(&playerBoard);

            char playerName[20];

            printf("\nEnter your name: ");
            scanf("%s", playerName);

            insertPlayer(&leaderboard, playerName, score, "Battle Ship");

            break;
        }

        case 2:
        {

            float score = 0;
            Maze *maze = (Maze *)malloc(sizeof(Maze));
            int yes;
            level1(maze);
            score += (100 - (maze->hits * 10)); // Calculate score for Level 1
            printf("\nDo You Want to Play Level 2 (1.Yes,2.No): ");
            scanf("%i", &yes);
            if (yes == 1)
            {
                level2(maze);
                score += (100 - (maze->hits * 10));
                yes = -1;
                printf("\nDo You Want to Play Level 3 (1.Yes,2.No): ");
                scanf("%i", &yes);
                if (yes == 1)
                {
                    level3(maze);
                    score += (100 - (maze->hits * 10)); // Calculate score for Level 3
                    printf("\nCongratulations! You've completed all three levels!\n\n");
                    printf("Your total score: %0.2f%%\n", score / 3);
                    char playerName[20];
                    printf("\nEnter your name: ");
                    scanf("%s", playerName);

                    insertPlayer(&leaderboard, playerName, score / 3, "Maze Runner");
                }
                else
                {
                    printf("\nCongratulations! You've completed  two levels!\n\n");
                    printf("Your total score: %0.2f%%\n", score / 2);
                    char playerName[20];
                    printf("\nEnter your name: ");
                    scanf("%s", playerName);
                    insertPlayer(&leaderboard, playerName, score / 2, "Maze Runner");
                }
            }
            else
            {
                printf("Congratulations! You've completed level 1!\n\n");
                printf("Your total score: %0.2f%%\n\n", score);
                char playerName[20];
                printf("\nEnter your name: ");
                scanf("%s", playerName);
                insertPlayer(&leaderboard, playerName, score, "Maze Runner");
            }

            free(maze);
            break;
        }
        case 0:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
        printf("\nEnter 1 to start a new game: ");
        scanf("%d", &i);
        choice = (i == 1) ? 1 : 0;

    } while (choice != 0);

    displayLeaderboard(leaderboard);
    return 0;
}
