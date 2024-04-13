#include "Gracz.h"
#include <ctime>
#include <iostream>

Gracz::~Gracz(){
    delete[] karty;
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

void Gracz::wyświetlKarty(){
    for(int i = 0; i < liczbaKart; i++){
        karty[i]->wypisz();
    };
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