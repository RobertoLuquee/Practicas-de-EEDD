/**  @author Oier Fernandez de Leceta Villalmanzo ofv00003@red.ujaen.es
      @author Roberto Luque Peña rlp00041@red.ujaen.es */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
//Arreglar caracteres especiales por pantalla
#ifdef _WIN32
#include <windows.h>
#endif

#include "ControlParques.h"
#include "Arbol.h"
#include "CajaNido.h"
#include "Parque.h"
using namespace std;

//Rutas de los archivos (la configuración de CLion ejecuta el programa
//desde la carpeta "Práctica 5", que es donde están los CSV)
const string RUTA_ESPECIES = "arbolado-especies.csv";
const string RUTA_PARQUES = "parques.csv";
const string RUTA_ARBOLES = "arboladoMadrid.csv";
const string RUTA_CAJAS_NIDO = "cajas-nido.csv";


/**
 * @brief Muestra una posición UTM con sus decimales
 */
void mostrarCoordenadas(const UTM &coord) {
    cout << fixed << setprecision(3) << "(" << coord.getX() << ", " << coord.getY() << ")"
            << defaultfloat << setprecision(6);
}

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


        // PROGRAMA DE PRUEBA 1

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

        // PROGRAMA DE PRUEBA 2
        cout << "\nPROGRAMA DE PRUEBA 2\n";

        cout << "\nAPARTADO 1: BÚSQUEDA DE ÁRBOLES POR ASSETNUM\n";
        const string ARBOLES_APARTADO_1[] = {"6925456", "6635839", "5222166"};
        for (const string &assetnum: ARBOLES_APARTADO_1) {
            Arbol *arbol = control.buscarArbol(assetnum);
            if (arbol == nullptr) {
                cout << "\tÁrbol " << assetnum << ": no encontrado" << endl;
                continue;
            }
            cout << "\tÁrbol " << assetnum << ": especie " << arbol->getNbreComun()
                    << " (" << arbol->getNbreCientifico() << "), altura " << arbol->getAltura()
                    << " m, parque " << arbol->getNumParque() << endl;
        }

        cout << "\nAPARTADO 2: ÁRBOLES CON CAJA NIDO EN EL DISTRITO CENTRO\n";
        const string DISTRITO = "CENTRO";
        vector<Arbol *> arbolesConCaja = control.arbolesCajaDistrito(DISTRITO);
        cout << "\tÁrboles encontrados: " << arbolesConCaja.size() << endl;
        for (Arbol *arbol: arbolesConCaja) {
            cout << "\t" << arbol->getAssetnum() << " - " << arbol->getNbreComun()
                    << " - " << arbol->getnbredistrito() << endl;
        }

        cout << "\nAPARTADO 3: CAJAS NIDO ASOCIADAS A UN ÁRBOL\n";
        unsigned int cajasEnArbol = control.contarCajasEnArbol();
        cout << "\tCajas nido asociadas a un árbol: " << cajasEnArbol << endl;
        cout << "\tCajas nido sin asociar: " << control.get_nests().size() - cajasEnArbol << endl;

        cout << "\nAPARTADO 4: CAJAS NIDO EN EL DISTRITO CENTRO\n";
        vector<CajaNido *> cajasDistrito = control.cajasEnDistrito(DISTRITO);
        cout << "\tCajas nido encontradas: " << cajasDistrito.size() << endl;
        for (CajaNido *caja: cajasDistrito) {
            cout << "\tCaja " << control.idCajaNido(caja) << ": ";
            if (caja->estaEnArbol()) {
                cout << "asociada al árbol " << caja->getArbol()->getAssetnum() << endl;
            } else {
                cout << "sin asociar" << endl;
            }
        }

        cout << "\nAPARTADO 5: DETALLE DE CINCO CAJAS NIDO\n";
        const unsigned int CAJAS_APARTADO_5[] = {70, 75, 80, 85, 90};
        for (unsigned int linea: CAJAS_APARTADO_5) {
            CajaNido *caja = control.buscarCajaNido(linea);
            if (caja == nullptr) {
                cout << "\tCaja de la línea " << linea << " no encontrada" << endl << endl;
                continue;
            }
            cout << "\t" << "caja de la línea " << linea << endl;
            cout << "\t" << "coordenadas de la caja: ";
            mostrarCoordenadas(caja->getCoord());
            cout << endl;
            if (caja->estaEnArbol()) {
                Arbol *arbol = caja->getArbol();
                double distancia2 = caja->getCoord().distancia2(arbol->getCoord());
                cout << "\t" << "identificador del árbol: " << arbol->getAssetnum() << endl;
                cout << "\t" << "coordenadas del árbol: ";
                mostrarCoordenadas(arbol->getCoord());
                cout << endl;
                cout << "\t" << "distancia: " << fixed << setprecision(2) << sqrt(distancia2) << " m"
                        << " (al cuadrado " << distancia2 << ")" << defaultfloat << setprecision(6) << endl;
                cout << "\t" << (distancia2 < 100 ? "cumple" : "NO cumple")
                        << " la condición de estar a menos de 10 metros" << endl;
            } else {
                cout << "\t" << "sin árbol asociado: no hay ninguno a menos de 10 metros" << endl;
            }
            cout << endl;
        }

        cout << "APARTADO 6: PARQUES CON ALGUNA CAJA NIDO\n";
        vector<Parque *> parquesConCaja = control.parquesConCajaNido();
        cout << "\tParques encontrados: " << parquesConCaja.size() << endl;
        for (Parque *pq: parquesConCaja) {
            cout << "\t" << pq->get_cod_parque() << " - " << pq->get_nbre_parque() << endl;
        }

        //Solo parejas: redispersión forzada a una tabla un 30 % más grande. Si no se trabaja en pareja, borrar
        cout << "\nREDISPERSIÓN DE LA TABLA\n";
        control.redispersar(static_cast<unsigned>(control.tamTabla() * 1.3));
        control.mostrarEstadoTabla();
    } catch (const std::exception &error) {
        std::cerr << "\nError: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
