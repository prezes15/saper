#include <iostream>
void wyswietlPlansze(char **plansza, int rozmiar){
    std::cout << "  0 1 2 3 4 5 6 7 8 9" << std::endl; 
    for (int i = 0; i < rozmiar; i++) {
        std::cout << i << " "; 
        for (int j = 0; j < rozmiar; j++) {
            std::cout << plansza[i][j] << " ";
        }
        std::cout << std::endl;
    }
}