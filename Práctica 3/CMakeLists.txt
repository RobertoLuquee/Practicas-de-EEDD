cmake_minimum_required(VERSION 3.10)
project(Practica3)

set(CMAKE_CXX_STANDARD 14)


add_executable(Practica3 main.cpp Especie.cpp
        ListaDEnlazada.cpp
        Parque.cpp
        Parque.h
        ControlParques.cpp
        ControlParques.h)