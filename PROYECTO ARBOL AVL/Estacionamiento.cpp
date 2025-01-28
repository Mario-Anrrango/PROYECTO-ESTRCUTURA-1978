#include "Estacionamiento.h"

Estacionamiento::Estacionamiento() {
    for (int i = 0; i < TAMANIO; ++i) {
        espacios.push_back(0);  
    }
}

void Estacionamiento::ocuparEspacio(int espacio, Coche& coche) {
    if (espacio >= 0 && espacio < TAMANIO && espacios[espacio] == 0) {
        espacios[espacio] = 1;  
    } else {
        std::cout << "Espacio no disponible o inválido." << std::endl;
    }
}

void Estacionamiento::liberarEspacio(int espacio) {
    if (espacio >= 0 && espacio < TAMANIO && espacios[espacio] == 1) {
        espacios[espacio] = 0;  
    } else {
        std::cout << "Espacio no ocupado o inválido." << std::endl;
    }
}

void Estacionamiento::mostrarEstacionamiento() {
    for (int i = 0; i < TAMANIO; ++i) {
        std::cout << (espacios[i] == 0 ? "[ ] " : "[X] ");  

        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;  
        }
    }
    std::cout << std::endl;
}

int Estacionamiento::obtenerEspacioAleatorio() {
    int espacio = rand() % TAMANIO;
    while (espacios[espacio] == 1) {  
        espacio = rand() % TAMANIO;
    }
    return espacio;
}

int Estacionamiento::getNumeroEspacios() const {
    return TAMANIO; 
}
