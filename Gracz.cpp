#include "Gracz.h"
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <utility>

// Ten konstruktor powinień być nadpisywany później
Gracz::Gracz() {
    karty = new Karta*[10];
    liczbaKart = 0;
    nazwa = "TEMP_NAME";
}

Gracz::~Gracz(){
    delete[] karty;
}

Gracz &Gracz::operator=(const Gracz &g) {
    if (this != &g) { // Zabezpiecz przed przypisaniem samego do siebie
        this->nazwa = g.nazwa;
        this->status = g.status;

        this->liczbaKart = g.liczbaKart;
        this->karty = new Karta*[liczbaKart];
        std::copy(g.karty, g.karty + liczbaKart, this->karty);
    }

    return *this;
}

short Gracz::wartoscReki() {
    short suma = 0;
    for(short i = 0; i < liczbaKart; i++){
        suma += karty[i]->getWartosc();
    }
    return suma;
}

void Gracz::wezKarte(Karta *karta) {
    if(liczbaKart == 10){
        return;
    }
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
            try {
                wezKarte(kasyno->dajKarte());
            } catch (std::exception &e){
                // Wystąpienie błędu => brak kart w talii => spasuj
                status = SPASOWANY;
            }
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

//**** wyświetlanie kart ****
//tablica symboli kolorów
const char* kolory[] = { "\u2660", "\u2663", "\u2665", "\u2666" };
//wyświetlanie na konsoli
void Gracz::wyświetlKarty(bool dodajEnter){
    // Zmieniamy wartości na symbole kolorów
    for(int i = 0; i < liczbaKart; i++){
        std::cout << karty[i]->getFigura() << kolory[karty[i]->getKolor() - 3] << " ";
    };
    if(dodajEnter) {
        std::cout << "\n";
    }
}
//wyświetl karty na dowolnym strumieniu
std::ostream &Gracz::wyświetlKarty(std::ostream &o, bool dodajEnter){
    std::stringstream ss("");
    // Zmieniamy wartości na symbole kolorów
    for(int i = 0; i < liczbaKart; i++){
        ss << karty[i]->getFigura() << kolory[karty[i]->getKolor() - 3] << " ";
    };
    if(dodajEnter) {
        ss << "\n";
    }

    return o << ss.str();
}

//################### STREFA BOTA ########################
void Bot::DecyzjaSpasowania() {
    if (wartoscReki() >= 21) {
        status = SPASOWANY;
    }
    if (liczbaKart >= 10) {
        status = SPASOWANY;
    }

    short maksimum = 0;

   switch(odwaga){
        case ZACHOWAWCZY:
            maksimum = 10;
            break;
       case NORMALNY:
           maksimum = 15;
           break;
       case RYZYKUJĄCY:
           maksimum = 17;
           break;
    }

    if(wartoscReki() >= maksimum){
        status = SPASOWANY;
    }
}
//ruchy bota
void Bot::ruchGracza(Kasyno *kasyno) {
    DecyzjaSpasowania();
    if(status != SPASOWANY){
        try {
            wezKarte(kasyno->dajKarte());
        } catch (std::exception &e){
            // Wystąpienie błędu => brak kart w talii => spasuj
            status = SPASOWANY;
        }
    }
}