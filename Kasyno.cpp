#include "Kasyno.h"
#include "Utils.h"
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <random>
#include <array>

Kasyno::Kasyno() {
    graTrwa=true;
}

Kasyno::~Kasyno(){
    free(karty);
}

void Kasyno::Inicjuj(){
    int index = 0;
    for (short kolor = 0 ; kolor < 4; kolor++){
        for(short wartość = 0; wartość < 13; wartość++){
            karty[index++] = Karta(kolor, wartość);
        }
    }

    std::shuffle(std::begin(karty), std::end(karty), std::default_random_engine(time(nullptr)));

    aktualnaKarta = 0;
}

void Kasyno::koniecGry() {
    // Wyświetl informacje o graczu
    print(std::cout);

    // Zapis do  pliku
    std::ofstream plik("wyniki.txt", std::ios::out);
    print(plik);
    plik.close();

    // Zapytaj o nową grę
    char wybor;
    std::cout << "Czy chcesz rozpocząć nową grę? (t/n): ";
    std::cin >> wybor;
    if(tolower(wybor) == 't'){
        graTrwa = true;
        Inicjuj();
    } else {
        graTrwa = false;
    }
}

//Sprawdzenie czy gracz przekroczył 21 lub jeżeli wszyscy spasowali który z graczy ma wajtość najbliższą 21 ale nie większą
bool Kasyno::czy_Wygrana() {
    for(int i = 0; i < liczbaGraczy; i++){
        if(gracze[i].wartoscReki() > 21){
            std::cout << "Gracz " << gracze[i].getNazwa() << " przekroczył 21!" << std::endl;
        }
    }

    bool wszyscySpasowali = true;
    bool ktos_21 = false;
    for(short i = 0; i < liczbaGraczy; i++) {
        wszyscySpasowali = wszyscySpasowali && (gracze[i].getStatus() == SPASOWANY);
        ktos_21 = ktos_21 || (gracze[i].wartoscReki() == 21);
    }


    if(wszyscySpasowali || ktos_21){
        short najblizsza21 = 0;
        for(int i = 0; i < liczbaGraczy; i++){
            if(gracze[i].wartoscReki() <= 21){
                if(gracze[i].wartoscReki() > najblizsza21){
                    najblizsza21 = gracze[i].wartoscReki();
                }
            }
        }
        for(int i = 0; i < liczbaGraczy; i++){
            if(gracze[i].wartoscReki() == najblizsza21){
                std::cout << "Gracz " << gracze[i].getNazwa() << " wygrywa!" << std::endl;
            }
        }
        koniecGry();
        return true;
    }
    return false;
}

Karta* Kasyno::dajKarte() {
    return &karty[aktualnaKarta++];
}

void Kasyno::graj() {
    liczbaGraczy = Utils::IntUżytkownika("Podaj liczbe graczy (1-3): ", false, 1,3);

    gracze = new Gracz[liczbaGraczy];

    for(int i = 0; i < liczbaGraczy; i++){
        std::cout << "Gracz " << i+1 << ": ";
        gracze[i].wprowadzNazwe();
    }
    for(int i = 0; i < liczbaGraczy; i++){
        gracze[i].wezKarte(dajKarte());
        gracze[i].wezKarte(dajKarte());
    }

    bool _graTrwa = true;

    while (_graTrwa) {
        for(int i = 0; i < liczbaGraczy; i++) {
            // Akcje gracza
            if(gracze[i].tag == "GRACZ"){
                system("cls");
                std::cout << "Tura gracza: " << gracze[i].getNazwa() << std::endl;
                system("pause");
                gracze[i].wyświetlKarty();
                std::cout << gracze[i].wartoscReki() << std::endl;
                if(gracze[i].getStatus() == W_TRAKCIE) {
                    std::cout << "Gracz " << gracze[i].getNazwa() << ": ";
                    gracze[i].ruchGracza(this);

                }
                std::cout << "Wciśnij dowolny przycisk aby przejść do kolejnego graca: " << std::endl;
                system("pause");
            } else {
                // Działania BOTA
            }
        }

        // Logia sprawdzania gry
        if(czy_Wygrana())
            _graTrwa = false;
    }
}

std::ostream &Kasyno::print(std::ostream &out) {
     for(int i = 0; i < liczbaGraczy; i++){
         out << std::left << std::setw(20) << gracze[i].getNazwa();
                   gracze[i].wyświetlKarty(out << "\t" << std::setw(35), false)
                   << "\t" << gracze[i].wartoscReki() << std::endl;
     }

     return out;
 }