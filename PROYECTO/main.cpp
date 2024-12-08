#include <iostream>
#include "Coche.h"
#include "Lista.h"

int main() {
    ListaCircularDoble<Coche> listaCoches;
    Coche coche;

    coche.menu(listaCoches); // Llama al menú del coche

    return 0;
}