#ifndef KASYNO_KASYNO_H
#define KASYNO_KASYNO_H

#include "Karta.h"
#include "Gracz.h"

class Gracz;

class Kasyno {
private:
    bool graTrwa;
    Karta karty[52];
    Gracz **gracze = nullptr;
    int liczbaGraczy;
    short aktualnaKarta;
    void DodajBota(short liczbaBota = 0);
    template<typename T, typename ...args>
    void DodajGracza(args &&... arg);
public:
    Kasyno();
    ~Kasyno();

    Kasyno(const Kasyno& k)= delete;
    Kasyno& operator=(const Kasyno& k)= delete;

    void Inicjuj();
    void graj();
    bool czy_Wygrana();
    void koniecGry();
    Karta* dajKarte();
    void restart();

    bool GraTrwa(){ return graTrwa; };
    std::ostream& print(std::ostream &out);
};


#endif //KASYNO_KASYNO_H
