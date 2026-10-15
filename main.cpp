#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Especie.h"
#include "VDinamico.h"
#include "ControlParques.h"
//#include "LectorCSV.h"
#include "ListaDEnlazada.h"
#include "Parque.h"


/** @author Roberto Luque Peña rlp00041@red.ujaen.es
 * @author Oier Fernandez De Leceta Villalmanzo ofv00003@red.ujaen.es
 */

template <class T>
using Iterador = typename ListaDEnlazada<T>::Iterador;

template <class T>
void mostrarLista(ListaDEnlazada<T>& l)
{
    for (Iterador<T> it = l.iterador(); !it.fin(); it.siguiente())
    {
        std::cout << std::to_string(it.dato()) << "  ";
    }
    cout << endl;
}


Iterador<Parque> buscaParque(ListaDEnlazada<Parque>& lista, string nombre)
{
    Iterador<Parque> it = lista.iterador();
    for (it; !it.fin(); it.siguiente())
    {
        if (it.dato().get_nbre_parque() == nombre)
        {
            return it;
        }
    }
    return it;
}

bool buscaEspecieNbrComun(VDinamico<Especie*>& vector, string nombreComun)
{
    int n = vector.get__tlogico();
    for (int i = 0; i < n; ++i)
    {
        if (vector[i]->getnombre_comun() == nombreComun)
        {
            return true;
        }
    }
    return false;
}

bool buscaEspecieNbrCientif(VDinamico<Especie*>& vector, string nombreCentif)
{
    int n = vector.get__tlogico();
    for (int i = 0; i < n; ++i)
    {
        if (vector[i]->getnombre_cientifico() == nombreCentif)
        {
            return true;
        }
    }
    return false;
}

const string RUTA_ESPECIES = "arbolado-especies.csv";
const string RUTA_PARQUES = "parques.csv";

int main() {
    cout << "PROGRAMA DE PRUEBA 1" << endl;

    //Crear la lista vacía
    ListaDEnlazada<int> lista;

    cout<<"Insetar al final del 101 al 200"<<endl;

    for (int i = 101; i <= 200; ++i)
    {
        lista.insertarFin(i);
    }
    mostrarLista(lista);

    cout<<endl<<"Insertar por el comienzo del 1 al 98"<<endl;
    for (int i = 98; i >= 1; --i)
    {
        lista.insertarInicio(i);
    }
    mostrarLista(lista);

    cout<<endl<<"insertar el dato 100 delante del 101"<<endl;
    Iterador<int> itint = lista.iterador();
    while (itint.dato() != 102)
    {
        itint.siguiente();
    }
    lista.inserta(itint, 100);
    mostrarLista(lista);

    itint = lista.iterador();
    while (itint.dato() != 98)
    {
        itint.siguiente();
    }
    lista.inserta(itint, 99);
    mostrarLista(lista);

    cout<<endl<<"Borrar los 10 primeros y los 10 últimos"<<endl;
    for (int i = 0; i < 10; ++i)
    {
        lista.borrarAlInicio();
        lista.borrarAlFinal();
    }
    mostrarLista(lista);

    cout << "Borrar todos los múltiplos de 10:" << endl;
    Iterador<int> itBorrar = lista.iterador();
    while (!itBorrar.fin()) {
        if (itBorrar.dato() % 10 == 0) {
            lista.borrar(itBorrar); // borrar() desengancha el nodo y avanza itBorrar automáticamente al siguiente
        } else {
            itBorrar.siguiente();
        }
    }
    mostrarLista(lista);
    cout << endl;

    cout<<endl<<"PULSAR CUALQUIER TECLA PARA CONTINUAR"<<endl;
    std::cin.get();// Me da error -> getch();

    cout << "PROGRAMA DE PRUEBA 2" << endl;
    ControlParques cp(RUTA_ESPECIES, RUTA_PARQUES);

    //Variables fuera del bucle por eficiencia
    VDinamico<Especie>* especies = &cp.get_varieties();
    ListaDEnlazada<Parque>* parques = &cp.get_parks();


    // 2. Enlazamos las especies con sus parques
    cp.enlazarAutomatico();

    std::cout << "Enlaces generados con exito." << std::endl;

    cout << endl << "ASIGNACIÓN DE ESPECIES A LOS PARQUES" << endl;
    for (Iterador<Parque> it = parques->iterador(); !it.fin(); it.siguiente())
    {
        cout << "  Codigo: " << to_string(it.dato().get_cod_parque()) << " nombre: " << it.dato().
            get_nbre_parque() << " total especies: " << to_string(
                it.dato().get_contains().get__tlogico()) << endl;
    }

    //Ejercicio1
    cout << endl << "BUSCAR EN PARQUE PRINCESA LEONOR LOS NOMBRES COMUNES EUCALIPTO ROJO Y ARCE DE SIERRA" << endl;
    Parque* princLeonor = cp.buscarParque("PARQUE PRINCESA LEONOR");
    if (princLeonor->existeNbreCom("Eucalipto rojo"))
    {
        cout << "Encontrado Eucalipto rojo" << endl;
    }
    else
    {
        cout << "No se ha encontrado Eucalipto rojo" << endl;
    }

    //No debe estar
    if (princLeonor->existeNbreCom("Arce de sierra"))
    {
        cout << "  Encontrado Arce de sierra" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Arce de sierra" << endl;
    }
    //Ejercicio2
    cout << endl << "BUSCAR EN PARQUE MADRID RIO LOS NOMBRES CIENTÍFICOS HEBE FLORIBUNDA Y ANANAS COMOSA" << endl;
    Parque* madridRio = cp.buscarParque("PARQUE MADRID RIO");
    //No debe estar
    if (madridRio->existeNbreCie("Hebe floribunda"))
    {
        cout << "  Encontrado Hebe floribunda" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Hebe floribunda" << endl;
    }

    //No debe estar
    if (madridRio->existeNbreCie("Ananas comosa"))
    {
        cout << "  Encontrado Ananas comosa" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Ananas comosa" << endl;
    }
    //Ejercicio3
    cout << endl << "BUSCAR PARQUES JUAN CARLOS III Y VIVERO DE MIGAS CALIENTES" << endl;

    // No debe estar
    Parque* p1 = cp.buscarParque("PARQUE JUAN CARLOS III");
    if (p1 == nullptr)
    {
        cout << "  No se ha encontrado parque PARQUE JUAN CARLOS III" << endl;
    }
    else
    {
        cout << "  codigo: " << to_string(p1->get_cod_parque())
             << " nombre: " << p1->get_nbre_parque() << endl;
    }

    // Sí debe estar
    Parque* p2 = cp.buscarParque("VIVERO DE MIGAS CALIENTES");
    if (p2 == nullptr)
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout << "  codigo: " << to_string(p2->get_cod_parque())
             << " nombre: " << p2->get_nbre_parque() << endl;
    }


    //Ejercicio4
    cout << endl << "BUSCAR ESPECIES CON LA SUBCADENA ROSA EN SU NOMBRE CIENTÍFICO" << endl;
    VDinamico<Especie*> especiesRosa = cp.listadoEspecieSubNombre("rosa");
    for (int i = 0; i < especiesRosa.get__tlogico(); ++i)
    {
        especiesRosa[i]->mostrarInfo();
    }


    // Ejercicio 5
    cout << endl << "CONTAR CUÁNTOS PARQUES TIENEN LA ESPECIE CON NOMBRE COMÚN ABETO" << endl;
    int total = cp.contarEspecieParque("Abeto");
    cout << "  Total: " << total << endl;

    //Parejas

    std::cout << "Parques con Madroño antes de borrar: " << cp.contarEspecieParque("Madroño") << std::endl;

    if (cp.borrarEspecie("Madroño")) {
        cout<<"Borerada la especie MADROÑO de todos los parques y desenlazada tambien"<<std::endl;
    }
    else {
        cout << "No se encuentra la especie MADROÑO";
    }
    std::cout << "Parques con Madroño despues de borrar: " << cp.contarEspecieParque("Madroño") << std::endl;
    return 0;
}