//
// Created by Roberto Luque Peña on 23/11/2026.
//

#include <iostream>
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
    : numElem(0), maxCol(0), contMax10(0), totalCol(0),
      lambdaMax(lambda), numRedispersiones(0)
{
    tam = siguientePrimo((unsigned int)(maxElementos / lambda));
    tabla.resize(tam); //Nuestro vector emmpieza con 0 elementos, pero con el resize tiene tam casillas
                        //sí que es verdad que estan todas vacías, pero ya podemos acceder con tabla[pos]
}

ThashArbol::ThashArbol(ThashArbol &thash)
    : tabla(thash.tabla), tam(thash.tam), numElem(thash.numElem),
      maxCol(thash.maxCol), contMax10(thash.contMax10), totalCol(thash.totalCol),
      lambdaMax(thash.lambdaMax), numRedispersiones(thash.numRedispersiones)
{
}

ThashArbol& ThashArbol::operator=(ThashArbol &thash) {
    if (this != &thash) {
        tabla = thash.tabla;
        tam = thash.tam;
        numElem = thash.numElem;
        maxCol = thash.maxCol;
        contMax10 = thash.contMax10;
        totalCol = thash.totalCol;
        lambdaMax = thash.lambdaMax;
        numRedispersiones = thash.numRedispersiones;
    }
    return *this;
}
ThashArbol::~ThashArbol() {
}

bool ThashArbol::insertar(unsigned long clave, Arbol &tree) {
    if (static_cast<float>(numElem + 1) / static_cast<float>(tam) > lambdaMax) {
        redispersar(static_cast<unsigned int>(tam * 1.3f));
    }
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
            //Tengo que añadir esto porque si no no se actualizan los nuevos contadores
            totalCol+=intento;
            if (intento>maxCol)
                maxCol=intento;
            if (intento>10)
                contMax10++;
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
                totalCol+=intento;
                if (intento>maxCol)
                    maxCol=intento;
                if (intento>10)
                    contMax10++;
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

unsigned int ThashArbol::maxColisiones() {
    return maxCol;
}

unsigned int ThashArbol::numMax10() {
    return contMax10;
}

float ThashArbol::promedioColisiones() {
    if (numElem==0)
        return 0;
    return (float)totalCol/numElem;
}

float ThashArbol::factorCarga() {
    return (float)numElem/tam;
}

unsigned ThashArbol::tamTabla() {
    return tam;
}

void ThashArbol::mostrarEstadoTabla() {
    float factorcarga=factorCarga();
    int superar10=numMax10();
    float promedio=promedioColisiones();
    int maximoCol=maxColisiones();
    std::cout<<"Tamanio: "<<tam<<std::endl;
    std::cout<<"Factor de carga: "<<factorcarga<<std::endl;
    std::cout<<"Veces que se superan las 10 colisiones: "<<superar10<<std::endl;
    std::cout<<"Maximo de colisiones: "<<maximoCol<<std::endl;
    std::cout<<"Promedio: "<<promedio<<std::endl;
    std::cout << "Numero de redispersiones: " << numRedispersiones << std::endl;
}
void ThashArbol::redispersar(unsigned nuevoTamDeseado) {
    unsigned int nuevoTam = siguientePrimo(nuevoTamDeseado);
    std::vector<Entrada> tablaAntigua = tabla;

    this->tam = nuevoTam; // Es importante, hash() usa el atributo miembro tam
    tabla.clear(); // me ayuda para dejar el vector con 0 elementos
    tabla.resize(nuevoTam); // crea nuevoTam casillas vacias
    numElem = 0;
    totalCol = 0;
    maxCol = 0;
    contMax10 = 0;

    for (unsigned int i = 0; i < tablaAntigua.size(); ++i) {
        if (tablaAntigua[i].estado == ocupada) {
            unsigned long clave = tablaAntigua[i].clave;
            Arbol &dato = tablaAntigua[i].dato;

            int intento = 0;
            while (intento < (int)nuevoTam) {
                unsigned long pos = hash(clave, intento);
                if (tabla[pos].estado != ocupada) {
                    tabla[pos] = Entrada(clave, dato);
                    numElem++;
                    totalCol += intento;
                    if ((unsigned int)intento > maxCol)
                        maxCol = intento;
                    if (intento > 10)
                        contMax10++;
                    break;
                }
                intento++;
            }
        }
    }
    numRedispersiones++;
}

    unsigned int ThashArbol::getNumRedispersiones()const{
    return numRedispersiones;
}
