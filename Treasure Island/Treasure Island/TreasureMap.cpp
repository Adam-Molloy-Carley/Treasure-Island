#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  

#define TRAP     (1 << 0)
#define GOLD     (1 << 1)
#define GOLD_MASK 0xF0

void setPlayerNames(char player1[20], char player2[20]);
void setMaps(unsigned char ValueMap[6][6], unsigned char TreasureMap[6][6]);
void gameStart(char player1[], char player2[], unsigned char TreasureMap[6][6], unsigned char ValueMap[6][6],
int *p1Score, int *p2Score, int *p1Row, int *p1Col, int *p2Row, 
int *p2Col);

int main() {
    char player1[20] = "Player1";
    char player2[20] = "Player2";
    char password[] = "ahoy";
	char inputPassword[20];
    int menuOption;
    int menuSet = 1;
	int Player1Wins = 0;
	int Player2Wins = 0;
	int Player1Treasure = 0;
	int Player2Treasure = 0;
	int Player1Row, Player1Col;
	int Player2Row, Player2Col;

    srand(time(NULL));

    unsigned char TreasureMap[6][6] = {
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'}
    };

    unsigned char ValueMap[6][6];

	printf("Welcome to Treasure Island!\n");
	printf("Please enter the password to access the game: ");
	scanf("%19s", inputPassword);
    
    while (strcmp(inputPassword, password) != 0) {
        printf("Incorrect password! Try again! (Hint, whats a four letter greeting from a pirate?).\n");
        printf("Please enter the password to access the game: ");
        scanf("%19s", inputPassword);
	}

    while (menuSet == 1) {
        printf("\n=== Treasure Island ===\n");
		printf("Welcome to Treasure Island, %s and %s!\n", player1, player2);
        printf("1. Start the game!\n");
        printf("2. Set Player names!\n");
        printf("3. Check Win History!\n");
        printf("4. Help. \n");
        printf("5. Exit.\n");
        printf("Select an option: ");

        scanf("%d", &menuOption);

        if (menuOption == 1) {
            printf("Starting the game...\n\n");
			setMaps(ValueMap, TreasureMap); // generates the maps for the game, when play again is chosen at end of game, the maps will be regenerated for a new game
			gameStart(player1, player2, TreasureMap, ValueMap, &Player1Treasure, &Player2Treasure, &Player1Row, &Player1Col, &Player2Row, &Player2Col); // starts the game, and passes in all the necessary variables for the game to run, including player names, maps, scores, and player positions
            menuSet = 0;
        }
        else if (menuOption == 2) {
            printf("Setting player names...\n");
            setPlayerNames(player1, player2);
        }
        else if (menuOption == 3) {
            printf("Checking win history...\n");
        }
        else if (menuOption == 4) {
			printf("T = Trap, This removes 1 treasure from the player!\nG = Gold, This rewards the player with between 0 and 15 treasure! \n X = Hole, This cell has already been searched! \n . = Unsearched, This cell has not been searched yet! \n\n");
        }
        
        else if (menuOption == 5) {
            printf("Exiting the game...\n");
            break;
        }
        else {
            printf("Invalid option! Please select a valid option.\n");
        }
    }
	
    printf("Thank you for playing Treasure Island! Play again?\n 1.Yes\n 2.No ");
    
    scanf("%d", &menuOption);
     if (menuOption == 1) {
         main(); 
     }
     else {
         printf("Goodbye!\n");
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

void setMaps(unsigned char ValueMap[6][6], unsigned char TreasureMap[6][6])
{
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
           
            ValueMap[i][j] = rand() % 256; 
			TreasureMap[i][j] = '.';
        }
    }
}

void gameStart(char player1[], char player2[],unsigned char TreasureMap[6][6], unsigned char ValueMap[6][6], int* p1Score, int* p2Score, int* p1Row, int* p1Col, int* p2Row, int* p2Col)
{
    int targetRow = 0;
    int targetCol = 0;

    printf("==============================================\n");
    printf("=   This Island is Brimming with Treasure!   =\n");
    printf("==============================================\n");

    while (*p1Score < 50 && *p2Score < 50) {

        printf("\n = %ss Treasure: %d | %ss Treasure: %d =\n", player1, *p1Score, player2, *p2Score);

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                printf(" %c", TreasureMap[i][j]);
            }
            printf("\n");
        }

        printf("%s, enter row col: ", player1);
        scanf("%d %d", &targetRow, &targetCol);

        if (targetRow < 0 || targetRow >= 6 || targetCol < 0 || targetCol >= 6) {
            printf("Invalid move!\n");
        }
        else if (TreasureMap[targetRow][targetCol] == 'X') {
            printf("Already dug!\n");
        }
        else {
            unsigned char cell = ValueMap[targetRow][targetCol];

            if (cell & TRAP) {
                printf("Trap! -1 treasure\n");
                (*p1Score)--;
                TreasureMap[targetRow][targetCol] = 'T';
            }
            else if (cell & GOLD) {
                int gold = (cell & GOLD_MASK) >> 4;
                printf("Gold found: %d\n", gold);
                (*p1Score) += gold;
                TreasureMap[targetRow][targetCol] = 'G';
            }
            else {

                TreasureMap[targetRow][targetCol] = 'X';
            }
        }

        printf("%s, enter row col: ", player2);
        scanf("%d %d", &targetRow, &targetCol);

        if (targetRow < 0 || targetRow >= 6 || targetCol < 0 || targetCol >= 6) {
            printf("Invalid move!\n");
        }
        else if (TreasureMap[targetRow][targetCol] == 'X') {
            printf("Already dug!\n");
        }
        else {
            unsigned char cell = ValueMap[targetRow][targetCol];

            if (cell & TRAP) {
                printf("Trap! -1 treasure\n");
                (*p2Score)--;
                TreasureMap[targetRow][targetCol] = 'T';
            }
            else if (cell & GOLD) {
                int gold = (cell & GOLD_MASK) >> 4;
                printf("Gold found: %d\n", gold);
                (*p2Score) += gold;
                TreasureMap[targetRow][targetCol] = 'G';
            }
            else {
                TreasureMap[targetRow][targetCol] = 'X';
            }
        }
    }
    if (*p1Score >= 50)
        printf("%s wins!\n", player1);
    else
        printf("%s wins!\n", player2);
    return;
}
