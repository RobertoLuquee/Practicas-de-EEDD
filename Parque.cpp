//
// Created by Roberto Luque Peña on 13/10/2026.
//

#include "Parque.h"



// Constructor por defecto
Parque::Parque() : _cod_parque(0), _nbre_parque("") {}

// Constructor parametrizado
Parque::Parque(int cod, const std::string &nombre)
    : _cod_parque(cod), _nbre_parque(nombre) {}

// Destructor
Parque::~Parque() {}

//Aqui añado los getters y setters
int Parque::get_cod_parque() const {
    return _cod_parque;
}

void Parque::set_cod_parque(int cod) {
    _cod_parque = cod;
}

std::string Parque::get_nbre_parque() const {
    return _nbre_parque;
}

void Parque::set_nbre_parque(const std::string &nombre) {
    _nbre_parque = nombre;
}

VDinamico<Especie*>& Parque::get_contains() {
    return _contains;
}

//Metodos de la clase

void Parque::insertaEspecie(Especie *esp) {
    _contains.insertar(esp);
}

// Búsqueda por nombre común
bool Parque::existeNbreCom(const std::string &nombrecomun)  {
    for (unsigned int i = 0; i < _contains.get__tlogico(); ++i) {
        if (_contains[i] != nullptr && _contains[i]->getnombre_comun() == nombrecomun) {
            return true;
        }
    }
    return false;
}

// Búsqueda por nombre científico
bool Parque::existeNbreCie(const std::string &nombrecientifico)  {
    for (unsigned int i = 0; i < _contains.get__tlogico(); ++i) {
        if (_contains[i] != nullptr && _contains[i]->getnombre_cientifico() == nombrecientifico) {
            return true;
        }
    }
    return false;
}

