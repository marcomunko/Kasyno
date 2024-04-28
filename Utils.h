#ifndef KASYNO_UTILS_H
#define KASYNO_UTILS_H
#include <string>
#include <iostream>

class Utils {
public:
    static int IntUżytkownika(std::string msg, bool exception = true, int rangeStart = -1, int rangeEnd = -1){
        std::cout << msg;
        int n;
        std::cin >> n;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');

            if(exception)
                throw std::exception();
            else
                return IntUżytkownika(msg, exception, rangeStart, rangeEnd);
        }

        if(rangeStart != -1 && rangeEnd != -1 && (n < rangeStart || n > rangeEnd)){
            std::cout << "Podana liczba nie mieści się w zakresie" << std::endl;
            return IntUżytkownika(msg, exception, rangeStart, rangeEnd);
        }

        return n;
    }

    static std::string stringUżytkownika(std::string msg, int maxL = -1){
        std::cout << msg;
        std::string s;
        std::cin.ignore();
        getline(std::cin, s);

        if(maxL != -1 && s.length() > maxL){
            std::cout << "Podany tekst jest za długi\n";
            return stringUżytkownika(msg, maxL);
        }

        if(s.length() < 1){
            std::cout << "Tekst musi istnieć lol\n";
            return stringUżytkownika(msg, maxL);
        }

        return s;
    }
};
#endif //KASYNO_UTILS_H
