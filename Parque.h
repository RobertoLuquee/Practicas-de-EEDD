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
    VDinamico<Especie*> _contains;

public:

    //Constructores y destructor
    Parque();
    Parque(int cod, const std::string &nombre);
    ~Parque();

    int get_cod_parque() const;
    void set_cod_parque(int cod);

    std::string get_nbre_parque() const;
    void set_nbre_parque(const std::string &nombre);

    VDinamico<Especie*>& get_contains();

    void insertaEspecie(Especie *especie);

    bool existeNbreCom(const std::string &nombrecomun) ;
    bool existeNbreCie(const std::string &nombrecientifico) ;

};

#endif //PRACTICA1_PARQUE_H