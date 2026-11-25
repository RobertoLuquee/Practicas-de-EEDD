//
// Created by Oier Universidad on 26/10/2026.
//

#ifndef PRACTICA3_ARBOL_H
#define PRACTICA3_ARBOL_H

#include <string>
#include "Especie.h"
#include "Parque.h"
#include "UTM.h"

class Parque;
class Especie;

class Arbol {
private:
    std::string assetnum;
    int parque_id;
    std::string distrito;
    int distrito_id;
    std::string barrio;
    int num_barrio;
    std::string codEspecie;
    std::string nombreEspecie;
    UTM coordenadas;
    float perimetro;
    float altura;

    Especie* especie;

public:
    // Constructores

    Arbol();
    Arbol(std::string id);
    Arbol(std::string id, std::string parque, std::string distrito,int distrito_id, std::string barrio,int num_barrio,
          UTM coordenadas, float perimetro, float altura);
    Arbol(std::string id, int parc,std::string distrito, int dist_id, std::string barr,int num_barrio, std::string codEsp,
          std::string nomEsp, UTM coord, float perim, float alt);

    // Getters y Setters
    std::string getAssetnum() const;
    void setAssetnum(const std::string& id);
    int getNumParque() const;
    float getAltura() const;
    Especie* getEspecie() const;
    void setEspecie(Especie* esp);
    std::string getNbreComun() const;
    std::string getNbreCientifico() const;
    std::string getTipo() const;

    // Getters (snake_case para compatibilidad previa)
    std::string get_assetnum() const;
    float get_altura() const;
    Especie* get_especie() const;
    std::string getCodEspecie() const;
    int getTipoEspecie() const;

    // Operadores de comparación
    bool operator<(const Arbol &otro) const;
    bool operator>(const Arbol &otro) const;
    bool operator==(const Arbol &otro) const;

    Parque* getParque();
    void setParque(Parque* p);
    Parque* isInto=nullptr;

    int getNumDistrito() const {
        return distrito_id; // Cambia 'num_distrito' por el nombre real de tu atributo
    }

    int getNumBarrio() const {
        return num_barrio;   // Cambia 'num_barrio' por el nombre real de tu atributo
    }

    std::string getNbreBarrio() const {
        return barrio;  // Cambia 'nbre_barrio' por el nombre real de tu atributo
    }
    std::string getnbredistrito() const {
        return distrito;
    }
    UTM getCoord() const {
        return coordenadas;
    }
};
#endif //PRACTICA3_ARBOL_H