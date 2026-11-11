#ifndef CONTROLPARQUES_H
#define CONTROLPARQUES_H

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Arbol.h"
#include "Parque.h"
#include "Especie.h"
#include "VDinamico.h"

class ControlParques {
private:
    std::list<Parque> parks;
    std::map<std::string, Arbol> trees;
    std::map<std::string, Especie> species;

public:
    ControlParques(const std::string &fichEspecies,
                   const std::string &fichParques,
                   const std::string &fichArboles);

    // Métodos del Programa de Prueba I & II
    Parque* buscarParque(std::string nombre);
    Arbol* buscarArbol(const std::string &assetnum);
    std::vector<Arbol*> listaArbParque(const std::string &nombreParque);
    Arbol* arbolMasAlto();
    std::vector<Arbol*> buscarArbolesRango(const std::string &asNumMin, const std::string &asNumMax);

    unsigned int contarEspecies(const std::string &nombreParque);
    unsigned int contarTipos();

    // Métodos específicos del guión (Puntos 1 a 5 y Trabajo por parejas)
    std::string especieMasComunParque(const std::string &nombreParque);
    VDinamico<Parque*> parquesConEspecie(const std::string &nombreComun);
    VDinamico<Arbol*> buscarArbolesPorEspecie(const std::string &nombreComun);
    VDinamico<Arbol*> buscarArbolesQueEmpiezanPor(const std::string &prefijo);
    int contarArbolesBarrio(int numBarrio);
    VDinamico<Arbol*> buscarArbolesPorEspecieYDistrito(const std::string &nbreComun, int numDistrito);
};

#endif
