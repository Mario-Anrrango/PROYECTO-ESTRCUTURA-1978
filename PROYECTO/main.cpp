#include <iostream>
#include "Coche.h"
#include "Lista.h"

int main() {


    
    ListaCircularDoble<Coche> listaCoches;
    std::string nombreArchivo = "autos.txt";

    listaCoches.CargarArchivo("autos.txt");
    Coche coche;

    coche.menu(listaCoches); 

    return 0;
}