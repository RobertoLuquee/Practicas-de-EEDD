cmake_minimum_required(VERSION 3.10)
project(Practica1)

set(CMAKE_CXX_STANDARD 14)


add_executable(Practica1 main.cpp Especie.cpp
        ListaDEnlazada.cpp
        Parque.cpp
        Parque.h
        ControlParques.cpp
        ControlParques.h)