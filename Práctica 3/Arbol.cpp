//
// Created by Oier Universidad on 26/10/2026.
//

#include "Arbol.h"


Arbol::Arbol()
    : assetnum(""), parque_id(0), distrito_id(0), barrio(""), codEspecie(0),
      nombreEspecie(""), latitud(0.0), longitud(0.0), perimetro(0.0f),
      altura(0.0f), especie(nullptr) {}

// Constructor de 1 parámetro
Arbol::Arbol(std::string id)
    : assetnum(id), parque_id(0), distrito_id(0), barrio(""), codEspecie(0),
      nombreEspecie(""), latitud(0.0), longitud(0.0), perimetro(0.0f),
      altura(0.0f), especie(nullptr) {}

// Constructor de 8 parámetros
Arbol::Arbol(std::string id, std::string parque, std::string distrito, std::string barrio,
             double latitud, double longitud, float perimetro, float altura)
    : assetnum(id), parque_id(0), distrito_id(0), barrio(barrio), codEspecie(0),
      nombreEspecie(""), latitud(latitud), longitud(longitud), perimetro(perimetro),
      altura(altura), especie(nullptr) {}

// Constructor completo de 10 parámetros
Arbol::Arbol(std::string id, int parc, int dist, std::string barr, int codEsp,
             std::string nomEsp, double lat, double lon, float perim, float alt)
    : assetnum(id), parque_id(parc), distrito_id(dist), barrio(barr),
      codEspecie(codEsp), nombreEspecie(nomEsp), latitud(lat), longitud(lon),
      perimetro(perim), altura(alt), especie(nullptr) {}



std::string Arbol::getAssetnum() const {
    return assetnum;
}

void Arbol::setAssetnum(const std::string& id) {
    assetnum = id;
}

int Arbol::getNumParque() const {
    return parque_id;
}

float Arbol::getAltura() const {
    return altura;
}

Especie* Arbol::getEspecie() const {
    return especie;
}

void Arbol::setEspecie(Especie* esp) {
    especie = esp;
}

std::string Arbol::getNbreComun() const {
    if (especie != nullptr) {
        return especie->getnombre_comun();
    }
    return nombreEspecie;
}

std::string Arbol::getNbreCientifico() const {
    if (especie != nullptr) {
        return especie->getnombre_cientifico();
    }
    return "";
}

std::string Arbol::getTipo() const {
    if (especie != nullptr) {
        return std::to_string(especie->get_tipo_planta());
    }
    return "";
}



std::string Arbol::get_assetnum() const {
    return assetnum;
}

float Arbol::get_altura() const {
    return altura;
}

Especie* Arbol::get_especie() const {
    return especie;
}

std::string Arbol::getCodEspecie() const {
    if (especie != nullptr) {
        return especie->getCodigo();
    }
    return std::to_string(codEspecie);
}

int Arbol::getTipoEspecie() const {
    if (especie != nullptr) {
        return especie->get_tipo_planta();
    }
    return 0;
}



bool Arbol::operator<(const Arbol &otro) const {
    return assetnum < otro.assetnum;
}

bool Arbol::operator>(const Arbol &otro) const {
    return assetnum > otro.assetnum;
}

bool Arbol::operator==(const Arbol &otro) const {
    return assetnum == otro.assetnum;
}