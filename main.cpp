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