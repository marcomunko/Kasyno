#ifndef KASYNO_KARTA_H
#define KASYNO_KARTA_H

#pragma once
#include <iostream>

class Karta {
private:
    char kolor;
    char figura;
    int wartosc;
public:
    Karta(int _kolor = 0, int _wartosc = 0);
    void setKolor(int _kolor);
    void setWartosc(int _wartosc);
    char getKolor() const { return kolor; }
    char getFigura() const { return figura; }
    int getWartosc() const { return wartosc; }
    void wypisz() const { std::cout << figura << kolor; }
};

class Talia {
private:
    Karta karty[52];
    short aktualnaKarta = 0;
public:
    Talia();

    void Tasuj();
    Karta* dajKarte();
};

#endif //KASYNO_KARTA_H
