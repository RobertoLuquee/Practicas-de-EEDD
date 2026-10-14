//
// Created by admin on 02/10/2026.
//

#ifndef PRACTICA1_LISTADENLAZADA_H
#define PRACTICA1_LISTADENLAZADA_H
#include <stdexcept>
#include <iostream>
#include <random>


template <class T>
class Nodo {
public:
    T _dato;
    Nodo *_sig,*_ant;

    Nodo();
    Nodo(T &dato,Nodo *sig,Nodo *ant);
};

//IMPLEMENTACIONES CLASE NODO
template <class T>
Nodo<T>::Nodo():_dato(),_sig(nullptr),_ant(nullptr){};

template <class T>
Nodo<T>::Nodo(T &dato,Nodo *sig,Nodo *ant):_dato(dato),_sig(sig),_ant(ant){};

//CLASE LISTA ENLAZADA
template <class T>
class ListaDEnlazada {
private:
    Nodo<T> *_cabecera, *_cola;
    unsigned int _numelementos;

public:
    ListaDEnlazada();
    ListaDEnlazada(const ListaDEnlazada<T>& origen);
    ListaDEnlazada& operator=(const ListaDEnlazada<T>& arr);
    T& inicio();
    T& fin();
    void insertarInicio(T& dato);
    void insertarFin(T& dato);

    // 1. LA CLASE ITERADOR VA  DENTRO
    class Iterador {
    private:
        Nodo<T> *nodo;
        friend class ListaDEnlazada<T>;

    public:
        Iterador(Nodo<T> *aNodo=nullptr);
        bool fin() const;
        bool hayAnterior();
        bool haySiguiente();
        void anterior();
        void siguiente();
        T &dato();
    }; // acaba clase iterador

    // 2. Estos  son  de la lista, no del iterador
    Iterador iterador();
    void inserta(Iterador &i,const T &dato);
    void borrarAlInicio();
    void borrarAlFinal();
    void borrar(Iterador &i);
    int tam() const;
    ListaDEnlazada<T> concatena(const ListaDEnlazada<T> &lista)const;
    ListaDEnlazada<T> operator+(const ListaDEnlazada<T> &l) const;
    ~ListaDEnlazada();
};


//IMPLEMENTACIONES CLASE LISTADENLAZADA

template <class T>
ListaDEnlazada<T>::ListaDEnlazada():_cabecera(nullptr),_cola(nullptr),_numelementos(0){};

template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T>& origen) {
    Nodo<T> *p=origen._cabecera;
    while (p!=nullptr) {
        Nodo<T>* nuevo = new Nodo<T> (p->_dato,nullptr,_cabecera);
        _cola=p->_sig;
    }
}

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>:: operator=(const ListaDEnlazada<T>& arr) {
    if (this!=&arr) {
        Nodo<T>*actual=_cabecera;
        while (actual!=nullptr) {
            Nodo<T>*aBorrar=actual;  //Guardo la dirección del nodo a borrar
            actual=actual->_sig; //Avanzo al siguiente antes de borrarlo
            delete aBorrar;
        }
        _cabecera=nullptr;
        _cola=nullptr;
        _numelementos=0;

        Nodo<T>*parr=arr._cabecera;
        while (parr!=nullptr) {
            Nodo<T>*nuevo= new Nodo<T>(parr->_dato,nullptr,_cola);
            if (_cola!=nullptr) {
                _cola->_sig=nuevo;
            }else {
                _cabecera=nuevo; //Si la lista esta vacia, este nuevo nodo es tmabien la cabecera
            }
            _cola=nuevo;
            _numelementos++;
            parr=parr->_sig;
        }
    }
    return *this;
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
void ListaDEnlazada<T>::insertarInicio(T& dato) {
    Nodo<T> *nuevo= new Nodo<T>(dato,0,_cabecera);
    if (_cola==0)
        _cola=nuevo;
    if (_cabecera!=0)
        _cabecera->_ant=nuevo;
    _cabecera=nuevo;
    _numelementos++;
}

template<class T>
void ListaDEnlazada<T>::insertarFin(T& dato) {
    Nodo<T> *nuevo;
    nuevo=new Nodo<T>(dato,_cola,0);
    if (_cabecera==0)
        _cabecera=nuevo;
    if (_cola!=0)
        _cola->_sig=nuevo;
    _cola=nuevo;
    _numelementos++;
}

template <class T>
void ListaDEnlazada<T>::inserta(Iterador &i, const T &dato) {
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
    Nodo<T>*borra=_cabecera;
    _cabecera=_cabecera->_sig;
    _cabecera->_ant=nullptr;
    delete borra;
}

template<class T>
void ListaDEnlazada<T>::borrarAlFinal() {
    Nodo<T>*borra=_cola;
    _cola=borra->_ant;
    _cola->_sig=nullptr;
    delete borra;
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
        borra->_sig->ant=borra->_ant;
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

template <class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    Nodo<T> *actual = _cabecera;
    while (actual != nullptr) {
        Nodo<T> *aBorrar = actual;
        actual = actual->_sig; // Avanzo al siguiente antes de liberar el actual
        delete aBorrar;        // Libero la memoria
    }
    _cabecera = nullptr;
    _cola = nullptr;
    _numelementos = 0;
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
