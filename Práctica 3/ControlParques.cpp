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
                varieties.push_back(nuevoregistro);
            }
        }
        esEspecie.close();
        std::sort(varieties.begin(), varieties.end(), [](const Especie& a, const Especie& b) {
            return a.getCodigo() < b.getCodigo();
        });
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
                parks.push_back(nuevoParque);
            }
        }
        esParque.close();

        std::cout << "Parques cargados correctamente. Total: "
                  << parks.size() << " parques." << std::endl;
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

        // Reemplazar comas por puntos en TODOS los números flotantes
        std::replace(campos[6].begin(), campos[6].end(), ',', '.');
        std::replace(campos[7].begin(), campos[7].end(), ',', '.');
        std::replace(campos[10].begin(), campos[10].end(), ',', '.');
        std::replace(campos[11].begin(), campos[11].end(), ',', '.');

        float perim = campos[10].empty() ? -1.0f : std::stof(campos[10]);
        float alt = campos[11].empty() ? -1.0f : std::stof(campos[11]);

        // Crear árbol saltándose los barrios y apuntando al 8 (codEsp) y 9 (nomEsp)
        Arbol arbol(
            campos[0],
            campos[1].empty() ? 0 : std::stoi(campos[1]),
            campos[2].empty() ? 0 : std::stoi(campos[2]),
            campos[5], // barr
            campos[8], // codEsp (Este es el que importa)
            campos[9], // nomEsp
            campos[6].empty() ? 0.0 : std::stod(campos[6]),
            campos[7].empty() ? 0.0 : std::stod(campos[7]),
            perim,
            alt
        );

        // Enlazar puntero a Especie si existe en v_especies
        std::string codEspStr = campos[8];
        for (unsigned int i = 0; i < varieties.size(); ++i) {
            if (varieties[i].getCodigo() == codEspStr) {
                arbol.setEspecie(&varieties[i]);
                break;
            }
        }


        // 1. Inserto en std::map (clave assetnum)
        std::string idAsset = arbol.get_assetnum();
        trees[idAsset] = arbol;
        Arbol* ptrArbol = &trees[idAsset];

        // 2. Enlazo bidireccionalmente Parque y Arbol (Arbol::isInto y Parque::_contains)
        for (auto& parque : parks) {
            if (parque.get_cod_parque() == arbol.getNumParque()) {
                parque.insertarArbol(ptrArbol);
                ptrArbol->setParque(&parque); // Relación isInto
                break;
            }
        }

        // 3. Inserto puntero en std::multimap (clave nombre común)
        treeName.insert({ptrArbol->getNbreComun(), ptrArbol});

    }
    ficheroArboles.close();
}

void ControlParques::enlazarAutomatico() {
    for (size_t i = 0; i < varieties.size(); i++) {
        Especie& actual = varieties[i];
        int tipo = actual.get_tipo_planta();

        // Recorrido de std::list<Parque> con bucle range-based for
        for (auto& p_actual : parks) { //estos bucles sirven pra vectores,mapas,listas...
            int codParque = p_actual.get_cod_parque();
            bool esPar = (codParque % 2 == 0);
            if (esPar && (tipo == ARBUSTO || tipo == CONIFERA || tipo == PALMACEA || tipo == HERB_PERENNES || tipo == FRONDOSA)) {
                p_actual.insertaEspecie(&actual);
                          } else if (!esPar && (tipo == TAPIZANTE_TREPADORA ||tipo == CACTACEA_SUCULENTA || tipo == SUBTROPICAL_TROPICAL ||
                          tipo == HERB_ANUAL || tipo == HERB_ANUALES)) {
                              p_actual.insertaEspecie(&actual);
                                                }
        }
    }
}

void ControlParques::mostrarParques() {
    for (auto& parque : parks) {
        std::cout << "  Codigo: " << std::to_string(parque.get_cod_parque())
                  << " nombre: " << parque.get_nbre_parque()
                  << " total especies: " << std::to_string(parque.get_contains().size()) << std::endl;
    }
}

bool ControlParques::borrarEspecie(std::string ncomun) {
    bool encontrado = false;

    for (auto& parque : parks) {
        std::vector<Arbol*>& arbolesparque = parque.get_contains();
        for (size_t i = 0; i < arbolesparque.size(); i++) {
            if (arbolesparque[i] != nullptr &&
                arbolesparque[i]->getEspecie() != nullptr &&
                arbolesparque[i]->getNbreComun() == ncomun) {

                arbolesparque[i]->setEspecie(nullptr);
                arbolesparque[i] = nullptr;
                }
        }
    }

    for (auto it = varieties.begin(); it != varieties.end(); ) {
        if (it->getnombre_comun() == ncomun) {
            it = varieties.erase(it); //std::vector usa erase()
            encontrado = true;
        } else {
            ++it;
        }
    }
    return encontrado;
}

void ControlParques::asignarEspecieParque(Especie *e, Parque *p) {
    for (auto& actual : parks) {
        if (actual.get_cod_parque() != p->get_cod_parque()) {
            actual.insertaEspecie(e);
            return;
        }
    }
}

int ControlParques::contarEspecieParque(std::string ncomun) {
    int contador = 0;
    for (auto& parque : parks) {
        if (parque.existeNbreCom(ncomun)) {
            contador++;
        }
    }
    return contador;
}

vector<Especie*> ControlParques::listadoEspecieSubNombre(std::string cadena) {
    vector<Especie*> resultado;
    for (int i = 0; i < varieties.size(); i++) {
        std::string actual = varieties[i].getnombre_cientifico();

        if (actual.find(cadena) != std::string::npos) {
            resultado.push_back(&varieties[i]);
        }
    }
    return resultado;
}

Parque* ControlParques::buscarParque(std::string nombre_parque) {
    ListaDEnlazada<Parque>::Iterador iter = parks.iterador();
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
    return trees.buscaIt(aux);
}

// 2. Obtener lista de árboles de un parque específico
vector<Arbol*> ControlParques::listaArbParque(const std::string &nombreParque) {
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();
    while (!it.fin()) {
        if (it.dato().getNombre() == nombreParque) {
            return it.dato().get_contains();
        }
        it.siguiente();
    }
    return vector<Arbol*>();
}

// 3. Obtener el árbol más alto de todos los parques del sistema
Arbol* ControlParques::arbolMasAlto() {
    Arbol* masAltoGlobal = nullptr;
    ListaDEnlazada<Parque>::Iterador it = parks.iterador();

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


// Contar especies distintas en un parque por su nombre
int ControlParques::contarEspecies(const std::string &nombreParque) {
    for (auto& parque : parks) {
        if (parque.getNombre() == nombreParque) {
            return parque.contarEspecies();
        }
    }
    return 0;
}

// 5. Contar tipos de plantas distintos en todos los parques
int ControlParques::contarTipos() {
    vector<int> tiposUnicos;//recorrro el buce de principio a final !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!!!!!!!!
    for (auto& parque : parks) {
        vector<Arbol*>& arboles = parque.get_contains();
        for (unsigned int i = 0; i < arboles.size(); ++i) {
            if (arboles[i] != nullptr) {
                int tipo = arboles[i]->getTipoEspecie();
                if (tipo != 0) {
                    bool yaExiste = false;
                    for (unsigned int j = 0; j < tiposUnicos.size() && !yaExiste; ++j) {
                        if (tiposUnicos[j] == tipo) {
                            yaExiste = true;
                        }
                    }
                    if (!yaExiste) {
                        tiposUnicos.push_back(tipo);
                    }
                }
            }
        }
    }
    return tiposUnicos.size();
}

// 6. Búsqueda por rango (ejercicio por parejas)
vector<Arbol*> ControlParques::buscarArbolesRango(const std::string& asNumMin, const std::string& asNumMax) {
    // Excepción si el límite inferior es mayor
    if (asNumMin > asNumMax) {
        throw std::invalid_argument("Error: El límite inferior no puede ser mayor que el superior.");
    }

    // Usamos el constructor de 1 parámetro de Arbol para crear objetos de comparación
    Arbol minArbol(asNumMin);
    Arbol maxArbol(asNumMax);

    // Asumiendo que tu atributo AVL se llama 'arbolesAVL'
    return trees.buscarRango(minArbol, maxArbol);
}