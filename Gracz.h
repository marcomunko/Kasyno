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

class Gracz{
protected:
    Kasyno *kasyno;
    Karta **karty;
    int liczbaKart = 0;
    StatusGracza status = W_TRAKCIE;
    std::string nazwa;
public:
    //**** ROZPOZNAIE GRZACZA ****
    //virtual = możliwość przesłonięcia danej funkcji przez funkcję pochodną
    //czyli bot przesłania Gracza
    //rozpoznaj Gracza od Bota
    virtual std::string tag() const {
        return "GRACZ";
    }

    //Gracz wie w jakim kasynie gra
    void UstawAdresKlassyGracz(Kasyno* _kasyno) {
        kasyno = _kasyno;
    }

    //**** USTAWIANIE NAZWY ****
    void wprowadzNazwe() {
        nazwa = Utils::stringUżytkownika("Wprowadź nazwę: ", 20);
    }

    std::string getNazwa() const {
        return nazwa;
    }

    virtual void ruchGracza(Kasyno* kasyno);


    //kostruktory
    Gracz(); //tymczasowy do tworzenia list
    Gracz(Kasyno* kasyno){
        karty = new Karta*[10];
        liczbaKart = 0;
        UstawAdresKlassyGracz(kasyno);
        status = W_TRAKCIE;
        wprowadzNazwe();
    };
    Gracz(const Gracz&) = delete;
    //operator =
    Gracz& operator=(const Gracz& g);
    //destruktory
    ~Gracz();

    Karta* getKarty();
    void wezKarte(Karta *karta);
    short wartoscReki();

    void wyświetlKarty(bool dodajEnter = true);
    // wyświetlanie kart (strumień wyjścia, czy dodać /n = zwykkle tak)
    std::ostream &wyświetlKarty(std::ostream &o, bool dodajEnter = true);

    StatusGracza getStatus(){
        return status;
    }
};
//################### STREFA BOTA ########################
enum Odwaga {
    RYZYKUJĄCY, NORMALNY, ZACHOWAWCZY
};

class Bot: public Gracz {
public:
    Bot(Odwaga odwaga, Kasyno* kasyno, std::string nazwa){
        this->nazwa = std::move(nazwa);
        //zamiast UstawAdresKlassyGracz tak teżdziała :))
        this->kasyno = kasyno;
        this->odwaga = odwaga;
    };
    //funkcja klasy pochodnej
    //rozpoznaj Gracza od Bota
    std::string tag() const override{
        return "BOT";
    }
    //funkcja klasy pochodnej
    void ruchGracza(Kasyno* kasyno) override;

    void DecyzjaSpasowania();
    Odwaga odwaga;
};

#endif //KASYNO_GRACZ_H
