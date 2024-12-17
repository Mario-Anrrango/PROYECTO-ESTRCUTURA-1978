#include <iostream>
#include "Menu.h"

int main()
{

ListaCircularDoble<Coche> listaCochesHistorial;
    listaCochesHistorial.CargarArchivo("autos_historial.txt");

    ListaCircularDoble<Coche> listaCoches;
    listaCoches.CargarArchivo("autos.txt");

    menu(listaCoches, listaCochesHistorial);

    return 0;
}