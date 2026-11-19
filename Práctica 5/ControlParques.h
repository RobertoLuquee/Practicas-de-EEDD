#ifndef CONTROLPARQUES_H
#define CONTROLPARQUES_H

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Arbol.h"
#include "Parque.h"
#include "Especie.h"

class ControlParques {
private:
    std::list<Parque> parks;
    std::map<std::string, Arbol> trees;
    std::vector<Especie> varieties;
    std::multimap<std::string, Arbol*> treeName;

public:
    ControlParques(const std::string &fichEspecies,
                   const std::string &fichParques,
                   const std::string &fichArboles);

    // Métodos de las prácticas anteriores
    Parque* buscarParque(std::string nombre);
    Arbol* buscarArbol(const std::string &assetnum);
    std::vector<Arbol*> listaArbParque(const std::string &nombreParque);
    Arbol* arbolMasAlto();
    std::vector<Arbol*> buscarArbolesRango(const std::string &asNumMin, const std::string &asNumMax);
    unsigned int contarEspecies(const std::string &nombreParque);
    unsigned int contarTipos();

    // Métodos nuevos de la práctica 4
    std::vector<Parque*> listarParquesArbol(const std::string &nbreComun);
    std::vector<Arbol*> buscarArbolNcomun(const std::string &nbreComun);
    std::vector<Arbol*> buscarArbolNcomunComienzo(const std::string &comienzo);
    int contarArbolesBarrio(int numBarrio);
    std::vector<Arbol*> buscarArbolesPorEspecieYDistrito(const std::string &nbreComun, int numDistrito);
};

#endif
