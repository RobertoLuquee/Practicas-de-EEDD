//
// Created by Roberto Luque Peña on 13/10/2026.
//
 
#include "Parque.h"
#include <map>
#include <set>
 
 
 
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
 
vector<Arbol*>& Parque::get_contains() {
    return _contains;
}
 
 
// Búsqueda por nombre común
bool Parque::existeNbreCom(const std::string &nombrecomun)  {
    vector<Arbol*>::iterator it;
    for (it = _contains.begin(); it != _contains.end(); it++) {
            if (*it != nullptr && (*it)->get_especie() != nullptr && (*it)->get_especie()->getnombre_comun() == nombrecomun) {
            return true;
        }
    }
    return false;
}
 
// Búsqueda por nombre científico
bool Parque::existeNbreCie(const std::string &nombrecientifico)  {
    vector<Arbol*>::iterator it;
    for (it = _contains.begin(); it != _contains.end(); it++) {
        if (*it != nullptr && (*it)->get_especie() != nullptr && (*it)->get_especie()->getnombre_cientifico() == nombrecientifico) {
            return true;
        }
    }
    return false;
}
 
 
 
void Parque::insertarArbol(Arbol *a) {
    _contains.push_back(a);
}
 
Arbol * Parque::arbolMasAlto() {
    if (_contains.empty()) {
        return nullptr;
    }
    Arbol* masalto=_contains[0];
    vector<Arbol*>::iterator it;
    for (it = _contains.begin(); it != _contains.end(); it++) {
        if ((*it)->get_altura()>masalto->get_altura()) {
            masalto=*it;
        }
    }
    return masalto;
}
 
int Parque::contarEspecies() {
    std::set<std::string> especiesUnicas;

    std::vector<Arbol*>::iterator it;
    for (it = _contains.begin(); it != _contains.end(); it++) {
        if (*it != nullptr && (*it)->get_especie() != nullptr) {
            // El set ignora los repetidos automáticamente
            especiesUnicas.insert((*it)->getCodEspecie());
        }
    }

    return especiesUnicas.size();
}

 
int Parque::contarTipos() {
    std::set<int> tiposUnicos;

    std::vector<Arbol*>::iterator it;
    for (it = _contains.begin(); it != _contains.end(); it++) {
        if (*it != nullptr && (*it)->get_especie() != nullptr) {
            tiposUnicos.insert((*it)->getTipoEspecie());
        }
    }

    return tiposUnicos.size();
}
 
    std::string Parque::getNombre() const {
        return _nbre_parque;
    }
 
Especie * Parque::especieMasComun() {
    if (_contains.empty()) {
        return nullptr;
    }
    std::map<Especie*,int> contadores;
    Especie* masComun=nullptr;
    int maxFrecuencia=0;
 
    vector<Arbol*>::iterator it;
    for (it = _contains.begin(); it != _contains.end(); it++) { //recorremos todos los elementos de la eedd
        Arbol* arbol = *it;
        if (arbol!=nullptr && arbol->getEspecie()!=nullptr) {
          Especie* esp=arbol->getEspecie();
          contadores[esp]++;
          if (contadores[esp]>maxFrecuencia) {
              maxFrecuencia=contadores[esp];
              masComun=esp;
          }
      }
    }
return masComun;
}
 
void Parque::insertaEspecie(Especie *especie) {}
 