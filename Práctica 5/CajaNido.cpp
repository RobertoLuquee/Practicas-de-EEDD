//
// Created by Oier Universidad on 24/11/2026.
//

#include "CajaNido.h"

std::string CajaNido::get_barrio() const {
    return barrio;
}

CajaNido::CajaNido(std::string dist, std::string barr, std::string ubic, UTM c)
    : distrito(dist), barrio(barr), ubicacion(ubic), coord(c), itsTree(nullptr) {}

// Establece el árbol al que está asociada la caja nido (puede recibir nullptr)
void CajaNido::setArbol(Arbol* a) {
    itsTree = a;
}

// Devuelve un puntero al árbol asociado, o nullptr si no tiene ninguno
Arbol* CajaNido::getArbol() {
    return itsTree;
}

std::string CajaNido::get_distrito() const {
    return distrito;
}

UTM CajaNido::get_coord() const {
    return coord;
}

// Devuelve true si la caja nido tiene un árbol asociado y false en caso contrario
bool CajaNido::estaEnArbol() {
    return itsTree != nullptr;
}