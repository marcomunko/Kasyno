#include "Kasyno.h"

Kasyno::Kasyno() {
    graTrwa=true;
}

Kasyno::~Kasyno(){
    delete[] talia;
}

void Kasyno::Inicjuj(){
    talia = new Talia();
    talia->Tasuj();
}

Karta* Kasyno::dajKarte() {
    return talia->dajKarte();
}

void Kasyno::graj() {
    gracze = new Gracz[2];
    for(int i = 0; i < 2; i++){
        gracze[0].wezKarte(dajKarte());
        gracze[1].wezKarte(dajKarte());
    }
    std::cout << "Gracz 1: ";
    gracze[0].wyświetlKarty();
    std::cout << "\nGracz 2: ";
    gracze[1].wyświetlKarty();
}