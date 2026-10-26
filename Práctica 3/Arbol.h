//
// Created by Oier Universidad on 26/10/2026.
//

#ifndef PRACTICA3_ARBOL_H
#define PRACTICA3_ARBOL_H

#include <string>
#include "Especie.h"

class Arbol {
private:
    int assetnum;
    std::string nombreParque;
    std::string distrito;
    std::string barrio;
    double latitud;
    double longitud;
    float perimetro;
    float altura;

    Especie* especie;

public:


    Arbol();
    Arbol(int assetnum, std::string parque, std::string distrito, std::string barrio,
          double latitud, double longitud, float perimetro, float altura);

    int get_assetnum() const;
    float get_altura() const;
    Especie * get_especie() const;

    void setEspecie(Especie* especie);
    std::string getCodEspecie() const;
    int getTipoEspecie() const;
};


#endif //PRACTICA3_ARBOL_H