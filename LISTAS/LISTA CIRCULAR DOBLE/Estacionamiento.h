#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>  // Para el uso de rand()

class Estacionamiento {
private:
    std::vector<int> espacios;  
    const int TAMANIO = 100;     

public:
    Estacionamiento();
    void ocuparEspacio(int espacio);
    void liberarEspacio(int espacio);
    void mostrarEstacionamiento();
    int obtenerEspacioAleatorio(); 
};