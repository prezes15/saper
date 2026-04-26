#include <iostream>
#include "display.h"

void displayBoard(char **board, int size) {
    std::cout << "  0 1 2 3 4 5 6 7 8 9" << std::endl; 
    for (int i = 0; i < size; i++) {
        std::cout << i << " "; 
        for (int j = 0; j < size; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}