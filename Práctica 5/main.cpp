
#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ControlParques.h"
#include "Arbol.h"
#include "Especie.h"

/**  @author Oier Fernandez de Leceta Villalmanzo ofv00003@red.ujaen.es
      @author Roberto Luque Peña rlp00041@red.ujaen.es */

using namespace std;

float leerMedida(std::string campo)
{
    std::replace(campo.begin(), campo.end(), ',', '.');

    return campo.empty() ? -1.0f : std::stof(campo);
}

Arbol leerArbol(const std::string &linea)
{
    std::stringstream registro(linea);
    std::string campos[12];

    for (unsigned int i = 0; i < 12; ++i)
    {
        if (!std::getline(registro, campos[i], ';'))
        {
            if (i != 11 || linea.empty() || linea.back() != ';')
                throw std::runtime_error("Registro de arbol incompleto");
        }
    }

    std::replace(campos[6].begin(), campos[6].end(), ',', '.');
    std::replace(campos[7].begin(), campos[7].end(), ',', '.');

    return Arbol(
        campos[0], // ASSETNUM
        campos[1].empty() ? 0 : std::stoi(campos[1]), // NUM_PARQUE
        campos[2].empty() ? 0 : std::stoi(campos[2]), // NUM_DISTRITO
        campos[5], // NBRE_BARRIO
        campos[4].empty() ? 0 : std::stoi(campos[4]),//num_barrio
        campos[8], // CODIGO_ESPECIE
        campos[9], // ESPECIE
        campos[6].empty() ? 0.0 : std::stod(campos[6]), // X
        campos[7].empty() ? 0.0 : std::stod(campos[7]), // Y
        leerMedida(campos[10]), // PERIMETRO
        leerMedida(campos[11])  // ALTURA_TOTAL
    );
}



int main()
{
    try
    {


        std::cout << "\nPROGRAMA DE PRUEBA II\n"
                  << "-------------------\n\n";

        ControlParques control(
            "./arbolado-especies.csv",
            "./parques.csv",
            "./arboladoMadrid.csv");

std::cout << "\n--- PUNTO 1: BUSQUEDA DE ARBOLES ESPECIFICOS ---\n";
        const std::string idsGuion[] = {"6951831", "10152826", "8887777", "6906686"};

        for (const std::string &id : idsGuion)
        {
            Arbol *arbol = control.buscarArbol(id);

            if (arbol == nullptr)
            {
                std::cout << "Arbol ID " << id << ": NO EXISTE\n";
            }
            else
            {
                std::cout << "ID: " << arbol->get_assetnum()
                          << " | Codigo Parque: " << arbol->getNumParque()
                          << " | Nombre comun: " << arbol->getNbreComun()
                          << " | Nombre cientifico: " << arbol->getNbreCientifico()
                          << " | Tipo de planta: " << arbol->getTipo()
                          << '\n';
            }
        }

std::cout << "\n--- PUNTO 2: ESPECIE MAS COMUN EN 'PARQUE PRINCESA LEONOR' ---\n";
        Parque *princesa = control.buscarParque("PARQUE PRINCESA LEONOR");
        std::string especieMasComun = "Ninguna";
        if (princesa != nullptr && princesa->especieMasComun() != nullptr)
            especieMasComun = princesa->especieMasComun()->getnombre_comun();
        std::cout << "La especie mas comun es: " << especieMasComun << '\n';

        std::cout << "\n--- PUNTO 3: PARQUES CON AL MENOS UN 'abeto' ---\n";
        std::vector<Parque*> parquesAbeto = control.listarParquesArbol("Abeto");
        if (parquesAbeto.size() == 0)
        {
            std::cout << "No se encontraron parques con la especie 'abeto'.\n";
        }
        else
        {
            for (unsigned int i = 0; i < parquesAbeto.size(); ++i)
            {
                Parque *p = parquesAbeto[i];
                std::cout << "Parque " << i + 1 << ": " << p->get_nbre_parque()
                          << " (Codigo Parque: " << p->get_cod_parque() << ")\n";
            }
        }

        std::cout << "\n--- PUNTO 4: BUSQUEDA DE PINOS ---\n";
        std::vector<Arbol*> pinoResinero = control.buscarArbolNcomun("Pino resinero");
        std::cout << "Total ejemplares 'Pino resinero': " << pinoResinero.size() << '\n';

        std::vector<Arbol*> empiezanPorPino = control.buscarArbolNcomunComienzo("Pino");
        std::cout << "Total ejemplares que empiezan por 'Pino': " << empiezanPorPino.size() << '\n';

        std::cout << "\n--- PUNTO 5: ARBOLES EN BARRIOS 43 Y 91 ---\n";
        std::cout << "Numero de arboles en el barrio 43: " << control.contarArbolesBarrio(43) << '\n';
        std::cout << "Numero de arboles en el barrio 91: " << control.contarArbolesBarrio(91) << '\n';

        // TRABAJO POR PAREJAS
        std::cout << "\n--- TRABAJO POR PAREJAS: 'Pino' EN DISTRITO 9 ---\n";
        std::vector<Arbol*> pinosDistrito9 = control.buscarArbolesPorEspecieYDistrito("Pino", 9);
        std::cout << "Resultados encontrados: " << pinosDistrito9.size() << "\n\n";

        for (unsigned int i = 0; i < pinosDistrito9.size(); ++i)
        {
            Arbol *arbol = pinosDistrito9[i];

            std::cout << "ID (assetnum): " << arbol->get_assetnum()
                      << " | Barrio: " << arbol->getNbreBarrio();

            Parque *parqueAsociado = arbol->isInto;
            if (parqueAsociado != nullptr)
            {
                std::cout << " | Parque: " << parqueAsociado->get_nbre_parque() << '\n';
            }
            else
            {
                std::cout << " | Parque: Sin parque asignado\n";
            }
        }
    }
    catch (const std::exception &error)
    {
        std::cerr << "\nError: " << error.what() << '\n';
        return 1;
    }

    return 0;
}