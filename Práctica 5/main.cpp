
/**  @author Oier Fernandez de Leceta Villalmanzo ofv00003@red.ujaen.es
      @author Roberto Luque Peña rlp00041@red.ujaen.es */

#include <exception>
#include <iostream>
#include <string>
//Arreglar caracteres especiales por pantalla
#ifdef _WIN32
#include <windows.h>
#endif

#include "ControlParques.h"
using namespace std;

//Rutas de los archivos (la configuración de CLion ejecuta el programa
//desde la carpeta "Práctica 5", que es donde están los CSV)
const string RUTA_ESPECIES = "arbolado-especies.csv";
const string RUTA_PARQUES = "parques.csv";
const string RUTA_ARBOLES = "arboladoMadrid.csv";
const string RUTA_CAJAS_NIDO = "cajas-nido.csv";

int main() {
    //Arreglar caracteres especiales por pantalla
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        // Al construir ControlParques se leen todos los ficheros y se
        // insertan los árboles en la tabla hash
        ControlParques control(
            RUTA_ESPECIES,
            RUTA_PARQUES,
            RUTA_ARBOLES,
            RUTA_CAJAS_NIDO);

        cout << "\nPROGRAMA DE PRUEBA 1: AJUSTE DE LA TABLA\n";
        cout << "\nESTADO DE LA TABLA HASH\n";
        control.mostrarEstadoTabla();
    } catch (const std::exception &error) {
        std::cerr << "\nError: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
