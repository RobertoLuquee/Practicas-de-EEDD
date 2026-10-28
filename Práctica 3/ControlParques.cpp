//
// Created by Oier Universidad on 13/10/2026.
//

#include "ControlParques.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

ControlParques::ControlParques() {}

ControlParques::ControlParques(const std::string &rutaEspecies, const std::string &rutaParques) {
    std::ifstream esEspecie(rutaEspecies);
    std::string fila;
    std::stringstream columna;
    char separador = ',';

    std::string _codigoEspecie, _nombreComun, _nombreCientifico, _tipoStr;

    if (esEspecie.good()) {
        getline(esEspecie, fila);
        while (getline(esEspecie, fila)) {
            if (fila != "") {
                columna.str(fila);

                getline(columna, _codigoEspecie, separador);
                getline(columna, _nombreComun, separador);
                getline(columna, _nombreCientifico, separador);
                getline(columna, _tipoStr, separador);

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
    } else {
        std::cerr << "Error de apertura en archivo: " << rutaEspecies << std::endl;
    }

    std::ifstream esParque(rutaParques);
    std::string filaparque;
    std::stringstream columnaparque;

    std::string _codigoParqueStr, _nombreParque;

    if (esParque.good()) {
        getline(esParque, filaparque);

        while (getline(esParque, filaparque)) {
            if (filaparque != "") {
                columnaparque.str(filaparque);

                getline(columnaparque, _codigoParqueStr, separador);
                getline(columnaparque, _nombreParque, separador);

                columnaparque.clear();

                if (!_nombreParque.empty() && _nombreParque.back() == '\r') {
                    _nombreParque.pop_back();
                }

                if (!_nombreParque.empty() && _nombreParque.front() == '"') {
                    _nombreParque.erase(0, 1);
                    if (_nombreParque.back() == '"') {
                        _nombreParque.pop_back();
                    }
                }

                int codParqueInt = 0;
                try {
                    codParqueInt = std::stoi(_codigoParqueStr);
                } catch (const std::exception& e) {
                    std::cerr << "Error al convertir codigo de parque a numero: " << _codigoParqueStr << std::endl;
                    continue;
                }

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

// Constructor de 3 ficheros CSV exigido por main.cpp
ControlParques::ControlParques(const std::string &rutaEspecies,
                               const std::string &rutaParques,
                               const std::string &rutaArboles)
    : ControlParques(rutaEspecies, rutaParques) {

    std::ifstream ficheroArboles(rutaArboles);
    if (!ficheroArboles.is_open()) {
        std::cerr << "Error al abrir el archivo de arboles: " << rutaArboles << std::endl;
        return;
    }

    std::string linea;
    std::getline(ficheroArboles, linea); // Saltar cabecera

    while (std::getline(ficheroArboles, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        if (linea.empty()) continue;

        std::stringstream registro(linea);
        std::string campos[12];

        for (unsigned int i = 0; i < 12; ++i) {
            std::getline(registro, campos[i], ';');
        }

        std::replace(campos[6].begin(), campos[6].end(), ',', '.');
        std::replace(campos[7].begin(), campos[7].end(), ',', '.');

        float perim = campos[10].empty() ? -1.0f : std::stof(campos[10]);
        float alt = campos[11].empty() ? -1.0f : std::stof(campos[11]);

        Arbol arbol(campos[0], std::stoi(campos[1]), std::stoi(campos[2]), campos[3],
                    std::stoi(campos[4]), campos[5], std::stod(campos[6]),
                    std::stod(campos[7]), perim, alt);

        // Enlazar puntero a Especie si existe en v_especies
        std::string codEspStr = std::to_string(std::stoi(campos[4]));
        for (unsigned int i = 0; i < v_especies.get__tlogico(); ++i) {
            if (v_especies[i].getCodigo() == codEspStr) {
                arbol.setEspecie(&v_especies[i]);
                break;
            }
        }

        // Insertar en AVL
        avl_arboles.inserta(arbol);

        // Insertar puntero en el parque correspondiente
        Arbol* ptrArbol = avl_arboles.buscaIt(arbol);
        if (ptrArbol != nullptr) {
            ListaDEnlazada<Parque>::Iterador it = ld_parques.iterador();
            while (!it.fin()) {
                if (it.dato().get_cod_parque() == arbol.getNumParque()) {
                    it.dato().insertarArbol(ptrArbol);
                    break;
                }
                it.siguiente();
            }
        }
    }
    ficheroArboles.close();
}

void ControlParques::enlazarAutomatico() {
    for (int i = 0; i < v_especies.get__tlogico(); i++) {
        Especie& actual = v_especies[i];
        int tipo = actual.get_tipo_planta();

        ListaDEnlazada<Parque>::Iterador iter = ld_parques.iterador();

        while (!iter.fin()) {
            Parque& p_actual = iter.dato();
            int codParque = p_actual.get_cod_parque();

            bool esPar = (codParque % 2 == 0);

            if (esPar && (tipo == ARBUSTO || tipo == CONIFERA ||
                          tipo == PALMACEA || tipo == HERB_PERENNES ||
                          tipo == FRONDOSA)) {
                p_actual.insertaEspecie(&actual);
            } else if (!esPar && (tipo == TAPIZANTE_TREPADORA ||
                                tipo == CACTACEA_SUCULENTA ||
                                tipo == SUBTROPICAL_TROPICAL ||
                                tipo == HERB_ANUAL ||
                                tipo == HERB_ANUALES)) {
                p_actual.insertaEspecie(&actual);
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
    bool encontrado = false;

    ListaDEnlazada<Parque>::Iterador iter = ld_parques.iterador();

    while (!iter.fin()) {
        Parque& actual = iter.dato();
        VDinamico<Arbol*>& arbolesparque = actual.get_contains();

        for (int i = 0; i < arbolesparque.get__tlogico(); i++) {
            if (arbolesparque[i] != nullptr &&
                arbolesparque[i]->getEspecie() != nullptr &&
                arbolesparque[i]->getEspecie()->getnombre_comun() == ncomun) {

                arbolesparque[i]->setEspecie(nullptr);
                arbolesparque[i] = nullptr;
            }
        }
        iter.siguiente();
    }

    for (int i = 0; i < v_especies.get__tlogico(); i++) {
        if (v_especies[i].getnombre_comun() == ncomun) {
            v_especies.borrar(i);
            encontrado = true;
            i--;
        }
    }
    return encontrado;
}

void ControlParques::asignarEspecieParque(Especie *e, Parque *p) {
    ListaDEnlazada<Parque>::Iterador iter = ld_parques.iterador();

    bool acabado = false;

    while (!acabado) {
        try {
            Parque& actual = iter.dato();
            if (actual.get_cod_parque() != p->get_cod_parque()) {
                actual.insertaEspecie(e);
                return;
            }

            if (iter.haySiguiente()) {
                iter.siguiente();
            } else {
                acabado = true;
            }
        } catch (const std::invalid_argument& ex) {
            acabado = true;
        }
    }
}

int ControlParques::contarEspecieParque(std::string ncomun) {
    int contador = 0;

    ListaDEnlazada<Parque>::Iterador iter = ld_parques.iterador();

    bool acabado = false;
    while (!acabado) {
        try {
            Parque& actual = iter.dato();
            if (actual.existeNbreCom(ncomun)) {
                contador++;
            }

            if (iter.haySiguiente()) {
                iter.siguiente();
            } else {
                acabado = true;
            }
        } catch (const std::invalid_argument &ex) {
            acabado = true;
        }
    }
    return contador;
}

VDinamico<Especie*> ControlParques::listadoEspecieSubNombre(std::string cadena) {
    VDinamico<Especie*> resultado;
    for (int i = 0; i < v_especies.get__tlogico(); i++) {
        std::string actual = v_especies[i].getnombre_cientifico();

        if (actual.find(cadena) != std::string::npos) {
            resultado.insertar(&v_especies[i]);
        }
    }
    return resultado;
}

Parque* ControlParques::buscarParque(std::string nombre_parque) {
    ListaDEnlazada<Parque>::Iterador iter = ld_parques.iterador();
    while (!iter.fin()) {
        if (iter.dato().getNombre() == nombre_parque) {
            return &(iter.dato());
        }
        iter.siguiente();
    }
    return nullptr;
}

// 1. Buscar árbol en el AVL por assetnum (string)
Arbol* ControlParques::buscarArbol(const std::string &assetnum) {
    Arbol aux(assetnum);
    return avl_arboles.buscaIt(aux);
}

// 2. Obtener lista de árboles de un parque específico
VDinamico<Arbol*> ControlParques::listaArbParque(const std::string &nombreParque) {
    ListaDEnlazada<Parque>::Iterador it = ld_parques.iterador();
    while (!it.fin()) {
        if (it.dato().getNombre() == nombreParque) {
            return it.dato().get_contains();
        }
        it.siguiente();
    }
    return VDinamico<Arbol*>();
}

// 3. Obtener el árbol más alto de todos los parques del sistema
Arbol* ControlParques::arbolMasAlto() {
    Arbol* masAltoGlobal = nullptr;
    ListaDEnlazada<Parque>::Iterador it = ld_parques.iterador();

    while (!it.fin()) {
        Arbol* masAltoParque = it.dato().arbolMasAlto();
        if (masAltoParque != nullptr) {
            if (masAltoGlobal == nullptr || masAltoParque->getAltura() > masAltoGlobal->getAltura()) {
                masAltoGlobal = masAltoParque;
            }
        }
        it.siguiente();
    }
    return masAltoGlobal;
}

// 4. Contar especies distintas en un parque por su nombre
int ControlParques::contarEspecies(const std::string &nombreParque) {
    ListaDEnlazada<Parque>::Iterador it = ld_parques.iterador();
    while (!it.fin()) {
        if (it.dato().getNombre() == nombreParque) {
            return it.dato().contarEspecies();
        }
        it.siguiente();
    }
    return 0;
}

// 5. Contar tipos de plantas distintos en todos los parques
int ControlParques::contarTipos() {
    VDinamico<int> tiposUnicos;
    ListaDEnlazada<Parque>::Iterador it = ld_parques.iterador();

    while (!it.fin()) {
        VDinamico<Arbol*>& arboles = it.dato().get_contains();
        for (unsigned int i = 0; i < arboles.get__tlogico(); ++i) {
            if (arboles[i] != nullptr) {
                int tipo = arboles[i]->getTipoEspecie();
                if (tipo != 0) {
                    bool yaExiste = false;
                    for (unsigned int j = 0; j < tiposUnicos.get__tlogico() && !yaExiste; ++j) {
                        if (tiposUnicos[j] == tipo) {
                            yaExiste = true;
                        }
                    }
                    if (!yaExiste) {
                        tiposUnicos.insertar(tipo);
                    }
                }
            }
        }
        it.siguiente();
    }
    return tiposUnicos.get__tlogico();
}

// 6. Búsqueda por rango (ejercicio por parejas)
VDinamico<Arbol*> ControlParques::buscarArbolesRango(const std::string& asNumMin, const std::string& asNumMax) {
    // Excepción si el límite inferior es mayor
    if (asNumMin > asNumMax) {
        throw std::invalid_argument("Error: El límite inferior no puede ser mayor que el superior.");
    }

    // Usamos el constructor de 1 parámetro de Arbol para crear objetos de comparación
    Arbol minArbol(asNumMin);
    Arbol maxArbol(asNumMax);

    // Asumiendo que tu atributo AVL se llama 'arbolesAVL'
    return avl_arboles.buscarRango(minArbol, maxArbol);
}