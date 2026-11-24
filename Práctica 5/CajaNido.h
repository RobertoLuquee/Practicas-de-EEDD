//
// Created by Oier Universidad on 24/11/2026.
//

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
    CajaNido()=default;
    void setArbol(Arbol* a);
    Arbol* getArbol();
    bool estaEnArbol();
};


#endif //PRACTICA3_CAJANIDO_H