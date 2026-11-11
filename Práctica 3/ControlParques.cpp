//
// Created by Oier Universidad on 13/10/2026.
//

#include "ControlParques.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Constructor (Mantener tu carga de ficheros existente)
ControlParques::ControlParques(const std::string &fichEspecies,
                               const std::string &fichParques,
                               const std::string &fichArboles)
{
    // Carga de ficheros...
}

Parque* ControlParques::buscarParque(std::string nombre)
{
    for (auto &parque : parks)
    {
        if (parque.getNombre() == nombre)
            return &parque;
    }
    return nullptr;
}

Arbol* ControlParques::buscarArbol(const std::string &assetnum)
{
    auto it = trees.find(assetnum);
    if (it != trees.end())
        return &(it->second);
    return nullptr;
}

std::vector<Arbol*> ControlParques::listaArbParque(const std::string &nombreParque)
{
    std::vector<Arbol*> resultado;
    for (auto &par : trees)
    {
        if (par.second.isInto != nullptr && par.second.isInto->getNombre() == nombreParque)
        {
            resultado.push_back(&(par.second));
        }
    }
    return resultado;
}

Arbol* ControlParques::arbolMasAlto()
{
    Arbol* masAlto = nullptr;
    float maxAltura = -1.0f;

    for (auto &par : trees)
    {
        if (par.second.getAltura() > maxAltura)
        {
            maxAltura = par.second.getAltura();
            masAlto = &(par.second);
        }
    }
    return masAlto;
}

std::vector<Arbol*> ControlParques::buscarArbolesRango(const std::string &asNumMin, const std::string &asNumMax)
{
    std::vector<Arbol*> resultado;
    auto itLow = trees.lower_bound(asNumMin);
    auto itUp = trees.upper_bound(asNumMax);

    for (auto it = itLow; it != itUp; ++it)
    {
        resultado.push_back(&(it->second));
    }
    return resultado;
}

unsigned int ControlParques::contarEspecies(const std::string &nombreParque)
{
    std::map<std::string, bool> especiesUnicas;
    for (auto &par : trees)
    {
        if (par.second.isInto != nullptr && par.second.isInto->getNombre() == nombreParque)
        {
            especiesUnicas[par.second.getCodEspecie()] = true;
        }
    }
    return especiesUnicas.size();
}

unsigned int ControlParques::contarTipos()
{
    std::map<std::string, bool> tiposUnicos;
    for (auto &par : trees)
    {
        tiposUnicos[par.second.getTipo()] = true;
    }
    return tiposUnicos.size();
}

// ---------------------------------------------------------
// MÉTODOS DEL GUIÓN (Puntos 2 a 5 y Parejas)
// ---------------------------------------------------------

std::string ControlParques::especieMasComunParque(const std::string &nombreParque)
{
    std::map<std::string, int> conteoEspecies;
    for (auto &par : trees)
    {
        Arbol &a = par.second;
        if (a.isInto != nullptr && a.isInto->getNombre() == nombreParque)
        {
            conteoEspecies[a.getNbreComun()]++;
        }
    }

    std::string masComun = "Ninguna";
    int maxConteo = 0;
    for (auto &par : conteoEspecies)
    {
        if (par.second > maxConteo)
        {
            maxConteo = par.second;
            masComun = par.first;
        }
    }
    return masComun;
}

VDinamico<Parque*> ControlParques::parquesConEspecie(const std::string &nombreComun)
{
    VDinamico<Parque*> resultado;
    std::string especieBuscada = nombreComun;
    std::transform(especieBuscada.begin(), especieBuscada.end(), especieBuscada.begin(), ::tolower);

    for (auto &parque : parks)
    {
        bool tieneEspecie = false;
        for (auto &parTree : trees)
        {
            Arbol &a = parTree.second;
            if (a.isInto == &parque)
            {
                std::string nombreArbol = a.getNbreComun();
                std::transform(nombreArbol.begin(), nombreArbol.end(), nombreArbol.begin(), ::tolower);
                if (nombreArbol.find(especieBuscada) != std::string::npos)
                {
                    tieneEspecie = true;
                    break;
                }
            }
        }
        if (tieneEspecie)
            resultado.insertar(&parque);
    }
    return resultado;
}

VDinamico<Arbol*> ControlParques::buscarArbolesPorEspecie(const std::string &nombreComun)
{
    VDinamico<Arbol*> resultado;
    for (auto &par : trees)
    {
        if (par.second.getNbreComun() == nombreComun)
        {
            resultado.insertar(&(par.second));
        }
    }
    return resultado;
}

VDinamico<Arbol*> ControlParques::buscarArbolesQueEmpiezanPor(const std::string &prefijo)
{
    VDinamico<Arbol*> resultado;
    for (auto &par : trees)
    {
        if (par.second.getNbreComun().rfind(prefijo, 0) == 0)
        {
            resultado.insertar(&(par.second));
        }
    }
    return resultado;
}

int ControlParques::contarArbolesBarrio(int numBarrio)
{
    int contador = 0;
    for (auto &par : trees)
    {
        if (par.second.getNumBarrio() == numBarrio)
        {
            contador++;
        }
    }
    return contador;
}

VDinamico<Arbol*> ControlParques::buscarArbolesPorEspecieYDistrito(const std::string &nbreComun, int numDistrito)
{
    VDinamico<Arbol*> resultado;
    for (auto &par : trees)
    {
        Arbol &a = par.second;
        if (a.getNbreComun().find(nbreComun) != std::string::npos && a.getNumDistrito() == numDistrito)
        {
            resultado.insertar(&a);
        }
    }
    return resultado;
}