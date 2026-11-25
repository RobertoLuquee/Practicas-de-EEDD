
/**  @author Oier Fernandez de Leceta Villalmanzo ofv00003@red.ujaen.es
      @author Roberto Luque Peña rlp00041@red.ujaen.es */

#include <exception>
#include <iostream>
#include <string>
#include <vector>
 #include <algorithm>
 #include <random>
 #include <chrono>
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

        cout << "PROGRAMA DE PRUEBA 1: AJUSTE DE LA TABLA"<<endl;
        cout << "ESTADO DE LA TABLA HASH"<<endl;
        control.mostrarEstadoTabla();

        vector<string> ids = control.getIdsArboles();
        shuffle(ids.begin(), ids.end(), mt19937(random_device{}()));
        ids.resize(2000);

        cout << "PRUEBA DE RENDIMIENTO (2000 búsquedas)"<<endl;

        // Tabla hash
        auto inicio = chrono::high_resolution_clock::now();
        for (vector<string>::iterator it = ids.begin(); it != ids.end(); ++it) {
            control.buscarArbol(*it);
        }
        auto fin = chrono::high_resolution_clock::now();
        double msHash = chrono::duration<double, milli>(fin -inicio).count();

        // Lista
        inicio = chrono::high_resolution_clock::now();
        for (vector<string>::iterator it = ids.begin(); it != ids.end(); ++it) {
            control.buscarArbolLista(*it);
        }
        fin = chrono::high_resolution_clock::now();
        double msLista = chrono::duration<double, milli>(fin - inicio).count();

        cout << "Tiempo tabla hash: " << msHash << " ms" <<endl;
        cout << "Tiempo lista: " << msLista << " ms" <<endl;

    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() <<endl;
        return 1;
    }

    return 0;
}
