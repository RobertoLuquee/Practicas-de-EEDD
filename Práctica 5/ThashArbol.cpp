//
// Created by Roberto Luque Peña on 23/11/2026.
//

#include "ThashArbol.h"
/**
 * Función de dispersión: devuelve la posición de la tabla que hay que mirar
 * para "clave" en el intento número "intento" (0, 1, 2, ...).
 * Se dejan las 3 funciones probadas; solo una está activa.
 */
unsigned long ThashArbol::hash(unsigned long clave, int intento) {

    unsigned long i = (unsigned long) intento;
    /*
    // Exploración cuadrática
    return (clave + i * i) % tam;
    */
    // Dispersión doble 1

    //SEGUN LO QUE HE COMPROBADO, ESTA ES LA MAS EFICIENTE
    //AUNQUE DA RESULTADOS PARECIDOS CON LA DISPERSION DOBLE

    unsigned long h1 = clave % tam;
    unsigned long h2 = 1 + (clave % (tam - 2));
    return (h1 + i * h2) % tam;


    // Dispersión doble 2
    /*
    unsigned long h1 = clave % tam;
    unsigned long h2 = 1 + ((clave / tam) % (tam - 1));
    return (h1 + i * h2) % tam;
    */
}

bool ThashArbol::esPrimo(unsigned int n) {
    if (n < 2) return false;
    for (unsigned int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;   // tiene un divisor,entonces,no es primo
    }
    return true;
}
unsigned int ThashArbol::siguientePrimo(unsigned int n) {
    while (!esPrimo(n)) {
        n++;
    }
    return n;
}

ThashArbol::ThashArbol(int maxElementos, float lambda)
    : numElem(0) // Inicializo los arbolesf a 0
{
    tam = siguientePrimo((unsigned int)(maxElementos / lambda)); //Aqui uso unsigned int para quitar
    //los decimales, ya que, un tamaño no puede tener decimales.
    //Ademas, aqui es donde se usa la formula de la teoria: t=n/lambda
    tabla.resize(tam);
}

//constructor copia
ThashArbol::ThashArbol(ThashArbol &thash)
      : tabla(thash.tabla),tam(thash.tam),numElem(thash.numElem) {
}

//el operador asignacion de nuestra clase thasharbol
ThashArbol& ThashArbol::operator=(ThashArbol &thash) {
    if (this != &thash) {
        tabla = thash.tabla;
        tam = thash.tam;
        numElem = thash.numElem;
    }
    return *this; //Aquí devuelvo el propio puntero
}
ThashArbol::~ThashArbol() {
}

bool ThashArbol::insertar(unsigned long clave, Arbol &tree) {
    int intento=0;
    long hueco=-1; //variable con la que guardare la posicion del primer disponible

    //lo que hago con esta funcion es no insertar en el primer hueco disponible
    //sino que me aseguro de que la clave no está mas adelante
    while (1) {
        unsigned long pos= hash(clave,intento);
        if (tabla[pos].estado==vacia) {
            if (hueco==-1)
                hueco=pos;
            tabla[hueco]=Entrada(clave,tree); //aqui uso el constructor que añadi antes
            //y ya se encarga de poner el estado=ocupado
            numElem++;
            return true;
        }
        if (tabla[pos].estado==disponible) {
            if (hueco==-1)
                hueco=pos; //aqui me guardo la posicion
        }else if (tabla[pos].clave==clave) { //repetida asi que devuelvo false
            return false;
        }
        intento++;

        //Creo que el ultimo if no es necesario pq se supone que la exploracion siempre encuentra sitio
        if (intento>=tam) { //no hay mas huecos
            if (hueco!=-1) {
                tabla[hueco]=Entrada(clave,tree);
                numElem++;
                return true;
            }
            return false;
        }

    }
}

Arbol* ThashArbol::buscar(unsigned long clave) {
    int intento=0;
    while (1) {
        unsigned long pos=hash(clave,intento);
        if (tabla[pos].estado==vacia) {
            return nullptr;
        }
        if (tabla[pos].estado==ocupada && tabla[pos].clave==clave) {
            return &tabla[pos].dato; //lo hemos encontrado
        }
        intento++;
        if (intento>=tam) { // si ya hemos recorrido toda la tabla
            return nullptr;
        }
    }
}
bool ThashArbol::borrar(unsigned long clave) {
    int intento=0;

    while (1) {
        unsigned long pos=hash(clave,intento);
        if (tabla[pos].estado==vacia) {
            return false;
        }
        if (tabla[pos].estado==ocupada && tabla[pos].clave==clave) {
            tabla[pos].estado=disponible;
            numElem--;
            return true;
        }
        intento++;
        if (intento>=tam) {
            return false;
        }
    }
}

//Creo que no hay forma mas eficiente de hacerlo
unsigned int ThashArbol::numElementos() const {
    return numElem;
}
