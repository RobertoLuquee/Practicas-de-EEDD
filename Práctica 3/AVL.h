//
// Created by Roberto Luque Peña on 21/10/2026.
//

#ifndef PRACTICA1_AVL_H
#define PRACTICA1_AVL_H
#include <iostream>

#include "VDinamico.h"


template <class T>
class NodoAVL {
public:
    NodoAVL<T> *izq;
    NodoAVL<T> *der;
    T dato;
    char bal;
    NodoAVL();
    NodoAVL(const T& ele);
};

template <class T>
NodoAVL<T>::NodoAVL(): izq(0), der(0), dato(), bal(0) {}

template <class T>
NodoAVL<T>::NodoAVL(const T& ele): izq(0), der(0), bal(0), dato(ele) {}

template <class T>
class AVL {
private:
    NodoAVL<T> *raiz;
    unsigned int _numelementos_cnt;

    void preorden(NodoAVL<T> *p, int nivel);
    void inordenVector(NodoAVL<T> *p, VDinamico<T*> &v);
    void postorden(NodoAVL<T> *p, int nivel);
    void rotDer(NodoAVL<T>* &nodo);
    void rotIzq(NodoAVL<T>* &nodo);
    int inserta(NodoAVL<T>* &c, const T &dato,bool &ok);
    void copiar(NodoAVL<T> *p);
    void destruye(NodoAVL<T>* &p);
    T* habitacion(NodoAVL<T>* p, const T &dato);
    unsigned int calculaAltura(NodoAVL<T>* p) const;

    void buscarRangoRec(NodoAVL<T>* nodo, const T& min, const T& max, VDinamico<T*>& resultado) {
        if (nodo == nullptr) return;

        // Si el nodo actual es mayor que el mínimo, los elementos válidos podrían estar a la izquierda
        if (nodo->dato > min) {
            buscarRangoRec(nodo->izq, min, max, resultado);
        }

        // Si el nodo está dentro del intervalo (no es menor que el mínimo ni mayor que el máximo), se añade
        if (!(nodo->dato < min) && !(nodo->dato > max)) {
            resultado.insertar(&(nodo->dato)); // Almacenamos el puntero para evitar copias
        }

        // Si el nodo actual es menor que el máximo, los elementos válidos podrían estar a la derecha
        if (nodo->dato < max) {
            buscarRangoRec(nodo->der, min, max, resultado);
        }
    }


public:
    AVL();
    AVL(const AVL<T> &origen);
    ~AVL();

    void recorrePreorden();
    VDinamico<T*> recorreInorden();
    void recorrePostorden();

    bool inserta(const T& dato);
    AVL<T>& operator=(const AVL<T> &origen);

    // Búsqueda recursiva e iterativa
    T* buscarecursiva(const T &dato);
    T* buscariterativo(const T &dato);
    T* buscaRec(const T &dato);
    T* buscaIt(const T &dato);


    unsigned int nelementos() const;
    unsigned int _numelementos() const;
    unsigned int numElementos() const;
    unsigned int altura() const;
    VDinamico<T*> buscarRango(const T& min, const T& max) {
        VDinamico<T*> resultado;
        buscarRangoRec(raiz, min, max, resultado);
        return resultado;
    }

};

template<class T>
AVL<T>::AVL(): raiz(nullptr), _numelementos_cnt(0) {}

template <class T>
void AVL<T>::copiar(NodoAVL<T> *p) {
    if (p != nullptr) {
        inserta(p->dato);
        copiar(p->izq);
        copiar(p->der);
    }
}

template <class T>
void AVL<T>::destruye(NodoAVL<T>* &p) {
    if (p != nullptr) {
        destruye(p->izq);
        destruye(p->der);
        delete p;
        p = nullptr;
    }
}

template<class T>
T* AVL<T>::habitacion(NodoAVL<T> *p, const T &dato) {
    if (p == nullptr) return nullptr;
    if (dato == p->dato) return &p->dato;
    if (dato < p->dato) return habitacion(p->izq, dato);
    return habitacion(p->der, dato);
}

template <class T>
AVL<T>& AVL<T>::operator=(const AVL<T> &origen) {
    if (this != &origen) {
        destruye(raiz);
        _numelementos_cnt = 0;
        copiar(origen.raiz);
    }
    return *this;
}

template<class T>
T* AVL<T>::buscarecursiva(const T &dato) {
    return habitacion(raiz, dato);
}

template<class T>
T* AVL<T>::buscaRec(const T &dato) {
    return buscarecursiva(dato);
}

template<class T>
T* AVL<T>::buscariterativo(const T &dato) {
    NodoAVL<T> *actual = raiz;
    while (actual != nullptr) {
        if (actual->dato == dato) {
            return &actual->dato;
        }
        if (dato < actual->dato) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    return nullptr;
}

template<class T>
T* AVL<T>::buscaIt(const T &dato) {
    return buscariterativo(dato);
}

template <class T>
AVL<T>::AVL(const AVL<T> &origen) : raiz(nullptr), _numelementos_cnt(0) {
    copiar(origen.raiz);
}

template<class T>
void AVL<T>::preorden(NodoAVL<T> *p, int nivel) {
    if (p) {
        std::cout << "Procesando nodo " << p->dato;
        std::cout << "en el nivel " << nivel << std::endl;
        preorden(p->izq, nivel + 1);
        preorden(p->der, nivel + 1);
    }
}

template<class T>
void AVL<T>::inordenVector(NodoAVL<T> *p, VDinamico<T*> &v) {
    if (p) {
        inordenVector(p->izq, v);
        v.insertar(&(p->dato));
        inordenVector(p->der, v);
    }
}

template<class T>
void AVL<T>::postorden(NodoAVL<T> *p, int nivel) {
    if (p) {
        postorden(p->izq, nivel + 1);
        postorden(p->der, nivel + 1);
        std::cout << "Procesando nodo " << p->dato;
        std::cout << "en el nivel " << nivel << std::endl;
    }
}

template<class T>
void AVL<T>::recorrePreorden() {
    preorden(raiz, 0);
}

template<class T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> resultado;
    inordenVector(raiz, resultado);
    return resultado;
}

template<class T>
void AVL<T>::recorrePostorden() {
    postorden(raiz, 0);
}

template<class T>
void AVL<T>::rotDer(NodoAVL<T>* &nodo) {
    NodoAVL<T> *q = nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0) l->bal -= -q->bal;
}

template<class T>
void AVL<T>::rotIzq(NodoAVL<T>* &nodo) {
    NodoAVL<T> *q = nodo, *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0) r->bal += q->bal;
}

template<typename T>
int AVL<T>::inserta(NodoAVL<T>* &c, const T &dato, bool &ok) {
    NodoAVL<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new NodoAVL<T>(dato);
        c = p;
        deltaH = 1;
        _numelementos_cnt++;
        ok = true; // Inserción con éxito
    } else if (dato > p->dato) {
        if (inserta(p->der, dato, ok)) {
            p->bal--;
            if (p->bal == -1) deltaH = 1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der);
                rotIzq(c);
            }
        }
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato, ok)) {
            p->bal++;
            if (p->bal == 1) deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1) rotIzq(p->izq);
                rotDer(c);
            }
        }
    } else {
        ok = false; // Elemento duplicado
        deltaH = 0;
    }
    return deltaH;
}

template<class T>
bool AVL<T>::inserta(const T &dato) {
    bool ok = false;
    inserta(raiz, dato, ok);
    return ok;
}

template <class T>
unsigned int AVL<T>::nelementos() const {
    return _numelementos_cnt;
}

template <class T>
unsigned int AVL<T>::_numelementos() const {
    return _numelementos_cnt;
}

template <class T>
unsigned int AVL<T>::numElementos() const {
    return _numelementos_cnt;
}

template <class T>
unsigned int AVL<T>::calculaAltura(NodoAVL<T>* p) const {
    if (p == nullptr) {
        return 0;
    }
    unsigned int altIzq = calculaAltura(p->izq);
    unsigned int altDer = calculaAltura(p->der);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

template <class T>
unsigned int AVL<T>::altura() const {
    return calculaAltura(raiz);
}

template <class T>
AVL<T>::~AVL() {
    destruye(raiz);
    _numelementos_cnt = 0;
}



#endif //PRACTICA1_AVL_H