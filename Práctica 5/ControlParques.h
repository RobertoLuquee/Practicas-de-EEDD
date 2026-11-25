#ifndef CONTROLPARQUES_H
#define CONTROLPARQUES_H

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Arbol.h"
#include "Parque.h"
#include "Especie.h"
#include "CajaNido.h"
#include "ThashArbol.h"

class ControlParques {
private:
    std::map <int,Parque> parks;
    ThashArbol trees;
    std::map<std::string,Especie> varieties;
    std::multimap<std::string, Arbol*> treeName;
    std::vector <CajaNido> nests;

    unsigned long djb2(const char* str);

public:
    ControlParques(const std::string &fichEspecies,
                   const std::string &fichParques,
                   const std::string &fichArboles,
                   const std::string &fichCajas);


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

    Arbol* buscarArbol(std::string& assetnum);
    std::vector<Arbol*> arbolesCajaDistrito(std::string& ndistrito);
    unsigned int contarCajasEnArbol();
    std::vector<CajaNido*> cajasEnDistrito(std::string& nbre_distrito);
    unsigned int tamTabla();
    void mostrarEstadoTabla();
};

#endif
