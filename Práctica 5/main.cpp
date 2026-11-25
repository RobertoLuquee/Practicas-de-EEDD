#include <algorithm>
#include <chrono>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ControlParques.h"
#include "Arbol.h"
#include "Especie.h"
#include "CajaNido.h"
#include "Parque.h"

/**  @author Oier Fernandez de Leceta Villalmanzo ofv00003@red.ujaen.es
      @author Roberto Luque Peña rlp00041@red.ujaen.es */

using namespace std;

int main()
{
    try
    {
        std::cout << "\nPROGRAMA DE PRUEBA II (PRACTICA 5)\n"
                  << "----------------------------------\n\n";

        ControlParques control(
                    "./arbolado-especies.csv",
                    "./parques.csv",
                    "./arboladoMadrid.csv",
                    "./cajas-nido.csv"
                );

       // ---------------------------------------------------------
        // 1. Buscar assetnum: 6925456, 6635839, 5222166
        // ---------------------------------------------------------
        std::cout << "\n--- ACCION 1: BUSQUEDA DE ARBOLES ESPECIFICOS ---\n";
        std::vector<std::string> idsGuion = {"6925456", "6635839", "5222166"};

        for (std::string &id : idsGuion)
        {
            Arbol *arbol = control.buscarArbol(id);
            if (arbol == nullptr)
            {
                std::cout << "Arbol ID " << id << ": NO EXISTE\n";
            }
            else
            {
                std::cout << "ID: " << arbol->get_assetnum()
                          << " | Especie: " << arbol->getNbreComun()
                          << " (" << arbol->getNbreCientifico() << ")"
                          << " | Altura: " << arbol->getAltura() << " m"
                          << " | Num Parque: " << arbol->getNumParque() << '\n';
            }
        }

        // ---------------------------------------------------------
        // 2. Árboles con caja nido asociada en el distrito "CENTRO"
        // ---------------------------------------------------------
        std::cout << "\n--- ACCION 2: ARBOLES CON CAJA NIDO EN 'CENTRO' ---\n";
        std::string distritoCentro = "CENTRO";
        std::vector<Arbol*> arbCentro = control.arbolesCajaDistrito(distritoCentro);
        std::cout << "Numero de arboles encontrados: " << arbCentro.size() << "\n";

        for (Arbol* a : arbCentro)
        {
            std::cout << "  - ID: " << a->get_assetnum()
                      << " | Especie: " << a->getNbreComun()
                      << " | Distrito: " << distritoCentro << "\n";
        }

        // ---------------------------------------------------------
        // 3. Total de cajas asociadas y sin asociar
        // ---------------------------------------------------------
        std::cout << "\n--- ACCION 3: CONTEO TOTAL DE CAJAS NIDO ---\n";
        unsigned int asociadas = control.contarCajasEnArbol();
        unsigned int sinAsociar = control.getTotalCajas() - asociadas;
        std::cout << "Cajas nido asociadas a un arbol: " << asociadas << "\n";
        std::cout << "Cajas nido sin asociar: " << sinAsociar << "\n";

        // ---------------------------------------------------------
        // 4. Todas las cajas nido ubicadas en el distrito "CENTRO"
        // ---------------------------------------------------------
        std::cout << "\n--- ACCION 4: CAJAS NIDO EN DISTRITO 'CENTRO' ---\n";
        std::vector<CajaNido*> cajasCentro = control.cajasEnDistrito(distritoCentro);
        std::cout << "Numero de cajas encontradas en CENTRO: " << cajasCentro.size() << "\n";

        for (unsigned int i = 0; i < cajasCentro.size(); ++i)
        {
            CajaNido* c = cajasCentro[i];
            std::cout << "  - Caja " << i + 1 << ": ";
            if (c->estaEnArbol())
                std::cout << "Asociada al arbol ID: " << c->getArbol()->get_assetnum() << "\n";
            else
                std::cout << "No asociada a ningun arbol\n";
        }

        // ---------------------------------------------------------
        // 5. Cajas de las líneas {70, 75, 80, 85, 90} del fichero
        // ---------------------------------------------------------
        // La línea 1 es la cabecera y la línea 2 es nests[0] -> índice = línea - 2
        std::cout << "\n--- ACCION 5: COMPROBACION LINEAS {70, 75, 80, 85, 90} ---\n";
        std::vector<int> lineas = {70, 75, 80, 85, 90};
        const std::vector<CajaNido>& todasCajas = control.getNests();

        for (int numLinea : lineas)
        {
            unsigned int idx = numLinea - 2;
            if (idx < todasCajas.size())
            {
                const CajaNido& c = todasCajas[idx];
                std::cout << "Linea " << numLinea
                          << " | UTM Caja: (" << c.get_coord().getX() << ", " << c.get_coord().getY() << ")";

                if (c.estaEnArbol())
                {
                    Arbol* a = c.getArbol();
                    double dist2 = c.get_coord().distancia2(a->getCoord());
                    double distMetros = std::sqrt(dist2);

                    std::cout << " | Arbol ID: " << a->get_assetnum()
                              << " | UTM Arbol: (" << a->getCoord().getX() << ", " << a->getCoord().getY() << ")"
                              << " | Distancia: " << distMetros << " m (d^2 = " << dist2
                              << " -> " << (dist2 < 100.0 ? "CUMPLE < 100" : "NO CUMPLE") << ")\n";
                }
                else
                {
                    std::cout << " | Sin arbol asociado\n";
                }
            }
        }

        // ---------------------------------------------------------
        // 6. Todos los parques que tengan al menos alguna caja nido
        // ---------------------------------------------------------
        std::cout << "\n--- ACCION 6: PARQUES CON AL MENOS UNA CAJA NIDO ---\n";
        std::vector<Parque*> parquesCajas = control.parquesConCajaNido();
        std::cout << "Total parques con cajas nido: " << parquesCajas.size() << "\n";

        for (Parque* p : parquesCajas)
        {
            std::cout << "  - Codigo: " << p->get_cod_parque()
                      << " | Nombre: " << p->get_nbre_parque() << "\n";
        }
    }
    catch (const std::exception &error)
    {
        std::cerr << "\nError: " << error.what() << '\n';
        return 1;
    }

    return 0;
}