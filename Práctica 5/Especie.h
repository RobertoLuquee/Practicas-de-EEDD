//
// Created by Roberto Luque Peña on 24/09/2026.
//

#ifndef INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
#define INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
#include <string>

/**
 * @brief Enumeración que define las distintas categorías o tipos de plantas disponibles.
 */
enum TipoPlanta {
    ARBUSTO,
    CONIFERA,
    PALMACEA,
    HERB_PERENNES,
    FRONDOSA,
    TAPIZANTE_TREPADORA,
    CACTACEA_SUCULENTA,
    SUBTROPICAL_TROPICAL,
    HERB_ANUAL,
    HERB_ANUALES
};
/**
 * @brief Clase que representa una especie.
 */
class Especie {
private:
    std::string codigoEspecie;
    std::string nombreComun;
    std::string nombreCientifico;
    TipoPlanta tipoPlanta;

public:
    /**
     * @brief Constructor por defecto. Crea una especie vacía.
     */
    Especie() = default;
    /**
     * @brief Constructor parametrizado.
     * @param codigo Código identificador de la especie.
     * @param comun Nombre común de la especie.
     * @param cientifico Nombre científico de la especie.
     * @param tipo Tipo de planta según la enumeración TipoPlanta.
     */
    Especie(std::string codigo,std::string comun,std::string cientifico,TipoPlanta tipo);
    /**
    * @brief Sobrecarga del operador de igualdad.
    * @param e Especie a comparar con la actual.
    * @return true si ambas especies son iguales, false en caso contrario.
    */
    bool operator==(const Especie& e)const;
    /**
     * @brief Sobrecarga del operador menor que (útil para ordenaciones).
     * @param e Especie a comparar con la actual.
     * @return true si esta especie es menor que la pasada por parámetro.
     */
    bool operator<(const Especie& e)const;
    /**
     * @brief Obtiene el código de la especie.
     * @return String con el código.
     */
    std::string getCodigo() const;
    /**
     * @brief Obtiene el nombre común de la especie.
     * @return String con el nombre común.
     */
    std::string getnombre_comun() const;
    /**
     * @brief Obtiene el nombre científico de la especie.
     * @return String con el nombre científico.
     */
    std::string getnombre_cientifico() const;
    /**
     * @brief Muestra la información de la especie por consola.
     */
    void mostrarInfo() const;
    /**
     * @brief Obtiene el tipo de planta como valor entero.
     * @return Entero asociado al valor de la enumeración TipoPlanta.
     */
    int get_tipo_planta() const;
};




#endif //INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
