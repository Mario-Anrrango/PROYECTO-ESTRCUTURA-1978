#include <iostream>
#include "Coche.h"
#include "Lista.h"

int main() {


    
    ListaCircularDoble<Coche> listaCoches;
    Coche coche;

    coche.menu(listaCoches); 

    return 0;
}