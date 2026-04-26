#include "plansza.h"
char **generujPlansze(int rozmiar){
    
    char ** tab = new char*[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        *(tab + i) = new char[rozmiar];
        for(int j = 0; j < rozmiar; j++){
            *(*(tab + i) + j) = '.';
        }
    }
    return tab;
}
void usunPlansze(char **plansza, int rozmiar){
    for(int i = 0; i < rozmiar; i++){
        delete[] *(plansza + i);
    }
    delete[] plansza;
}