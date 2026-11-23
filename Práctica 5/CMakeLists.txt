cmake_minimum_required(VERSION 3.10)
project(Practica5)

set(CMAKE_CXX_STANDARD 14)


add_executable(Practica5 main.cpp Especie.cpp
        Parque.cpp
        Parque.h
        ControlParques.cpp
        ControlParques.h
        Arbol.cpp
        Arbol.h)