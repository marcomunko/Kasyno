#include "Kasyno.h"

int main() {
    //ustawienie UTF 8 -> polskie znaki i ujednolicenie kodowania
    system("chcp 65001 >nul 2>&1");
    setlocale( LC_ALL, "pl_PL.UTF-8" );

    //utwórz kasyno
    Kasyno kasyno;

    //głowna pętla
    while(kasyno.GraTrwa()) {
        kasyno.Inicjuj();
        system("cls");
        kasyno.graj();
    }

    return 0;
}
