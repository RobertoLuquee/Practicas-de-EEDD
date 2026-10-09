#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Especie.h"
#include "VDinamico.h"


/** @author Roberto Luque Peña rlp00041@red.ujaen.es
 * @author Oier Fernandez De Leceta Villalmanzo ofv00003@red.ujaen.es
 */

void ordenarBurbuja(VDinamico<Especie>& v) {

    unsigned int n=v.get__tlogico();
    for (unsigned int i=0;i<n-1;i++) {
        for (unsigned int j=0;j<n-i-1;j++) {
            if (v[j+1]<v[j]) {
                Especie aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
            }
        }
    }
}

VDinamico<Especie*>BuscarPorNombre(VDinamico<Especie>&catalogoarboles,const string& palabraquesebusca) {
    VDinamico<Especie*> resultado;
    for (unsigned int i=0;i<catalogoarboles.get__tlogico();i++) {
        std::string nombreArbolCientifico=catalogoarboles[i].getnombre_cientifico();
        std::string aux="";

        bool espacioEncontrado=false;
        for (int j=0;j<nombreArbolCientifico.length() && !espacioEncontrado;j++) {
            if (nombreArbolCientifico[j]==' ') {
                espacioEncontrado=true; //uso esta variable para salir del bucle
            }else
                aux+=nombreArbolCientifico[j]; //Como no he encontrado un espacio, almaceno los caracteres en este vector
        }

        if (aux==palabraquesebusca)
            resultado.insertar(&catalogoarboles[i]); //Si coincide, lo añado a mi vector creado de punteros

    }

    return resultado;
}


 VDinamico<Especie*> getEspNComun(VDinamico<Especie>& catalogoarboles) {
    //Buscar los "" y omitirlos y los q si tienen nombre metyerlos en un vector
    VDinamico<Especie*> aux;


    for (int i=0;i<catalogoarboles.get__tlogico();i++) {
        if(catalogoarboles[i].getnombre_comun()!="") {
            aux.insertar(&catalogoarboles[i]);
        }
    }
    return aux;
}






int main(int argc, const char * argv[]) {
try {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;
    char delimitador = ',';

    std::string _codigoEspecie = "";
    std::string _nombreComun = "";
    std::string _nombreCientifico = "";
    std::string _tipoPlanta = "";





    VDinamico<Especie> catalogoarboles;

    is.open("../arbolado-especies.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();
        getline(is, fila ); //salto la cabecera

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //Código - Nombre común - Nombre científico - Tipo de planta

                getline(columnas, _codigoEspecie, delimitador);
                getline(columnas, _nombreComun, delimitador);
                getline(columnas, _nombreCientifico, delimitador);
                getline(columnas, _tipoPlanta, delimitador);

                fila="";
                columnas.clear();

                Especie nuevoregistro(_codigoEspecie,_nombreComun,_nombreCientifico,_tipoPlanta);
                catalogoarboles.insertar(nuevoregistro);

                /*std::cout << ++contador
                          << " Codigo Especie= " << _codigoEspecie
                          << " Nombre comun= " << _nombreComun << " Nombre Cientifico= " << _nombreCientifico
                          << " Tipo planta= " << _tipoPlanta << std::endl;*/
            }
        }

        is.close();

        std::cout<< "Primeros 50 registros de especie: "<<std::endl;
        for (int i=0;i<50;i++) {
            std::cout <<i+1<<"- "<<catalogoarboles[i].getCodigo()<<std::endl;
        }
        std::cout << std::endl;
        catalogoarboles.ordenar();
        std::cout<< "Primeros 50 registros ORDENADOS: "<<std::endl;
        for (int i=0;i<50;i++) {
            std::cout <<i+1<<"- "<<catalogoarboles[i].getCodigo()<<std::endl;
        }
        std::cout << std::endl;

        std::string encontrarCodigos[]={"CTA","DMD","HCN","NDOF","JAX"};
        for (int i=0;i<5;i++) {
            Especie especiesEncontrar(encontrarCodigos[i],"","","");

            int posicion = catalogoarboles.busquedaBinaria(especiesEncontrar);

            if (posicion!=-1) {
                std::cout<< "Encontrada la especie de codigo: " <<encontrarCodigos[i]<<" en la posicion: "<<posicion<<std::endl;
            }
            else {
                std::cout << "No se ha encontrado ninguna especie de codigo: "<<encontrarCodigos[i]<<std::endl;
            }
        }
        std::cout << std::endl;

        VDinamico<Especie*> arbolesconnombre=getEspNComun(catalogoarboles);
        std::cout <<"Tamanio logico del vector de Arboles que si contienen nombre comun: "<<arbolesconnombre.get__tlogico()<<std::endl;
        std::cout << std::endl;
        for (int i=0;i<50;i++) {
            std::cout <<i+1<<"- "<< arbolesconnombre[i]->getnombre_comun()<<std::endl;
        }

        std::cout << std::endl;

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    ordenarBurbuja(catalogoarboles);

    int total=catalogoarboles.get__tlogico();
    for (int i=total-1;i<total-50;i--) {
        std::cout<<i+1<<"- "<<catalogoarboles[i].getCodigo()<<std::endl;
    }

    std::cout << std::endl;

    VDinamico<Especie*> nombrePalabra= BuscarPorNombre(catalogoarboles,"Koelreuteria");
    std::cout << "Numero de especies encontradas: " << nombrePalabra.get__tlogico()<<std::endl;

}catch (const std::exception& e) {
    std::cerr << "Excepcion capturada: " << e.what() << std::endl;
    //Lo hago para capturar cualquier excecion de las declaradas en la clase VDinamico
}


    return 0;
}