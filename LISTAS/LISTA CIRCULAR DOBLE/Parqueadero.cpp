#include "Parqueadero.h"


Parqueadero::Parqueadero() {
}


void Parqueadero::agregarCoche(Coche coche) {
    int espacioLibre = estacionamiento.obtenerEspacioAleatorio();  

    
    arbolCoches.agregarDistancia(espacioLibre);

  
    estacionamiento.ocuparEspacio(espacioLibre);

    std::cout << "Coche con placa " << coche.getPlaca() << " estacionado en el espacio " << espacioLibre << "." << std::endl;
}


void Parqueadero::quitarCoche(int espacio) {
    
    if (estacionamiento.obtenerEspacioAleatorio() == espacio) {
      
        arbolCoches.agregarDistancia(espacio);

       
        estacionamiento.liberarEspacio(espacio);

        std::cout << "Coche en el espacio " << espacio << " ha sido retirado." << std::endl;
    } else {
        std::cout << "El espacio no está ocupado por un coche." << std::endl;
    }
}


void Parqueadero::mostrarEstadoParqueadero() {
    std::cout << "Estado del Parqueadero:" << std::endl;
    estacionamiento.mostrarEstacionamiento();  
}


void Parqueadero::mostrarCoches() {
    std::cout << "Coches estacionados:" << std::endl;
    arbolCoches.mostrarDistancias();  
}