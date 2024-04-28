#include "Kasyno.h"

int main() {
    system("chcp 65001 >nul 2>&1");
    setlocale( LC_ALL, "pl_PL.UTF-8" );

    Kasyno kasyno;
    kasyno.Inicjuj();

    while(kasyno.GraTrwa()) {
        system("cls");
        kasyno.graj();
    }

    return 0;
}
