#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  

#define TRAP     (1 << 0) // Bitwise flags for the hidden map values, this reads the first bit to determine if a trap is present
#define GOLD     (1 << 1) // same as above but for gold, reads the second bit to determine if gold is present, then uses the GOLD_MASK to read the amount of gold found in the cell
#define GOLD_MASK 0xF0    //used to check the amount of gold found in a cell, this reads the last 4 bits of the value to determine how much gold is found

void setPlayerNames(char player1[20], char player2[20]); //function declarations for the functions used in the program
void setMaps(unsigned char ValueMap[6][6], unsigned char TreasureMap[6][6]);
void gameStart(char player1[], char player2[], unsigned char TreasureMap[6][6], unsigned char ValueMap[6][6],
int *p1Score, int *p2Score, int *p1Row, int *p1Col, int *p2Row, 
int *p2Col, int *Player1Wins, int *Player2Wins);

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
       
    srand(time(NULL)); //Seeds Rand() with time to ensure truly(ish) random values 

	unsigned char TreasureMap[6][6] = { //The outward facing map that the players see, this will be updated as the game goes on to show where traps, gold, searched and unsearched cells are
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'},
        {'.','.','.','.','.','.'}
    };

	unsigned char ValueMap[6][6]; // The hidden map that contains the actual values of the cells, this is what the game will reference to determine if a cell has a trap, gold, or is empty. This map is generated randomly at the start of each game and when play again is chosen

	printf("Welcome to Treasure Island!\n");
	printf("Please enter the password to access the game: "); 
	scanf("%19s", inputPassword);
    
    while (strcmp(inputPassword, password) != 0) {
        printf("Incorrect password! Try again! (Hint, whats a four letter greeting from a pirate?).\n");
        printf("Please enter the password to access the game: "); //Password checker
        scanf("%19s", inputPassword);
	}

    while (menuSet == 1) { //Menus system for a game like feel
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
			gameStart(player1, player2, TreasureMap, ValueMap, &Player1Treasure, &Player2Treasure, &Player1Row, &Player1Col, &Player2Row, &Player2Col, &Player1Wins, &Player2Wins); // starts the game, and passes in all the necessary variables for the game to run, including player names, maps, scores, and player positions
			Player1Treasure = 0; // resets player treasure for next game
            Player2Treasure = 0;
            menuSet = 0;
        }
        else if (menuOption == 2) {
            printf("\nSetting player names...\n"); //Sets persistent player names through repeat games until the program closes, then resets
            setPlayerNames(player1, player2);
        }
        else if (menuOption == 3) {
            printf("\nChecking win history...\n");
			printf("%s wins: %d\n", player1, Player1Wins); //Win tracker through the programs lifetime, resets on close
			printf("%s wins: %d\n", player2, Player2Wins);
        }
		else if (menuOption == 4) { //Helps menu to show the player what the symbols on the map mean
			printf("\nT = Trap, This removes 1 treasure from the player!\n G = Gold, This rewards the player with between 0 and 15 treasure! \n X = Hole, This cell has already been searched! \n . = Unsearched, This cell has not been searched yet! \n\n");
        }
        
        else if (menuOption == 5) {
            printf("Exiting the game...\n"); //Simple way to terminate prgram on startup
            break;
        }
        else {
			printf("Invalid option! Please select a valid option.\n"); //Ensure valid choice
        }
    }
	
    printf("Thank you for playing Treasure Island! Play again?\n 1.Yes\n 2.No "); //Repeat option on game end
    
    scanf("%d", &menuOption);
     if (menuOption == 1) {
         main(); 
     }
     else {
         printf("Goodbye!\n");
	 }
    return 0;
}

void setPlayerNames(char player1[20], char player2[20]) // function to set player names
{
    printf("Enter Player 1 name: ");
    scanf("%19s", player1);

    printf("Enter Player 2 name: ");
    scanf("%19s", player2);

    printf("\nPlayer 1: %s\n", player1);
    printf("\nPlayer 2: %s\n", player2);
}

void setMaps(unsigned char ValueMap[6][6], unsigned char TreasureMap[6][6]) //generates the hidden values for the map and resets the outward facing map
{
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
           
            ValueMap[i][j] = rand() % 256; 
			TreasureMap[i][j] = '.';
        }
    }
}

void gameStart(char player1[], char player2[],unsigned char TreasureMap[6][6], unsigned char ValueMap[6][6], int* p1Score, int* p2Score, int* p1Row, int* p1Col, int* p2Row, int* p2Col, int* Player1Wins, int* Player2Wins)
{ // Main function where the game basically runs. Heart of the Program
    int targetRow = 0;
	int targetCol = 0; // Variables to store player input for row and column and turn count for use in map generation after 36 turns, this is to ensure the game doesn't end in a stalemate if all cells are searched 
                        // without a player reaching 50 treasure. Basically softlock prevention.
	int turn = 0;

    printf("==============================================\n");
    printf("=   This Island is Brimming with Treasure!   =\n"); //Cute intro :3
    printf("==============================================\n");

    while (*p1Score < 50 && *p2Score < 50) {
        
        if (turn == 36) {
            printf("All cells have been searched!\n");
            printf("Regenerating maps\n"); // Mechanism to regenerate the map after 36 turns 
            setMaps(ValueMap, TreasureMap);
            turn = 0;
        }
        
        printf("\n = %ss Treasure: %d | %ss Treasure: %d =\n", player1, *p1Score, player2, *p2Score);

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                printf(" %c", TreasureMap[i][j]); //Map Display
            }
            printf("\n");
        }

        printf("  %s, Enter row and column: ", player1);
        printf("Row: ");
		scanf("%d", &targetRow); //Player input for row and column, same for Player 2
        printf("Column: ");
        scanf("%d", &targetCol);

        turn++;

        if (targetRow < 0 || targetRow >= 6 || targetCol < 0 || targetCol >= 6) {
            printf("Invalid move!\n"); //Ensured valid choice
        }
        else if (TreasureMap[targetRow][targetCol] == 'X') { 
            printf("Already dug!\n"); //Ensures Cells cant be plundered ad nauseum 
            turn--;
        }
        else {
			unsigned char cell = ValueMap[targetRow][targetCol]; // Gets the value of the cell from the hidden map to determine if its a trap, gold, or empty, where bitwise operators come into player

            if (cell & TRAP) {
                printf("Trap! -1 treasure\n");
				(*p1Score)--; //Reads the bit on the found value to determine if trap is set and applies the trap penalty to the player score, then updates the outward facing map to show a trap was found
                TreasureMap[targetRow][targetCol] = 'T';
            }
            else if (cell & GOLD) {
                int gold = (cell & GOLD_MASK) >> 4;
				printf("Gold found: %d\n", gold); //Reads the bits on the found value to determine if gold is set and how much gold is found, then applies the gold reward to the player score, then updates the outward facing map to show gold was found
                (*p1Score) += gold;
                TreasureMap[targetRow][targetCol] = 'G';
            }
            else {
				printf("Nothing found!\n");
                TreasureMap[targetRow][targetCol] = 'X'; //Tells you that your broke 
            }
        }

		printf("  %s, Enter row and column: ", player2); //Repeat of above code for Player 2, same mechanics apply just with different player score and name
        printf("Row: ");
        scanf("%d", &targetRow);
        printf("Column: ");
        scanf("%d", &targetCol);
       
        turn++;

        if (targetRow < 0 || targetRow >= 6 || targetCol < 0 || targetCol >= 6) {
            printf("Invalid move!\n");
        }
        else if (TreasureMap[targetRow][targetCol] == 'X' || TreasureMap[targetRow][targetCol] == 'T' || TreasureMap[targetRow][targetCol] == 'G') {
            printf("Already dug!\n");
            turn--;
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
				printf("Nothing found!\n");
                TreasureMap[targetRow][targetCol] = 'X';
            }
        }
    }
	if (*p1Score >= 50) { //player win condition check, updates win tracker and announces winner at end of game
		(*Player1Wins)++;
        printf("%s wins!\n", player1);
	}     
    else {
		(*Player2Wins)++;
        printf("%s wins!\n", player2);
    }      
    return;
}
