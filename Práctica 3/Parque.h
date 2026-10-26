//
// Created by Roberto Luque Peña on 13/10/2026.
//

#ifndef PRACTICA1_PARQUE_H
#define PRACTICA1_PARQUE_H
#include <iostream>
#include "VDinamico.h"
#include "Especie.h"
#include "Arbol.h"

/**
 * @brief Clase que representa un parque y gestiona la colección de especies que lo habitan.
 */
class Parque {
private:
    std::string nombre;
    int _cod_parque;
    std::string _nbre_parque;
    VDinamico<Arbol*> _contains;



public:

    /**
      * @brief Constructor por defecto. Inicializa un parque vacío.
      */
    Parque();
    /**
     * @brief Constructor parametrizado.
     * @param cod Código identificador del parque.
     * @param nombre Nombre del parque.
     */
    Parque(int cod, const std::string &nombre);
    /**
     * @brief Destructor de la clase Parque.
     */
    ~Parque();
    /**
     * @brief Obtiene el código del parque.
     * @return Código identificador del parque.
     */
    int get_cod_parque() const;
    /**
     * @brief Establece un nuevo código para el parque.
     * @param cod Nuevo código identificador.
     */
    void set_cod_parque(int cod);
    /**
     * @brief Obtiene el nombre del parque.
     * @return String con el nombre del parque.
     */
    std::string get_nbre_parque() const;
    /**
     * @brief Establece un nuevo nombre para el parque.
     * @param nombre Nuevo nombre del parque.
     */
    void set_nbre_parque(const std::string &nombre);
    /**
     * @brief Obtiene el vector dinámico que contiene las especies del parque.
     * @return Referencia al vector de punteros a Especie.
     */
    VDinamico<Arbol*>& get_contains();
    /**
     * @brief Añade una nueva especie al parque.
     * @param especie Puntero a la especie que se desea insertar en el vector del parque.
     */
    void insertaEspecie(Especie *especie);
    /**
     * @brief Comprueba si una especie habita en el parque buscando por su nombre común.
     * @param nombrecomun Nombre común de la especie a buscar.
     * @return true si la especie está en el parque, false en caso contrario.
     */
    bool existeNbreCom(const std::string &nombrecomun) ;
    /**
     * @brief Comprueba si una especie habita en el parque buscando por su nombre científico.
     * @param nombrecientifico Nombre científico de la especie a buscar.
     * @return true si la especie está en el parque, false en caso contrario.
     */
    bool existeNbreCie(const std::string &nombrecientifico) ;

    bool existeNbreCom(std::string nbreCom);
    void insertarArbol(Arbol* a);
    Arbol* arbolMasAlto();
    int contarEspecies();
    int contarTipos();

};

#endif //PRACTICA1_PARQUE_H