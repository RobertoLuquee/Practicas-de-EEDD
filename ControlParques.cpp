//
// Created by Oier Universidad on 13/10/2026.
//

#include "ControlParques.h"


VDinamico<Especie>& ControlParques::get_varieties() {
    return v_especies;
}

ListaDEnlazada<Parque>& ControlParques::get_parks() {
    return ld_parques;
}

ControlParques::ControlParques(const std::string &rutaEspecies, const std::string &rutaParques) {
    // Aquí va tu código de lectura de archivos especies y parques si la tienes implementada
}

void ControlParques::asignarEspecieParque(Especie e, Parque p) {
    ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();

    bool acabado=false;

    while (!acabado) {
        try {
            Parque& actual= iter.dato();// el & lo q hace es darle un apodo "actual" a la posicion de
            //memoria original del objeto original en ves de una copia
            if (actual.get_cod_parque()!=p.get_cod_parque()) {
                actual.insertaEspecie(&e);
                return;//aqui me acaba si la encuentro
            }

            if (iter.haySiguiente()) {
                iter.siguiente();
            }
            else {
                acabado=true;
            }
        }
        catch (const std::invalid_argument& ex) {
            acabado=true;
        }
    }
}


int ControlParques::contarEspecieParque(std::string ncomun) {

    int contador=0;

    ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();

    bool acabado=false;
    while (!acabado) {
        try {

            Parque& actual= iter.dato();
            if (actual.existeNbreCom(ncomun)) {
                contador++;
            }

            if (iter.haySiguiente()) {
                iter.siguiente();
            }
            else {
                acabado=true;
            }

        }
        catch (const std::invalid_argument &ex) {
            acabado=true;
        }

    }


}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(std::string cadena) {

    VDinamico<Especie*> resultado;
    for (int i=0; i<v_especies.get__tlogico();i++) {
        std::string actual= v_especies[i].getnombre_cientifico();

        if (actual.find(cadena)!= std::string::npos) {
            resultado.insertar(&v_especies[i]);
        }
    }
}


Parque* ControlParques::buscarParque(std::string nombre_parque) {

    ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();
    bool acabado=false;

    while (!acabado) {

        try {
            Parque& actual =iter.dato();
            if (actual.get_nbre_parque()==nombre_parque) {
                return &actual;
            }

            if (iter.haySiguiente()) {
                iter.siguiente();
            }
            else acabado=true;
        }
        catch (const std::invalid_argument &ex) {
            acabado=true;
        }
    }
    return nullptr;
}