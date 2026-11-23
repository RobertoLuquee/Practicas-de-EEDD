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

//CONSTRUCTOR COPIA
ThashArbol::ThashArbol(ThashArbol &thash)
      : tabla(thash.tabla),tam(thash.tam),numElem(thash.numElem) {
}

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
