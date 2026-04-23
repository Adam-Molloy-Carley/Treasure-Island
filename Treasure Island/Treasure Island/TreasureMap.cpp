#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>   

void setPlayerNames(char player1[20], char player2[20]);

int main() {
    char player1[20] = "Player1";
    char player2[20] = "Player2";
    int menuOption;
	
    srand(time(NULL)); 

    int TreasureMap[6][6] = {
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'}
    };

    while (1) {
        printf("\n=== Treasure Island ===\n");
		printf("Welcome to Treasure Island, %s and %s!\n", player1, player2);
        printf("1. Start the game!\n");
        printf("2. Set Player names!\n");
        printf("3. View Map.\n");
        printf("4. Check Win History!\n");
        printf("5. Exit.\n");
        printf("Select an option: ");

        scanf("%d", &menuOption);

        if (menuOption == 1) {
            printf("Starting the game...\n");
        }
        else if (menuOption == 2) {
            printf("Setting player names...\n");
            setPlayerNames(player1, player2);
        }
        else if (menuOption == 3) {
            printf("Viewing map...\n");
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    printf("%c ", TreasureMap[i][j]);
                }
                printf("\n");
            }
        }
        else if (menuOption == 4) {
            printf("Checking win history...\n");
        }
        else if (menuOption == 5) {
            printf("Exiting the game...\n");
            break;
        }
        else {
            printf("Invalid option! Please select a valid option.\n");
        }
    }

    return 0;
}

void setPlayerNames(char player1[20], char player2[20])
{
    printf("Enter Player 1 name: ");
    scanf("%19s", player1);

    printf("Enter Player 2 name: ");
    scanf("%19s", player2);

    printf("Player 1: %s\n", player1);
    printf("Player 2: %s\n", player2);
}