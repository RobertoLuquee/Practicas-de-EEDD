
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
#include "AVL.h"

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

void cargarAVL(const std::string &ruta, AVL<Arbol> &avl)
{
    std::ifstream fichero(ruta);

    if (!fichero.is_open())
        throw std::runtime_error("No se puede abrir: " + ruta);

    std::string linea;
    std::getline(fichero, linea); // Saltar cabecera.

    while (std::getline(fichero, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        if (linea.empty())
            continue;

        Arbol arbol = leerArbol(linea);

        if (!avl.inserta(arbol))
            throw std::runtime_error(
                "Identificador duplicado: " + arbol.get_assetnum());
    }
}

void cargarVector(
    const std::string &ruta, VDinamico<Arbol> &arboles)
{
    std::ifstream fichero(ruta);

    if (!fichero.is_open())
        throw std::runtime_error("No se puede abrir: " + ruta);

    std::string linea;
    std::getline(fichero, linea); // Saltar cabecera.

    while (std::getline(fichero, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        if (linea.empty())
            continue;

        Arbol arbol = leerArbol(linea);
        arboles.insertar(arbol);
    }
}

int main()
{
    try
    {
        std::cout << "PROGRAMA DE PRUEBA I\n"
                  << "-------------------\n\n";

        const std::string ruta = "./arboladoMadrid.csv";

        AVL<Arbol> avl;
        VDinamico<Arbol> arboles;
        VDinamico<std::string> identificadores;

        // 1. Leer los árboles e insertarlos en el AVL.
        cargarAVL(ruta, avl);

        // 2. Leer nuevamente los árboles y almacenarlos en el vector.
        cargarVector(ruta, arboles);

        std::cout << "Arboles en el AVL: "
                  << avl._numelementos() << '\n';

        std::cout << "Arboles en el vector: "
                  << arboles.get__tlogico() << '\n';

        if (avl._numelementos() != arboles.get__tlogico())
            throw std::runtime_error(
                "Las estructuras contienen cantidades diferentes");

        // 3. Seleccionar 500 identificadores: posiciones
        // 0, 250, 500, ..., 124750.
        const unsigned int numeroBusquedas = 500;
        const unsigned int salto = 250;

        if (arboles.get__tlogico() <= (numeroBusquedas - 1) * salto)
            throw std::runtime_error(
                "No hay suficientes arboles para seleccionar la muestra");

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            std::string id = arboles[i * salto].get_assetnum();
            identificadores.insertar(id);
        }

        // Preparar las claves antes de empezar a medir.
        VDinamico<Arbol> claves;

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            Arbol clave(identificadores[i]);
            claves.insertar(clave);
        }

        // 4. Buscar los 500 árboles en el AVL.
        unsigned int encontradosAVL = 0;

        auto inicioAVL = std::chrono::steady_clock::now();

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            if (avl.buscaRec(claves[i]) != nullptr)
                ++encontradosAVL;
        }

        auto finAVL = std::chrono::steady_clock::now();

        // 5. Buscar linealmente los mismos árboles en el vector.
        unsigned int encontradosVector = 0;

        auto inicioVector = std::chrono::steady_clock::now();

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            for (unsigned int j = 0; j < arboles.get__tlogico(); ++j)
            {
                if (arboles[j] == claves[i])
                {
                    ++encontradosVector;
                    break;
                }
            }
        }

        auto finVector = std::chrono::steady_clock::now();

        // 6. Mostrar los resultados y los tiempos en milisegundos.
        double tiempoAVL =
            std::chrono::duration<double, std::milli>(
                finAVL - inicioAVL)
                .count();

        double tiempoVector =
            std::chrono::duration<double, std::milli>(
                finVector - inicioVector)
                .count();

        std::cout << "\nEncontrados en AVL: "
                  << encontradosAVL << '/' << numeroBusquedas;

        std::cout << "\nEncontrados en vector: "
                  << encontradosVector << '/' << numeroBusquedas;

        std::cout << "\n\nTiempo AVL: "
                  << tiempoAVL << " ms";

        std::cout << "\nTiempo busqueda lineal: "
                  << tiempoVector << " ms\n";

        if (encontradosAVL != numeroBusquedas ||
            encontradosVector != numeroBusquedas)
        {
            throw std::runtime_error(
                "Alguna busqueda no ha encontrado el arbol esperado");
        }

        if (tiempoAVL < tiempoVector)
            std::cout << "El AVL ha sido mas rapido en esta medicion.\n";
        else
            std::cout << "El AVL no ha sido mas rapido en esta medicion.\n";

        // 7. Mostrar la altura.
        std::cout << "\nAltura del AVL: "
                  << avl.altura() << '\n';

        // 8. Mostrar los 100 primeros árboles en inorden.
        VDinamico<Arbol *> ordenados = avl.recorreInorden();

        std::cout << "\nPrimeros 100 arboles en inorden:\n";

        for (unsigned int i = 0;
             i < 100 && i < ordenados.get__tlogico(); ++i)
        {
            Arbol *arbol = ordenados[i];

            std::cout << i + 1
                      << ". ID: " << arbol->get_assetnum() << endl;
        }


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