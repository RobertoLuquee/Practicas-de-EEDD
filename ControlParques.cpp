//
// Created by Oier Universidad on 13/10/2026.
//

#include "ControlParques.h"

void ControlParques::asignarEspecieParque(Especie e, Parque p) {
    ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();

    bool acabado=false;

    while (acabado) {
        try {
            Parque& actual= iter.dato();
            if (actual.getCodParque!=p.getCodParque) {

            }





        }
        catch (const std::invalid_argument& ex) {
            acabado=true;
        }
    }
}


int ControlParques::contarEspecieParque(std::string ncomun) {
}

VDinamico<Especie> ControlParques::listadoEspecieSubNombre(std::string cadena) {
}

Parque ControlParques::buscarParque(std::string nombre_parque) {
}