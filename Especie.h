//
// Created by Roberto Luque Peña on 24/09/2026.
//

#ifndef INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
#define INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
#include <string>

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

class Especie {
private:
    std::string codigoEspecie;
    std::string nombreComun;
    std::string nombreCientifico;
    TipoPlanta tipoPlanta;

public:
    Especie() = default;
    Especie(std::string codigo,std::string comun,std::string cientifico,TipoPlanta tipo);
    bool operator==(const Especie& e)const;
    bool operator<(const Especie& e)const;

    std::string getCodigo() const;

    std::string getnombre_comun() const;

    std::string getnombre_cientifico() const;

    void mostrarInfo() const;

    int get_tipo_planta() const;
};

inline std::string Especie::getnombre_comun() const {
    return nombreComun;
}


#endif //INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
