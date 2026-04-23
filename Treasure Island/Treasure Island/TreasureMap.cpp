#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  

void setPlayerNames(char player1[20], char player2[20]);
void gameStart(char player1[], char player2[], char TreasureMap[6][6],
    int *p1Score, int *p2Score, int *p1Row, int *p1Col, int *p2Row, 
    int *p2Col);

int main() {
    char player1[20] = "Player1";
    char player2[20] = "Player2";
    int menuOption;
    int menuSet = 1;
	int Player1Wins = 0;
	int Player2Wins = 0;
	int Player1Treasure = 0;
	int Player2Treasure = 0;
	int Player1Row, Player1Col;
	int Player2Row, Player2Col;

    srand(time(NULL));

    char TreasureMap[6][6] = {
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'}
    };

    while (menuSet) {
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
            printf("Starting the game...\n\n");
			gameStart(player1, player2, TreasureMap, &Player1Treasure, &Player2Treasure, &Player1Row, &Player1Col, &Player2Row, &Player2Col);
            menuSet = 0;
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

void gameStart(char player1[], char player2[], char TreasureMap[6][6], int *p1Score, int *p2Score, int *p1Row, int *p1Col, int *p2Row, int *p2Col)
{
    int targetRow = 0;
    int targetCol = 0;

        printf("==============================================\n");
        printf("=   This Island is Brimming with Treasure!   =\n");
        printf("=   See Who can dig up the most treasure!    =\n");
        printf("==============================================\n");
    while (*p1Score < 50 && *p2Score < 50) {
        printf("==============================================\n");
        printf("= -%s's treasure-", player1);
        printf("= -%s's treasure- =\n", player2);
        printf("==============================================\n\n");
		printf("%s, enter the row and column to dig (0-5): ", player1);
		scanf("%d %d", &targetRow, &targetCol);
		
          if (targetRow >= 0 && targetCol < 6 && targetCol >= 0 && targetRow < 6) {
            *p1Row = targetRow;
            *p1Col = targetCol;
        }
        else {
            printf("Invalid move!\n");
        }
        
        printf("%s, enter the row and column to dig (0-5): ", player2);
		scanf("%d %d", targetRow, targetCol);

        if (targetRow >= 0 && targetCol < 6 && targetCol >= 0 && targetRow < 6) {
            *p2Row = targetRow;
            *p2Col = targetCol;
        }
        else {
            printf("Invalid move!\n");
        }
           
        TreasureMap[*p1Row][*p1Col] = 'X';
        TreasureMap[*p2Row][*p2Col] = 'X';
        
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                printf(" %c ", TreasureMap[i][j]);
            }
            printf("\n");
        }
            
    }
}