//
// Created by Oier Universidad on 26/10/2026.
//

#include "Arbol.h"

int Arbol::get_assetnum() const {
    return assetnum;
}

float Arbol::get_altura() const {
    return altura;
}

Especie* Arbol::get_especie()const {
    return especie;
}

Arbol::Arbol():assetnum(0),latitud(0.0),longitud(0.0),perimetro(0.0),altura(0.0),especie(nullptr);

Arbol::Arbol(int assetnum, std::string parque, std::string distrito, std::string barrio, double latitud,
    double longitud, float perimetro, float altura) {

    this->assetnum = assetnum;
    this->especie = nullptr;
}


void Arbol::setEspecie(Especie* especie) {
    this->especie = especie;
    }

std::string Arbol::getCodEspecie() const {
    if (especie!=nullptr) {
        return especie->getCodigo();
    }
    return "No hay especie asociada";
}

int  Arbol::getTipoEspecie() const {
    if (especie!=nullptr) {
        return especie->get_tipo_planta();
    }
    return 0;


};
