#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <cctype>
#include <memory>
#include <fstream>
#include <errno.h>
#include <exception>
#include <ctime>
#include <cstdlib>
const int rozmiar = 10;
void usunPlansze(char **plansza);
void wyswietlPlansze(char **plansza);
char** generujPlansze();
void generujMiny(char **tabMiny);
void wykonajRuch(char **plansza, char **tabMiny);
int sprawdzPole(char **tabMiny, int x, int y);
void odkryj(char **tabMiny, char **plansza, int x, int y);
int main(){
    char **plansza = generujPlansze();
    char **miny = generujPlansze();
    generujMiny(miny);
    wykonajRuch(plansza, miny);
    usunPlansze(plansza);
    return 0;
}
char** generujPlansze(){
    char ** tab = new char*[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        *(tab + i) = new char[rozmiar];
        for(int j = 0; j < rozmiar; j++){
            *(*(tab + i) + j) = '.';
        }
    }
    return tab;
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
void usunPlansze(char **plansza){
    for(int i = 0; i < rozmiar; i++){
        delete[] *(plansza + i);
    }
    delete[] plansza;
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
        
        plansza[x][y] = static_cast<char>(sprawdzPole(tabMiny, x, y) + '0');
       
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
