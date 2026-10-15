//
// Created by Oier Universidad on 13/10/2026.
//

#ifndef PRACTICA1_CONTROLPARQUES_H
#define PRACTICA1_CONTROLPARQUES_H
#include "ListaDEnlazada.h"
#include "VDinamico.h"
#include "Parque.h"


class ControlParques {

private:

    VDinamico<Especie> v_especies;
    ListaDEnlazada<Parque> ld_parques;

public:

    //VDinamico<Especie>& get_varieties();
    //ListaDEnlazada<Parque>& get_parks();
    ControlParques(const std::string &rutaEspecies, const std::string &rutaParques);
    void enlazarAutomatico();
    bool borrarEspecie(std::string ncomun);
    void mostrarParques();
    void asignarEspecieParque(Especie *e, Parque *p);
    int contarEspecieParque(std::string ncomun);
    VDinamico<Especie*> listadoEspecieSubNombre(std::string cadena);
    Parque* buscarParque(std::string nombre_parque);


};



#endif //PRACTICA1_CONTROLPARQUES_H
