//
// Created by Oier Universidad on 13/10/2026.
//

#include "ControlParques.h"
#include <fstream>
#include <sstream>
#include <iostream>



ControlParques::ControlParques(const std::string &rutaEspecies, const std::string &rutaParques) {
    std::ifstream esEspecie(rutaEspecies);
    std::string fila;
    std::stringstream columna;
    char separador = ',';

    std::string _codigoEspecie, _nombreComun, _nombreCientifico, _tipoStr;


    if (esEspecie.good()) {
        getline(esEspecie,fila);
        while (getline(esEspecie, fila)) {
            if (fila!="") {
                columna.str(fila);

                getline(columna, _codigoEspecie,separador);
                getline(columna,_nombreComun,separador);
                getline(columna,_nombreCientifico,separador);
                getline(columna,_tipoStr,separador);

                columna.clear();

                if (!_tipoStr.empty() && _tipoStr.back() == '\r') {
                    _tipoStr.pop_back();
                }

                TipoPlanta tipoEnum = ARBUSTO; // Valor por defecto
                if (_tipoStr == "ARBUSTO") tipoEnum = ARBUSTO;
                else if (_tipoStr == "CONIFERA") tipoEnum = CONIFERA;
                else if (_tipoStr == "PALMACEA") tipoEnum = PALMACEA;
                else if (_tipoStr == "HERB_PERENNES") tipoEnum = HERB_PERENNES;
                else if (_tipoStr == "FRONDOSA") tipoEnum = FRONDOSA;
                else if (_tipoStr == "TAPIZANTE/TREPADORA") tipoEnum = TAPIZANTE_TREPADORA;
                else if (_tipoStr == "CACTACEA/SUCULENTA") tipoEnum = CACTACEA_SUCULENTA;
                else if (_tipoStr == "SUBTROPICAL/TROPICAL") tipoEnum = SUBTROPICAL_TROPICAL;
                else if (_tipoStr == "HERB_ANUAL") tipoEnum = HERB_ANUAL;
                else if (_tipoStr == "HERB_ANUALES") tipoEnum = HERB_ANUALES;

                Especie nuevoregistro(_codigoEspecie, _nombreComun, _nombreCientifico, tipoEnum);
                v_especies.insertar(nuevoregistro);
            }
        }
        esEspecie.close();
        v_especies.ordenar();
    }
    else {
        std::cerr << "Error de apertura en archivo: " << rutaEspecies << std::endl;
    }


    std::ifstream esParque(rutaParques);
    std::string filaparque;
    std::stringstream columnaparque;

    std::string _codigoParqueStr,_nombreParque;

    if (esParque.good()) {
        getline(esParque,filaparque);

        while (getline(esParque,filaparque)) {
            if (filaparque!="") {
                columnaparque.str(filaparque);

                getline(columnaparque, _codigoParqueStr, separador);
                getline(columnaparque, _nombreParque, separador);

                columnaparque.clear();

                if (!_nombreParque.empty() && _nombreParque.back() == '\r') {
                    _nombreParque.pop_back();
                }

                if (!_nombreParque.empty() && _nombreParque.front() == '"') {
                    _nombreParque.erase(0, 1); // Borramos la primera comilla
                    if (_nombreParque.back() == '"') {
                        _nombreParque.pop_back(); // Borramos la última comilla
                    }
                }

                int codParqueInt = 0;
                try {
                    codParqueInt = std::stoi(_codigoParqueStr);
                } catch (const std::exception& e) {
                    std::cerr << "Error al convertir codigo de parque a numero: " << _codigoParqueStr << std::endl;
                    continue;
                }

                // Creamos el objeto Parque y lo insertamos al FINAL de la lista
                Parque nuevoParque(codParqueInt, _nombreParque);
                ld_parques.insertarFin(nuevoParque);
            }
        }
        esParque.close();

        std::cout << "Parques cargados correctamente. Total: "
                  << ld_parques.tam() << " parques." << std::endl;

    } else {
        std::cerr << "Error de apertura en archivo de parques: " << rutaParques << std::endl;

    }
}

void ControlParques::enlazarAutomatico() {
    for (int i=0;i<v_especies.get__tlogico();i++) {
        Especie& actual=v_especies[i];
        int tipo=actual.get_tipo_planta();

        ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();

        while (!iter.fin()) {
            Parque& p_actual=iter.dato();
            int codParque=p_actual.get_cod_parque();

            bool esPar=(codParque%2==0);//el resto de la division entre 2 es=0

            if (esPar && (tipo == ARBUSTO || tipo == CONIFERA ||
                          tipo == PALMACEA || tipo == HERB_PERENNES ||
                          tipo == FRONDOSA)) {
                p_actual.insertaEspecie(&actual);
                          }

            else if (!esPar && (tipo == TAPIZANTE_TREPADORA ||
                                tipo == CACTACEA_SUCULENTA ||
                                tipo == SUBTROPICAL_TROPICAL ||
                                tipo == HERB_ANUAL ||
                                tipo == HERB_ANUALES)) {

                p_actual.insertaEspecie(&actual); // Insertamos el puntero
                                }

            iter.siguiente();
        }
    }
}
void ControlParques::mostrarParques() {
    for (ListaDEnlazada<Parque>::Iterador it = ld_parques.iterador(); !it.fin(); it.siguiente()) {
        std::cout << "  Codigo: " << std::to_string(it.dato().get_cod_parque())
                  << " nombre: " << it.dato().get_nbre_parque()
                  << " total especies: " << std::to_string(it.dato().get_contains().get__tlogico()) << std::endl;
    }
}

bool ControlParques::borrarEspecie(std::string ncomun) {
    bool encontrado=false;

    ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();

    while (!iter.fin()) {
        Parque& actual=iter.dato();
        VDinamico<Especie*>& especiesparque =actual.get_contains();

        for (int i=0;i<especiesparque.get__tlogico();i++) {
            if (especiesparque[i]!=nullptr && especiesparque[i]->getnombre_comun()==ncomun) {
                especiesparque[i]=nullptr; //desenlazamos la especie del parque
            }
        }
        iter.siguiente();
    }
    for (int i=0;i<v_especies.get__tlogico();i++) {
        if (v_especies[i].getnombre_comun()==ncomun) {
            v_especies.borrar(i);
            encontrado=true;
            i--;
        }
    }
    return encontrado;
}


void ControlParques::asignarEspecieParque(Especie *e, Parque *p) {
    ListaDEnlazada<Parque>::Iterador iter=ld_parques.iterador();

    bool acabado=false;

    while (!acabado) {
        try {
            Parque& actual= iter.dato();// el & lo q hace es darle un apodo "actual" a la posicion de
            //memoria original del objeto original en ves de una copia
            if (actual.get_cod_parque()!=p->get_cod_parque()) {
                actual.insertaEspecie(e);
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
    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(std::string cadena) {

    VDinamico<Especie*> resultado;
    for (int i=0; i<v_especies.get__tlogico();i++) {
        std::string actual= v_especies[i].getnombre_cientifico();

        if (actual.find(cadena)!= std::string::npos) {
            resultado.insertar(&v_especies[i]);
        }
    }
    return resultado;
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