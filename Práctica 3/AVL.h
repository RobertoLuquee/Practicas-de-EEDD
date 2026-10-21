//
// Created by Roberto Luque Peña on 21/10/2026.
//

#ifndef PRACTICA1_AVL_H
#define PRACTICA1_AVL_H

template <class T>
class Nodo {
public:
    Nodo<T> *izq;
    Nodo<T> *der;
    T dato;
    Nodo();
    Nodo(T& ele);
};

class AVL {

    Noodo<T> *raiz;
    
public:
    AVL();
    AVL<T>(const AVL<T> &origen);

};





#endif //PRACTICA1_AVL_H