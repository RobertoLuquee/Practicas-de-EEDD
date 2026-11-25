//
// Created by Oier Universidad on 24/11/2026.
//
#include <string>
#include "UTM.h"
#ifndef PRACTICA3_CAJANIDO_H
#define PRACTICA3_CAJANIDO_H

class Arbol;

class CajaNido {

private:
    std::string distrito;
    std::string barrio;
    std::string ubicacion;
    UTM coord;
    Arbol* itsTree=nullptr;// del uml que va inicializado a nulo.

public:
    std::string get_barrio() const;

    Arbol * get_its_tree() const;

    CajaNido()=default;
    CajaNido(std::string dist, std::string barr, std::string ubic, UTM c);
    void setArbol(Arbol* a);
    Arbol* getArbol() const;

    std::string get_distrito() const;
    std::string getUbicacion() const { return ubicacion; }

    UTM get_coord() const;

    bool estaEnArbol() const;
};


#endif //PRACTICA3_CAJANIDO_H