#ifndef KASYNO_KASYNO_H
#define KASYNO_KASYNO_H

#include "Karta.h"
#include "Gracz.h"

class Kasyno {
private:
    bool graTrwa;
    Talia *talia;
    Gracz *gracze;
public:
    Kasyno();
    ~Kasyno();

    void Inicjuj();
    void graj();

    Karta* dajKarte();

    bool GraTrwa();
};


#endif //KASYNO_KASYNO_H
