//
// Created by Oier Universidad on 24/11/2026.
//

#include "CajaNido.h"

// Establece el árbol al que está asociada la caja nido (puede recibir nullptr)
void CajaNido::setArbol(Arbol* a) {
    itsTree = a;
}

// Devuelve un puntero al árbol asociado, o nullptr si no tiene ninguno
Arbol* CajaNido::getArbol() {
    return itsTree;
}

// Devuelve true si la caja nido tiene un árbol asociado y false en caso contrario
bool CajaNido::estaEnArbol() {
    return itsTree != nullptr;
}