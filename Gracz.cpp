#include "Gracz.h"
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>

Gracz::~Gracz(){
    free(karty);
}

short Gracz::wartoscReki() {
    short suma = 0;
    for(short i = 0; i < liczbaKart; i++){
        suma += karty[i]->getWartosc();
    }
    return suma;
}

void Gracz::wezKarte(Karta *karta) {
    karty[liczbaKart++] = karta;
}

Karta *Gracz::getKarty() {
    return *karty;
}

void Gracz::ruchGracza(Kasyno* kasyno) {
    std::string decyzja;
    std::cout << "Czy chcesz dobrać kartę (d) czy spasować (s)? ";

    do {
        std::cin >> decyzja;
        if(decyzja.length() > 1 || (decyzja != "d" && decyzja != "s")){
            std::cout << "Niepoprawna wartość, spróbuj ponownie: ";
            continue;
        }
        if (decyzja == "d") {
            wezKarte(kasyno->dajKarte());
            wyświetlKarty();
        } else if (decyzja == "s") {
            status = SPASOWANY;
        }
    } while (decyzja != "d" && decyzja != "s");

    if(wartoscReki() >= 21){
        status = SPASOWANY;
        std::cout << "Wartość ręki przekroczyła 21 \n";
        return;
    }
}

const char* kolory[] = { "\u2660", "\u2663", "\u2665", "\u2666" };

void Gracz::wyświetlKarty(bool dodajEnter){
    // Zmieniamy wartości na symbole kolorów
    for(int i = 0; i < liczbaKart; i++){
        std::cout << karty[i]->getFigura() << kolory[karty[i]->getKolor() - 3] << " ";
    };
    if(dodajEnter) {
        std::cout << "\n";
    }
}

std::ostream &Gracz::wyświetlKarty(std::ostream &o, bool dodajEnter){
    std::stringstream ss("");
    for(int i = 0; i < liczbaKart; i++){
        ss << karty[i]->getFigura() << kolory[karty[i]->getKolor() - 3] << " ";
    };
    if(dodajEnter) {
        ss << "\n";
    }

    return o << ss.str();
}

/* Strefa bota */
bool Bot::DecyzjaSpasowania() {
    if (wartoscReki() >= 21) {
        return true;
    }
    if (liczbaKart >= 10) {
        return true;
    }
    // Im większa wartość ręki, tym większa szansa na spasowanie
    // losowanko liczby z przedziału 0-1 i mnożenie przez 21 jak wartość ręki jest większa to spasuj
    srand(time(NULL));
    double random = (double) rand() / RAND_MAX;
    if (wartoscReki() <= random * 21) {
        return true;
    }

    return false;
}