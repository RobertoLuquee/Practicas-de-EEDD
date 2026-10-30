//
// Created by Oier Universidad on 13/10/2026.
//

#ifndef PRACTICA1_CONTROLPARQUES_H
#define PRACTICA1_CONTROLPARQUES_H

#include <string>
#include "ListaDEnlazada.h"
#include "VDinamico.h"
#include "Parque.h"
#include "Especie.h"
#include "Arbol.h"
#include "AVL.h"

/**
 * @brief Clase que gestiona el sistema central de parques y las especies que habitan en ellos.
 */
class ControlParques {
private:
    VDinamico<Especie> v_especies;
    ListaDEnlazada<Parque> ld_parques;
    AVL<Arbol> avl_arboles;

public:
    /**
     * @brief Constructor por defecto.
     */
    ControlParques();

    /**
     * @brief Constructor que inicializa el sistema cargando los datos desde 2 ficheros.
     * @param rutaEspecies Ruta del fichero que contiene los datos de las especies.
     * @param rutaParques Ruta del fichero que contiene los datos de los parques.
     */
    ControlParques(const std::string &rutaEspecies, const std::string &rutaParques);

    /**
     * @brief Constructor que inicializa el sistema cargando los datos desde 3 ficheros CSV.
     * @param rutaEspecies Ruta del fichero que contiene los datos de las especies.
     * @param rutaParques Ruta del fichero que contiene los datos de los parques.
     * @param rutaArboles Ruta del fichero que contiene los datos de los árboles.
     */
    ControlParques(const std::string &rutaEspecies, const std::string &rutaParques, const std::string &rutaArboles);

    /**
     * @brief Relaciona automáticamente las especies cargadas con sus respectivos parques basándose en los datos leídos.
     */
    void enlazarAutomatico();

    /**
     * @brief Elimina una especie del sistema a partir de su nombre común.
     * @param ncomun Nombre común de la especie a eliminar.
     * @return true si la especie fue encontrada y eliminada con éxito, false en caso contrario.
     */
    bool borrarEspecie(std::string ncomun);

    /**
     * @brief Muestra por consola el listado y la información de todos los parques.
     */
    void mostrarParques();

    /**
     * @brief Asigna de forma manual una especie a un parque determinado.
     * @param e Puntero a la especie que se quiere asignar.
     * @param p Puntero al parque de destino.
     */
    void asignarEspecieParque(Especie *e, Parque *p);

    /**
     * @brief Cuenta el número de apariciones o ejemplares de una especie específica en los parques.
     * @param ncomun Nombre común de la especie a contabilizar.
     * @return Número total contabilizado para esa especie.
     */
    int contarEspecieParque(std::string ncomun);

    /**
     * @brief Genera un listado de especies cuyo nombre contenga una subcadena de texto específica.
     * @param cadena Subcadena de texto a buscar dentro de los nombres de las especies.
     * @return Un vector dinámico que contiene punteros a las especies que coinciden con la búsqueda.
     */
    VDinamico<Especie*> listadoEspecieSubNombre(std::string cadena);

    /**
     * @brief Busca un parque específico por su nombre exacto.
     * @param nombre_parque Nombre del parque a buscar.
     * @return Puntero al parque si se encuentra, o nullptr si no existe.
     */
    Parque* buscarParque(std::string nombre_parque);

    /**
     * @brief Localiza un árbol en el árbol AVL a partir de su identificador assetnum.
     * @param assetnum Identificador único del ejemplar en formato string.
     * @return Puntero al objeto Arbol si se encuentra, nullptr en caso contrario.
     */
    Arbol* buscarArbol(const std::string &assetnum);

    /**
     * @brief Devuelve el listado completo de árboles de un parque dado su nombre.
     * @param nombreParque Nombre del parque a consultar.
     * @return Vector dinámico con los punteros a los árboles del parque.
     */
    VDinamico<Arbol*> listaArbParque(const std::string &nombreParque);

    /**
     * @brief Devuelve el árbol de mayor altura de entre todos los parques.
     * @return Puntero al árbol más alto. Si hay empate, devuelve el primero encontrado.
     */
    Arbol* arbolMasAlto();

    /**
     * @brief Devuelve el número de especies distintas de un parque dado su nombre.
     * @param nombreParque Nombre del parque a consultar.
     * @return Número de especies distintas presentes en el parque.
     */
    int contarEspecies(const std::string &nombreParque);

    /**
     * @brief Devuelve el número de tipos de planta distintos presentes en todo el sistema.
     * @return Cantidad de tipos de planta únicos acumulados entre todos los parques.
     */
    int contarTipos();

    /**
     * @brief Busca árboles cuyo identificador assetnum se encuentre en un rango determinado.
     * @param inicio Identificador inicial del rango.
     * @param fin Identificador final del rango.
     * @return Vector dinámico con los árboles encontrados dentro del rango.
     */
    VDinamico<Arbol*> buscarArbolesRango(const std::string& asNumMin, const std::string& asNumMax);
};

#endif // PRACTICA1_CONTROLPARQUES_H