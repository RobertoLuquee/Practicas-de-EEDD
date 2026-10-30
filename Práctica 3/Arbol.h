//
// Created by Oier Universidad on 26/10/2026.
//

#ifndef PRACTICA3_ARBOL_H
#define PRACTICA3_ARBOL_H

#include <string>
#include "Especie.h"

class Arbol {
private:
    std::string assetnum;
    int parque_id;
    int distrito_id;
    std::string barrio;
    std::string codEspecie;
    std::string nombreEspecie;
    double latitud;
    double longitud;
    float perimetro;
    float altura;

    Especie* especie;

public:
    // Constructores
    Arbol();
    Arbol(std::string id);
    Arbol(std::string id, std::string parque, std::string distrito, std::string barrio,
          double latitud, double longitud, float perimetro, float altura);
    Arbol(std::string id, int parc, int dist, std::string barr, std::string codEsp,
          std::string nomEsp, double lat, double lon, float perim, float alt);

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
};
#endif //PRACTICA3_ARBOL_H