#ifndef KASYNO_GRACZ_H
#define KASYNO_GRACZ_H

#include "Karta.h"

class Gracz {
protected:
    Karta *karty[10];
    int liczbaKart = 0;
public:
    Gracz() = default;
    ~Gracz();

    Karta* getKarty();
    void wezKarte(Karta *karta);
    short wartoscReki();

    void wyświetlKarty();
};

class Bot: public Gracz {
public:
    bool DecyzjaSpasowania();
};

#endif //KASYNO_GRACZ_H
