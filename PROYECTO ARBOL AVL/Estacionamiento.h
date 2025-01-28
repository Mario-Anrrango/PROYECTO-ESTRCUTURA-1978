#pragma once

#include <vector>
#include <iostream>
#include "Coche.h"

class Estacionamiento {
private:
    std::vector<int> espacios;  
    const int TAMANIO = 100;    

public:
    Estacionamiento();  
    void ocuparEspacio(int espacio, Coche& coche);  
    void liberarEspacio(int espacio); 
    void mostrarEstacionamiento();  
    int obtenerEspacioAleatorio();  
    int getNumeroEspacios() const;  
};