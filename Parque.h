//
// Created by Roberto Luque Peña on 13/10/2026.
//

#ifndef PRACTICA1_PARQUE_H
#define PRACTICA1_PARQUE_H
#include <iostream>
#include "VDinamico.h"
#include "Especie.h"
class Parque {
private:
    int _cod_parque;
    std::string _nbre_parque;
    VDinamico<Especie*> contains;

public:

    //Constructores y destructor
    Parque();
    Parque(int cod, const std::string &nombre);
    ~Parque();

};


#endif //PRACTICA1_PARQUE_H