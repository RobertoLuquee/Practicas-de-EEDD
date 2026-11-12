//
// Created by Oier Universidad on 13/10/2026.
//

#include "ControlParques.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

//ESTA FUNCIÓN ME HACE FALTA PORQUE SI NO NO ME LEE BIEN EL FICHERO POR LAS COMILLAS Y COMAS DENTRO DE ALGUNOS CAMPOS
std::vector<std::string> separarLinea(const std::string &linea, char separador)
{
    std::vector<std::string> campos;
    std::string campo = "";
    bool dentroComillas = false;

    for (unsigned int i = 0; i < linea.size(); i++)
    {
        if (linea[i] == '"')
        {
            // Dos comillas seguidas dentro de un campo son una comilla normal
            if (dentroComillas && i + 1 < linea.size() && linea[i + 1] == '"')
            {
                campo += '"';
                i++;
            }
            else
            {
                dentroComillas = !dentroComillas;
            }
        }
        else if (linea[i] == separador && !dentroComillas)
        {
            campos.push_back(campo);
            campo = "";
        }
        else
        {
            campo += linea[i];
        }
    }
    campos.push_back(campo);
    return campos;
}

// Pasa el texto del fichero de especies al enum TipoPlanta
TipoPlanta leerTipo(std::string tipo)
{
    std::replace(tipo.begin(), tipo.end(), '/', '_');

    if (tipo == "CONIFERA") return CONIFERA;
    if (tipo == "PALMACEA") return PALMACEA;
    if (tipo == "HERB_PERENNES") return HERB_PERENNES;
    if (tipo == "FRONDOSA") return FRONDOSA;
    if (tipo == "TAPIZANTE_TREPADORA") return TAPIZANTE_TREPADORA;
    if (tipo == "CACTACEA_SUCULENTA") return CACTACEA_SUCULENTA;
    if (tipo == "SUBTROPICAL_TROPICAL") return SUBTROPICAL_TROPICAL;
    if (tipo == "HERB_ANUAL") return HERB_ANUAL;
    if (tipo == "HERB_ANUALES") return HERB_ANUALES;
    return ARBUSTO;
}

ControlParques::ControlParques(const std::string &fichEspecies,
                               const std::string &fichParques,
                               const std::string &fichArboles)
{
    std::string linea;

    // 1. Leer el fichero de especies y guardarlas en el vector
    std::ifstream fEspecies(fichEspecies);
    if (!fEspecies.is_open())
        throw std::runtime_error("No se puede abrir: " + fichEspecies);

    std::getline(fEspecies, linea); // cabecera
    while (std::getline(fEspecies, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        if (linea.empty())
            continue;

        std::vector<std::string> campos = separarLinea(linea, ',');
        while (campos.size() < 4)
            campos.push_back("");

        varieties.push_back(Especie(campos[0], campos[1], campos[2], leerTipo(campos[3])));
    }
    fEspecies.close();

    // Mapa auxiliar codigo -> especie para enlazar los arboles rapido.
    // El vector ya no cambia de tamaño, asi que los punteros no se invalidan.
    std::map<std::string, Especie*> especiePorCodigo;
    std::vector<Especie>::iterator itVar;
    for (itVar = varieties.begin(); itVar != varieties.end(); itVar++)
        especiePorCodigo[itVar->getCodigo()] = &(*itVar);

    // Leo el fichero de parques y los guardo en la lista
    std::ifstream fParques(fichParques);
    if (!fParques.is_open())
        throw std::runtime_error("No se puede abrir: " + fichParques);

    std::getline(fParques, linea); // cabecera
    while (std::getline(fParques, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        if (linea.empty())
            continue;

        std::vector<std::string> campos = separarLinea(linea, ',');
        if (campos.size() < 2)
            continue;

        parks.push_back(Parque(std::stoi(campos[0]), campos[1]));
    }
    fParques.close();

    // Mapa auxiliar codigo -> parque (los elementos de una list no se mueven)
    std::map<int, Parque*> parquePorCodigo;
    std::list<Parque>::iterator itPar;
    for (itPar = parks.begin(); itPar != parks.end(); itPar++)
        parquePorCodigo[itPar->get_cod_parque()] = &(*itPar);

    // Leo los arboles, los guardo en el map y hago los enlaces
    std::ifstream fArboles(fichArboles);
    if (!fArboles.is_open())
        throw std::runtime_error("No se puede abrir: " + fichArboles);

    std::getline(fArboles, linea); // cabecera
    while (std::getline(fArboles, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        if (linea.empty())
            continue;


        std::vector<std::string> campos = separarLinea(linea, ';');
        while (campos.size() < 12)
            campos.push_back("");

        // Cambiar la coma decimal por punto
        for (int i = 6; i < 12; i++)
            std::replace(campos[i].begin(), campos[i].end(), ',', '.');

        Arbol arbol(
            campos[0],
            campos[1].empty() ? 0 : std::stoi(campos[1]),
            campos[2].empty() ? 0 : std::stoi(campos[2]),
            campos[5],
            campos[4].empty() ? 0 : std::stoi(campos[4]),
            campos[8],
            campos[9],
            campos[6].empty() ? 0.0 : std::stod(campos[6]),
            campos[7].empty() ? 0.0 : std::stod(campos[7]),
            campos[10].empty() ? -1.0f : std::stof(campos[10]),
            campos[11].empty() ? -1.0f : std::stof(campos[11])
        );

        // Insertamos en el map y trabajamos con el arbol que esta DENTRO del map,
        // no con la variable local (si no, los punteros quedarian colgando)
        std::pair<std::map<std::string, Arbol>::iterator, bool> resultado =
            trees.insert(std::make_pair(campos[0], arbol));
        Arbol &arbolMapa = resultado.first->second;

        // Enlace arbol -> especie
        std::map<std::string, Especie*>::iterator itEspecie = especiePorCodigo.find(campos[8]);
        if (itEspecie != especiePorCodigo.end())
            arbolMapa.setEspecie(itEspecie->second);

        // Enlace parque -> arbol y arbol -> parque (isInto)
        std::map<int, Parque*>::iterator itParque = parquePorCodigo.find(arbolMapa.getNumParque());
        if (itParque != parquePorCodigo.end())
        {
            itParque->second->insertarArbol(&arbolMapa);
            arbolMapa.setParque(itParque->second);
        }

        // Multimap con clave el nombre comun
        treeName.insert(std::make_pair(arbolMapa.getNbreComun(), &arbolMapa));
    }
    fArboles.close();
}

Parque* ControlParques::buscarParque(std::string nombre)
{
    std::list<Parque>::iterator it;
    for (it = parks.begin(); it != parks.end(); it++)
    {
        if (it->getNombre() == nombre)
            return &(*it);
    }
    return nullptr;
}

Arbol* ControlParques::buscarArbol(const std::string &assetnum)
{
    std::map<std::string, Arbol>::iterator it = trees.find(assetnum);
    if (it != trees.end())
        return &(it->second);
    return nullptr;
}

std::vector<Arbol*> ControlParques::listaArbParque(const std::string &nombreParque)
{
    std::vector<Arbol*> resultado;
    Parque *parque = buscarParque(nombreParque);
    if (parque != nullptr)
        resultado = parque->get_contains();
    return resultado;
}

Arbol* ControlParques::arbolMasAlto()
{
    Arbol* masAlto = nullptr;
    float maxAltura = -1.0f;

    std::map<std::string, Arbol>::iterator it;
    for (it = trees.begin(); it != trees.end(); it++)
    {
        if (it->second.getAltura() > maxAltura)
        {
            maxAltura = it->second.getAltura();
            masAlto = &(it->second);
        }
    }
    return masAlto;
}

std::vector<Arbol*> ControlParques::buscarArbolesRango(const std::string &asNumMin, const std::string &asNumMax)
{
    std::vector<Arbol*> resultado;
    std::map<std::string, Arbol>::iterator itLow = trees.lower_bound(asNumMin);
    std::map<std::string, Arbol>::iterator itUp = trees.upper_bound(asNumMax);
    std::map<std::string, Arbol>::iterator it;

    for (it = itLow; it != itUp; it++)
    {
        resultado.push_back(&(it->second));
    }
    return resultado;
}

unsigned int ControlParques::contarEspecies(const std::string &nombreParque)
{
    Parque *parque = buscarParque(nombreParque);
    if (parque == nullptr)
        return 0;
    return parque->contarEspecies();
}

unsigned int ControlParques::contarTipos()
{
    std::map<int, bool> tiposUnicos;
    std::vector<Especie>::iterator it;
    for (it = varieties.begin(); it != varieties.end(); it++)
    {
        tiposUnicos[it->get_tipo_planta()] = true;
    }
    return tiposUnicos.size();
}


// Parques que tienen al menos un arbol con ese nombre comun (sin repetir)
std::vector<Parque*> ControlParques::listarParquesArbol(const std::string &nbreComun)
{
    std::vector<Parque*> resultado;
    std::pair<std::multimap<std::string, Arbol*>::iterator,
              std::multimap<std::string, Arbol*>::iterator> rango = treeName.equal_range(nbreComun);
    std::multimap<std::string, Arbol*>::iterator it;

    for (it = rango.first; it != rango.second; it++)
    {
        Parque *parque = it->second->getParque();
        if (parque != nullptr &&
            std::find(resultado.begin(), resultado.end(), parque) == resultado.end())
        {
            resultado.push_back(parque);
        }
    }
    return resultado;
}

// Todos los arboles con ese nombre comun exacto
std::vector<Arbol*> ControlParques::buscarArbolNcomun(const std::string &nbreComun)
{
    std::vector<Arbol*> resultado;
    std::pair<std::multimap<std::string, Arbol*>::iterator,
              std::multimap<std::string, Arbol*>::iterator> rango = treeName.equal_range(nbreComun);
    std::multimap<std::string, Arbol*>::iterator it;

    for (it = rango.first; it != rango.second; it++)
    {
        resultado.push_back(it->second);
    }
    return resultado;
}

// Todos los arboles cuyo nombre comun empieza por "comienzo"
std::vector<Arbol*> ControlParques::buscarArbolNcomunComienzo(const std::string &comienzo)
{
    std::vector<Arbol*> resultado;
    std::multimap<std::string, Arbol*>::iterator it = treeName.lower_bound(comienzo);

    // Como el multimap esta ordenado, los que empiezan igual van todos seguidos
    while (it != treeName.end() && it->first.compare(0, comienzo.size(), comienzo) == 0)
    {
        resultado.push_back(it->second);
        it++;
    }
    return resultado;
}

int ControlParques::contarArbolesBarrio(int numBarrio)
{
    int contador = 0;
    std::map<std::string, Arbol>::iterator it;
    for (it = trees.begin(); it != trees.end(); it++)
    {
        if (it->second.getNumBarrio() == numBarrio)
        {
            contador++;
        }
    }
    return contador;
}

std::vector<Arbol*> ControlParques::buscarArbolesPorEspecieYDistrito(const std::string &nbreComun, int numDistrito)
{
    std::vector<Arbol*> resultado;
    std::pair<std::multimap<std::string, Arbol*>::iterator,
              std::multimap<std::string, Arbol*>::iterator> rango = treeName.equal_range(nbreComun);
    std::multimap<std::string, Arbol*>::iterator it;

    for (it = rango.first; it != rango.second; it++)
    {
        if (it->second->getNumDistrito() == numDistrito)
        {
            resultado.push_back(it->second);
        }
    }
    return resultado;
}
