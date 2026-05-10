
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <limits>
#include"board.h" 
#include"display.h"

const int BOARD_SIZE = 10;

void generateMines(char **mineTable);
void performMove(char **board, char **mineTable);
int checkField(char **mineTable, int x, int y);
void reveal(char **mineTable, char **board, int x, int y);
bool checkWin(char**board);
int main() {
    char choice;
    do {
        char **board = createBoard(BOARD_SIZE);
        char **mines = createBoard(BOARD_SIZE);
        generateMines(mines);
        performMove(board, mines);
        deleteBoard(board, BOARD_SIZE);


        std::cout << "Do you want play again (y/n)";
        std::cin >> choice;
        

    } while (choice == 'y');
    return 0;
}

void generateMines(char **mineTable) {
    srand(time(NULL));
    int placed = 0;
    while(placed < 10) {
        int randomX = rand() % 10;
        int randomY = rand() % 10;
        

        if(*(*(mineTable + randomX) + randomY) == '.') {
            *(*(mineTable + randomX) + randomY) = '*';
            placed++; 
        }
    }
}

void performMove(char **board, char **mineTable) {
    int x, y;
    char action;
    while(true) {
        std::cout << "Action: (d - discover the field f - flag the field): ";
        std::cin >> action;

        std::cout << "x: ";
        if (!(std::cin >> x)){ 
            continue; }
        
        
        if(x == 111){ 
            displayBoard(mineTable, BOARD_SIZE); 
            continue; 
        }

        std::cout << "y: ";
        if (!(std::cin >> y)){ 
            continue; 
        }

        if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            std::cout << "out of range" << std::endl;
            continue;
        }

   
        if (action == 'f' || action == 'F') {
            if (board[x][y] == '.') {
                board[x][y] = 'F'; 
            } else if (board[x][y] == 'F') {
                board[x][y] = '.'; 
            } else {
                std::cout << "You can't place a flag in an open field!" << std::endl;
            }
        } 
        else if (action == 'd' || action == 'd') {
            if (board[x][y] == 'F') {
                std::cout << "This field is flagged! Unflag it first." << std::endl;
                continue;
            }

            if (mineTable[x][y] == '*') {
                std::cout << "Game Over!" << std::endl;
                displayBoard(mineTable, BOARD_SIZE);
                break;
            }

            reveal(mineTable, board, x, y);
        }

        displayBoard(board, BOARD_SIZE);

        if(checkWin(board)) {
            std::cout << "You won" << std::endl;
            break;
        }
    }
}

int checkField(char **mineTable, int x, int y) {
    int counter = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int checkX = x + i;
            int checkY = y + j;

            if(checkX >= 0 && checkX < BOARD_SIZE && checkY >= 0 && checkY < BOARD_SIZE) {
                if(mineTable[checkX][checkY] == '*') {
                    counter++;
                }
            }
        }
    }
    return counter;
}

void reveal(char **mineTable, char **board, int x, int y) {
 
    if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return;
    }

    if(board[x][y] != '.') {
        return;
    }

    int minesAround = checkField(mineTable, x, y);
    board[x][y] = static_cast<char>(minesAround + '0');


    if (minesAround == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue; 
                reveal(mineTable, board, x + i, y + j);
            }
        }
    }
}
bool checkWin(char** board) {
    int unrevealed = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '.' || board[i][j] == 'F') {
                unrevealed++;
            }
        }
    }
    return unrevealed == 10;
}

#include<iostream>
#include<cstdlib>
#include<ctime>
#include <limits>
#include"board.h" 
#include"display.h"

const int BOARD_SIZE = 10;

// Generates mines on the hidden mine table
void generateMines(char **mineTable);

// Handles player actions and game loop
void performMove(char **board, char **mineTable);

// Counts mines around a specific field
int checkField(char **mineTable, int x, int y);

// Reveals fields recursively
void reveal(char **mineTable, char **board, int x, int y);

// Checks if the player has won
bool checkWin(char**board);

int main() {
    char choice;

    // Main game loop
    do {
        // Create visible board and hidden mine board
        char **board = createBoard(BOARD_SIZE);
        char **mines = createBoard(BOARD_SIZE);

        // Place mines randomly
        generateMines(mines);

        // Start gameplay
        performMove(board, mines);

        // Free allocated memory
        deleteBoard(board, BOARD_SIZE);

        // Ask player if they want to play again
        std::cout << "Do you want play again (y/n)";
        std::cin >> choice;

    } while (choice == 'y');

    return 0;
}

void generateMines(char **mineTable) {

    // Seed random number generator
    srand(time(NULL));

    int placed = 0;

    // Place exactly 10 mines
    while(placed < 10) {

        // Generate random coordinates
        int randomX = rand() % 10;
        int randomY = rand() % 10;

        // Place mine only if field is empty
        if(*(*(mineTable + randomX) + randomY) == '.') {
            *(*(mineTable + randomX) + randomY) = '*';
            placed++; 
        }
    }
}

void performMove(char **board, char **mineTable) {

    int x, y;
    char action;

    // Infinite game loop until player wins or loses
    while(true) {

        // Ask player for action
        std::cout << "Action: (d - discover the field f - flag the field): ";
        std::cin >> action;

        // Get X coordinate
        std::cout << "x: ";

        // Handle invalid input
        if (!(std::cin >> x)){ 
            continue; 
        }

        // Debug option to reveal mine table
        if(x == 111){ 
            displayBoard(mineTable, BOARD_SIZE); 
            continue; 
        }

        // Get Y coordinate
        std::cout << "y: ";

        // Handle invalid input
        if (!(std::cin >> y)){ 
            continue; 
        }

        // Validate coordinates
        if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            std::cout << "out of range" << std::endl;
            continue;
        }

        // Handle flag action
        if (action == 'f' || action == 'F') {

            // Place flag on unopened field
            if (board[x][y] == '.') {
                board[x][y] = 'F'; 
            } 

            // Remove existing flag
            else if (board[x][y] == 'F') {
                board[x][y] = '.'; 
            } 

            // Prevent flagging revealed fields
            else {
                std::cout << "You can't place a flag in an open field!" << std::endl;
            }
        } 
        
        // Handle discover action
        else if (action == 'd' || action == 'd') {

            // Prevent opening flagged fields
            if (board[x][y] == 'F') {
                std::cout << "This field is flagged! Unflag it first." << std::endl;
                continue;
            }

            // Check if player clicked a mine
            if (mineTable[x][y] == '*') {
                std::cout << "Game Over!" << std::endl;

                // Reveal all mines
                displayBoard(mineTable, BOARD_SIZE);
                break;
            }

            // Reveal selected field
            reveal(mineTable, board, x, y);
        }

        // Display current board state
        displayBoard(board, BOARD_SIZE);

        // Check win condition
        if(checkWin(board)) {
            std::cout << "You won" << std::endl;
            break;
        }
    }
}

int checkField(char **mineTable, int x, int y) {

    int counter = 0;

    // Check all surrounding fields
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {

            int checkX = x + i;
            int checkY = y + j;

            // Make sure coordinates are inside board
            if(checkX >= 0 && checkX < BOARD_SIZE && checkY >= 0 && checkY < BOARD_SIZE) {

                // Count nearby mines
                if(mineTable[checkX][checkY] == '*') {
                    counter++;
                }
            }
        }
    }

    return counter;
}

void reveal(char **mineTable, char **board, int x, int y) {

    // Stop if coordinates are outside board
    if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return;
    }

    // Stop if field is already revealed
    if(board[x][y] != '.') {
        return;
    }

    // Count nearby mines
    int minesAround = checkField(mineTable, x, y);

    // Convert number to character and display it
    board[x][y] = static_cast<char>(minesAround + '0');

    // If there are no nearby mines, reveal neighboring fields
    if (minesAround == 0) {

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {

                // Skip current field
                if (i == 0 && j == 0) continue; 

                // Recursive reveal
                reveal(mineTable, board, x + i, y + j);
            }
        }
    }
}

bool checkWin(char** board) {

    int unrevealed = 0;

    // Count unrevealed and flagged fields
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {

            if (board[i][j] == '.' || board[i][j] == 'F') {
                unrevealed++;
            }
        }
    }

    // Player wins when only mines remain hidden
    return unrevealed == 10;
}

