
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

// Rutas de los archivos CSV
const string RUTA_ESPECIES = "arbolado-especies.csv";
const string RUTA_PARQUES = "parques.csv";
const string RUTA_ARBOLES = "arboladoMadrid.csv";
const string RUTA_CAJAS_NIDO = "cajas-nido.csv";

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try {
        // Inicialización de ControlParques (carga los 4 CSV y enlaza todo)
        ControlParques control(
            RUTA_ESPECIES,
            RUTA_PARQUES,
            RUTA_ARBOLES,
            RUTA_CAJAS_NIDO
        );

        // =========================================================
        // PROGRAMA DE PRUEBA 1: AJUSTE Y RENDIMIENTO DE LA TABLA HASH
        // =========================================================
        cout << "\n==========================================" << endl;
        cout << "PROGRAMA DE PRUEBA 1: AJUSTE DE LA TABLA" << endl;
        cout << "==========================================" << endl;
        cout << "ESTADO DE LA TABLA HASH:" << endl;
        control.mostrarEstadoTabla();

        vector<string> ids = control.getIdsArboles();
        shuffle(ids.begin(), ids.end(), mt19937(random_device{}()));
        if (ids.size() > 2000) {
            ids.resize(2000);
        }

        cout << "\nPRUEBA DE RENDIMIENTO (2000 búsquedas):" << endl;

        // Tiempo en Tabla Hash
        auto inicio = chrono::high_resolution_clock::now();
        for (vector<string>::iterator it = ids.begin(); it != ids.end(); ++it) {
            control.buscarArbol(*it);
        }
        auto fin = chrono::high_resolution_clock::now();
        double msHash = chrono::duration<double, milli>(fin - inicio).count();

        // Tiempo en Lista (si el método sigue disponible en ControlParques)
        inicio = chrono::high_resolution_clock::now();
        for (vector<string>::iterator it = ids.begin(); it != ids.end(); ++it) {
            control.buscarArbolLista(*it);
        }
        fin = chrono::high_resolution_clock::now();
        double msLista = chrono::duration<double, milli>(fin - inicio).count();

        cout << "Tiempo tabla hash: " << msHash << " ms" << endl;
        cout << "Tiempo lista: " << msLista << " ms" << endl;

        // =========================================================
        // PROGRAMA DE PRUEBA 2: CONSULTAS Y RELACIONES
        // =========================================================
        cout << "\n==========================================" << endl;
        cout << "PROGRAMA DE PRUEBA 2: CONSULTAS" << endl;
        cout << "==========================================" << endl;

        // 1. Buscar assetnum: 6925456, 6635839, 5222166
        cout << "\n--- ACCION 1: BUSQUEDA DE ARBOLES ESPECIFICOS ---\n";
        vector<string> idsGuion = {"6925456", "6635839", "5222166"};

        for (string &id : idsGuion) {
            Arbol *arbol = control.buscarArbol(id);
            if (arbol == nullptr) {
                cout << "Arbol ID " << id << ": NO EXISTE\n";
            } else {
                cout << "ID: " << arbol->get_assetnum()
                     << " | Especie: " << arbol->getNbreComun()
                     << " (" << arbol->getNbreCientifico() << ")"
                     << " | Altura: " << arbol->getAltura() << " m"
                     << " | Num Parque: " << arbol->getNumParque() << '\n';
            }
        }

        // 2. Árboles con caja nido asociada en el distrito "CENTRO"
        cout << "\n--- ACCION 2: ARBOLES CON CAJA NIDO EN 'CENTRO' ---\n";
        string distritoCentro = "CENTRO";
        vector<Arbol*> arbCentro = control.arbolesCajaDistrito(distritoCentro);
        cout << "Numero de arboles encontrados: " << arbCentro.size() << "\n";

        for (Arbol* a : arbCentro) {
            cout << "  - ID: " << a->get_assetnum()
                 << " | Especie: " << a->getNbreComun()
                 << " | Distrito: " << distritoCentro << "\n";
        }

        // 3. Total de cajas asociadas y sin asociar
        cout << "\n--- ACCION 3: CONTEO TOTAL DE CAJAS NIDO ---\n";
        unsigned int asociadas = control.contarCajasEnArbol();
        unsigned int sinAsociar = control.getTotalCajas() - asociadas;
        cout << "Cajas nido asociadas a un arbol: " << asociadas << "\n";
        cout << "Cajas nido sin asociar: " << sinAsociar << "\n";

        // 4. Todas las cajas nido ubicadas en el distrito "CENTRO"
        cout << "\n--- ACCION 4: CAJAS NIDO EN DISTRITO 'CENTRO' ---\n";
        vector<CajaNido*> cajasCentro = control.cajasEnDistrito(distritoCentro);
        cout << "Numero de cajas encontradas en CENTRO: " << cajasCentro.size() << "\n";

        for (unsigned int i = 0; i < cajasCentro.size(); ++i) {
            CajaNido* c = cajasCentro[i];
            cout << "  - Caja " << i + 1 << ": ";
            if (c->estaEnArbol())
                cout << "Asociada al arbol ID: " << c->getArbol()->get_assetnum() << "\n";
            else
                cout << "No asociada a ningun arbol\n";
        }

        // 5. Cajas de las líneas {70, 75, 80, 85, 90} del fichero
        cout << "\n--- ACCION 5: COMPROBACION LINEAS {70, 75, 80, 85, 90} ---\n";
        vector<int> lineas = {70, 75, 80, 85, 90};
        const vector<CajaNido>& todasCajas = control.getNests();

        for (int numLinea : lineas) {
            unsigned int idx = numLinea - 2;
            if (idx < todasCajas.size()) {
                const CajaNido& c = todasCajas[idx];
                cout << "Linea " << numLinea
                     << " | UTM Caja: (" << c.get_coord().getX() << ", " << c.get_coord().getY() << ")";

                if (c.estaEnArbol()) {
                    Arbol* a = c.getArbol();
                    double dist2 = c.get_coord().distancia2(a->getCoord());
                    double distMetros = sqrt(dist2);

                    cout << " | Arbol ID: " << a->get_assetnum()
                         << " | UTM Arbol: (" << a->getCoord().getX() << ", " << a->getCoord().getY() << ")"
                         << " | Distancia: " << distMetros << " m (d^2 = " << dist2
                         << " -> " << (dist2 < 100.0 ? "CUMPLE < 100" : "NO CUMPLE") << ")\n";
                } else {
                    cout << " | Sin arbol asociado\n";
                }
            }
        }

        // 6. Todos los parques que tengan al menos alguna caja nido
        cout << "\n--- ACCION 6: PARQUES CON AL MENOS UNA CAJA NIDO ---\n";
        vector<Parque*> parquesCajas = control.parquesConCajaNido();
        cout << "Total parques con cajas nido: " << parquesCajas.size() << "\n";

        for (Parque* p : parquesCajas) {
            cout << "  - Codigo: " << p->get_cod_parque()
                 << " | Nombre: " << p->get_nbre_parque() << "\n";
        }

    } catch (const std::exception &error) {
        std::cerr << "\nError: " << error.what() << endl;
        return 1;
    }

    return 0;
}