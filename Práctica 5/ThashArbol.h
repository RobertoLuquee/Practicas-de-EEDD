//
// Created by Roberto Luque Peña on 23/11/2026.
//

#ifndef PRACTICA5_THASHARBOL_H
#define PRACTICA5_THASHARBOL_H

#include "Arbol.h"
#include <vector>
enum EstadoCasilla { vacia,disponible,ocupada };

class Entrada {
public:
    unsigned long clave;
    Arbol dato;
    EstadoCasilla estado;
    Entrada(): clave(0),dato(),estado(vacia){} //Crea una casilla vacia
    Entrada(unsigned long aClave, const Arbol &aDato)
        : clave(aClave), dato(aDato), estado(ocupada) {} // Crea una casilla con esos datos, lo utilizo luego en insertar
};


class ThashArbol {
private:
    std::vector<Entrada>tabla;
    unsigned int tam; //lo pongo pq se usa en la fórmula, aunque no me lo pide la practica en si
    unsigned int numElem;
    unsigned int maxCol;
    unsigned int contMax10;
    unsigned long totalCol;
    unsigned long hash(unsigned long clave, int intento);
    bool esPrimo(unsigned int n);
    unsigned int siguientePrimo(unsigned int n);
    float lambdaMax;
    unsigned int numRedispersiones;

public:

    ThashArbol()=default;
    ThashArbol(int maxElementos, float lambda=0.65 );
    ThashArbol(ThashArbol &thash);
    ThashArbol& operator=(ThashArbol &thash);
    ~ThashArbol();
    bool insertar(unsigned long clave, Arbol &tree);
    Arbol* buscar(unsigned long clave);
    bool borrar(unsigned long clave);
    unsigned int numElementos() const;
    //Estos son los que se piden en la primera prueba
    unsigned int maxColisiones();
    unsigned int numMax10();
    float promedioColisiones();
    float factorCarga();
    unsigned tamTabla();
    void mostrarEstadoTabla();
    void redispersar(unsigned tam);
    unsigned int getNumRedispersiones() const;
};


#endif //PRACTICA5_THASHARBOL_H