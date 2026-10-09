//
// Created by Roberto Luque Peña on 24/09/2026.
//

#ifndef INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
#define INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
#include <string>

class Especie {
private:
    std::string codigoEspecie;
    std::string nombreComun;
    std::string nombreCientifico;
    std::string tipoPlanta;

public:
    Especie() = default;
    Especie(std::string codigo,std::string comun,std::string cientifico,std::string tipo);
    bool operator==(const Especie& e)const;
    bool operator<(const Especie& e)const;

    std::string getCodigo() const;

    std::string getnombre_comun() const;

    std::string getnombre_cientifico() const;
};

inline std::string Especie::getnombre_comun() const {
    return nombreComun;
}


#endif //INC_B9580CB4EF714E6CA853FC0D5FAEC9CB
