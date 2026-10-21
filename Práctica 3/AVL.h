//
// Created by Roberto Luque Peña on 21/10/2026.
//

#ifndef PRACTICA1_AVL_H
#define PRACTICA1_AVL_H
#include <iostream>


template <class T>
class Nodo {
public:
    Nodo<T> *izq;
    Nodo<T> *der;
    T dato;
    char bal;
    Nodo();
    Nodo(T& ele);

};
template <class T>
Nodo<T>::Nodo(): izq(0),der(0),dato(),bal(0){}

template <class T>
Nodo<T>::Nodo(T& ele): izq(0),der(0),bal(0),dato(ele){}

template <class T>
class AVL {
private:
    Nodo<T> *raiz;
    unsigned int _numelementos;

    void preorden(Nodo<T> *p, int nivel);
    void inorden(Nodo<T> *p, int nivel);
    void postorden(Nodo<T> *p, int nivel);
    void rotDer(Nodo<T>* &nodo);
    void rotIzq(Nodo<T>* &nodo);
    int inserta(Nodo<T>* &c, T &dato);
    void copiar(Nodo<T>*p);


public:
    AVL();
    AVL(const AVL<T> &origen);
    void recorrePreorden();
    void recorreInorden();
    void recorrePostorden();
    bool inserta(T& dato);


};

template<class T>
AVL<T>::AVL():raiz(nullptr){}

template <class T>
void AVL<T>::copiar(Nodo<T> *p) {
    if (p != nullptr) {
        inserta(p->dato); // Inserta el dato en la raiz actual
        copiar(p->izq);   // Recorre e inserta la rama izquierda
        copiar(p->der);   // Recorre e inserta la rama derecha
    }
}

template <class T>
AVL<T>::AVL(const AVL<T> &origen) : raiz(nullptr), _numelementos(0) {
    copiar(origen.raiz); // Se iniicia la copia desde la raíz del árbol origen
}

template<class T>
void AVL<T>::preorden(Nodo<T> *p, int nivel) {
    if (p){
        std::cout << "Procesando nodo "<< p->dato ;
        std::cout << "en el nivel " << nivel << std::endl;
        preorden (p->izq, nivel+1);
        preorden (p->der, nivel+1);
    }
}

template<class T>
void AVL<T>::inorden(Nodo<T> *p, int nivel) {
    if (p){
        inorden (p->izq, nivel+1);
        std::cout << "Procesando nodo " << p->dato;
        std::cout << "en el nivel " << nivel << std::endl;
        inorden (p->der, nivel+1);
    }
}

template<class T>
void AVL<T>::postorden(Nodo<T> *p, int nivel) {
    if (p){
        postorden (p->izq, nivel+1);
        postorden (p->der, nivel+1);
        // Sustituir por procesamiento ----
        std::cout << "Procesando nodo "<< p->dato;
        std::cout << "en el nivel " << nivel << std::endl;
    }
}

template<class T>
void AVL<T>::recorrePreorden() {
    preorden(raiz,0);
}

template<class T>
void AVL<T>::recorreInorden() {
    inorden(raiz,0);
}

template<class T>
void AVL<T>::recorrePostorden() {
    postorden(raiz,0);
}

template<class T>
void AVL<T>::rotDer(Nodo<T>* &nodo) {
    Nodo<T> *q = nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}

template<class T>
void AVL<T>::rotIzq(Nodo<T>* &nodo) {
    Nodo<T> *q = nodo, *r;
    nodo = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}

template<typename T>
int AVL<T>::inserta(Nodo<T>* &c, T &dato) {
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p){
        p = new Nodo<T>(dato);
        c = p; deltaH=1;
    }
    else if (dato > p->dato){
        if (inserta(p->der, dato)){
            p->bal--;
            if (p->bal == -1) deltaH=1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der);
                rotIzq(c);
            } } }
    else if (dato < p->dato){
        if (inserta(p->izq, dato)){
            p->bal++;
            if (p->bal==1) deltaH = 1;
            else if (p->bal == 2){
                if (p->izq->bal == -1) rotIzq(p->izq);
                rotDer(c);
            } } }
    return deltaH;
}

template<class T>
bool AVL<T>::inserta(T &dato) {
    int insertado = inserta(raiz, dato);
    if (insertado != 0) {
        return true;
    }
    return false;
}





#endif //PRACTICA1_AVL_H