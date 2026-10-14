#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Especie.h"
#include "VDinamico.h"
#include <iostream>
//#include <conio.h>
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
void mostrarLista(ListaDEnlazada<T> l)
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
        string s = vector[i]->getnombre_cientifico();
        if (vector[i]->getnombre_cientifico() == nombreCentif)
        {
            return true;
        }
    }
    return false;
}

const string RUTA_ESPECIES = "data/arbolado-especies.csv";
const string RUTA_PARQUES = "data/parques.csv";

int main()
{

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

    cout << "6. Borrar todos los múltiplos de 10:" << endl;
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

    for (int i = 0; i < especies->get__tlogico(); ++i)
    {
        Iterador<Parque> it = parques->iterador();
        Especie& esp = (*especies)[i];
        int tipo = esp.get_tipo_planta();
        for (it; !it.fin(); it.siguiente())
        {
            Parque& pq = it.dato();
            int resto = pq.get_cod_parque() % 2;

            //parques con codigo par
            if ((tipo == ARBUSTO || tipo == CONIFERA || tipo == PALMACEA ||
                tipo == HERB_PERENNES || tipo == FRONDOSA) && (resto == 0))
            {
                pq.insertaEspecie(&esp);
                //Parques con codigo impar
            }
            else if ((tipo == TAPIZANTE_TREPADORA || tipo == CACTACEA_SUCULENTA ||
                tipo == SUBTROPICAL_TROPICAL ||
                tipo == HERB_ANUAL || tipo == HERB_ANUALES) && (resto == 1))
            {
                pq.insertaEspecie(&esp);
            }
        }
    }

    cout << endl << "ASIGNACIÓN DE ESPECIES A LOS PARQUES" << endl;
    for (Iterador<Parque> it = parques->iterador(); !it.fin(); it.siguiente())
    {
        cout << "  Codigo: " << to_string(it.dato().get_cod_parque()) << " nombre: " << it.dato().
            get_nbre_parque() << " total especies: " << to_string(
                it.dato().get_contains().get__tlogico()) << endl;
    }


    cout << endl << "BUSCAR EN PARQUE PRINCESA LEONOR LOS NOMBRES COMUNES EUCALIPTO ROJO Y ARCE DE SIERRA" << endl;
    Parque& princLeonor = buscaParque(cp.get_parks(), "PARQUE PRINCESA LEONOR").dato();
    //Debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contains(), "Eucalipto rojo"))
    {
        cout << "  Encontrado Eucalipto rojo" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Eucalipto rojo" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contains(), "Arce de sierra"))
    {
        cout << "  Encontrado Arce de sierra" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Arce de sierra" << endl;
    }

    cout << endl << "BUSCAR EN PARQUE MADRID RIO LOS NOMBRES CIENTÍFICOS HEBE FLORIBUNDA Y ANANAS COMOSA" << endl;
    Parque& madridRio = buscaParque(cp.get_parks(), "PARQUE MADRID RIO").dato();
    //No debe estar
    if (buscaEspecieNbrCientif(madridRio.get_contains(), "Hebe floribunda"))
    {
        cout << "  Encontrado Hebe floribunda" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Hebe floribunda" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(madridRio.get_contains(), "Ananas comosa"))
    {
        cout << "  Encontrado Ananas comosa" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Ananas comosa" << endl;
    }

    cout << endl << "BUSCAR PARQUES JUAN CARLOS III Y VIVERO DE MIGAS CALIENTES" << endl;
    //No debe estar
    Iterador<Parque> it = buscaParque(cp.get_parks(), "JUAN CARLOS III");
    if (it.fin())
    {
        cout << "  No se ha encontrado parque JUAN CARLOS III" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.dato().get_cod_parque()) <<" nombre: "<< it.dato().get_nbre_parque()<< endl;
    }

    Iterador<Parque> it2 = buscaParque(cp.get_parks(), "VIVERO DE MIGAS CALIENTES");

    //Sí debe estar
    if (it.fin())
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.dato().get_cod_parque()) <<" nombre: "<< it.dato().get_nbre_parque()<< endl;
    }

    cout<< endl<<"BUSCAR ESPECIES CON LA SUBCADENA ROSA EN SU NOMBRE CIENTÍFICO"<<endl;
    for (int i =0; i < especies->get__tlogico(); ++i)
    {
        string ncientif = (*especies)[i].getnombre_cientifico();
        if (ncientif.find("rosa") != string::npos)
        {
            (*especies)[i].mostrarInfo();
        }
    }

    cout<< endl<<"CONTAR CUÁNTOS PARQUES TIENEN LA ESPECIE CON NOMBRE COMÚN ABETO"<<endl;
    it = cp.get_parks().iterador();
    int total = 0;
    for (it; !it.fin(); it.siguiente())
    {
       VDinamico<Especie*>  esp = it.dato().get_contains();
        for (int i =0; i < esp.get__tlogico(); ++i)
        {
            string nombreComun = esp[i]->getnombre_comun();
            if (nombreComun.find("Abeto") != string::npos)
            {
                ++total;
                break;
            }
        }
    }
    cout<<"  Total: "<<total<<endl;



    return 0;
}