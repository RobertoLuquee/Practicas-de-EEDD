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

VDinamico<Arbol*>& Parque::get_contains() {
    return _contains;
}


// Búsqueda por nombre común
bool Parque::existeNbreCom(const std::string &nombrecomun)  {
    for (unsigned int i = 0; i < _contains.get__tlogico(); ++i) {
            if (_contains[i] != nullptr && _contains[i]->get_especie() != nullptr && _contains[i]->get_especie()->getnombre_comun() == nombrecomun) {
            return true;
        }
    }
    return false;
}

// Búsqueda por nombre científico
bool Parque::existeNbreCie(const std::string &nombrecientifico)  {
    for (unsigned int i = 0; i < _contains.get__tlogico(); ++i) {
        if (_contains[i] != nullptr && _contains[i]->get_especie()->getnombre_cientifico() == nombrecientifico) {
            return true;
        }
    }
    return false;
}



void Parque::insertarArbol(Arbol *a) {
    _contains.insertar(a);
}

Arbol * Parque::arbolMasAlto() {
    if (_contains.get__tlogico()==0) {
        return nullptr;
    }
    Arbol* masalto=_contains[0];
    for (int i=1;i<_contains.get__tlogico();i++) {
        if (_contains[i]->get_altura()>masalto->get_altura()) {
            masalto=_contains[i];
        }
    }
    return masalto;
}

int Parque::contarEspecies() {
    VDinamico<std::string> especiesUnicas;

    for (unsigned int i = 0; i < _contains.get__tlogico(); ++i) {
        // Nos aseguramos de que el puntero no sea nulo y tenga especie asociada
        if (_contains[i] != nullptr && _contains[i]->get_especie() != nullptr) {
            std::string codActual = _contains[i]->getCodEspecie();
            bool encontrado = false;

            // Comprobamos si el código ya está en nuestro vector de únicos
            for (unsigned int j = 0; j < especiesUnicas.get__tlogico(); ++j) {
                if (especiesUnicas[j] == codActual) {
                    encontrado = true;
                    break;
                }
            }

            // Si no estaba, lo añadimos
            if (!encontrado) {
                especiesUnicas.insertar(codActual);
            }
        }
    }

    return especiesUnicas.get__tlogico();
}


int Parque::contarTipos() {
    VDinamico<int> tiposUnicos;

    for (unsigned int i = 0; i < _contains.get__tlogico(); ++i) {
        if (_contains[i] != nullptr && _contains[i]->get_especie() != nullptr) {
            int tipoActual = _contains[i]->getTipoEspecie();
            bool encontrado = false;

            // Comprobamos si el tipo ya está en nuestro vector de únicos
            for (unsigned int j = 0; j < tiposUnicos.get__tlogico(); ++j) {
                if (tiposUnicos[j] == tipoActual) {
                    encontrado = true;
                    break;
                }
            }

            // Si no estaba, lo añadimos
            if (!encontrado) {
                tiposUnicos.insertar(tipoActual);
            }
        }
    }

    return tiposUnicos.get__tlogico();
}

