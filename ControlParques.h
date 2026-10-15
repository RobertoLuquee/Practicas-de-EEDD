//
// Created by Oier Universidad on 13/10/2026.
//

#ifndef PRACTICA1_CONTROLPARQUES_H
#define PRACTICA1_CONTROLPARQUES_H
#include "ListaDEnlazada.h"
#include "VDinamico.h"
#include "Parque.h"

/**
 * @brief Clase que gestiona el sistema central de parques y las especies que habitan en ellos.
 */
class ControlParques {

private:

    VDinamico<Especie> v_especies;
    ListaDEnlazada<Parque> ld_parques;

public:

    //VDinamico<Especie>& get_varieties();
    //ListaDEnlazada<Parque>& get_parks();

    /**
     * @brief Constructor que inicializa el sistema cargando los datos desde ficheros.
     * @param rutaEspecies Ruta del fichero que contiene los datos de las especies.
     * @param rutaParques Ruta del fichero que contiene los datos de los parques.
     */
    ControlParques(const std::string &rutaEspecies, const std::string &rutaParques);
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

};

#endif //PRACTICA1_CONTROLPARQUES_H
