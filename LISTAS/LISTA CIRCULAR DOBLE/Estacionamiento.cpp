#include "Estacionamiento.h"
#include <cstdlib>  
#include <ctime>    


Estacionamiento::Estacionamiento() {
   
    espacios.resize(TAMANIO, 0);  
}


void Estacionamiento::ocuparEspacio(int espacio) {
    if (espacio >= 1 && espacio <= TAMANIO) {
        if (espacios[espacio - 1] == 0) {
            espacios[espacio - 1] = 1;  
            std::cout << "Espacio " << espacio << " ocupado." << std::endl;
        } else {
            std::cout << "El espacio " << espacio << " ya está ocupado." << std::endl;
        }
    } else {
        std::cout << "Número de espacio no válido." << std::endl;
    }
}


void Estacionamiento::liberarEspacio(int espacio) {
    if (espacio >= 1 && espacio <= TAMANIO) {
        if (espacios[espacio - 1] == 1) {
            espacios[espacio - 1] = 0;  
            std::cout << "Espacio " << espacio << " liberado." << std::endl;
        } else {
            std::cout << "El espacio " << espacio << " ya está libre." << std::endl;
        }
    } else {
        std::cout << "Número de espacio no válido." << std::endl;
    }
}


void Estacionamiento::mostrarEstacionamiento() {
    for (int i = 0; i < TAMANIO; i++) {
        if (espacios[i] == 0) {
            std::cout << "[ ] ";  
        } else {
            std::cout << "[X] ";  
        }
    }
    std::cout << std::endl;
}


int Estacionamiento::obtenerEspacioAleatorio() {
    srand(time(0)); 
    int espacioAleatorio = rand() % TAMANIO;  
    
    
    while (espacios[espacioAleatorio] == 1) {
        espacioAleatorio = rand() % TAMANIO;  
    }

    return espacioAleatorio + 1;  
}