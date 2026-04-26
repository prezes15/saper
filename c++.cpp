#include<iostream>
#include<cstdlib>
#include<ctime>
#include"plansza.h"
const int rozmiar = 10;
void usunPlansze(char **plansza);
void wyswietlPlansze(char **plansza);
void generujMiny(char **tabMiny);
void wykonajRuch(char **plansza, char **tabMiny);
int sprawdzPole(char **tabMiny, int x, int y);
void odkryj(char **tabMiny, char **plansza, int x, int y);
int main(){
    char **plansza = generujPlansze(rozmiar);
    char **miny = generujPlansze(rozmiar);
    generujMiny(miny);
    wykonajRuch(plansza, miny);
    usunPlansze(plansza, rozmiar);
    return 0;
}

void wyswietlPlansze(char **plansza){
    std::cout << "  0 1 2 3 4 5 6 7 8 9" << std::endl; 
    for (int i = 0; i < rozmiar; i++) {
        std::cout << i << " "; 
        for (int j = 0; j < rozmiar; j++) {
            std::cout << plansza[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void generujMiny(char **tabMiny){
    srand(time(NULL));
    int podstawione = 0;
    while(podstawione < 10){
        int losowana1 = rand() % 10;
        int losowana2 = rand() % 10;
        if(*(*(tabMiny + losowana1) + losowana2) == '.'){
            *(*(tabMiny + losowana1) + losowana2) = '*';
            podstawione++; 
        }
    }
}
void wykonajRuch(char **plansza, char **tabMiny){
    int x, y;
    while(true){
        std::cout << "podaj pole np 1 2: ";
        std::cin >> x >> y;
        if(plansza[x][y] != '.'){
            std::cout << "to pole jest odkryte" << std::endl;
            continue;
        }
        if(tabMiny[x][y] == '*'){
            std::cout << "koniec gry" << std::endl;
            std::cout << "\n";
            wyswietlPlansze(tabMiny);
            break;
        }
        
        odkryj(tabMiny, plansza, x, y);
       
        wyswietlPlansze(plansza);
    }

}
int sprawdzPole(char **tabMiny, int x, int y){
    int licznik = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            int sprawdzX = x + i;
            int sprawdzY = y + j;

            if(sprawdzX >= 0 && sprawdzX < rozmiar && sprawdzY >= 0 && sprawdzY < rozmiar){
                if(tabMiny[sprawdzX][sprawdzY] == '*'){
                    licznik++;
                }
            }
        }
    }
    return licznik;
}
void odkryj(char **tabMiny, char **plansza, int x, int y) {
    
    if(x < 0 || x >= rozmiar || y < 0 || y >= rozmiar){
        return;
    }

    if(plansza[x][y] != '.'){
        return;
    }

    int minyWokol = sprawdzPole(tabMiny, x, y);
    plansza[x][y] = static_cast<char>(minyWokol + '0');

    if (minyWokol == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue; // Pomiń samego siebie
                odkryj(tabMiny, plansza, x + i, y + j);
            }
        }
    }
}