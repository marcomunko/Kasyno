#include "Kasyno.h"
#include "Utils.h"
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <random>
#include <array>


Kasyno::Kasyno() {
    graTrwa = true;
}

Kasyno::~Kasyno(){
    delete[] gracze;
}

template<typename T, typename ...tArgs>
void Kasyno::DodajGracza(tArgs &&... args) {
    //pointer jest ale nie wiem czy wskazuje na cokolwiek, czasami lubi wskazywać na nic XD teraz dzięki if działa
    if(liczbaGraczy == 0) gracze = new Gracz*[1];
    else {
        auto temp = new Gracz*[liczbaGraczy + 1];
        for(int i = 0; i < liczbaGraczy; i++){
            temp[i] = gracze[i];
        }

        delete[] gracze;
        gracze = temp;
    }

    liczbaGraczy++;
    gracze[liczbaGraczy - 1] = new T(std::forward<tArgs>(args)...);
}

// przygotuj grę
void Kasyno::Inicjuj(){
    int index = 0;
    for (short kolor = 0 ; kolor < 4; kolor++){
        for(short wartość = 0; wartość < 13; wartość++){
            karty[index++] = Karta(kolor, wartość);
        }
    }
    //tasowanie
    std::shuffle(std::begin(karty), std::end(karty), std::default_random_engine(time(nullptr)));
    aktualnaKarta = 0;
    //nie ma graczy
    delete gracze;

    //tworzenie miejsc na graczy
    gracze = new Gracz*[0];
    //warunek startu
    graTrwa=true;
    liczbaGraczy = 0;
}

//zakończ grę
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
        if(gracze[i]->wartoscReki() > 21){
            std::cout << "Gracz " << gracze[i]->getNazwa() << " przekroczył 21!" << std::endl;
        }
    }

    bool wszyscySpasowali = true;
    bool ktos_21 = false;
    for(short i = 0; i < liczbaGraczy; i++) {
        wszyscySpasowali = wszyscySpasowali && (gracze[i]->getStatus() == SPASOWANY);
        ktos_21 = ktos_21 || (gracze[i]->wartoscReki() == 21);
    }


    if(wszyscySpasowali || ktos_21){
        short najblizsza21 = 0;
        for(int i = 0; i < liczbaGraczy; i++){
            if(gracze[i]->wartoscReki() <= 21){
                if(gracze[i]->wartoscReki() > najblizsza21){
                    najblizsza21 = gracze[i]->wartoscReki();
                }
            }
        }
        for(int i = 0; i < liczbaGraczy; i++){
            if(gracze[i]->wartoscReki() == najblizsza21){
                std::cout << "Gracz " << gracze[i]->getNazwa() << " wygrywa!" << std::endl;
            }
        }
        koniecGry();
        return true;
    }
    return false;
}

Karta* Kasyno::dajKarte() {
    if(aktualnaKarta == 52){
        throw std::out_of_range("Brak kart w talii");
    }
    return &karty[aktualnaKarta++];
}

// ********** GŁÓWNY SILNIK GRY *********
void Kasyno::graj() {
    short _liczbaGraczy = Utils::IntUżytkownika("Podaj liczbę graczy (1-3): ", false, 1,3);

    for(int i = 0; i < _liczbaGraczy; i++){
        std::cout << "Gracz " << i+1 << ": ";
        DodajGracza<Gracz>(this);
    }

    short _liczbaBotów = Utils::IntUżytkownika("Podaj liczbę botów (1-3): ", false, 1,3);

    for(int i = 0; i < _liczbaBotów; i++){
        DodajBota(i + 1);
    }

    //daj karty graczom
    for(int i = 0; i < liczbaGraczy; i++){
        gracze[i]->wezKarte(dajKarte());
        gracze[i]->wezKarte(dajKarte());
    }


    bool _graTrwa = true;

    while (_graTrwa) {
        for(int i = 0; i < liczbaGraczy; i++) {
            //******* Akcje *********
            if(gracze[i]->tag() == "GRACZ"){
                if (gracze[i] -> getStatus()==SPASOWANY)
                    continue;
                system("cls");
                std::cout << "Tura gracza: " << gracze[i]->getNazwa() << std::endl;
                system("pause");
                gracze[i]->wyświetlKarty();
                std::cout << gracze[i]->wartoscReki() << std::endl;
                if(gracze[i]->getStatus() == W_TRAKCIE) {
                    std::cout << "Gracz " << gracze[i]->getNazwa() << ": ";
                    gracze[i]->ruchGracza(this);

                }
                std::cout << "Wciśnij dowolny przycisk aby przejść do kolejnego graca: " << std::endl;
                system("pause");
            } else {
                  // Działania BOTA
                  gracze[i]->ruchGracza(this);
            }
        }

        // Logia sprawdzania gry
        if(czy_Wygrana())
            _graTrwa = false;
    }
}
//Druk informacji
std::ostream &Kasyno::print(std::ostream &out) {
    for (int i = 0; i < liczbaGraczy; i++) {
        out << std::left << std::setw(20) << (gracze[i]->getNazwa());
        gracze[i]->wyświetlKarty(out << "\t" << std::setw(35), false)
                << "\t" << gracze[i]->wartoscReki() << std::endl;
    }

    return out;
}


void Kasyno::DodajBota(short liczbaBota) {
    // losuj odwagę bota
    short odwaga = rand() % 3;
    std::string nazwa = "Bot " + std::to_string(liczbaBota);

    switch(odwaga){
        case 0:
            DodajGracza<Bot>(RYZYKUJĄCY, this, nazwa);
            break;
        case 1:
            DodajGracza<Bot>(NORMALNY, this, nazwa);
            break;
        case 2:
            DodajGracza<Bot>(ZACHOWAWCZY, this, nazwa);
            break;
    }
}