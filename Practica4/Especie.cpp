//
// Created by Roberto Luque Peña on 24/09/2026.
//
#include <iostream>
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

std::string Especie::getnombre_comun() const {
     return nombreComun;
 }

Especie::Especie(std::string codigo, std::string comun, std::string cientifico, TipoPlanta tipo):codigoEspecie(codigo),nombreComun(comun),nombreCientifico(cientifico),tipoPlanta(tipo){}


void Especie::mostrarInfo() const {
     std::cout << "Codigo: " << codigoEspecie;
     std::cout << " | Nombre comun: " << nombreComun;
     std::cout << " | Nombre cientifico: " << nombreCientifico;
     std::cout << " | Tipo: " << tipoPlanta << std::endl;
 }


int Especie::get_tipo_planta() const {
     return tipoPlanta;
 }
