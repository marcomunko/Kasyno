#ifndef KASYNO_GRACZ_H
#define KASYNO_GRACZ_H

#include "Karta.h"
#include "Kasyno.h"
#include "Utils.h"
#include <string>
#include <iostream>


class Kasyno;

enum StatusGracza {
    SPASOWANY, W_TRAKCIE
};

class Gracz {
    Kasyno *kasyno;

protected:
    Karta *karty[10];
    int liczbaKart = 0;
    StatusGracza status = W_TRAKCIE;
public:
    const std::string tag = "GRACZ";
    std::string nazwa;

    void UstawAdresKlassyGracz(Kasyno* _kasyno) {
        kasyno = _kasyno;
    }

    void ruchGracza(Kasyno* kasyno);

    void wprowadzNazwe() {
        nazwa = Utils::stringUżytkownika("Wprowadź nazwę: ", 20);
    }

    std::string getNazwa() const {
        return nazwa;
    }

    Gracz() = default;
    ~Gracz();

    Karta* getKarty();
    void wezKarte(Karta *karta);
    short wartoscReki();

    void wyświetlKarty(bool dodajEnter = true);
    std::ostream &wyświetlKarty(std::ostream &o, bool dodajEnter = true);

    StatusGracza getStatus() {
        return status;
    }
};

class Bot: public Gracz {
public:
    const std::string tag = "BOT";
    bool DecyzjaSpasowania();
};

#endif //KASYNO_GRACZ_H
