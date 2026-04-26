#include<iostream>
#include<cstdlib>
#include<ctime>
#include"board.h" 
#include"display.h"

const int BOARD_SIZE = 10;

void generateMines(char **mineTable);
void performMove(char **board, char **mineTable);
int checkField(char **mineTable, int x, int y);
void reveal(char **mineTable, char **board, int x, int y);

int main() {
    char **board = createBoard(BOARD_SIZE);
    char **mines = createBoard(BOARD_SIZE);
    
    generateMines(mines);
    performMove(board, mines);
    
    deleteBoard(board, BOARD_SIZE);
    return 0;
}

void generateMines(char **mineTable) {
    srand(static_cast<unsigned int>(time(NULL)));
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
    while(true) {
        std::cout << "Enter coordinates (e.g., 1 2): ";
        std::cin >> x >> y;


        if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            std::cout << "Coordinates out of bounds!" << std::endl;
            continue;
        }

        if(board[x][y] != '.') {
            std::cout << "This field is already revealed." << std::endl;
            continue;
        }

        if(mineTable[x][y] == '*') {
            std::cout << "Game Over!" << std::endl;
            std::cout << "\n";
            displayBoard(mineTable, BOARD_SIZE);
            break;
        }
        
        reveal(mineTable, board, x, y);
        displayBoard(board, BOARD_SIZE);
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