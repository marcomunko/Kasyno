cmake_minimum_required(VERSION 3.26)
project(Kasyno)

set(CMAKE_CXX_STANDARD 23)

add_executable(Kasyno main.cpp
        Karta.cpp
        Karta.h
        Kasyno.cpp
        Kasyno.h
        Gracz.cpp
        Gracz.h
        Utils.h
)
