#include <iostream>
#include "Menu.h"

int main() {
ListaCircularDoble<Propietario> listaPropietarios;
listaPropietarios.CargarPropietarios("propietarios.txt");
ListaCircularDoble<Coche> listaCochesHistorial;
    listaCochesHistorial.CargarArchivo("autos_historial.txt");
    Estacionamiento estacionamiento;
    Parqueadero parqueadero;
    ListaCircularDoble<Coche> listaCoches;
    listaCoches.CargarArchivo("autos.txt");

    menu(listaCoches, listaCochesHistorial, listaPropietarios, estacionamiento, parqueadero);

    return 0;
}