//
// Created by admin on 02/10/2026.
//

#ifndef PRACTICA1_LISTADENLAZADA_H
#define PRACTICA1_LISTADENLAZADA_H
#include <stdexcept>
#include <iostream>
#include <random>

/**
 * @brief Clase que representa un nodo de la lista.
 * @tparam T Tipo de dato que almacena.
 */
template <class T>
class Nodo {
public:
    T _dato;
    Nodo *_sig,*_ant;

    /**
     * @brief Constructor por defecto. Inicializa los punteros a nulo.
     */
    Nodo();

    /**
     * @brief Constructor parametrizado.
     * @param dato Valor a almacenar en el nodo.
     * @param sig Puntero al siguiente nodo.
     * @param ant Puntero al nodo anterior.
     */

    Nodo(const T &dato,Nodo *sig,Nodo *ant);
};

//IMPLEMENTACIONES CLASE NODO
template <class T>
Nodo<T>::Nodo():_dato(),_sig(nullptr),_ant(nullptr){};

template <class T>
Nodo<T>::Nodo(const T &dato,Nodo *sig,Nodo *ant):_dato(dato),_sig(sig),_ant(ant){};

/**
 * @brief Clase que implementa una lista doblemente enlazada.
 * @tparam T Tipo de dato que almacena la lista.
 */

//CLASE LISTA ENLAZADA
template <class T>
class ListaDEnlazada {
private:
    Nodo<T> *_cabecera,*_cola;
    unsigned int _numelementos;

    /**
     * @brief Copia el contenido de otra lista en esta.
     * @param origen Lista a copiar.
     */
    void copiar(const ListaDEnlazada<T>& origen);
    /**
     * @brief Libera la memoria ocupada por todos los nodos de la lista.
     */
    void destruye();

public:
    /**
     * @brief Constructor por defecto. Crea una lista vacía.
     */
    ListaDEnlazada();
    /**
     * @brief Constructor de copia.
     * @param origen Lista de la cual se copiarán los elementos.
     */
    ListaDEnlazada(const ListaDEnlazada<T>& origen);
    /**
     * @brief Operador de asignación.
     * @param arr Lista a asignar.
     * @return Referencia a la lista actual.
     */
    ListaDEnlazada& operator=(const ListaDEnlazada<T>& arr);
    /**
     * @brief Obtiene el primer elemento de la lista.
     * @return Referencia al dato del primer nodo.
     * @throw std::invalid_argument Si la lista está vacía.
     */
    T& inicio();
    /**
     * @brief Obtiene el último elemento de la lista.
     * @return Referencia al dato del último nodo.
     * @throw std::invalid_argument Si la lista está vacía.
     */
    T& fin();
    /**
     * @brief Inserta un nuevo elemento al principio de la lista.
     * @param dato Valor a insertar.
     */
    void insertarInicio(const T& dato);
    /**
     * @brief Inserta un nuevo elemento al final de la lista.
     * @param dato Valor a insertar.
     */
    void insertarFin(const T& dato);


    /**
     * @brief Clase que implementa un iterador para recorrer la lista doblemente enlazada.
     */
    // 1. LA CLASE ITERADOR Q VA  DENTRO PA Q FUNCIONE
    class Iterador {
    private:
        Nodo<T> *nodo;
        friend class ListaDEnlazada<T>;

    public:
        /**
        * @brief Constructor del iterador.
        * @param aNodo Puntero al nodo inicial (por defecto nulo).
        */
        Iterador(Nodo<T> *aNodo=nullptr);
        /**
         * @brief Comprueba si el iterador ha llegado al final (nulo).
         * @return true si es el final, false en caso contrario.
         */
        bool fin() const;
        /**
         * @brief Comprueba si existe un nodo anterior al actual.
         * @return true si hay nodo anterior, false en caso contrario.
         */
        bool hayAnterior();
        /**
         * @brief Comprueba si existe un nodo siguiente al actual.
         * @return true si hay nodo siguiente, false en caso contrario.
         */
        bool haySiguiente();
        /**
         * @brief Retrocede el iterador al nodo anterior.
         */
        void anterior();
        /**
         * @brief Avanza el iterador al nodo siguiente.
         */
        void siguiente();
        /**
         * @brief Obtiene el dato del nodo apuntado por el iterador.
         * @return Referencia al dato.
         * @throw std::invalid_argument Si el iterador es nulo.
         */
        T &dato();
    }; // acaba clase iterador

    // 2. Estos  son  de la lista, no del iterador
    /**
     * @brief Crea un iterador apuntando al inicio de la lista.
     * @return Objeto Iterador.
     */
    Iterador iterador();
    /**
     * @brief Inserta un elemento justo antes de la posición del iterador.
     * @param i Iterador que indica la posición de inserción.
     * @param dato Valor a insertar.
     */
    void inserta(Iterador &i,const T &dato);
    /**
     * @brief Elimina el primer elemento de la lista.
     */
    void borrarAlInicio();
    /**
     * @brief Elimina el último elemento de la lista.
     */
    void borrarAlFinal();
    /**
     * @brief Elimina el elemento apuntado por el iterador y avanza el iterador al siguiente.
     * @param i Iterador apuntando al nodo a borrar.
     */
    void borrar(Iterador &i);
    /**
     * @brief Obtiene el número total de elementos en la lista.
     * @return Cantidad de elementos.
     */
    int tam() const;
    /**
     * @brief Concatena esta lista con otra y devuelve el resultado en una nueva lista.
     * @param lista Lista a concatenar al final.
     * @return Nueva lista con los elementos concatenados.
     */
    ListaDEnlazada<T> concatena(const ListaDEnlazada<T> &lista)const;
    /**
    * @brief Sobrecarga del operador + para concatenar dos listas.
    * @param l Lista a sumar/concatenar.
    * @return Nueva lista resultante de la concatenación.
    */
    ListaDEnlazada<T> operator+(const ListaDEnlazada<T> &l) const;
    /**
    * @brief Destructor de la lista. Libera toda la memoria ocupada.
    */
    ~ListaDEnlazada();
};


//IMPLEMENTACIONES CLASE LISTADENLAZADA

template <class T>
ListaDEnlazada<T>::ListaDEnlazada():_cabecera(nullptr),_cola(nullptr),_numelementos(0){};


template <class T>
void ListaDEnlazada<T>::destruye() {
    Nodo<T> *actual = _cabecera;
    while (actual != nullptr) {
        Nodo<T> *aBorrar = actual;
        actual = actual->_sig;
        delete aBorrar;
    }
    _cabecera = nullptr;
    _cola = nullptr;
    _numelementos = 0;
}

template <class T>
void ListaDEnlazada<T>::copiar(const ListaDEnlazada<T>& origen) {
    _cabecera = nullptr;
    _cola = nullptr;
    _numelementos = 0;

    Nodo<T> *p = origen._cabecera;
    while (p != nullptr) {

        Nodo<T> *nuevo = new Nodo<T>(p->_dato, nullptr, _cola);
        if (_cola != nullptr) {
            _cola->_sig = nuevo;
        } else {
            _cabecera = nuevo;
        }
        _cola = nuevo;
        _numelementos++;
        p = p->_sig;
    }
}


// 1. Operador de asignación
template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T>& arr) {
    if (this != &arr) {
        destruye();   // Llama a liberar la memoria actual
        copiar(arr);  // Llama a copiar los nuevos nodos
    }
    return *this;
}

// 2. Constructor de copia
template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T>& origen) {
    copiar(origen);
}

// 3. Destructor
template <class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    destruye();
}

template <class T>
T& ListaDEnlazada<T>::inicio() {
    if (_cabecera==nullptr) {
        throw std::invalid_argument("La lista esta vacia");
    }
    return _cabecera->_dato;
}

template <class T>
T& ListaDEnlazada<T>::fin() {
    if (_cola==nullptr) {
        throw std::invalid_argument("La lista esta vacia");
    }
    return _cola->_dato;
}

template<class T>
void ListaDEnlazada<T>::insertarInicio(const T& dato){
    Nodo<T> *nuevo= new Nodo<T>(dato,_cabecera,0);
    if (_cola==0)
        _cola=nuevo;
    if (_cabecera!=0)
        _cabecera->_ant=nuevo;
    _cabecera=nuevo;
    _numelementos++;
}

template<class T>
void ListaDEnlazada<T>::insertarFin(const T& dato) {
    Nodo<T> *nuevo;
    nuevo=new Nodo<T>(dato,0,_cola);
    if (_cabecera==0)
        _cabecera=nuevo;
    if (_cola!=0)
        _cola->_sig=nuevo;
    _cola=nuevo;
    _numelementos++;
}

template <class T>
void ListaDEnlazada<T>::inserta(Iterador &i, const T &dato) {
   // Nodo<T> *p = i.nodo;
    if (i.nodo == nullptr) {
        insertarFin(dato);
        return;
    }
    if (i.nodo == _cabecera) {
        insertarInicio(dato);
        return;
    }
    Nodo<T> *nuevo = new Nodo<T>(dato, i.nodo, i.nodo->_ant);
    if (i.nodo->_ant != nullptr) {
        i.nodo->_ant->_sig = nuevo;
    }
    i.nodo->_ant = nuevo;
    _numelementos++;
}

template<class T>
void ListaDEnlazada<T>::borrarAlInicio() {
    if (_cabecera == nullptr) return;

    Nodo<T> *borra = _cabecera;
    _cabecera = _cabecera->_sig;

    if (_cabecera != nullptr) {
        _cabecera->_ant = nullptr;
    } else {
        _cola = nullptr; // La lista se ha quedado vacía
    }

    delete borra;
    _numelementos--;
}


template<class T>
void ListaDEnlazada<T>::borrarAlFinal() {
    if (_cola == nullptr) return;

    Nodo<T> *borra = _cola;
    _cola = _cola->_ant;

    if (_cola != nullptr) {
        _cola->_sig = nullptr;
    } else {
        _cabecera = nullptr; // La lista se ha quedado vacía
    }

    delete borra;
    _numelementos--;
}


template<class T>
void ListaDEnlazada<T>::borrar(Iterador &i) {
    Nodo<T> *borra=i.nodo;

    if (borra==nullptr) return;

    if (borra->_ant!=nullptr)
        borra->_ant->_sig=borra->_sig;
    else
        _cabecera=borra->_sig;

    if (borra->_sig!=nullptr)
        borra->_sig->_ant=borra->_ant;
    else _cola=borra->_ant;

    i.nodo = borra->_sig;
    delete borra;
    _numelementos--;

}

template <class T>
int ListaDEnlazada<T>::tam()const {
    return _numelementos;
}

template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::concatena(const ListaDEnlazada<T> &lista)const {
    ListaDEnlazada<T>resultado;

    Nodo<T>* p1=_cabecera;
    while (p1!=nullptr) {
        resultado.insertarFin(p1->_dato);
        p1=p1->_sig;
    }

    Nodo<T>*p2=lista._cabecera;
    while (p2!=nullptr) {
        resultado.insertarFin(p2->_dato);
        p2=p2->_sig;
    }
    return resultado;
}


template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator+(const ListaDEnlazada<T> &lista) const {
    return concatena(lista);
}



//Aqui añado los metodos de la clase Iterador

template<class T>
ListaDEnlazada<T>::Iterador::Iterador(Nodo<T> *aNodo):nodo (aNodo) {}

template <class T>
bool ListaDEnlazada<T>::Iterador::fin() const {
    return nodo == nullptr;
}

template<class T>
bool ListaDEnlazada<T>::Iterador::hayAnterior() {
    if (nodo!=nullptr && nodo->_ant!=nullptr)
        return true;
    return false;
}

template <class T>
bool ListaDEnlazada<T>::Iterador::haySiguiente() {
    if (nodo != nullptr && nodo->_sig != nullptr) {
        return true;
    }
    return false;
}

template<class T>
void ListaDEnlazada<T>::Iterador::anterior() {
    if (nodo!=nullptr) {
        nodo=nodo->_ant;
    }
}

template<class T>
void ListaDEnlazada<T>::Iterador::siguiente() {
    if (nodo!=nullptr) {
        nodo=nodo->_sig;
    }
}

template<class T>
T& ListaDEnlazada<T>::Iterador::dato() {
    if (nodo==nullptr)
        throw std::invalid_argument("Iterador nulo");
    return nodo->_dato;
}

template <class T>
typename ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::iterador() {
    return Iterador(_cabecera); //Con esto devuelvo un objeto iteradorfd
}





#endif //PRACTICA1_LISTADENLAZADA_H
