#include <iostream>
#include <windows.h>
#include "display.h"

void displayBoard(char **board, int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "\n  "; 

    SetConsoleTextAttribute(hConsole, 12); 
    for (int k = 0; k < size; k++) {
        std::cout << k << " ";
    }
    SetConsoleTextAttribute(hConsole, 7); 
    std::cout << "\n";

    for (int i = 0; i < size; i++) {
        SetConsoleTextAttribute(hConsole, 12); 
        std::cout << i << " ";
        SetConsoleTextAttribute(hConsole, 7); 

        for (int j = 0; j < size; j++) {
            if (board[i][j] == 'F') {
                SetConsoleTextAttribute(hConsole, 14); 
                std::cout << board[i][j] << " ";
                SetConsoleTextAttribute(hConsole, 7); 
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n";
}