#include "board.h"

char **createBoard(int size) {
    char **table = new char*[size];
    for (int i = 0; i < size; i++) {
        *(table + i) = new char[size];
        for (int j = 0; j < size; j++) {
            // Setting default character to '.'
            *(*(table + i) + j) = '.';
        }
    }
    return table;
}

void deleteBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        delete[] *(board + i);
    }
    delete[] board;
}