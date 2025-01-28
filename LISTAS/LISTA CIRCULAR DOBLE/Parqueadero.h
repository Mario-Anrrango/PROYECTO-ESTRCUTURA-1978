#pragma once

#include "Estacionamiento.h"
#include "ArbolAVL.h"
#include "Coche.h"  

class Parqueadero {
private:
    Estacionamiento estacionamiento;  
    ArbolAVL arbolCoches;  
    const int TAMANIO = 100;  

public:
    Parqueadero();
    void agregarCoche(Coche coche);
    void quitarCoche(int espacio);
    void mostrarEstadoParqueadero();
    void mostrarCoches();
    void guardarEstadoParqueadero(const std::string& nombreArchivo);
    void cargarYAsignarParqueadero(ListaCircularDoble<Coche>& listaCoches);

};