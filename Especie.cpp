//
// Created by Roberto Luque Peña on 24/09/2026.
//

#include "Especie.h"

 bool Especie::operator==(const Especie &e)const {
  return codigoEspecie == e.codigoEspecie;
}

 bool Especie::operator<(const Especie &e)const {
     return codigoEspecie < e.codigoEspecie;
 }

std::string Especie::getCodigo() const {
  return codigoEspecie;
}

std::string Especie::getnombre_cientifico() const {
    return nombreCientifico;
}

Especie::Especie(std::string codigo, std::string comun, std::string cientifico, std::string tipo):codigoEspecie(codigo),nombreComun(comun),nombreCientifico(cientifico),tipoPlanta(tipo){}
