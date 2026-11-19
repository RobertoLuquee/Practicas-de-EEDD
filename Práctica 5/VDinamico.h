//
// Created by Roberto Luque Peña on 23/09/2026.
//

#ifndef INC_50085834A3194F8ABB30A4A6712C768D
#define INC_50085834A3194F8ABB30A4A6712C768D
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;
#include "Especie.h"

template<class T>
class VDinamico {

private:
    T* v;
    unsigned int _tlogico;
    unsigned int _tfisico;

public:

    /**
     * @brief Constructor por defecto
     */
    VDinamico();
    /**
     * @brief Constructor que inicializa el vector con un tamaño lógico inicial y un elemento por defecto.
     * @param tamlog Tamaño lógico inicial del vector.
     * @param dato Referencia al objeto utilizado para rellenar las casillas iniciales.
     */
    VDinamico(unsigned int tamlog, T&dato);
    /**
     * @brief Constructor de copia.
     * @param origen Objeto `VDinamico` desde el cual se copiarán los datos.
     */
    VDinamico(const VDinamico<T>& origen);
    /**
     * @brief Constructor de copia parcial.
     * @param origen Objeto
     * @param posicionInicial Índice inicial .
     * @param numElementos Cantidad de elementos a copiar desde la posición inicial.
     * @throw std::out_of_range Si la suma de `posicionInicial` y `numElementos` sobrepasa el tamaño lógico de `origen`.
     */
    VDinamico(const VDinamico<T>& origen, unsigned int posicionInicial, unsigned int numElementos);
    /**
     * @brief Operador de asignación.
     * @param arr Referencia al vector fuente para realizar la asignación.
     * @return Devuelve el objeto  `*this`.
     */
    VDinamico& operator=(VDinamico& arr);
    /**
     * @brief Operador []
     * @param pos Posición o índice del elemento al que queremos acceder.
     * @return Referencia al elemento.
     * @throw std::out_of_range Si el índice `pos` es mayor o igual que el tamaño lógico.
     */
    T &operator[] (unsigned int pos);
    /**
     * @brief Inserta un elemento en una posición específica del vector.
     * @param dato Elemento constante a insertar.
     * @param pos Posición de inserción (por defecto ponemos `UINT_MAX`).
     * @throw std::out_of_range Si `pos` es estrictamente mayor que el tamaño lógico.
     */
    void insertar(const T& dato, unsigned int pos =UINT_MAX);
    /**
     * @brief Elimina un elemento del vector en la posición indicada y lo devuelve.
     * @param pos Posición del elemento a borrar (por defecto ponemos `UINT_MAX`).
     * @return Copia del elemento eliminado.
     * @throw std::out_of_range Si el vector está vacío o la posición especificada excede los límites válidos.
     */
    T borrar(unsigned int pos =UINT_MAX);
    /**
     * @brief Ordena los elementos del vector dinámico en orden ascendente.
     */
    void ordenar();
    /**
     * @brief Realiza una búsqueda binaria sobre el vector.
     * @param dato Elemento a localizar.
     * @return Índice de la posición del elemento si se encuentra, o `-1` en caso contrario.
     */
    int busquedaBinaria(const T& dato);
    /**
     * @brief Obtiene el número actual de elementos almacenados (tamaño lógico).
     * @return Entero con el tamaño lógico del vector.
     */
    int get__tlogico();
    /**
     * @brief Destructor
     */
    ~VDinamico();

};

template<class T>
VDinamico<T>::VDinamico() {
    _tlogico=0;
    _tfisico=1;
    v=new T[_tfisico];
}

template<class T>
VDinamico<T>::VDinamico(unsigned int tamlog, T&dato) {
    _tlogico=tamlog;
    _tfisico=1;

    while (_tfisico<_tlogico) {
        _tfisico*=2;
    }
    v=new T[_tfisico];

    for (unsigned int i=0;i<_tlogico;i++) {
        v[i]=dato;
    }
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen) {
    _tfisico=origen._tfisico;
    _tlogico=origen._tlogico;

    v=new T[_tfisico];

    for (unsigned int i=0;i<_tlogico;i++)
        v[i]=origen.v[i];

}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned
        int posicionInicial, unsigned int numElementos) {
    if (posicionInicial+numElementos>origen._tlogico) {
        throw out_of_range("Rango fuera de los limites del vector origen");
    }
    _tlogico=numElementos;
    _tfisico = 1;
    while (_tfisico < _tlogico) {
        _tfisico *= 2;
    }
    v=new T[_tfisico];

    // Lo hago para reordenar los datos
    for (unsigned int i = 0; i < _tlogico; i++) {
        v[i] = origen.v[posicionInicial + i];
    }
}

template <class T>
VDinamico<T>& VDinamico<T>::operator=(VDinamico& arr) {
    if (&arr !=this) {
        delete[] v;
        _tfisico=arr._tfisico;
        _tlogico=arr._tlogico;

        v=new T[_tfisico];
        for (unsigned int i=0;i<_tlogico;i++) {
            v[i]=arr.v[i];
        }
    }
    return *this;
}

template <class T>
T& VDinamico<T>::operator[] (unsigned int pos) {

    if (pos>=_tlogico) {
        throw out_of_range("T& VDinamico<T>::operator[] (unsigned int pos): Indice fuera de rango");
    }
    return v[pos];
}

template <class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos) {

    if (pos == UINT_MAX) {
        pos = _tlogico;
    }

    if (pos>_tlogico)
        throw std::out_of_range("void VDinamico<T>::insertar(const T& dato, unsigned int pos): Posicion de insercion mayor que el tamaño logico.");


    if (_tlogico==_tfisico) {
        _tfisico*=2;
        T* v_aux=new T[_tfisico];
        for (unsigned int i=0;i<_tlogico;i++) {
            v_aux[i]=v[i];
        }
        delete[] v;
        v=v_aux;
    }

    for (unsigned int i=_tlogico;i>pos;i--)
        v[i]=v[i-1];

    v[pos]=dato;
    _tlogico++;
}

template <class T>
T VDinamico<T>::borrar(unsigned int pos) {

    if (_tlogico==0)
        throw out_of_range("No se puede eliminar ningun elemento");
    if (pos==UINT_MAX || pos>=_tlogico)
        throw std::out_of_range("T VDinamico<T>::borrar(unsigned int pos): Posicion invalida o fuera de limites.");

    T aux=v[pos]; //Aquí guardo una copia antes de perderlo

    for (unsigned int i=pos; i<_tlogico - 1 ;i++)
        v[i]=v[i+1];
    //Dejamos el ultimo valor del vector duplicado como basura y le restamos 1 al tlog para que en las proximas operaciones lo tome como vacio,
    //ya que no podemos borrar una casilla del vector pq daria error de compilacion en Clion.

    _tlogico--;

    return aux;
}

template<class T>
void VDinamico<T>::ordenar() {
    std::sort(v, v + _tlogico);
}

template<class T>
int VDinamico<T>::busquedaBinaria(const T &dato) {
    ordenar();
    int min=0;
    int max=_tlogico-1;
    int aux;

    while (min<=max) {
        aux=min+(max-min)/2;
        if (v[aux]==dato) {
            return aux;
        }
        if (v[aux]<dato) min=aux+1;

        else max=aux-1;
    }
    return -1;
}

template<class T>
int VDinamico<T>::get__tlogico() {
    return _tlogico;
}

template<class T>
VDinamico<T>::~VDinamico() {
    delete[] v;
}




#endif //INC_50085834A3194F8ABB30A4A6712C768D
