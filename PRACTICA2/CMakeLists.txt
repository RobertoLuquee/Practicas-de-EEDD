cmake_minimum_required(VERSION 3.10)
project(Practica2)

set(CMAKE_CXX_STANDARD 14)


add_executable(Practica2 main.cpp Especie.cpp
        ListaDEnlazada.cpp
        Parque.cpp
        Parque.h
        ControlParques.cpp
        ControlParques.h
        "../Práctica 3/AVL.cpp"
        "../Práctica 3/AVL.h"
        "../Práctica 3/AVL.h")